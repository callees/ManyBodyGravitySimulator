#include "NBodySimulation.h"
#include "RK4Function.h"
#include <algorithm>
#include <functional>
#include <cmath>
//#include <random>

NBodySimulation::NBodySimulation()
{
	G_ = 6.6743e-11;
	unsigned int dayInSeconds = 86400;
	timeStep_ = dayInSeconds / 100;
}

NBodySimulation::NBodySimulation(std::vector<Body<TwoVector>> bodiesToSimulate)
{
	unsigned int dayInSeconds = 86400;
	timeStep_ = dayInSeconds / 100;
	gravitationalODEfunc_ = std::bind(&NBodySimulation::gravitationalODE, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	for(auto body : bodiesToSimulate)
	{
		simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, body, timeStep_));
	}
	calculateFactorsOnSimulatedBodies();
}

void NBodySimulation::setUpTestSimulation()
{
	createEarthSystem(TwoVector(0, 0));
	calculateFactorsOnSimulatedBodies();
}

void NBodySimulation::createSolarSystem()
{
	//Sun
	TwoVector positionOfSun = TwoVector(0, 0);
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(TwoVector(0, 0), TwoVector(0, 0), 1.989e+30), timeStep_));
	//Mercury
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(TwoVector(6.9615e+10, 0), TwoVector(0, -47362.5), 3.285e+23), timeStep_));
	//Venus
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(TwoVector(-1.0769e+11, 0), TwoVector(0, 35000), 4.867e+24), timeStep_));
	createEarthSystem(positionOfSun);
	//Mars
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(TwoVector(0, -2.4554e+11), TwoVector(-24100, 0), 6.39e+23), timeStep_));
	//Saturn
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(TwoVector(0, -1400000000000), TwoVector(9.69e+3, 0), 5.685e+26), timeStep_));
	//Uranus
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(TwoVector(2900000000000, 0), TwoVector(0, -6.8e+3), 8.682e+25), timeStep_));
	//Neptune
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(TwoVector(-4500000000000, 0), TwoVector(0, 5.4e+3), 1.024e+26), timeStep_));
	createJovianSystem(positionOfSun);
	createPlutoSystem(positionOfSun);
}

void NBodySimulation::createEarthSystem(TwoVector positionOfSun)
{
	TwoVector positionOfEarth = positionOfSun + TwoVector(0, 1.4724e+11);
	TwoVector velocityOfEarth = TwoVector(29951.68, 0);
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfEarth, velocityOfEarth, 5.972e+24), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfEarth + TwoVector(0, 384400e+3), velocityOfEarth + TwoVector(-1.022e+3, 0), 7.34767309e+22), timeStep_));
}

void NBodySimulation::createJovianSystem(TwoVector positionOfSun)
{
	TwoVector positionOfJupiter = positionOfSun + TwoVector(0, 779000000000);
	TwoVector velocityOfJupiter = TwoVector(-13.1e+3, 0);
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfJupiter, velocityOfJupiter, 1.899e+27), timeStep_));
	//Io
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfJupiter + TwoVector(0, 421800e+3), velocityOfJupiter + TwoVector(17.334e+3, 0), 893.2e+20), timeStep_));
	//Europa
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfJupiter + TwoVector(0, -671100e+3), velocityOfJupiter + TwoVector(-13.74e+3, 0), 480.0e+20), timeStep_));
	//Ganymede
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfJupiter + TwoVector(1070400e+3, 0), velocityOfJupiter + TwoVector(0, -10.88e+3), 1481.9e+20), timeStep_));
	//Callisto
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfJupiter + TwoVector(-1882700e+3, 0), velocityOfJupiter + TwoVector(0, 8.2e+3), 1075.9e+20), timeStep_));
}

void NBodySimulation::createPlutoSystem(TwoVector positionOfSun)
{
	TwoVector positionOfPluto = TwoVector(5906380000e+3, 0) + positionOfSun;
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfPluto, TwoVector(-0.21 * 0.5e+3, 0), 1.30900e+22), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc_, Body<TwoVector>(positionOfPluto + TwoVector(0, 19640e+3), TwoVector(0.21 * 0.5e+3, 0), 1.5897e+21), timeStep_));
}

void NBodySimulation::calculateFactorsOnSimulatedBodies()
{
	for (std::vector<SimulatedBody>::iterator currentBody = simulatedBodies_.begin(); currentBody != simulatedBodies_.end(); currentBody++)
	{
		currentBody->changeInteractionValues(calculateInteractionFactorAtCurrentBody(*currentBody), calculateInteractionFromAllOtherBody(*currentBody));
	};
}


void NBodySimulation::simulateOneTimeStep()
{
	for (std::vector<SimulatedBody>::iterator currentBody = simulatedBodies_.begin(); currentBody != simulatedBodies_.end(); currentBody++)
	{
		currentBody->calculateNewPosition();
	}
	updateAllPositions();
	updateBodyHistory();
	calculateFactorsOnSimulatedBodies();
}

void NBodySimulation::simulate(unsigned int epoch)
{
	for (unsigned int currentEpoch = 0; currentEpoch < epoch; currentEpoch++)
	{
		simulateOneTimeStep();
	}
	systemHistory_.save();
}

BodiesHistories NBodySimulation::getBodyHistory()
{
	return systemHistory_;
}

BodiesHistories* NBodySimulation::bodyHistory()
{
	return &systemHistory_;
}

void NBodySimulation::updateAllPositions()
{
	std::for_each(simulatedBodies_.begin(), simulatedBodies_.end(), [this](SimulatedBody& simBody) {simBody.updatePosition(); });
}

void NBodySimulation::updateBodyHistory()
{
	std::vector<Body<TwoVector>> intermediateBodyVector;
	for (auto simulatedBody : simulatedBodies_) intermediateBodyVector.push_back(simulatedBody.body());
	systemHistory_.addHistory(intermediateBodyVector);
}

RK4FOODEs<TwoVector> NBodySimulation::gravitationalODE(RK4FOODEs<TwoVector> positionAndVelocity, double step, double interactionFactorAtCurrentBody, TwoVector interactionFromAllOtherBodies)
{
	return RK4FOODEs<TwoVector>(positionAndVelocity.dy(), interactionFactorAtCurrentBody * positionAndVelocity.y() - interactionFromAllOtherBodies);
}

TwoVector NBodySimulation::calculateInteractionFromAllOtherBody(const SimulatedBody& currentBody)
{
	TwoVector sumOfInteractionsAtOtherBodies(0, 0);
	for (std::vector<SimulatedBody>::iterator actingBody = simulatedBodies_.begin(); actingBody != simulatedBodies_.end(); actingBody++)
	{
		if (&(*actingBody) != &currentBody && withinAllowedInteractionLimit(currentBody, *actingBody))
		{
			sumOfInteractionsAtOtherBodies = sumOfInteractionsAtOtherBodies + (actingBody->body().position() * actingBody->body().mass()) / pow(distanceBetweenTwoVectors(currentBody.body().position(), actingBody->body().position()), 3);
		}
	}
	return -G_ * sumOfInteractionsAtOtherBodies;
}

double NBodySimulation::calculateInteractionFactorAtCurrentBody(const SimulatedBody& currentBody)
{
	double sumOfInteractionsAtCurrentBody = 0;
	for (std::vector<SimulatedBody>::iterator actingBody = simulatedBodies_.begin(); actingBody != simulatedBodies_.end(); actingBody++)
	{
		if (&(*actingBody) != &currentBody && withinAllowedInteractionLimit(currentBody, *actingBody))
		{
			sumOfInteractionsAtCurrentBody += actingBody->body().mass() / pow(distanceBetweenTwoVectors(currentBody.body().position(), actingBody->body().position()), 3);
		}
	}
	return -G_ * sumOfInteractionsAtCurrentBody;
}

double NBodySimulation::gravitationalFactor(const SimulatedBody& currentBody)
{
	double interactionFromNeighbouringBodies = 0;

	for (std::vector<SimulatedBody>::iterator actingBody = simulatedBodies_.begin(); actingBody != simulatedBodies_.end(); actingBody++)
	{
		if (&(*actingBody) != &currentBody && withinAllowedInteractionLimit(currentBody, *actingBody))
		{
			interactionFromNeighbouringBodies += actingBody->body().mass() / pow(distanceBetweenTwoVectors(currentBody.body().position(), actingBody->body().position()), 3);
		}
	}
	return G_ * interactionFromNeighbouringBodies;
}

bool NBodySimulation::withinAllowedInteractionLimit(const SimulatedBody& currentBody, const SimulatedBody& actingBody)
{
	return distanceBetweenTwoVectors(actingBody.body().position(), currentBody.body().position()) > interactionLimit_;
}
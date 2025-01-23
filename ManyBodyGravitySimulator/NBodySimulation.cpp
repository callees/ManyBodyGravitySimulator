#include "NBodySimulation.h"
#include "RK4Function.h"
#include <algorithm>
#include <functional>
#include <fstream>
#include <random>

NBodySimulation::NBodySimulation()
{

}
void NBodySimulation::setUpTestSimulation()
{
	G_ = 6.6743e-11;
	unsigned int dayInSeconds = 86400;
	timeStep_ = dayInSeconds / 1000;


	std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc = std::bind(&NBodySimulation::gravitationalODE, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	//createSimpleSystem(10, TwoVector(0, 0), TwoVector(1, 0), gravitationalODEfunc);
	createSolarSystem(gravitationalODEfunc);

	calculateFactorsOnSimulatedBodies();
}

void NBodySimulation::createSolarSystem(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc)
{
	double massOfSun = 1.989e+30;
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(1e+11, 0), TwoVector(0, 2.5e3), TwoVector(0, 0), 10*massOfSun), timeStep_));
	//Sun
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(0, 0), TwoVector(0, 0), TwoVector(0, 0), 1.989e+30), timeStep_));
	//Mercury
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(6.9615e+10, 0), TwoVector(0, -47362.5), TwoVector(0, 0), 3.285e+23), timeStep_));
	//Venus
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(-1.0769e+11, 0), TwoVector(0, 35000), TwoVector(0, 0), 4.867e+24), timeStep_));
	//Earth
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(0, 1.4724e+11), TwoVector(29951.68, 0), TwoVector(0, 0), 5.972e+24), timeStep_));
	//Mars
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(0, -2.4554e+11), TwoVector(-24100, 0), TwoVector(0, 0), 6.39e+23), timeStep_));
	//Saturn
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(0, -1400000000000), TwoVector(9.69e+3, 0), TwoVector(0, 0), 5.685e+26), timeStep_));
	//Uranus
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(2900000000000, 0), TwoVector(0, -6.8e+3), TwoVector(0, 0), 8.682e+25), timeStep_));
	//Neptune
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(-4500000000000, 0), TwoVector(0, 5.4e+3), TwoVector(0, 0), 1.024e+26), timeStep_));
	//Jupiter
	createJovianSystem(gravitationalODEfunc, TwoVector(0, 0));
	//Pluto
	createPlutoSystem(gravitationalODEfunc, TwoVector(0, 0));
}

void NBodySimulation::createJovianSystem(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc, TwoVector positionOfSun)
{
	TwoVector positionOfJupiter = positionOfSun + TwoVector(0, 779000000000);
	TwoVector velocityOfJupiter = TwoVector(-13.1e+3, 0);
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(positionOfJupiter, velocityOfJupiter, TwoVector(0, 0), 1.899e+27), timeStep_));
	//Io
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(positionOfJupiter + TwoVector(0, 421800e+3), velocityOfJupiter + TwoVector(17.334e+3, 0), TwoVector(0, 0), 893.2e+20), timeStep_));
	//Europa
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(positionOfJupiter + TwoVector(0, -671100e+3), velocityOfJupiter + TwoVector(-13.74e+3, 0), TwoVector(0, 0), 480.0e+20), timeStep_));
	//Ganymede
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(positionOfJupiter + TwoVector(1070400e+3, 0), velocityOfJupiter + TwoVector(0, -10.88e+3), TwoVector(0, 0), 1481.9e+20), timeStep_));
	//Callisto
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(positionOfJupiter + TwoVector(-1882700e+3, 0), velocityOfJupiter + TwoVector(0, 8.2e+3), TwoVector(0, 0), 1075.9e+20), timeStep_));
}

void NBodySimulation::createPlutoSystem(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc, TwoVector positionOfSun)
{
	TwoVector positionOfPluto = TwoVector(5906380000e+3, 0) + positionOfSun;
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(positionOfPluto, TwoVector(-0.21 * 0.5e+3, 0), TwoVector(0, 0), 1.30900e+22), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(positionOfPluto + TwoVector(0, 19640e+3), TwoVector(0.21 * 0.5e+3, 0), TwoVector(0, 0), 1.5897e+21), timeStep_));
}

void NBodySimulation::createSimpleSystem(double mass, TwoVector origin, TwoVector velocity, std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc)
{
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(origin, velocity, TwoVector(0, 0), mass), timeStep_));
}

void NBodySimulation::createRandomBody(double mass, odeFunc gravitationalODEfunc, double origin)
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<double> d{ origin, 5 };
	std::normal_distribution<double> d2{ 0, 1.2 };
	auto random = [&d, &gen] { return std::round(d(gen));};
	auto randomVelocity = [&d2, &gen] { return std::round(d2(gen));};
	double randomX = random();
	double randomY = random();
	double randomVX = randomVelocity();
	double randomVY = randomVelocity();
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(randomX, randomY), TwoVector(randomVX, randomVY), TwoVector(0, 0), mass), timeStep_));
}

void NBodySimulation::createSystemWithRandomPositionsAndSimilarMasses(odeFunc gravitationalODEfunc)
{
	for (unsigned int numberOfBodies = 0; numberOfBodies < 10; numberOfBodies++) createRandomBody(1.5, gravitationalODEfunc, 20);
	for (unsigned int numberOfBodies = 0; numberOfBodies < 10; numberOfBodies++) createRandomBody(1.5, gravitationalODEfunc, -10);
	for (unsigned int numberOfBodies = 0; numberOfBodies < 10; numberOfBodies++) createRandomBody(1.5, gravitationalODEfunc, 30);
	for (unsigned int numberOfBodies = 0; numberOfBodies < 10; numberOfBodies++) createRandomBody(1.5, gravitationalODEfunc, -60);
}

void NBodySimulation::calculateFactorsOnSimulatedBodies() //could be multithreaded in the future?
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

void NBodySimulation::trackBodyPositionHistory()
{
	if (!trackBodyPositionHistory_) {
		trackBodyPositionHistory_ = true;
		updateBodyPositionHistory();
	}
}

void NBodySimulation::trackBodyHistory()
{
	if (!trackBodyHistory_) {
		trackBodyHistory_ = true;
		updateBodyHistory();
	}
}

std::vector<std::vector<Body<TwoVector>>> NBodySimulation::getBodyHistory()
{
	return bodyHistory_;
}


void NBodySimulation::updateAllPositions()
{
	std::for_each(simulatedBodies_.begin(), simulatedBodies_.end(), [this](SimulatedBody& simBody) {simBody.updatePosition();});
}

void NBodySimulation::updateBodyHistory()
{
	if (trackBodyHistory_) {
		std::vector<Body<TwoVector>> intermediateBodyVector;
		for (auto simulatedBody : simulatedBodies_) intermediateBodyVector.push_back(simulatedBody.body());
		bodyHistory_.push_back(intermediateBodyVector);
	}
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
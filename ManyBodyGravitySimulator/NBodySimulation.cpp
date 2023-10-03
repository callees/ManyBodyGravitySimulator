#include "NBodySimulation.h"
#include "RK4Function.h"
#include <functional>
#include <fstream>

NBodySimulation::NBodySimulation()
{

}

void NBodySimulation::setUpTestSimulation()
{
	G_ = 1;
	timeStep_ = 0.01;


	std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc = std::bind(&NBodySimulation::gravitationalODE, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(-1, 0), TwoVector(0, 0), TwoVector(0, 0), 2), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(-0.55, 0), TwoVector(0, -1), TwoVector(0, 0), 2e-6), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(-0.35, 0.75), TwoVector(1, 0.2), TwoVector(0, 0), 1e-6), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(-0.2, -0.2), TwoVector(0.5, -0.7), TwoVector(0, 0), 1e-5), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(1, 0), TwoVector(0, 0), TwoVector(0, 0), 2), timeStep_));

	calculateFactorsOnSimulatedBodies();
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
	calculateFactorsOnSimulatedBodies();
}

#include <algorithm>

void NBodySimulation::updateAllPositions()
{
	std::for_each(simulatedBodies_.begin(), simulatedBodies_.end(), [this](SimulatedBody& simBody) {simBody.updatePosition();});
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
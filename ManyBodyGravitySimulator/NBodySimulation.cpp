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
	
	
	std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double)> gravitationalODEfunc = std::bind(&NBodySimulation::gravitationalODE, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(1, 0), TwoVector(0, 0), TwoVector(0, 0), 5), timeStep_));
	simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(-1, 0), TwoVector(0, 0), TwoVector(0, 0), 5), timeStep_));
	//simulatedBodies_.push_back(SimulatedBody(gravitationalODEfunc, Body<TwoVector>(TwoVector(0, 75), TwoVector(0, 0), TwoVector(0, 0), 5), timeStep_));

	calculateFactorsOnSimulatedBodies();
}

void NBodySimulation::calculateFactorsOnSimulatedBodies() //could be multithreaded in the future?
{
	for (std::vector<SimulatedBody>::iterator currentBody = simulatedBodies_.begin(); currentBody != simulatedBodies_.end(); currentBody++)
	{
		currentBody->changeFactor(gravitationalFactor(*currentBody));
	};
}

void NBodySimulation::testSimulate()
{
	for (std::vector<SimulatedBody>::iterator currentBody = simulatedBodies_.begin(); currentBody != simulatedBodies_.end(); currentBody++)
	{
		RK4FOODEs<TwoVector> currentStep = currentBody->rk4().calculateStep();
		currentBody->updatePosition(currentStep);
	}
	calculateFactorsOnSimulatedBodies();
	//std::ofstream myfile;
	//myfile.open("testgravity.csv");
	//for (unsigned int step = 0; step < 1000000; step++)
	//{
	//	RK4FOODEs<TwoVector> currentStep;
	//	if (distanceBetweenTwoVectors(bodies_[0].position(), bodies_[1].position()) > 10) {
	//		currentStep = rk4Methods_.calculateStep();
	//		rk4Method_.changeValue(currentStep);
	//		bodies_[1].setVelocity(currentStep.dy());
	//		bodies_[1].setPosition(currentStep.y());
	//		rk4Method_.changeFactor(gravitationalFactor(bodies_[1], bodies_[0]));
	//	}
	//	else {
	//		bodies_[1].setPosition(bodies_[1].position() + bodies_[1].velocity() * timeStep_);
	//		currentStep = RK4FOODEs<TwoVector>(bodies_[1].position(), bodies_[1].velocity());
	//		rk4Method_.changeValue(currentStep);
	//	}

	//	myfile << currentStep.y().x1() << "," << step << "\n";
	//}
	//myfile.close();
}

RK4FOODEs<TwoVector> NBodySimulation::gravitationalODE(RK4FOODEs<TwoVector> positionAndVelocity, double step, double factorFromActingBody)
{

	return RK4FOODEs<TwoVector>(positionAndVelocity.dy(), -factorFromActingBody * positionAndVelocity.y());
}

double NBodySimulation::gravitationalFactor(const SimulatedBody& currentBody)
{
	double interactionFromNeighbouringBodies = 0;

	for (std::vector<SimulatedBody>::iterator actingBody = simulatedBodies_.begin(); actingBody != simulatedBodies_.end(); actingBody++)
	{
		if (&(*actingBody) != &currentBody)
		{
			interactionFromNeighbouringBodies += actingBody->body().mass() / pow(distanceBetweenTwoVectors(currentBody.body().position(), actingBody->body().position()), 3);
		}
	}
	//&& distanceBetweenTwoVectors(actingBody->body().position(), currentBody.body().position()) > 0.1
	return G_ * interactionFromNeighbouringBodies;
}
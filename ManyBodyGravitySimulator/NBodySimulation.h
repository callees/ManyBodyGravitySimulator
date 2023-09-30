#pragma once

#include <map>
#include "Body.h"
#include "SimulatedBody.h"
#include "TwoVector.h"
#include "RK4Method.h"

class NBodySimulation
{
public:
	NBodySimulation();
	double escapeVelocity(Body<TwoVector> currentBody, Body<TwoVector> actingBody);
	void setUpTestSimulation();
	void calculateFactorsOnSimulatedBodies();
	void testSimulate();
	std::vector<SimulatedBody> simulatedBodies_;

private:
	double gravitationalFactor(const SimulatedBody& currentBody);
	RK4FOODEs<TwoVector> gravitationalODE(RK4FOODEs<TwoVector> positionAndVelocity, double step, double factorFromActingBody);
	double G_;
	double timeStep_;
	double interactionLimit_ = 10;
};


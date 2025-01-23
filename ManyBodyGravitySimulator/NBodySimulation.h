#pragma once

#include <map>
#include "Body.h"
#include "SimulatedBody.h"
#include "Body.h"
#include "TwoVector.h"
#include "RK4Method.h"

typedef std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> odeFunc;

class NBodySimulation
{
public:
	NBodySimulation();
	double escapeVelocity(Body<TwoVector> currentBody, Body<TwoVector> actingBody);
	void setUpTestSimulation();
	void createSimpleSystem(double mass, TwoVector origin, TwoVector velocity, std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc);
	void calculateFactorsOnSimulatedBodies();
	void simulateOneTimeStep();
	void trackBodyPositionHistory();
	std::vector<std::vector<TwoVector>> getBodyPositionHistory();
	std::vector<SimulatedBody> simulatedBodies_;

private:
	double gravitationalFactor(const SimulatedBody& currentBody);
	bool withinAllowedInteractionLimit(const SimulatedBody& currentBody, const SimulatedBody& actingBody);
	RK4FOODEs<TwoVector> gravitationalODE(RK4FOODEs<TwoVector> positionAndVelocity, double step, double interactionAtCurrentBody, TwoVector interactionAtOtherBody);
	TwoVector calculateInteractionFromAllOtherBody(const SimulatedBody& currentBody);
	double calculateInteractionFactorAtCurrentBody(const SimulatedBody& currentBody);
	void updateAllPositions();
	void updateBodyPositionHistory();

	double G_;
	double timeStep_;
	double interactionLimit_ = 50;
	bool trackBodyPositionHistory_ = false;
	std::vector<std::vector<TwoVector>> bodyPositionHistory_;
};

//position -> 2 values
//velocity -> 2 values

//100000*4
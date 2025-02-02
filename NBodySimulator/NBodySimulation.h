#pragma once

#include <map>
#include "Body.h"
#include "SimulatedBody.h"
#include "Body.h"
#include "TwoVector.h"
#include "RK4Method.h"

class NBodySimulation
{
public:
	NBodySimulation();
	double escapeVelocity(Body<TwoVector> currentBody, Body<TwoVector> actingBody);
	void setUpTestSimulation();
	void createSolarSystem();
	void createEarthSystem(TwoVector positionOfSun);
	void createJovianSystem(TwoVector origin);
	void createPlutoSystem(TwoVector positionOfSun);
	void createSimpleSystem(double mass, TwoVector origin, TwoVector velocity);
	void createRandomBody(double mass, double origin);
	void createSystemWithRandomPositionsAndSimilarMasses();
	void calculateFactorsOnSimulatedBodies();
	void simulateOneTimeStep();
	void trackBodyHistory();
	std::vector<std::vector<Body<TwoVector>>> getBodyHistory();
	std::vector<std::vector<Body<TwoVector>>>* bodyHistory();
	std::vector<SimulatedBody> simulatedBodies_;

private:
	double gravitationalFactor(const SimulatedBody& currentBody);
	bool withinAllowedInteractionLimit(const SimulatedBody& currentBody, const SimulatedBody& actingBody);
	RK4FOODEs<TwoVector> gravitationalODE(RK4FOODEs<TwoVector> positionAndVelocity, double step, double interactionAtCurrentBody, TwoVector interactionAtOtherBody);
	TwoVector calculateInteractionFromAllOtherBody(const SimulatedBody& currentBody);
	double calculateInteractionFactorAtCurrentBody(const SimulatedBody& currentBody);
	void updateAllPositions();
	void updateBodyHistory();

	double G_;
	double timeStep_;
	double interactionLimit_ = 1e+5;
	bool trackBodyHistory_ = false;
	std::vector<std::vector<Body<TwoVector>>> bodyHistory_;
	std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc_;
};

//position -> 2 values
//velocity -> 2 values

//100000*4
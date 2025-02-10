#pragma once

#include "BodiesHistories.h"
#include "Body.h"
#include "SimulatedBody.h"
#include "Body.h"
#include "TwoVector.h"
#include "RK4Method.h"

class NBodySimulation
{
public:
	NBodySimulation();
	void setUpTestSimulation();
	void createSolarSystem();
	void createEarthSystem(TwoVector positionOfSun);
	void createJovianSystem(TwoVector origin);
	void createPlutoSystem(TwoVector positionOfSun);
	//void createRandomBody(double mass, double origin);
	void createSystemWithRandomPositionsAndSimilarMasses();
	void calculateFactorsOnSimulatedBodies();
	void simulateOneTimeStep();
	void simulate(unsigned int epoch);
	void trackBodyHistory();
	BodiesHistories getBodyHistory();
	BodiesHistories* bodyHistory();
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
	BodiesHistories systemHistory_;
	std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc_;
};
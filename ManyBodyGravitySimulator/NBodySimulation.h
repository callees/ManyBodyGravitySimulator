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
	void createSolarSystem(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc);
	void createJovianSystem(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc, TwoVector origin);
	void createPlutoSystem(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc, TwoVector positionOfSun);
	void createSimpleSystem(double mass, TwoVector origin, TwoVector velocity, std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEfunc);
	void createRandomBody(double mass, odeFunc gravitationalODEfunc, double origin);
	void createSystemWithRandomPositionsAndSimilarMasses(odeFunc gravitationalODEfunc);
	void calculateFactorsOnSimulatedBodies();
	void simulateOneTimeStep();
	void trackBodyHistory();
	std::vector<std::vector<Body<TwoVector>>> getBodyHistory();
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
	double interactionLimit_ = 1e+4;
	bool trackBodyHistory_ = false;
	std::vector<std::vector<Body<TwoVector>>> bodyHistory_;
};


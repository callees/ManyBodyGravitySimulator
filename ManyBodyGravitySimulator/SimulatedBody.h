#pragma once
#include "Body.h"
#include "TwoVector.h"
#include "RK4Method.h"

class TwoVector;
template <class T = TwoVector> class Body;
template <class T = TwoVector> class RK4FOODEs;

class SimulatedBody
{
public:
	SimulatedBody(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalODEs, Body<TwoVector> body, double timeStep);
	void changeInteractionValues(double newInteractionFactorAtCurrentBody, TwoVector newInteractionFromAllOtherBodies);
	Body<TwoVector> body() const;
	RK4Method<TwoVector> rk4();
	void calculateNewPosition();
	void updatePosition(RK4FOODEs<TwoVector> newStep);
	void updatePosition();
private:
	Body<TwoVector> body_;

	RK4Method<TwoVector> rk4_;
};


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
	SimulatedBody(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double)> gravitationalODEs, Body<TwoVector> body, double timeStep);
	void changeFactor(double newFactor);
	Body<TwoVector> body() const;
	RK4Method<TwoVector> rk4();
	void updatePosition(RK4FOODEs<TwoVector> newStep);
private:
	Body<TwoVector> body_;

	RK4Method<TwoVector> rk4_;
};


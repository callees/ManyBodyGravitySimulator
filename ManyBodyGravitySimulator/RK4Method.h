#pragma once
#ifndef RK4Method_H
#define RK4Method_H

#include <functional>
#include <vector>
#include <iostream>
#include "TwoVector.h"
#include "RK4FOODEs.h"
#include "RK4Function.h"

template<class T>
class RK4Method
{
public:
	RK4Method();
	RK4Method(RK4Function<T> functionToSolve, RK4FOODEs<T> initialValue, double timeStep, double initialTimeStep = 0, double interactionFactorAtCurrentBody = 0, TwoVector interactionFromAllOtherBodies = TwoVector(0,0));
	RK4FOODEs<T> calculateSteps(int numberOfSteps = 1);
	void changeInteractionValues(double newInteractionFactorAtCurrentBody, TwoVector newInteractionFromAllOtherBodies);
	void changeInteractionValues(RK4FOODEs<T> newValue);
	RK4FOODEs<T> getCurrentValue();
protected:
	RK4FOODEs<T> calculateStep();
	void update(RK4FOODEs<T> currentValue);
	RK4FOODEs<T> currentValue_;
	TwoVector interactionFromAllOtherBodies_;
	double interactionFactorAtCurrentBody_;
	double currentTimeStep_;
	double timeStep_;
	RK4Function<T> functionToSolve_;
	RK4FOODEs<T> k1();
	RK4FOODEs<T> k2();
	RK4FOODEs<T> k3();
	RK4FOODEs<T> k4();
	double factor_;
};

#include "RK4Method.cpp"

#endif
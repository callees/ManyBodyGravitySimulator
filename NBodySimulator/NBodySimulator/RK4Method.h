#pragma once

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

template <class T>
RK4Method<T>::RK4Method()
{

}

template <class T>
RK4Method<T>::RK4Method(RK4Function<T> functionToSolve, RK4FOODEs<T> initialValue, double timeStep, double initialTimeStep, double interactionFactorAtCurrentBody, TwoVector interactionFromAllOtherBodies) : functionToSolve_(functionToSolve), currentValue_(initialValue), currentTimeStep_(initialTimeStep), timeStep_(timeStep), interactionFactorAtCurrentBody_(interactionFactorAtCurrentBody), interactionFromAllOtherBodies_(interactionFromAllOtherBodies)
{
}

template<class T>
RK4FOODEs<T> RK4Method<T>::calculateSteps(int numberOfSteps)
{
	for (int currentStep = 0; currentStep < numberOfSteps; currentStep++)
	{
		currentValue_ = calculateStep();
	}
	return currentValue_;
}

template<class T>
void RK4Method<T>::changeInteractionValues(double newInteractionFactorAtCurrentBody, TwoVector newInteractionFromAllOtherBodies)
{
	interactionFactorAtCurrentBody_ = newInteractionFactorAtCurrentBody;
	interactionFromAllOtherBodies_ = newInteractionFromAllOtherBodies;
}

template<class T>
void RK4Method<T>::changeInteractionValues(RK4FOODEs<T> newValue)
{
	currentValue_ = newValue;
}

template<class T>
RK4FOODEs<T> RK4Method<T>::getCurrentValue()
{
	return currentValue_;
}

template <class T>
RK4FOODEs<T> RK4Method<T>::calculateStep()
{
	return currentValue_ + timeStep_ * (k1() + k2() * 2 + k3() * 2 + k4()) / 6;
}

template<class T>
void RK4Method<T>::update(RK4FOODEs<T> currentValue)
{
	currentValue_ = currentValue;
	currentTimeStep_ += timeStep_;
}

template <class T>
RK4FOODEs<T> RK4Method<T>::k1()
{
	return functionToSolve_(currentValue_, currentTimeStep_, interactionFactorAtCurrentBody_, interactionFromAllOtherBodies_);
}

template <class T>
RK4FOODEs<T> RK4Method<T>::k2()
{
	auto args = currentValue_ + timeStep_ * k1() / 2;
	return functionToSolve_(args, currentTimeStep_ + (timeStep_ / 2), interactionFactorAtCurrentBody_, interactionFromAllOtherBodies_);
}

template <class T>
RK4FOODEs<T> RK4Method<T>::k3()
{
	auto args = currentValue_ + timeStep_ * k2() / 2;
	return functionToSolve_(args, currentTimeStep_ + (timeStep_ / 2), interactionFactorAtCurrentBody_, interactionFromAllOtherBodies_);
}

template <class T>
RK4FOODEs<T> RK4Method<T>::k4()
{
	auto args = currentValue_ + timeStep_ * k3();
	return functionToSolve_(args, currentTimeStep_ + timeStep_, interactionFactorAtCurrentBody_, interactionFromAllOtherBodies_);
}
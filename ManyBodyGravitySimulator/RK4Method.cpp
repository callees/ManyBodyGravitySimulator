#include "RK4Method.h"
#pragma once
#ifndef _RK4Method_CPP_
#define _RK4Method_CPP_

template <class T>
RK4Method<T>::RK4Method()
{

}

template <class T>
RK4Method<T>::RK4Method(RK4Function<T> functionToSolve, RK4FOODEs<T> initialValue, double timeStep, double initialTimeStep, double factor) : functionToSolve_(functionToSolve), currentValue_(initialValue), currentTimeStep_(initialTimeStep), timeStep_(timeStep), factorFromActingBody_(factor)
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
void RK4Method<T>::changeFactor(double newFactor)
{
    factorFromActingBody_ = newFactor;
}

template<class T>
void RK4Method<T>::changeValue(RK4FOODEs<T> newValue)
{
    currentValue_ = newValue;
}

template <class T>
RK4FOODEs<T> RK4Method<T>::calculateStep()
{
    return currentValue_ + timeStep_*(k1() + k2()*2 + k3()*2 + k4())/6;
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
    return functionToSolve_(currentValue_, currentTimeStep_, factorFromActingBody_);
}

template <class T>
RK4FOODEs<T> RK4Method<T>::k2()
{
    auto args = currentValue_ + timeStep_ * k1() / 2;
    return functionToSolve_(args, currentTimeStep_ + (timeStep_ / 2), factorFromActingBody_);
}

template <class T>
RK4FOODEs<T> RK4Method<T>::k3()
{
    auto args = currentValue_ + timeStep_ * k2() / 2;
    return functionToSolve_(args, currentTimeStep_+ (timeStep_/2), factorFromActingBody_);
}

template <class T>
RK4FOODEs<T> RK4Method<T>::k4()
{
    auto args = currentValue_ + timeStep_ * k3();
    return functionToSolve_(args, currentTimeStep_+timeStep_, factorFromActingBody_);
}

#endif
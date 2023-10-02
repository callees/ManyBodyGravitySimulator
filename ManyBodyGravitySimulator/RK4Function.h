#include "RK4FOODEs.h"
#include <functional>
#include "TwoVector.h"

#pragma once
#ifndef RK4Function_H
#define RK4Function_H

template<class T>
class RK4Function
{
public:
	RK4Function();
	RK4Function(std::function<RK4FOODEs<T>(RK4FOODEs<T>, double, double, TwoVector)> rk4Function, double factor = 0);
	void changeFactor(double newFactor);
	RK4FOODEs<T> operator()(RK4FOODEs<T> , double, double, TwoVector);

private:
	std::function<RK4FOODEs<T>(RK4FOODEs<T>, double, double, TwoVector)> rk4Function_;
	double factor_;
};

#include "RK4Function.cpp"

#endif
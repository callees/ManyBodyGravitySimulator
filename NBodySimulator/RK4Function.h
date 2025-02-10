#pragma once
#include "RK4FOODEs.h"
#include <functional>
#include "TwoVector.h"

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

template<class T>
RK4Function<T>::RK4Function()
{
}

template <class T>
RK4Function<T>::RK4Function(std::function<RK4FOODEs<T>(RK4FOODEs<T>, double, double, TwoVector)> rk4Function, double factor) : rk4Function_(rk4Function), factor_(factor)
{

}

template <class T>
void RK4Function<T>::changeFactor(double factor)
{
	factor_ = factor;
}


template<class T>
RK4FOODEs<T> RK4Function<T>::operator()(RK4FOODEs<T> rk4Arguments, double step, double interactionFactorAtCurrentBody, TwoVector interactionFromAllOtherBodies)
{
	return rk4Function_(rk4Arguments, step, interactionFactorAtCurrentBody, interactionFromAllOtherBodies);
}
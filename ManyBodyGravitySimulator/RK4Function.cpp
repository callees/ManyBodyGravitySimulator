#include "RK4Function.h"
#pragma once
#ifndef _RK4Function_CPP_
#define _RK4Function_CPP_

template<class T>
RK4Function<T>::RK4Function()
{
}

template <class T>
RK4Function<T>::RK4Function(std::function<RK4FOODEs<T>(RK4FOODEs<T>, double, double)> rk4Function, double factor) : rk4Function_(rk4Function), factor_(factor)
{

}

template <class T>
void RK4Function<T>::changeFactor(double factor)
{
	factor_ = factor;
}

template<class T>
RK4FOODEs<T> RK4Function<T>::operator()(RK4FOODEs<T> rk4Arguments, double step, double factor)
{
	return rk4Function_(rk4Arguments, step, factor);
}

#endif
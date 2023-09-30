#include "RK4FOODEs.h"
#pragma once
#ifndef _RK4FOODEs_CPP_
#define _RK4FOODEs_CPP_

template<class T>
RK4FOODEs<T>::RK4FOODEs()
{
}

template <class T>
RK4FOODEs<T>::RK4FOODEs(T initialy, T initialdy) : y_(initialy), dy_(initialdy)
{

}

template <class T>
void RK4FOODEs<T>::update(T nexty, T nextdy)
{
	y_ = nexty;
	dy_ = nextdy;
}

template <class T>
T RK4FOODEs<T>::y()
{
	return y_;
}

template <class T>
T RK4FOODEs<T>::dy()
{
	return dy_;
}

template<class T>
RK4FOODEs<T> RK4FOODEs<T>::operator+(const RK4FOODEs<T>& other)
{
	return RK4FOODEs<T>(this->y_ + other.y_, this->dy_ + other.dy_);
}

template<class T>
RK4FOODEs<T> RK4FOODEs<T>::operator+(const double& other)
{
	return RK4FOODEs<T>(this.y_ + other, this.dy_ + other);
}

template<class T>
RK4FOODEs<T> RK4FOODEs<T>::operator-(const RK4FOODEs<T>& other)
{
	return RK4FOODEs<T>(this->y_ - other.y_, this->dy_ - other.dy_);
}

template<class T>
RK4FOODEs<T> RK4FOODEs<T>::operator-(const double& other)
{
	return RK4FOODEs<T>(this->y_ - other, this->dy_ - other);
}

template<class T>
RK4FOODEs<T> operator*(const double& aDouble, const RK4FOODEs<T>& aFOOD)
{
	return RK4FOODEs<T>(aFOOD.y_ * aDouble, aFOOD.dy_ * aDouble);
}

template<class T>
RK4FOODEs<T> operator*(const RK4FOODEs<T>& aFOOD, const double& aDouble)
{
	return RK4FOODEs<T>(aFOOD.y_ * aDouble, aFOOD.dy_ * aDouble);
}

template<class T>
RK4FOODEs<T> RK4FOODEs<T>::operator/(const double& other)
{

	return RK4FOODEs<T>(this->y_/other, this->dy_/other);
}


#endif


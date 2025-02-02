#pragma once
#ifndef RK4FOODEs_H
#define RK4FOODEs_H

template<class T>
class RK4FOODEs
{
public:
	RK4FOODEs();
	RK4FOODEs(T initialy, T dinitialdy);
	void update(T nexty, T nextdy);
	T y();
	T dy();

	RK4FOODEs<T> operator+(const RK4FOODEs<T>& other);
	RK4FOODEs<T> operator+(const double& other);
	RK4FOODEs<T> operator-(const RK4FOODEs<T>& other);
	RK4FOODEs<T> operator-(const double& other);
	template<typename T> friend RK4FOODEs<T> operator*(const double& aDouble, const RK4FOODEs<T>& aFOOD);
	template<typename T> friend RK4FOODEs<T> operator*(const RK4FOODEs<T>& aFOOD, const double& aDouble);
	RK4FOODEs operator/(const double& other);

private:
	T y_;
	T dy_;
};

#include "RK4FOODEs.cpp"
#endif
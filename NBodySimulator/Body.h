#pragma once
#ifndef Body_H
#define Body_H

template<class T>
class Body
{
public:
	Body(T position, T velocity, T acceleration, double mass);
	T position();
	T velocity();
	T acceleration();
	double mass();

	void setPosition(T position);
	void setVelocity(T velocity);
	void setAcceleration(T acceleration);
	bool operator<(const Body<T>& rhs) const noexcept;

	//Body operator+(const Body& other);
	//Body operator+(const Body& double);
private:
	T position_;
	T velocity_;
	T acceleration_;

	double mass_;
};

//Dont have to make children for types of stars since they are defined by their masses

#include "Body.cpp"

#endif
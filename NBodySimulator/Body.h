#pragma once
#ifndef Body_H
#define Body_H

template<class T>
class Body
{
public:
	Body(T position, T velocity, double mass);
	T position();
	T velocity();
	double mass();

	void setPosition(T position);
	void setVelocity(T velocity);
	bool operator<(const Body<T>& rhs) const noexcept;

private:
	T position_;
	T velocity_;

	double mass_;
};

//Dont have to make children for types of stars since they are defined by their masses

#include "Body.cpp"

#endif
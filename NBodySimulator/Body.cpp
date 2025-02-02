#include "Body.h"
#pragma once
#ifndef _Body_CPP_
#define _Body_CPP_

template <class T>
Body<T>::Body(T position, T velocity, T acceleration, double mass) : position_(position), velocity_(velocity), acceleration_(acceleration), mass_(mass)
{
}

template <class T>
T Body<T>::position()
{
	return position_;
}

template <class T>
T Body<T>::velocity()
{
	return velocity_;
}

template <class T>
T Body<T>::acceleration()
{
	return acceleration_;
}

template <class T>
double Body<T>::mass()
{
	return mass_;
}

template <class T>
void Body<T>::setPosition(T position)
{
	position_ = position;
}

template <class T>
void Body<T>::setVelocity(T velocity)
{
	velocity_ = velocity;
}

template <class T>
void Body<T>::setAcceleration(T acceleration)
{
	acceleration_ = acceleration;
}

template<class T>
bool Body<T>::operator<(const Body<T>& rhs) const noexcept
{
	return this->mass_ < rhs.mass_;
}

//template<class T>
//Body<T> Body<T>::operator+(const Body& other)
//{
//	return Body(this.position + other.position, this.velocity + other.velocity, this.acceleration + other.acceleration, this.mass);
//}

#endif
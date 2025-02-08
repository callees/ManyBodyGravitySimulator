#include "Body.h"
#pragma once
#ifndef _Body_CPP_
#define _Body_CPP_

template <class T>
Body<T>::Body(T position, T velocity, double mass) : position_(position), velocity_(velocity), mass_(mass)
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

template<class T>
bool Body<T>::operator<(const Body<T>& rhs) const noexcept
{
	return this->mass_ < rhs.mass_;
}


#endif
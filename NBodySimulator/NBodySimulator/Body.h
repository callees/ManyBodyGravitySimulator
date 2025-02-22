#pragma once

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
	bool operator<(const Body<T>& rhs) const;

private:
	T position_;
	T velocity_;

	double mass_;
};

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
bool Body<T>::operator<(const Body<T>& rhs) const
{
	return this->mass_ < rhs.mass_;
}
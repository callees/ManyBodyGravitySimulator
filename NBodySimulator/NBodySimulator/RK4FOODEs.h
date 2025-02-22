#pragma once

template<class T> class RK4FOODEs;
template<class T> RK4FOODEs<T> operator*(const double& aDouble, const RK4FOODEs<T>& aFOOD);
template<class T> RK4FOODEs<T> operator*(const RK4FOODEs<T>& aFOOD, const double& aDouble);

template<class T> class RK4FOODEs
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

	friend RK4FOODEs<T> operator* <> (const double& aDouble, const RK4FOODEs<T>& aFOOD);
	friend RK4FOODEs<T> operator* <> (const RK4FOODEs<T>& aFOOD, const double& aDouble);
	RK4FOODEs operator/(const double& other);

private:
	T y_;
	T dy_;
};

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

	return RK4FOODEs<T>(this->y_ / other, this->dy_ / other);
}
#include "TwoVector.h"
#include <math.h>

TwoVector::TwoVector()
{
	x_ = 0;
	y_ = 0;
}

TwoVector::TwoVector(double x, double y) : x_(x), y_(y)
{
}

double TwoVector::length()
{
	return sqrt(pow(this->x1(), 2) + pow(this->x2(), 2));
}

double TwoVector::x1()
{
	return x_;
}

double TwoVector::x2()
{
	return y_;
}

TwoVector TwoVector::operator+(const TwoVector& other)
{
	return TwoVector(this->x_ + other.x_, this->y_ + other.y_);
}

TwoVector TwoVector::operator+(const double& aDouble)
{
	return TwoVector(this->x_ + aDouble, this->y_ + aDouble);
}

TwoVector TwoVector::operator-(const TwoVector& other)
{
	return TwoVector(this->x_ - other.x_, this->y_ - other.y_);
}

TwoVector TwoVector::operator-(const double& aDouble)
{
	return TwoVector(this->x_ - aDouble, this->y_ - aDouble);
}

TwoVector operator*(const TwoVector& aVector, const double& aDouble)
{
	return TwoVector(aVector.x_ * aDouble, aVector.y_ * aDouble);
}

std::ostream& operator<<(std::ostream& os, const TwoVector& vector)
{
	os << vector.x_ << "\t" << vector.y_;
	return os;
}

TwoVector operator*(const double& aDouble, const TwoVector& aVector)
{
	return TwoVector(aVector.x_ * aDouble, aVector.y_ * aDouble);
}

TwoVector TwoVector::operator/(const double& other)
{
	return TwoVector(this->x_ / other, this->y_ / other);
}

bool TwoVector::operator<(const TwoVector& rhs) const noexcept
{
	return sqrt(pow(this->x_, 2) + pow(this->y_, 2)) < sqrt(pow(rhs.x_, 2) + pow(rhs.y_, 2));
}


double distanceBetweenTwoVectors(TwoVector vector1, TwoVector vector2)
{
	return sqrt(pow(vector1.x1() - vector2.x1(), 2) + pow(vector1.x2() - vector2.x2(), 2));
}
#pragma once
#include <iostream>
class TwoVector
{
public:
	TwoVector();
	TwoVector(double x1, double x2);
	double length();
	double x1();
	double x2();

	TwoVector operator+(const TwoVector& other);
	TwoVector operator+(const double& aDouble);
	TwoVector operator-(const TwoVector& other);
	TwoVector operator-(const double& aDouble);
	friend TwoVector operator*(const double& aDouble, const TwoVector& aVector);
	friend TwoVector operator*(const TwoVector& aVector, const double& aDouble);
	TwoVector operator/(const double& other);
	friend std::ostream& operator<<(std::ostream& os, const TwoVector& vector);
	bool operator<(const TwoVector& rhs) const noexcept;

private:
	double x_;
	double y_;

};

double distanceBetweenTwoVectors(TwoVector vector1, TwoVector vector2);
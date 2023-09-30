#pragma once
#include <functional>

class TwoOrderRK4Method
{
public:
	TwoOrderRK4Method();

private:
	std::function<double()> fFunction_;
	std::function<double()> gFunction_;
	double k1();
	double k2();
	double k3();
	double k4();

	double l1();
	double l2();
	double l3();
	double l4();
};


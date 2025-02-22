#include "gtest/gtest.h"

#include "../ManyBodyGravitySimulator/RK4Method.h"

#include <math.h>
#include "../ManyBodyGravitySimulator/TwoVector.h"

template<class T>
class TestRK4Method : public RK4Method<T>
{
public:
	TestRK4Method(RK4Function<T> functionToSolve, RK4FOODEs<T> initialValue, double timeStep) : RK4Method<T>(functionToSolve, initialValue, timeStep)
	{
	}

	using RK4Method<T>::k1;
	using RK4Method<T>::k2;
	using RK4Method<T>::k3;
	using RK4Method<T>::k4;
};

RK4FOODEs<double> testODE(RK4FOODEs<double> y, double step, double factor)
{
	double yValue = y.y();
	double returnValue = (5 * pow(step, 2) - yValue) / exp(step + yValue);
	return RK4FOODEs<double>(returnValue, 0);
}

double stepSize = 0.1;
std::function<RK4FOODEs<double>(RK4FOODEs<double>, double, double)> test = std::bind(&testODE, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
RK4FOODEs<double> initialValue(1, 0);
RK4Function<double> ode(test, 0);
TestRK4Method<double> testMethod(test, initialValue, stepSize);
double equalityTolerance = 1e-7;

TEST(RK4MethodTests_FirstOrder, k1Double)
{
	EXPECT_TRUE(abs(-0.0367879 - stepSize * testMethod.k1().y()) < equalityTolerance);
}

TEST(RK4MethodTests_FirstOrder, k2Double)
{
	EXPECT_TRUE(abs(-0.0345422 - stepSize * testMethod.k2().y()) < equalityTolerance);
}

TEST(RK4MethodTests_FirstOrder, k3Double)
{
	EXPECT_TRUE(abs(-0.0345435 - stepSize * testMethod.k3().y()) < equalityTolerance);
}

TEST(RK4MethodTests_FirstOrder, k4Double)
{
	EXPECT_TRUE(abs(-0.0315439 - stepSize * testMethod.k4().y()) < equalityTolerance);
}

TEST(RK4MethodTests_FirstOrder, RK4OneStep)
{
	EXPECT_TRUE(abs(0.9655828 - testMethod.calculateStep().y()) < equalityTolerance);
}

RK4FOODEs<double> test2DODE(RK4FOODEs<double> Y, double step, double factor)
{
	return RK4FOODEs<double>(Y.dy(), 6 * Y.y() - Y.dy());
}

std::function<RK4FOODEs<double>(RK4FOODEs<double>, double, double)> test2D = std::bind(&test2DODE, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
RK4Function<double> ode2d(test2D);
TestRK4Method<double> test2dMethod(test2D, RK4FOODEs<double>(3, 1), stepSize);

TEST(RK4MethodTests_SecondOrder, RK4TenSteps)
{
	RK4FOODEs<double> result = test2dMethod.calculateSteps(10);

	EXPECT_TRUE(abs(14.827578509968 - result.y()) < equalityTolerance);
	EXPECT_TRUE(abs(29.406156886687 - result.dy()) < equalityTolerance);
}
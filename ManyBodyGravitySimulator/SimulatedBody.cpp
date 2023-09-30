#include "SimulatedBody.h"

SimulatedBody::SimulatedBody(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double)> gravitationalOdes, Body<TwoVector> body, double timeStep) : body_(body)
{
	RK4Function<TwoVector> rk4Function(gravitationalOdes);
	rk4_ = RK4Method<TwoVector>(rk4Function, RK4FOODEs<TwoVector>(body.position(), body.velocity()), timeStep, 0);
}

void SimulatedBody::changeFactor(double newFactor)
{
	rk4_.changeFactor(newFactor);
}

void SimulatedBody::updatePosition(RK4FOODEs<TwoVector> newStep)
{
	rk4_.changeValue(newStep);
	body_.setVelocity(newStep.dy());
	body_.setPosition(newStep.y());
}

RK4Method<TwoVector> SimulatedBody::rk4()
{
	return rk4_;
}

Body<TwoVector> SimulatedBody::body() const
{
	return body_;
}
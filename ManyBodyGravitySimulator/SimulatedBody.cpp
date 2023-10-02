#include "SimulatedBody.h"

SimulatedBody::SimulatedBody(std::function<RK4FOODEs<TwoVector>(RK4FOODEs<TwoVector>, double, double, TwoVector)> gravitationalOdes, Body<TwoVector> body, double timeStep) : body_(body)
{
	RK4Function<TwoVector> rk4Function(gravitationalOdes);
	rk4_ = RK4Method<TwoVector>(rk4Function, RK4FOODEs<TwoVector>(body.position(), body.velocity()), timeStep, 0);
}

void SimulatedBody::changeInteractionValues(double newInteractionFactorAtCurrentBody,TwoVector newInteractionFromAllOtherBodies)
{
	rk4_.changeInteractionValues(newInteractionFactorAtCurrentBody, newInteractionFromAllOtherBodies);
}

void SimulatedBody::updatePosition(RK4FOODEs<TwoVector> newStep)
{
	rk4_.changeInteractionValues(newStep);
	body_.setVelocity(newStep.dy());
	body_.setPosition(newStep.y());
}

void SimulatedBody::updatePosition()
{
	body_.setPosition(rk4_.getCurrentValue().y());
	body_.setVelocity(rk4_.getCurrentValue().dy());
}

RK4Method<TwoVector> SimulatedBody::rk4()
{
	return rk4_;
}

void SimulatedBody::calculateNewPosition()
{
	rk4_.calculateSteps();
}

Body<TwoVector> SimulatedBody::body() const
{
	return body_;
}
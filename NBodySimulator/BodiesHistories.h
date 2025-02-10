#pragma once
#include <vector>
#include "Body.h"
#include "TwoVector.h"
class BodiesHistories
{
public:
	BodiesHistories();
	void addHistory(std::vector<Body<TwoVector> > bodyHistory);
	void save();
private:
	std::vector<std::vector<Body<TwoVector> > > systemHistory_ = {{}};
};


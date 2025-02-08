#include "BodiesHistories.h"
#include <fstream>

BodiesHistories::BodiesHistories()
{
}

void BodiesHistories::addHistory(std::vector<Body<TwoVector>> bodyHistory)
{
	systemHistory_.push_back(bodyHistory);
}

void BodiesHistories::save()
{
	std::ofstream file("testFile.txt");

	for(unsigned int currentSystemHistory = 0; currentSystemHistory < systemHistory_.size(); currentSystemHistory++)
	{
		file << currentSystemHistory << "\n";
		for(unsigned int currentBodyHistory = 0 ; currentBodyHistory < systemHistory_[currentBodyHistory].size(); currentBodyHistory++)
		{
			file << systemHistory_[currentSystemHistory][currentBodyHistory].position().x1() << "," << systemHistory_[currentSystemHistory][currentBodyHistory].position().x2() << "\n";
		}
	}
}

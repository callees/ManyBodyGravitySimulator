#include "BodiesHistories.h"
#include "../nlohmann/json.hpp"
#include <string>
#include <iostream>
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
	nlohmann::json historyObject;
	for(unsigned int epoch = 0; epoch < systemHistory_.size(); epoch++)
	{
		nlohmann::json bodies = {};
		for(unsigned int body = 0; body < systemHistory_[body].size(); body++)
		{
			TwoVector position = systemHistory_[epoch][body].position();
			nlohmann::json positionObject = {"position", {position.x1(), position.x2()}};
			
			TwoVector velocity = systemHistory_[epoch][body].velocity();
			nlohmann::json velocityObject = {"velocity", {velocity.x1(), velocity.x2()}};
			
			nlohmann::json bodyObject;
			bodyObject[std::to_string(body)] = {velocityObject, positionObject};
			bodies.push_back(bodyObject);
		}
		historyObject[std::to_string(epoch)] = bodies;
		bodies = {};
	}

	std::ofstream file;
	file.open("output.json");
	file << historyObject;
	file.close();
}

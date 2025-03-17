#include <fstream>
#include <vector>

#include "../nlohmann/json.hpp"
#include "../NBodySimulator/NBodySimulation.h"
#include "../NBodySimulator/Body.h"


int main(int argc, const char* argv[])
{
	std::ifstream inputJsonFile("build/input.json");
	auto bodyJsonObject = nlohmann::json::parse(inputJsonFile);
	std::vector<Body<TwoVector>> bodies;
	auto bodiesJson = bodyJsonObject["bodies"];

	for(unsigned int currentBodyObject = 0; currentBodyObject < bodiesJson.size(); currentBodyObject++)
	{
		auto bodyObject = bodiesJson[currentBodyObject];

		TwoVector position(bodyObject["position"]["x1"], bodyObject["position"]["x2"]);
		TwoVector velocity(bodyObject["velocity"]["x1"], bodyObject["velocity"]["x2"]);

		bodies.push_back(Body<TwoVector>(position, velocity, bodyObject["mass"]));
	}

	NBodySimulation simulation(bodies);
	simulation.setUpTestSimulation();
	simulation.simulate(1000);
	std::cout << "Simulation finished\n";
	return 0;
}
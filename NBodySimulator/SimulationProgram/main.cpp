#include "../NBodySimulator/NBodySimulation.h"

int main(int argc, const char* argv[])
{
	NBodySimulation simulation;
	simulation.setUpTestSimulation();
	simulation.simulate(100);
	std::cout << "Simulation finished\n";
	return 0;
}
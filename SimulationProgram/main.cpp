#include "../NBodySimulator/NBodySimulation.h"

int main(int argc, const char* argv[])
{
	NBodySimulation simulation;
	simulation.setUpTestSimulation();
	simulation.simulate(100);
	return 0;
}
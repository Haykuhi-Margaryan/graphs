#include "Graph.h"

int main()
{
	std::vector <std::vector <int>> Nodes;

	CreateGraph(Nodes);

	std::cout << std::endl << "Creating done" << std::endl;

	HamiltonianCycle(Nodes);

	return 0;
}
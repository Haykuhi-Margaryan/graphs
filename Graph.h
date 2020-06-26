#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

int num;
void CreateGraph(std::vector <std::vector <int>>& Graph)
{
	std::vector <int> Adj;
	int k=0;
	int tmp=0;
	int count;
	std::cout << "Enter number of Vertexes  ";
	std::cin >> num;
	
	for (int i = 0; i < num; i++) //Creating graph //rand() function used for generate adjacent nodes
	{
		Adj.push_back(i);
		k = ((rand() % 3) + num-3);
		for (int it = 1; it < k; it++)
		{
			tmp = rand() % num;
			count = 0;
			for (int t = 0; t < Adj.size(); t++)
			{
				if (tmp == Adj[t])
					count++;
			}
			if (count == 0)
				Adj.push_back(tmp);
		}
		k = 0;
		Graph.push_back(Adj);
		Adj.clear();
	}
	int u = 0;
	for (auto& vec_it : Graph.back())
		if (vec_it == 0)
			u++;
	if(u==0)
		Graph.back().insert(Graph.back().end(), 0);
	
	for (auto& bigvec_it : Graph)
	{
		std::cout << std::endl;
		for (auto& vec_it : bigvec_it)
		{
			std::cout << vec_it<<" ";
		}
	}
}

//Checking if two nodes are adjacent in graph
void CheckAdjacency(int a, int b, std::vector <std::vector <int>>& Graph, int& l)
{
	l = 0;
	std::vector <int> Temp;
	for (auto& bigvec_it : Graph)
	{
		for (auto& vec_it : bigvec_it)
		{
			Temp.push_back(vec_it);
		}
		for (int i = 0; i < Temp.size(); i++)
		{
			if ((a == Temp[0] && b == Temp[i]) || (b == Temp[0] && a == Temp[i]))
			{
				l++;
			}			
		}
		Temp.clear();
	}	
}

void HamiltonianCycle(std::vector <std::vector <int>>& Graph)
{
	//Randomising nodes to check their adjacency
	std::vector <int> RandomNodes;
	for (int i = 0; i < num; i++)
		RandomNodes.push_back(i);
	random_shuffle(RandomNodes.begin(), RandomNodes.end()); 
	int l;
	std::vector <int> NonAdj;
	for (int i=0;i< RandomNodes.size()-1;i++)
	{
		CheckAdjacency(RandomNodes[i], RandomNodes[i + 1], Graph,l);
		if(l==0)
		{
			NonAdj.push_back(RandomNodes[i]);
			NonAdj.push_back(RandomNodes[i + 1]);
		}   
	}  

	//Counting number of adjacents for every node
	int number = 0;
	std::vector <int> Num;
	for (auto& bigvec_it : Graph)
	{
		for (auto& vec_it : bigvec_it)
		{
			number++;
		}
		Num.push_back(number -1);
		number = 0;
	}

	//Checking conditions of O.Ore
	int count = 0;
	for(int j = 0; j < NonAdj.size()-1; j++)
	{
		auto itt1 = next(Num.begin(), NonAdj[j]);
		auto itt2 = next(Num.begin(), NonAdj[j+1]);
		if ((*itt1 + *itt2) <= Graph.size() && (*itt1 + *itt2) <= Graph.size()-1)
		{
			count++;
		}
	}
	if (num >= 3 && count == 0) 
	{
		std::vector <int> Cycle;
		std::vector <int> OutOfCycle;

		//Creating Hamiltonian cycle
		Cycle.push_back(Graph[0][0]);
		for (int i = 1; i < num; i++)
		{
			CheckAdjacency(Cycle.back(), i, Graph, l);
			if (l > 0)
			{
				Cycle.push_back(i);
			}
			else OutOfCycle.push_back(i);
		}
		Cycle.push_back(Graph.back().back());
		
		int h = 0;
		for (int j = 0; j < OutOfCycle.size(); j++)
		{
			for (int i = 0; i < Cycle.size() - 1; i++)
			{
				CheckAdjacency(OutOfCycle[j], Cycle[i], Graph, l);
				if (l > 0)
				{
					CheckAdjacency(OutOfCycle[j], Cycle[i + 1], Graph, l);
					if (l > 0)
					{
						h = i;
					}
				}
			}
			Cycle.insert(Cycle.begin() + h+1, OutOfCycle[j]);
		}
		std::cout << std::endl << "Hamiltonian cycle" << std::endl;
		for (int i = 0; i < Cycle.size(); i++)
			std::cout << Cycle[i] << " ";
	}
	else 
	{
		std::cout << std::endl << "Graph is a non-Hamiltonian" << std::endl;
		Graph.clear();
		CreateGraph(Graph);
		HamiltonianCycle(Graph);
	}
}  

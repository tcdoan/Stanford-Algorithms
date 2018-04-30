#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

// return true if there is a negative circle in graph
// Use output shortestValue as return value.
bool FindShortestShortestPath(const string& fileName, int* shortestValue)
{
	ifstream input(fileName);
	int V;
	int E;
	input >> V;
	V = V + 1;
	input >> E;

	vector<vector<int>> g(V);
	for (int i = 1; i < V; i++)
	{
		g[i] = vector<int>(V, numeric_limits<int>::max());
		g[i][i] = 0;
	}

	int v, w, cost;
	for (int e = 0; e < E; e++)
	{
		input >> v;
		input >> w;
		input >> cost;
		g[v][w] =  cost;
	}

	// distance values in previous iteration (i.e. iteration k-1) 
	vector<vector<int>> pdist(V);

	// distance values in currrent iteration (i.e. iteration k) 
	vector<vector<int>> dist(V);
	for (int i = 1; i < V; i++)
	{
		dist[i] = vector<int>(V);
		for (int j = 1; j < V; j++)
		{
			dist[i][j] = g[i][j];
		}
	}

	pdist = dist;
	for (int k = 1; k < V; k++)
	{
		for (int i = 1; i < V; i++)
		{
			for (int j = 1; j < V; j++)
			{
				dist[i][j] = ((pdist[i][k] != numeric_limits<int>::max()) && (pdist[k][j] != numeric_limits<int>::max())) ? min(pdist[i][j], pdist[i][k] + pdist[k][j]) : pdist[i][j];
			}
		}
		pdist = dist;
	}

	bool isCycle = false;
	for (int i = 1; i < V; i++)
	{
		if (dist[i][i] < 0)
		{
			isCycle = true;
			break;
		}
	}

	if (isCycle)
	{
		*shortestValue = 0;
		return isCycle;
	}
	else
	{
		*shortestValue = dist[1][1];
		for (int i = 1; i < V; i++)
		{
			for (int j = 1; j < V; j++)
			{
				if ((*shortestValue) > dist[i][j])
				{
					*shortestValue = dist[i][j];
				}
			}
		}
		return false;
	}
}

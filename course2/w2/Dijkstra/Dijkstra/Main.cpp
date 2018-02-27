#include "Graph.h"
#include <queue>
#include <limits>
#include <iostream>

using namespace std;

// priority queue comparator 
auto cmp = [](pair<int, int> p1, pair<int, int> p2) { return p2.second < p1.second;	};

// Compute shortest distances d from from source vertex s to other vetices
// d[v] is shortest distance from s to v 
void ComputeShortestPaths(Graph& g, int s, vector<int>& dist)
{		
	for (int v = 0; v < dist.size(); v++) { dist[v] = numeric_limits<int>::max(); }
	dist[s] = 0;

	// custom comparator for priority queue 
	// we compare using the 2nd element, the current dijkstra score  
	auto cmp = [](pair<int, int> p1, pair<int, int> p2)
	{ 
		return p1.second < p2.second; 
	};
	
	// priority quue storing a pair (v, d)
	// d is the distance from s to v
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
	pq.push(make_pair(s, 0));

	while (!pq.empty())
	{
		auto p = pq.top();
		pq.pop();
		int v = p.first;
		for (const pair<int, int> e : g.AdjList(v))
		{
			int w = e.first;
			if (dist[w] > dist[v] + e.second)
			{
				dist[w] = dist[v] + e.second;
				pq.push(make_pair(w, dist[w]));
			}
		}
	}
}

int main()
{
	Graph g(201, "D:\\repos\\algorithm\\course2\\w2\\shortest_data.txt");
	vector<int> dist(g.V);
	ComputeShortestPaths(g, 1, dist);

	vector<int> vertices{ 7,37,59,82,99,115,133,165,188,197 };
	for (int v : vertices)
	{
		cout << dist[v] << ", ";
	}
	cout << endl;
	return 0;
}

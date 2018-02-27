#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

// Quick & dirty implementation of the directed graph 
// for computing stringly connected components 
class Digraph
{
public:
	// number of vertices
	int V;

	// number of edges
	int E;

	Digraph(int V) : V(V)
	{
		if (V < 0) throw runtime_error("Invalid number of vertices");
		edges = vector<vector<int>>(V);
		E = 0;
	}

	Digraph(const int V, const vector< int>& inputVec) : V(V)
	{
		if (V < 0) throw runtime_error("Invalid number of vertices");
		edges = vector<vector<int>>(V);
		E = 0;
		// Read pair (v, w) from input vector
		for (int i = 0; i < inputVec.size() - 1; i += 2)
		{
			int v = inputVec[i];
			int w = inputVec[i + 1];
			AddEdge(v, w);
		}
	}

	void AddEdge(int v, int w)
	{
		edges[v].emplace_back(w);
		E++;
	}

	const vector<int>& AdjList(int v) const
	{
		return edges[v];
	}

	// return a copy of this graph with all edges reversed.
	Digraph* Reverse()
	{
		Digraph* g2 = new Digraph(V);
		for (int v = 0; v < V; v++)
		{
			for (int w : AdjList(v))
			{
				g2->AddEdge(w, v);
			}
		}
		return g2;
	}

private:
	// Adjacency list representation of the digraph
	vector<vector<int>> edges;
};

// Implement the output operator for Digraph ADT.
ostream& operator<< (ostream &os, const Digraph& g)
{
	os << "Vertices: " << g.V << endl;
	os << "Edges: " << g.E << endl;

	for (int v = 0; v < g.V; v++)
	{
		os << v << ": ";
		const vector<int>& adj = g.AdjList(v);
		for (int w : adj)
		{
			os << w << " ";
		}
		os << endl;
	}
	return os;
}

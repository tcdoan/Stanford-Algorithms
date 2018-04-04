#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include  "edge.h"

using namespace std;

// Quick & dirty implementation of an weighted undirected graph
class Graph
{
public:
	// number of vertices
	int V;

	// number of edges
	int E;

	Graph(const string& file_name)
	{
		ifstream input(file_name);
		input >> V;
		V = V + 1;
		input >> E;

		edges = vector<vector<Edge>>(V);
		int v, w, cost;
		for (int i = 0; i < E; i++)
		{
			input >> v;
			input >> w;
			input >> cost;
			AddEdge(v, w, cost);
			AddEdge(w, v, cost);
		}
	}

	void AddEdge(int v, int w, int cost)
	{
		Edge e(v, w, cost);
		edges[v].emplace_back(e);
	}

	const vector<Edge>& AdjList(int v) const
	{
		return edges[v];
	}

private:
	// Adjacency list representation of the graph
	vector<vector<Edge>> edges;
};

// Implement the output operator for Digraph ADT.
ostream& operator<< (ostream &os, const Graph& g)
{
	os << "Vertices: " << g.V << endl;
	os << "Edges: " << g.E << endl;
	for (int v = 0; v < g.V; v++)
	{
		os << v << ": ";
		const vector<Edge>& adj = g.AdjList(v);
		for (const Edge& e : adj)
		{
			os << "(" << e.v << ", " << e.w << ", " << e.cost << "), ";
		}
		os << endl;
	}
	return os;
}
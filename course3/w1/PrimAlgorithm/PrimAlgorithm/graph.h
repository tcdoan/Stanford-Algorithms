#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <tuple>

using namespace std;

// Quick & dirty implementation of an costed undirected graph
// for computing single source shorest paths
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
		string firstline;
		getline(input, firstline);
		istringstream firstline_stream(firstline);
		firstline_stream >> V;
		firstline_stream >> E;
		edges = vector<vector<tuple<int, int, int>>>(V);
		int v;
		int w;
		int cost;
		for (string line; getline(input, line);)
		{
			istringstream line_stream(line);
			line_stream >> v;
			line_stream >> w;
			line_stream >> cost;
			AddEdge(v, w, cost);
		}
	}

	void AddEdge(int v, int w, int cost)
	{
		edges[v].emplace_back(make_tuple(v, w, cost));
	}

	const vector<tuple<int, int, int>>& AdjList(int v) const
	{
		return edges[v];
	}

private:
	// Adjacency list representation of the graph
	vector<vector<tuple<int, int, int>>> edges;
};

// Implement the output operator for Digraph ADT.
ostream& operator<< (ostream &os, const Graph& g)
{
	os << "Vertices: " << g.V << endl;
	os << "Edges: " << g.E << endl;
	for (int v = 0; v < g.V; v++)
	{
		os << v << ": ";
		const vector<tuple<int, int, int>>& adj = g.AdjList(v);
		for (auto e : adj)
		{
			os << "(" << std::get<0>(e) << ", " << std::get<1>(e) << ", " << std::get<2>(e) << "), ";
		}
		os << endl;
	}
	return os;
}
#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// Quick & dirty implementation of an weighted undirected graph 
// for computing single source shorest paths 
class Graph
{
public:
	// number of vertices
	int V;

	// number of edges
	int E;

	Graph(const int V) : V(V)
	{
		if (V < 0) throw runtime_error("Invalid number of vertices");
		edges = vector<vector<pair<int, int>>>(V);
		E = 0;
	}

	Graph(const int V, const string& file_name) : Graph(V)
	{
		ifstream input(file_name, ios::in);
		char no_op;
		int v;
		int w;
		int weight;
		for (string line; getline(input, line);)
		{
			istringstream line_stream(line);
			// read the first column, the vertex v
			line_stream >> v;
			while (!line_stream.eof())
			{
				line_stream >> w;
				line_stream >> no_op;
				line_stream >> weight;
				AddEdge(v, w, weight);
			}
		}
	}

	void AddEdge(int v, int w, int weight)
	{
		auto e = make_pair(w, weight);
		edges[v].emplace_back(e);
		E++;
		// cout << "Add edge " << E << "(" << v << ", " << w << ", " << weight << ") " << endl;
	}

	const vector<pair<int, int>>& AdjList(int v) const
	{
		return edges[v];
	}

private:
	// Adjacency list representation of the graph
	vector<vector<pair<int, int>>> edges;
};

// Implement the output operator for Digraph ADT.
ostream& operator<< (ostream &os, const Graph& g)
{
	os << "Vertices: " << g.V << endl;
	os << "Edges: " << g.E << endl;

	for (int v = 0; v < g.V; v++)
	{
		os << v << ": ";
		const vector<pair<int, int>>& adj = g.AdjList(v);
		for (auto e : adj)
		{
			os << "(" << e.first << ", " << e.second << "), ";
		}
		os << endl;
	}
	return os;
}

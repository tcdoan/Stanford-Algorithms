#pragma once
struct Edge
{
	int v;
	int w;
	int cost;
	Edge(int v, int w, int cost) : v(v), w(w), cost(cost) {}
};

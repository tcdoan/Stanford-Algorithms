#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Lazy implementation of union-find with O(log n) guarantee for  
// both find() and union() operations.
class Uf
{
public:
	int count;
	// cid[v] is the component id of vertex v.
	vector<int> cid;

	// cc[v] count the size of component represented by v.
	vector<int> cc;

	// Initialize the UF data structure with V number of vertices
	Uf(int N) : count(N)
	{
		cid.resize(N);
		cc.resize(N);

		for (int v =0; v < N; v++)
		{
			cid[v] = v;
			cc[v] = 1;
		}
	}

	// find the component id, i.e. clustering id, of vertex v
	// guarantee to run in O(logn)
	int Find(int v)
	{
		while (cid[v] != v)
		{
			v = cid[v];
		}
		return v;
	}

	void Union(int v, int w)
	{
		int rootV = Find(v);
		int rootW = Find(w);
		if (rootV == rootW)	return;

		int sizeV = cc[rootV];
		int sizeW = cc[rootV];
		if (sizeV == sizeW)
		{
			cid[rootW] = rootV;
			cc[rootV] = cc[rootV] + 1;
		}
		else if (sizeV > sizeW)
		{
			cid[rootW] = rootV;
		}
		else
		{
			cid[rootV] = rootW;
		}
		count--;
	}

	int Clusters()
	{
		return count;
	}
};
#pragma once
#include <iostream>
#include <vector>

using namespace std;

// Lazy implementation of union-find with O(log n) guarantee for  
// both find() and union() operations.
class Uf
{
public:
	// cid[v] is the component id of vertex v.
	vector<uint64_t> cid;

	// cc[v] count the size of component represented by v.
	vector<uint64_t> cc;

	// Initialize the UF data structure with V number of vertices
	Uf(uint64_t V)
	{
		cid.resize(V + 1);
		cc.resize(V + 1);

		for (uint64_t v = 1; v < V + 1; v++)
		{
			cid[v] = v;
			cc[v] = 1;
		}
	}

	// find the component id, i.e. clustering id, of vertex v
	// guarantee to run in O(logn)
	uint64_t Find(uint64_t v)	
	{
		while (cid[v] != v)
		{
			v = cid[v];
		}
		return v;
	}

	void Union(uint64_t v, uint64_t w)
	{
		uint64_t rootV = Find(v);
		uint64_t rootW = Find(w);
		uint64_t sizeV = cc[rootV];
		uint64_t sizeW = cc[rootV];
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
	}
};
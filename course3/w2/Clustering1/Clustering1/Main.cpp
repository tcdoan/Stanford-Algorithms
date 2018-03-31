#include "union_find.h"
#include <fstream>
#include <tuple>
#include <algorithm>
#include <utility>

int main()
{
	ifstream ifs("D:\\repos\\algorithm\\course3\\w2\\clustering1.txt", ifstream::in);

	// number of vertices
	int V;
	ifs >> V;
	vector<tuple<int, int, int>> edges;

	while (ifs.eof()==false)
	{
		uint64_t v;
		uint64_t w;
		uint64_t cost;
		ifs >> v;
		ifs >> w;
		ifs >> cost;

		tuple<uint64_t, uint64_t, uint64_t> edge = make_tuple(v, w, cost);
		edges.emplace_back(edge);
	}

	sort
	(
		edges.begin(), 
		edges.end(), 
		[](const tuple<uint64_t, uint64_t, uint64_t>& a, const tuple<uint64_t, uint64_t, uint64_t>& b)
		{
			return get<2>(a) < get<2>(b);
		}
	);


	Uf uf(V);
	int components = V;
	int k = 4;
	for (int i = 0; i < edges.size(); i++)
	{
		const tuple<uint64_t, uint64_t, uint64_t>& e = edges[i];
		uint64_t v = get<0>(e);
		uint64_t w = get<1>(e);
		uint64_t cost = get<2>(e);
		if (uf.Find(v) != uf.Find(w))
		{
			if (components > 4)
			{
				uf.Union(v, w);
				components -= 1;
			}
			else if (components == 4)
			{
				cout << cost;
				return 0;
			}
		}
	}
}
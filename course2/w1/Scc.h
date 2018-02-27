#pragma once

// Type to compute strong connected components
//
#include "Digraph.h"
#include <stack>
#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <map>

using namespace std;

class Scc
{

public:
	Scc()	{}

	void FirstDfs(Digraph* reverse, stack<int>& reversePost)
	{
		vector<bool> marked(reverse->V);
		for (int v = reverse->V-1; v >= 0; v--)
		{
			if (!marked[v])
			{
				dfs(reverse, marked, v, reversePost);
			}
		}
	}

	// Compute the connected components cc
	int ComputeCC(Digraph* g, stack<int>& reversePost, vector<int>& cc)
	{
		vector<bool> visited(g->V);
		int ccCount = 1;
		while (!reversePost.empty())
		{
			int v = reversePost.top();
			reversePost.pop();
			if (!visited[v])
			{
				dfs(g, visited, cc, v, ccCount);
				ccCount++;
			}
		}
		return ccCount-1;
	}

	void printTop6CC(vector<int>& cc, int ccCount)
	{
		multimap<int, int> m;
		for (int v = 0; v < cc.size(); v++)
		{
			if (cc[v] > 0)
			{
				m.emplace(cc[v], v);
			}
		}

		vector<pair<int, size_t>> pairCounts;
		for (int ccid = 1; ccid <= ccCount; ccid++)
		{
			if (m.find(ccid) != m.end())
			{
				pairCounts.push_back(make_pair(ccid, m.count(ccid)));
			}
		}

		// sort in descending order
		sort(pairCounts.begin(), pairCounts.end(), [](auto &a, auto &b)
		{
			return b.second < a.second;
		});

		// print top 6;
		for (size_t i = 0; i < std::min((size_t)6, pairCounts.size()); i++)
		{
			cout << pairCounts[i].first << ": " << pairCounts[i].second << endl;
		}
	}

private:
	void dfs(Digraph* g, vector<bool>& explored, int v, stack<int>& reversePost)
	{
		explored[v] = true;
		for (int w : g->AdjList(v))
		{
			if (!explored[w])
			{
				dfs(g, explored, w, reversePost);
			}
		}
		reversePost.push(v);
	}

	void dfs(Digraph* g, vector<bool>& explored, vector<int>& cc, int v, int ccid)
	{
		explored[v] = true;
		cc[v] = ccid;
		for (int w : g->AdjList(v))
		{
			if (!explored[w])
			{
				dfs(g, explored, cc, w, ccid);
			}
		}
	}
};
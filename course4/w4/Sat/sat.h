#pragma once
#include <vector>
#include <stack>

using namespace std;

class Sat
{
public:
	int V;
	Sat(int V) : V(V) 
	{
		adj = vector<vector<int>>(V);
		adj2 = vector<vector<int>>(V);
		visited = vector<bool>(V);
		visited2 = vector<bool>(V);
		scc = vector<int>(V);
	};

	bool Satisfiable(int n, int m, const vector<int>& x, const vector<int>& y)
	{
		for (int i = 0; i<m; i++)
		{
			// Use n+x to denote -x
			// (x[i] or y[i]), AddEdge -x[i] -> y[i] AND -y[i] -> x[i]
			if (x[i]>0 && y[i]>0)
			{
				AddEdge(x[i] + n, y[i]);
				AddEdge(y[i] + n, x[i]);
			}
			else if (x[i]>0 && y[i]<0)
			{
				AddEdge(x[i] + n, n - y[i]);
				AddEdge(-y[i], x[i]);
			}
			else if (x[i]<0 && y[i]>0)
			{
				AddEdge(-x[i], y[i]);
				AddEdge(y[i] + n, n - x[i]);
			}
			else
			{
				AddEdge(-x[i], n - y[i]);
				AddEdge(-y[i], n - x[i]);
			}
		}

		// step 1 traverses original digraph
		for (int i = 1; i <= 2 * n; i++)
			if (!visited[i]) Dfs1(i);

		// step 2 traverses inversed digraph.
		while (!s.empty())
		{
			int n = s.top();
			s.pop();

			if (!visited2[n])
			{
				Dfs2(n);
				ccCount++;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			// check if (x, -x) in same SCC
			if (scc[i] == scc[i + n])
			{
				return false;
			}
		}

		// no (x, -x) exist in same SCC
		return true;
	}

private:
	vector<vector<int>> adj;
	vector<vector<int>> adj2;
	vector<bool> visited;
	vector<bool> visited2;
	stack<int> s;
	vector<int> scc;
	int ccCount = 1;

	// construct original and reverse digraphs
	void AddEdge(int a, int b)
	{
		adj[a].push_back(b);
		adj2[b].push_back(a);
	}

	// step 1 to compute SCC
	void Dfs1(int u)
	{
		if (visited[u])	return;
		visited[u] = true;

		for (int i = 0; i<adj[u].size(); i++)
			Dfs1(adj[u][i]);

		s.push(u);
	}

	// step 2 to compute SCC
	void Dfs2(int u)
	{
		if (visited2[u]) return;

		visited2[u] = true;

		for (int i = 0; i<adj2[u].size(); i++)
			Dfs2(adj2[u][i]);

		scc[u] = ccCount;
	}
};

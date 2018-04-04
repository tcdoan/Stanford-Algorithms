#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Code up the dynamic programming algorithm for computing a maximum-weight independent set of a path graph.
int main()
{
	// data file consisting of weights for path graph vertices
	ifstream ifs("D:\\repos\\algorithm\\course3\\w3\\mwis.txt", ifstream::in);
	int N;
	ifs >> N;

	// w[i] is the weight corresponding to vertex i. 
	vector<uint64_t> w;
	w.emplace_back(0);
	for (int i = 0; i < N; i++)
	{
		uint64_t x;
		ifs >> x;
		w.emplace_back(x);
	}

	// a[i] is the total maximum-weight independent set of path graph 1, 2, ..i.
	vector<uint64_t> a(N+1);
	a[0] = w[0];
	a[1] = w[1];

	for (int i = 2; i < N; i++)
	{
		a[i] = max(a[i - 1], a[i - 2] + w[i]);
	}

	vector<int> s;
	int i = N;
	while (i > 0)
	{
		if (i>1 && a[i - 1] >= a[i - 2] + w[i])
		{
			i--;
		}
		else
		{
			s.emplace_back(i);
			i -= 2;
		}
	}

	// Check if vertices 1, 2, 3, 4, 17, 117, 517, and 997 are part of the solution
	vector<int> idx({1, 2, 3, 4, 17, 117, 517, 997 });
	for (int v : idx)
	{
		if (find(s.begin(), s.end(), v) != s.end()) cout << "1";
		else cout << "0";
	}
	cout << endl;
}
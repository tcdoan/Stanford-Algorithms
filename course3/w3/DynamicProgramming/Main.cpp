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
	for (int i = 0; i < N; i++)
	{
		uint64_t x;
		ifs >> x;
		w.emplace_back(x);
	}

	// a[i] is the total maximum-weight independent set of path graph 1, 2, ..i.
	vector<uint64_t> a(N);
	a[0] = 0;
	a[1] = w[0];
	for (int i = 2; i < N; i++)
	{
		a[i] = max(a[i - 1], a[i - 2] + w[i]);
	}

	// s[i] indicates if vertex i is part of the solition.
	// I.e. s[i] = true -> i is part of the maximum-weight independent set.
	vector<bool> s(N);
	int i = N - 1;
	while (i > 1)
	{
		if (a[i - 1] >= a[i - 2] + w[i])
		{
			i = i - 1;
		}
		else
		{
			s[i] = true;
			i = i - 2;
		}
	}

	// Check if vertices 1, 2, 3, 4, 17, 117, 517, and 997 are part of the solution
	vector<int> idx({1, 2, 3, 4, 17, 117, 517, 997 });
	for (int k : idx)
	{
		if (s[k - 1]) cout << "1";
		else cout << "0";
	}
	cout << endl;
}
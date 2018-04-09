#include <iostream>
#include <fstream>
#include "item.h"
#include <vector>
#include <algorithm>

using namespace std;

// Implement knapsack algorithm and run it on knapsack1.txt data set
int main()
{
	ifstream ifs("C:\\repos\\algorithm\\course3\\w4\\knapsack1.txt");

	int capcity, N;
	ifs >> capcity;
	ifs >> N;

	vector<Item> items;
	for (int i = 0; i < N; i++)
	{
		int value, weight;
		ifs >> value;
		ifs >> weight;
		Item item(value, weight);
		items.emplace_back(item);
	}

	// solution stored in 2-d array a
	vector<vector<int64_t>> a(N+1);
	for (int i = 0; i <= N; i++)
	{
		a[i] = vector<int64_t>(capcity + 1);
	}

	for (int x = 0; x <= capcity; x++)
	{
		a[0][x] = 0;
	}

	for (int i = 1; i <= N; i++)
	{
		for (int x = 0; x <= capcity; x++)
		{
			if (x - items[i-1].weight >= 0)
			{
				a[i][x] = max(a[i-1][x], a[i-1][x-items[i-1].weight] + items[i-1].value);
			}
			else
			{
				a[i][x] = a[i-1][x];
			}
		}
	}

	cout << "Optimal value: " << a[N][capcity] <<endl;
}


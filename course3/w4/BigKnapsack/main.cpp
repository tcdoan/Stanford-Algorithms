#include <iostream>
#include <fstream>
#include "item.h"
#include <vector>
#include <algorithm>

using namespace std;

// Implement knapsack algorithm and run it on knapsack1.txt data set
int main()
{
	ifstream ifs("D:\\repos\\algorithm\\course3\\w4\\knapsack_big.txt");

	int W, N;
	ifs >> W; // capacity constraint
	ifs >> N; // max number of items

	vector<Item> items;
	Item zero(0, 0);
	items.emplace_back(zero);
	for (int i = 0; i < N; i++)
	{
		int value, weight;
		ifs >> value;
		ifs >> weight;
		Item item(value, weight);
		items.emplace_back(item);
	}

	// Previous optimal value indexed by weight 
	vector<int64_t> p(W + 1, 0UL);

	// Current optimal value indexed by weight 
	vector<int64_t> a(W + 1, 0UL);

	for (int i = 1; i <= N; i++)
	{
		for (int x = 0; x <= W; x++)
		{
			if (x - items[i].weight >= 0)
			{
				a[x] = max(p[x], p[x - items[i].weight] + items[i].value);
			}
			else
			{
				a[x] = p[x];
			}
		}
		p = a;
	}

	cout << "Optimal value: " << a[W] << endl;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Consider an instance of the optimal binary search tree problem with 7 keys(say 1, 2, 3, 4, 5, 6, 7 in sorted order) 
// and frequencies w1 = .05, w2 = .4, w3 = .08, w4 = .04, w5 = .1, w6 = .1, w7 = .23. 
// Compute the minimum, the possible average search time of a binary search tree with these keys.
int main()
{
	vector<double> weights{ 0, 0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23 };
	vector<vector<double>> a(8);
	for (int i = 0; i < 8; i++)
	{
		a[i] = vector<double>(8, 0.0);
		a[i][i] = weights[i];
	}

	for (int s = 0; s < 7; s++)
	{
		for (int i = 1; i <= 7; i++)
		{
			vector<double> sums;
			for (int r = i; r <= i + s; r++)
			{
				double sumW = 0.0;
				for (int k = i; k <= i + s; k++)
				{
					sumW = sumW +
						((k < 8) ? weights[k] : 0.0);
				}
				sumW = sumW + ((r < 9) ? a[i][r - 1] : 0.0)
					+ ((r < 7 && (i + s) < 8) ? a[r + 1][i + s] : 0.0);
				sums.emplace_back(sumW);
			}
			if ((i + s) < 8)
			{
				a[i][i + s] = (sums.size() == 0) ? 0 : (*min_element(sums.begin(), sums.end()));
			}
		}
	}
	cout << a[1][7] << endl;
}

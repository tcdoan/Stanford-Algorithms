#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <limits>
#include "city.h"
#include <math.h>
#include <string>

using namespace std;

// A recursive routine to generate n choose k combinations
void GenerateCombos(int n, int k, int st, vector<vector<int>>& combos, vector<int>& combo)
{
	if (k == 0)
	{

		combos.emplace_back(combo);
		return;
	}
	for (int i = st; i <= n - k + 1; i++)
	{
		combo.emplace_back(i);
		GenerateCombos(n, k - 1, i + 1, combos, combo);
		combo.pop_back();
	}
	return;
}

double dist(const vector<City>& cities, int k, int j)
{
	if (k < 1 || j < 1)
	{
		string s = "dist() error with j=" + to_string(j) + ", and k=" + to_string(k);
		throw runtime_error(s);
	}
	City cityK = cities[k];
	City cityJ = cities[j];
	return cityK.dist(cityJ);
}

vector<City> Read()
{
	ifstream ifs("D:\\repos\\algorithm\\course4\\w2\\tsp.txt", ifstream::in);
	int N;
	ifs >> N;

	vector<City> cities;
	City sentinel(0, 0);
	cities.emplace_back(sentinel);

	for (int i = 0; i < N; i++)
	{
		double x;
		double y;
		ifs >> x;
		ifs >> y;
		City city(x, y);
		cities.emplace_back(city);
	}
	return cities;
}

void addOne(vector<vector<int>>& combos)
{
	for (vector<int>& combo : combos)
	{
		combo.insert(combo.begin(), 1);
	}
}

int main()
{

	vector<City> cities = Read();
	int n = cities.size()-1;

	map<pair<vector<int>, int>, double> previous;
	map<pair<vector<int>, int>, double> current;

	// base case 
	for (int j = 1; j <= n; j++)
	{
		vector<int> s{ j };
		pair<vector<int>, int> p = make_pair(s, 1);
		if (j == 1)
		{
			previous[p] = 0;
		}
		else
		{
			previous[p] = numeric_limits<double>::infinity();
		}
	}

	for (int m = 2; m <= n; m++)
	{
		std::cout << "m = " << m << endl;
		vector<vector<int>> combos;
		vector<int> combo;
		GenerateCombos(n, m-1, 2, combos, combo);
		addOne(combos);
		for (auto s : combos)
		{
			for (int j : s)
			{
				if (j != 1)
				{
					double minDist = numeric_limits<double>::infinity();
					for (int k : s)
					{
						if (k != j)
						{
							vector<int> newS = s;
							newS.erase(remove(newS.begin(), newS.end(), j), newS.end());
							pair<vector<int>, int> p = make_pair(newS, k);
							if (((previous.find(p) != previous.end()) ? previous[p] + dist(cities, k, j) : numeric_limits<double>::infinity()) < minDist )
							{
								minDist =  previous[p] + dist(cities, k, j);
							}
						}
					}
					current[make_pair(s, j)] = minDist;					
				}
			}
		}
		//cout << m <<  endl;
		previous = current;
		current.clear();
	}

	double minDist = numeric_limits<double>::infinity();
	vector<int> s;
	for (int i = 1; i <= n; i++) s.emplace_back(i);

	for (int j = 2; j <= n; j++)
	{
		
		pair<vector<int>, int> p = make_pair(s, j);
		if (previous[p] + dist(cities, j, 1) < minDist)
		{
			minDist = previous[p] + dist(cities, j, 1);
		}
	}

	cout << "tsp dist  " << minDist << endl;
	return 0;
}

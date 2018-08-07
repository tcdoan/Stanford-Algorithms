#include "union_find.h"
#include <string>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <unordered_set>
#include <cmath>
#include <unordered_map>

using namespace std;
const int N = 24;

int main()
{
	ifstream ifs("D:\\repos\\algorithm\\course3\\w2\\clustering_big.txt", ifstream::in);
	int V;
	ifs >> V;
	
	string firstline, line;
	getline(ifs, firstline);

	unordered_set<int> numbers;
	for (int i = 0; i < V; i++)
	{
		getline(ifs, line);
		line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
		numbers.insert(stoi(line, nullptr, 2));
	}

	cout << "Done insertion." << endl;
	unordered_map<int, int> numToId;

	int Id = 0;
	for (int v : numbers)
	{
		numToId.emplace(v, Id++);
	}

	Uf uf(numbers.size());
	for (int x : numbers)
	{
		int v = numToId[x];
		for (int i = 0; i < N; i++)
		{			
			bitset<N> bits(x);
			int w = bits.flip(i).to_ulong();
			if (numbers.find(w) != numbers.end())
			{
				uf.Union(v, numToId[w]);
			}

			for (int j = i + 1; j < N; j++)
			{
				w = bits.flip(j).to_ulong();
				if (numbers.find(w) != numbers.end())
				{
					uf.Union(v, numToId[w]);
				}
				bits.flip(j);
			}
			bits.flip(i);
		}
	}

	cout <<  "Clusters: " << uf.Clusters() << endl;
}

#include "AllPairShortestPaths.h"

int main()
{
	vector<string> files = vector<string>{"D:\\repos\\algorithm\\course4\\w1\\g1.txt", "D:\\repos\\algorithm\\course4\\w1\\g2.txt", "D:\\repos\\algorithm\\course4\\w1\\g3.txt"};
	vector<bool> cycles = vector<bool>(files.size());
	vector<int> values = vector<int>(files.size());

	for (int i = 0; i < files.size(); i++)
	{
		string s = files[i];
		int shortestValue = numeric_limits<int>::max();
		bool isCicle = FindShortestShortestPath(s, &shortestValue);
		cycles[i] = isCicle;
		values[i] = shortestValue;
	}

	if (cycles[0] && cycles[1] && cycles[2])
	{
		cout << "NULL" << endl;
	}
	else
	{
		int shortestShortestValue = numeric_limits<int>::max();
		for (int i = 0; i < files.size(); i++)
		{
			if ((!cycles[i]) && (values[i] < shortestShortestValue))
			{
				shortestShortestValue = values[i];
			}
		}
		cout << "shortestShortestValue: " << shortestShortestValue << endl;
	}
}
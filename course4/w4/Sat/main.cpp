#include "sat.h""
#include <iostream>
#include <fstream>
#include <string>

int main()
{
	vector<string> fileNames{ "2sat1.txt", "2sat2.txt", "2sat3.txt", "2sat4.txt", "2sat5.txt", "2sat6.txt" };
	for (string s : fileNames)
	{
		string fileName = "D:\\repos\\algorithm\\course4\\w4\\";
		fileName = fileName + s;
		ifstream ifs(fileName, ifstream::in);
		int n;
		ifs >> n;
		int m = n;
		int x;
		int y;
		vector<int> xs;
		vector<int> ys;
		for (int i = 0; i < n; i++)
		{
			ifs >> x;
			ifs >> y;
			xs.emplace_back(x);
			ys.emplace_back(y);
		}

		Sat sat(2 * n + 1);
		if (sat.Satisfiable(n, m, xs, ys))
		{
			cout << fileName << " is satisfiable." << endl;
		}
		else
		{
			cout << fileName << " is not satisfiable." << endl;
		}
	}

	return 0;
}
#include "priority_queue.h"
#include <fstream>

int SumMedians(string fileName)
{
	auto MinPqCompare = [](int lhs, int rhs)
	{
		return lhs < rhs;
	};

	auto MaxPqCompare = [](int lhs, int rhs)
	{
		return lhs > rhs;
	};

	PriorityQueue minPq(MinPqCompare);
	PriorityQueue maxPq(MaxPqCompare);

	int median = 0;
	int sumMedians = 0;

	int x;
	ifstream input(fileName, ios::in);	
	while (input >> x)
	{
		if (maxPq.Size() == 0)
		{
			maxPq.Insert(x);
		}
		else
		{
			if (x <= maxPq.First())
			{
				maxPq.Insert(x);
			}
			else
			{
				minPq.Insert(x);
			}
		}

		if (maxPq.Size() > minPq.Size() + 1)
		{
			int tmp = maxPq.First();
			maxPq.Pop();
			minPq.Insert(tmp);
		}

		if (minPq.Size() > maxPq.Size())
		{
			int tmp = minPq.First();
			minPq.Pop();
			maxPq.Insert(tmp);
		}
		median = maxPq.First();
		sumMedians += median;
	}
	return sumMedians;
}

int main()
{
	int sumMedians = SumMedians("D:\\repos\\algorithm\\course2\\w3\\Median.txt");
	cout << sumMedians << " / " << (sumMedians % 10000) << endl;
}

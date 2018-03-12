#include <iostream>
#include <fstream>

#include <iterator>
#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

int main()
{
	ifstream fis("D:\\repos\\algorithm\\course2\\w4\\2sum.txt");
	istream_iterator<int64_t> inStreamIter(fis);
	istream_iterator<int64_t> eof;

	vector<int64_t> x;
	copy(inStreamIter, eof, back_inserter(x));


	unordered_map<int64_t, bool> y(1997213);
	for (const int64_t& e : x)
	{
		y[e] = true;
	}
	std::cout << "current load_factor: " << y.load_factor() << std::endl;

	int count = 0;
	for (int t = -10000; t <= 10000; t++)
	{
		for (const int64_t& e : x)
		{
			if (y.find(t - e) != y.end())
			{
				count++;
				break;
			}
		}
	}
	cout << count << endl;
}

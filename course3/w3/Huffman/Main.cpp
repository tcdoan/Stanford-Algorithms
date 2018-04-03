#include <iostream>
#include <fstream>
#include <algorithm>

#include "Huffman.h"

int main()
{
	ifstream ifs("D:\\repos\\algorithm\\course3\\w3\\huffman.txt", ifstream::in);
	int N;
	ifs >> N;

	vector<unsigned int> freq;
	for (int i = 0; i < N; i++)
	{
		unsigned int x;
		ifs >> x;
		freq.emplace_back(x);
	}

	Huffman trie(freq);
	vector<string> encodeTable = trie.EnCoding();
	sort
	(
		encodeTable.begin(),
		encodeTable.end(),
		[](const string& a, const string& b)
		{
			return a.size() < b.size();
		}
	);

	cout << "Shortest code: " << encodeTable[0] << ", Size: " << encodeTable[0].size() <<endl;
	cout << "Longest code : " << encodeTable[N-1] << ", Size: " << encodeTable[N-1].size() << endl;
}
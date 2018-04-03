#pragma once
using namespace std;

struct Node
{
	unsigned int ch;
	unsigned int freq;
	Node* left;
	Node* right;
	Node()
	{
		ch = 0;
		freq = 0;
		left = nullptr;
		right = nullptr;
	}
	Node(unsigned int ch, unsigned int freq) : ch(ch), freq(freq)
	{
		left = nullptr;
		right = nullptr;
	}
	Node(unsigned int ch, unsigned int freq, Node* left, Node* right) : ch(ch), freq(freq), left(left), right(right)
	{
	}

	bool IsLeaf()
	{
		return (left == nullptr && right == nullptr);
	}
};
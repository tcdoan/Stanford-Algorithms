#pragma once
#include <memory>
#include <map>
#include <vector>
#include "node.h"
#include "pq.h"
#include <string>

using namespace std;

// Build a huffman trie for compression
class Huffman
{
public:
	Huffman(const vector<unsigned int>& freq)
	{
		auto nodeComparator = [](Node* x, Node* y)
		{
			return x->freq < y->freq;
		};
		MinPq pq(nodeComparator);

		for (unsigned int i = 0; i < freq.size(); i++)
		{
			pq.Insert(new Node(i, freq[i]));
		}

		while (pq.Size() > 1)
		{
			Node* x = pq.ExtractMin();
			Node* y = pq.ExtractMin();
			Node* parent = new Node(0, x->freq + y->freq, x, y);
			pq.Insert(parent);
		}

		root = pq.ExtractMin();
		encoding.resize(freq.size());
		BuildEncodeTable(root, "");
	}

	vector<string> EnCoding()
	{
		return encoding;
	}

private:
	Node * root;
	vector<string> encoding;
	void BuildEncodeTable(Node* x, string s)
	{
		if (!x->IsLeaf())
		{
			BuildEncodeTable(x->left, s+'0');
			BuildEncodeTable(x->right, s+'1');
		}
		else
		{
			encoding[x->ch] = s;
		}
	}
};

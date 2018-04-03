#pragma once
#include "node.h"
#include <vector>
#include <functional>

class MinPq
{
public:
	MinPq(function<bool(Node*, Node*)> less) : less(less), n(0)
	{
		Node ignore;
		heap.push_back(&ignore);
	}

	int Size()
	{
		return n;
	}

	Node* Top()
	{
		return heap[1];
	}

	Node* ExtractMin()
	{
		Node* x = heap[1];
		Swap(1, n);
		n--;
		heap.pop_back();
		Sink(1);
		return x;
	}

	void Insert(Node* x)
	{
		heap.push_back(x);
		n++;
		SwimUp(n);
	}
private:
	function<bool(Node*, Node*)> less;
	int n;
	vector<Node*> heap;
	void SwimUp(int k)
	{
		while (k > 1 && less(heap[k], heap[k / 2]))
		{
			Swap(k, k / 2);
			k = k / 2;
		}
	}

	void Sink(int k)
	{
		while (2 * k <= n)
		{
			int j = 2 * k;
			if (j < n && less(heap[j + 1], heap[j])) j++;
			if (!(less(heap[j], heap[k]))) break;
			Swap(k, j);
			k = j;
		}
	}

	void Swap(int i, int j)
	{
		Node* temp = heap[i];
		heap[i] = heap[j];
		heap[j] = temp;
	}
};

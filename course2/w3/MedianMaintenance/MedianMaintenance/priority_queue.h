#pragma once
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

// Quick & dirty implementation of a priority queue
class PriorityQueue
{
public:
	PriorityQueue(function<bool(int, int)> c) : compare(c), n(0)
	{
		vec.push_back(0);
	}

	void Insert(int x)
	{
		vec.push_back(x);
		n++;
		SwimUp(n);
	}

	// return the first prioritized element
	// I.e. return MIN or MAX value depending on PriorityQueueType.
	int First()
	{
		return vec[1];
	}

	// Remove first element
	void Pop()
	{
		swap(vec[1], vec[n]);
		n--;
		vec.pop_back();
		FixDown(1);
	}

	int Size()
	{
		return n;
	}
private:
	vector<int> vec;
	int n;
	function<bool(int, int)> compare;

	// Swim up from node k to root.
	// Repeated swap elements to mainatin heap invariant.
	void SwimUp(int k)
	{
		while (k > 1 && compare(vec[k], vec[k / 2]))
		{
			swap(vec[k], vec[k / 2]);
			k = k / 2;
		}
	}

	// Fix the elements to satisfy heap invariant.
	void FixDown(int k)
	{
		while (2 * k <= n)
		{
			int j = 2 * k;
			if (j < n  && compare(vec[j + 1], vec[j])) j++;
			if (compare(vec[k], vec[j])) break;
			swap(vec[k], vec[j]);
			k = j;
		}
	}
};
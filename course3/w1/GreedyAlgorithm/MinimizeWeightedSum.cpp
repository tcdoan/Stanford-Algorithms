//Implement greedy algorithms to minimize the weighted sum of job completion times.
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "job.h"

using namespace std;

// Compute sum of weighted completion times of the resulting schedule
uint64_t SumWeightedCompletionTimes(const vector<Job>& jobs)
{
	uint64_t completionTime = 0UL;
	uint64_t sum = 0UL;
	for (const Job& job : jobs)
	{
		completionTime += job.length;
		sum += job.weight * completionTime;
	}
	return sum;
}

int main()
{
	ifstream ifs("D:\\repos\\algorithm\\course3\\w1\\jobs.txt", ifstream::in);
	int N;
	ifs >> N;

	vector<Job> jobs;
	for (int i = 0; i < N; i++)
	{
		int weight, length;
		ifs >> weight;
		ifs >> length;
		Job job(weight, length);
		jobs.emplace_back(job);
	}

	sort
	(
		jobs.begin(),
		jobs.end(),
		[](const Job& a, const Job& b)
	{
		if ((a.weight - a.length) == (b.weight - b.length))
		{
			return a.weight > b.weight;
		}
		return (a.weight - a.length) > (b.weight - b.length);
	}
	);

	cout << "Schedule jobs in decreasing order of the difference (weight - length). SumWeightedCompletionTimes:  " << SumWeightedCompletionTimes(jobs) << endl;

	sort
	(
		jobs.begin(),
		jobs.end(),
		[](const Job& a, const Job& b)
		{
			return static_cast<double>(a.weight) / a.length > static_cast<double>(b.weight) / b.length;
		}
	);

	cout << "Optimally schedule jobs in decreasing order of the ratio (weight/length). SumWeightedCompletionTimes:  " << SumWeightedCompletionTimes(jobs) << endl;
}
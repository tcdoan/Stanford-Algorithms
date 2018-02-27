#include "Digraph.h"
#include "Scc.h"

#include <string>
using namespace std;

void readFile(vector<int>& inputVec)
{
	string inputFileName{ "C:\\test\\SCC.txt" };
	ifstream fileInputStream(inputFileName);
	istream_iterator<unsigned int> start(fileInputStream), eos;
	vector<int> x(start, eos);
	inputVec = x;
}

int main()
{
	vector<int> inputVec;
	readFile(inputVec);

	Digraph* g = new Digraph(875715, inputVec);
	Scc scc;
	Digraph* rev = g->Reverse();

	stack<int> postOrder;
	scc.FirstDfs(rev, postOrder);

	vector<int> cc(g->V);
	int numCC = scc.ComputeCC(g, postOrder, cc);

	scc.printTop6CC(cc, numCC);
	return 0;
}

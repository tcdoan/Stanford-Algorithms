#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

size_t CountSplitInversions(vector<int> &a, vector<int> &aux, int lo, int mid,
                         int hi) {
  for (int k = lo; k <= hi; k++) {
    aux[k] = a[k];
  }

  int i = lo;
  int j = mid + 1;

  size_t inversions = 0;
  for (int k = lo; k <= hi; k++) {
    if (i > mid)
      a[k] = aux[j++];
    else if (j > hi)
      a[k] = aux[i++];
    else if (aux[j] < aux[i]) {
      inversions += (mid + 1 - i);
      a[k] = aux[j++];
    } else {
      a[k] = aux[i++];
    }
  }
  return inversions;
}

size_t SortAndCount(vector<int> &a, vector<int> &aux, int lo, int hi) {
  if (lo == hi) {
    return 0;
  }

  int mid = (hi - lo) / 2 + lo;

  size_t leftCount;
  size_t rightCount;
  size_t splitCount;

  leftCount = SortAndCount(a, aux, lo, mid);
  rightCount = SortAndCount(a, aux, mid + 1, hi);
  splitCount = CountSplitInversions(a, aux, lo, mid, hi);
  return leftCount + rightCount + splitCount;
}

int main() {
  ifstream fis("input.txt");
  vector<int> ints;
  istream_iterator<int> is(fis);
  istream_iterator<int> eof;
  std::copy(is, eof, back_inserter(ints));
  
  vector<int> aux(ints.size());

  size_t inversions;
  inversions = SortAndCount(ints, aux, 0, ints.size()-1);
  cout << "number of inversions " << inversions << endl;
}

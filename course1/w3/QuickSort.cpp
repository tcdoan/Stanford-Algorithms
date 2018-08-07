#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

enum class PIVOT : short { FIRST, LAST, MEDIAN };

int FindMedianIndex(vector<int> &a, int lo, int hi) {
  // middle entry index
  int mid = lo + (hi - lo) / 2;

  // median = max(min(a,b), min(max(a,b),c));
  int median = max(min(a[lo], a[mid]), min(max(a[lo], a[mid]), a[hi]));

  // median index;
  if (a[lo] == median)
    return lo;
  if (a[mid] == median)
    return mid;
  return hi;
}

int Partition(vector<int> &a, int lo, int hi, PIVOT pivotType) {
  // Pivot index is lo
  // Unless pivotType != PIVOT::FIRST
  if (pivotType == PIVOT::LAST) {
    swap(a[lo], a[hi]);
  }

  if (pivotType == PIVOT::MEDIAN) {
    int medIdx = FindMedianIndex(a, lo, hi);
    if (medIdx != lo)
      swap(a[lo], a[medIdx]);
  }

  int i = lo + 1;
  for (int j = lo + 1; j <= hi; j++) {
    if (a[j] < a[lo]) {
      swap(a[i], a[j]);
      i++;
    }
  }
  swap(a[lo], a[i - 1]);
  return i - 1;
}

// Returns number of comparisons this function does
int QuickSort(vector<int> &a, int lo, int hi, PIVOT pivotType) {
  // cout << "lo: " << lo << ", hi: " << hi << ", pivot type " << (short)
  // pivotType << endl;
  if (lo >= hi)
    return 0;

  int pivotIdx = Partition(a, lo, hi, pivotType);
  int comparisons = hi - lo;
  int leftComparisons = QuickSort(a, lo, pivotIdx - 1, pivotType);
  int rightComparisons = QuickSort(a, pivotIdx + 1, hi, pivotType);
  return comparisons + leftComparisons + rightComparisons;
}

int main() {
  ifstream fis("QuickSort.txt");
  vector<int> a1;
  vector<int> a2;
  vector<int> a3;
  istream_iterator<int> is(fis);
  istream_iterator<int> eof;
  copy(is, eof, back_inserter(a1));
  a2 = a1;
  a3 = a1;

  int a1Comparisons = QuickSort(a1, 0, a1.size() - 1, PIVOT::FIRST);
  int a2Comparisons = QuickSort(a2, 0, a2.size() - 1, PIVOT::LAST);
  int a3Comparisons = QuickSort(a3, 0, a3.size() - 1, PIVOT::MEDIAN);
  cout << "Number of comparisons: a1 = " << a1Comparisons
       << ", a2 = " << a2Comparisons << ", a3 =" << a3Comparisons << endl;
}

#include <bits/stdc++.h>
using namespace std;


vector<int> arr;


int Partition(vector<int> &arr, int low, int high) {
  arr[0] = arr[low];
  int pivot = low;
  while (low < high) {
    while (arr[0] < arr[high] && high > low) --high;
    arr[pivot] = arr[high];
    pivot = high;
    while (arr[0] > arr[low] && high > low) ++low;
    arr[pivot] = arr[low];
    pivot = low;
  }
  arr[pivot] = arr[0];
  return pivot;
}


void QSort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pivot = Partition(arr, low, high);
    QSort(arr, low, pivot - 1);
    QSort(arr, pivot + 1, high);
  }
}


int main() {
  int N;
  cin >> N;
  arr.push_back(0);
  for (int i = 0; i < N; ++i) {
    int elem; cin >> elem;
    arr.push_back(elem);
  }
  int low = 1, high = N;
  QSort(arr, low, high);
  for (int i = 1; i <= N; i++) {
    cout << arr[i] << ' ';
  }
  cout << endl;
  return 0;
}

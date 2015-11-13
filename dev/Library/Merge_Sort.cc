#include <bits/stdc++.h>
using namespace std;

vector<int> TMR;
void init(vector<int> &data) {
  int elem;
  data.push_back(0);
  while (cin >> elem) data.push_back(elem);
}

void Merge(vector<int> SP, vector<int> &MR, int s, int m, int t) {
  int j, k;
  for (k = s, j = m + 1; s <= m && j <= t; ++k) {
    if (SP[s] <= SP[j]) MR[k] = SP[s++];
    else MR[k] = SP[j++];
  }
  if (s <= m) {
    for (int i = s; i <= m; i++, k++) MR[k] = SP[i];
  }
  if (j <= t) {
    for (int i = j; i <= t; i++, k++) MR[k] = SP[i];
  }
}

void MSort(vector<int> SP, vector<int> &MR, int s, int t) {
  if (s == t) MR[s] = SP[s];
  else {
    int m;
    m = (s + t) / 2;
    MSort(SP, TMR, s, m);
    MSort(SP, TMR, m + 1, t);
    Merge(TMR, MR, s, m, t);
  }
}

int main(int argc, char * argv[]) {
  //cout << argc << endl;
  vector<int> data;
  init(data);
  TMR.resize(data.size());
  MSort(data, data, 1, data.size() - 1);
  for (int i = 1; i < data.size(); i++) cout << data[i] << ' ';
  cout << endl;
  return 0;
}

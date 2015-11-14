#include <bits/stdc++.h>
using namespace std;

vector<int> t_ordered;
void init(vector<int> &data) {
  int elem;
  data.push_back(0);
  while (cin >> elem) data.push_back(elem);
}

void Merge(vector<int> origin, vector<int> &temp, int l, int m, int u) {
  int k, j;
  for (k = l, j = m + 1; l <= m && j <= u; ++k) {
    if (origin[l] <= origin[j]) temp[k] = temp[l++];
    else temp[k] = origin[j++];
  }
  if (l <= m) {
    for (int i = l; i <= m; i++, k++) temp[k] = origin[i];
  }
  if (j <= u) {
    for (int i = j; i <= u; i++, k++) temp[k] = origin[i];
  }
}

void MSort(vector<int> origin, vector<int> &ordered, int l, int u) {
  if (l == u) ordered[l] = origin[l];
  else {
    int m;
    m = (l + u) / 2;
    MSort(origin, t_ordered, l, m);
    MSort(origin, t_ordered, m + 1, u);
    Merge(t_ordered, ordered, l, m, u);
  }
}

int main(int argc, char * argv[]) {
  //cout << argc << endl;
  vector<int> data;
  init(data);
  t_ordered.resize(data.size());
  MSort(data, data, 1, data.size() - 1);
  for (int i = 1; i < data.size(); i++) cout << data[i] << ' ';
  cout << endl;
  return 0;
}

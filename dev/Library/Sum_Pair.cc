#include <bits/stdc++.h>
using namespace std;

map<int, vector<int> > hash;

pair<int, bool> elem;
pair<int, int> out;

vector<pair<int, int> > res;

int store(const vector<pair<int, bool> > &arr, const int &sum) {
  for (int i = 0; i < arr.size(); i++) {
    int key = sum - arr[i].first;
    hash[key].push_back(i);
  }
  return 0;
}

int find(vector<pair<int, bool> > &arr, const int &sum) {
  for (int i = 0; i < arr.size(); i++) {
    if (hash[arr[i].first].size() != 0) {
      for (int j = 0; j < hash[arr[i].first].size(); j++) {
        if (!arr[hash[arr[i].first][j]].second) {
          arr[hash[arr[i].first][j]].second = 1;
          if (arr[i].second == 0) {
            arr[i].second = 1;
          } else {
            break;
          }
          out = make_pair(arr[i].first, arr[hash[arr[i].first][j]].first);
          res.push_back(out);
        }
      }
    }
  }
  return 0;
}

int main(int argc, char * argv[]) {
  vector<pair<int, bool> > arr;
  int sum;
  cin >> sum;
  int value;
  while (cin >> value) {
    elem = make_pair(value, 0);
    arr.push_back(elem);
  }
  store(arr, sum);
  find(arr,sum);
  for (int i = 0; i < res.size(); i++) {
    cout << res[i].first << ' ' << res[i].second << endl;
  }
  return 0;
}

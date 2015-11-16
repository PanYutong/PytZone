#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[]) {
  unordered_map<int, vector<string> > test;
  vector<string> res;
  res.push_back("pyt");
  test[1] = res;
  cout << test[1][0] << endl;

  return 0;
}

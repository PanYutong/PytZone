#include <bits/stdc++.h>
using namespace std;


int main(int argc, char * argv[]) {
  map<double, int> test;
  test[1.1] = 4;
  test[1.2] = 1.1;
  for (auto & it : test) cout << it.first << ' ' << it.second << endl;
  return 0;
}

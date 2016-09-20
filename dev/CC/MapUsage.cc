#include <bits/stdc++.h>
using namespace std;


int main(int argc, char * argv[]) {
  map<double, int> test;
  test[1.1] = 4;
  test[1.2] = 1.1;
  test[2.2] = 2.1;
  double a = 1.2;
  test[a++]++;
  for (auto& it : test) cout << it.first << ' ' << it.second << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[]) {
  size_t st = 'a';
  unsigned int ui = 2;
  long l = 1;
  long long ll = 2;
  vector<int> vsize;
  for (int i = 0; i < 100; ++i) vsize.push_back(i);
  cout << sizeof(st) << endl;
  cout << sizeof(ui) << endl;
  cout << sizeof(l) << endl;
  cout << sizeof(ll) << endl;
  cout << sizeof(vsize) << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;


int main(int argc, char * argv[]) {
  vector<int> * p = new vector<int>[3];
  int a = 0, b = 1, c = 2;
  p->push_back(a);
  p->push_back(b);
  p->push_back(c);
  cout << "p" << endl;
  delete p;
  for (int i = 0; i < p->size(); ++i) cout << (*p)[i] << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;


int main(int argc, char * argv[]) {
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> subi;
  for (int i = 0; i < 10; i++) {
    for (int j = i; j < 10; j++) {
      subi.push_back(a[j]);
      for (int k = 0; k < subi.size(); k++) {
        cout << subi[k];
      }
      cout << endl;
    }
    subi.clear();
  }

  return 0;
}

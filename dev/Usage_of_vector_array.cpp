#include <iostream>
#include <string>
#include <cstring>
#include <cfloat>
#include <climits>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;


int main(int argc, char * argv[]) {
  vector < vector <bool> > haha[100];
  for (int i = 0; i < 100; i++) {
    haha[i].resize(100);
    for (int j = 0; j < 100; j++) {
      haha[i][j].resize(100);
    }
  }
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      for (int k = 0; k < 100; k++) {
        cout << haha[i][j][k] << endl;
      }
    }
  }
  
  return 0;
}

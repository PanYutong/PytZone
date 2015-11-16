#include <bits/stdc++.h>
using namespace std;

const long long inf = 1LL << 62;

const int intinf = 1 << 30;

typedef long long ll;

long long Add(int a, int b) {
  char * c = (char *)a;
  return (long long)&c[b];
}

int main (int argc, char * argv[]) {
  int a = 5, b = 10;
  cout << Add(a, b) << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

double change_root(double N) {
  return log10(N) / log10(2);
}

int main(int argc, char * argv[]) {
  char p = '+';
  int maxPowerOf3 = (int)pow(3, (int)(log10(0x7fffffff) / log10(3)));
  printf("%d\n", maxPowerOf3);
  printf("%d\n", 0x7fffffff);
  return 0;
}

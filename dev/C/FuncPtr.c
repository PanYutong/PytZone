//#include <bits/stdc++.h>
//using namespace std;
#include <stdio.h>

int main(int argc, char * argv[]) {
  int max(int a, int b);
  int (*p)(int ,int);
  p = max;
  int a = 1, b = 2;
  max(a, b);
  printf("p is %p, max is %p, &max is %p, max is %p\n",
      *p, *max, &max, max);
  return 0;
}

int max(int a, int b) {
  return 0;
}

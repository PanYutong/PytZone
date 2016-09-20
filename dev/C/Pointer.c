//#include <bits/stdc++.h>
//using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
  int* i = (int*)malloc(sizeof(int) * 10);
  int* j = i;
  j += 1;
  printf("i = %d, j = %d\n", i, j);
  return 0;
}

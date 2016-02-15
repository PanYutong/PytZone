//#include <bits/stdc++.h>
//using namespace std;
#include <stdio.h>

int main(int argc, char * argv[]) {
  int a = 0;
  int *b = &a;
  float c = 0;
  printf("int a is %ld\npointer b is %ld\nfloat c is %ld\n",
         sizeof(a), sizeof(b), sizeof(c));
  return 0;
}

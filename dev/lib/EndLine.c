//#include <bits/stdc++.h>
//using namespace std;
#include <stdio.h>

int main(int argc, char * argv[]) {
  printf("%d\n", argc);
  int j;
  for (j = 0; j < argc; ++j)
    printf("%s\n", argv[j]);
  char a[100];
  int i = 0;
  while (scanf("%c", &a[i]) != EOF) {
    if (a[i] != '\n')
      printf("%c", a[i]);
    ++i;
  }
  return 0;
}

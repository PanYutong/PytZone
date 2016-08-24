//#include <bits/stdc++.h>
//using namespace std;
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  char* str = (char*)malloc(10);
  int i = 0;
  str[0] = 'a';
  str[1] = 'b';
  str[2] = ' ';
  str[3] = 'c';
  char* str1 = (char*)malloc(10);
  for (; str[i]; ++i) printf("%c", str[i]);
  if (str[i] == '\0') printf("%c", 'Y');
  printf("%d", atoi(str1));
  printf("\n");
  char* num = "01";
  printf("num = %d\n", atoi(num));
  char* num1 = "1";
  printf("num1 = %d\n", atoi(num1));
  return 0;
}

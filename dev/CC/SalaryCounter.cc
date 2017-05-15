#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[]) {
  float monthly = 0.0;
  float sum = 0.0;
  int month = 0;
  while (cin >> monthly) {
    printf("Monthly: %f\n", monthly);
    sum += monthly;
    ++month;
  }
  printf("Sum: %f\n", sum);
  printf("Averrage: %f\n", sum / month);
  return 0;
}

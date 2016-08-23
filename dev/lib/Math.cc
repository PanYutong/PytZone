#include <bits/stdc++.h>
using namespace std;

double change_root(double N) {
  return log10(N) / log10(2);
}

int main(int argc, char * argv[]) {
  cout << 0.2 * -1 * change_root(0.2) + 0.5 * -1 * change_root(0.5)
    + 0.3 * -1 * change_root(0.3) << endl;
  return 0;
}

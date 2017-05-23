#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[]) {
  string test = "May the best fortune with you";
  size_t pos = test.find_first_not_of("May");
  cout << test.substr(pos, 5) << endl;

  string a1 = "GOOGLENET";

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    string addBinary(string a, string b) {
      int carry = 0, i = a.size() - 1, j = b.size() - 1;
      string ret;
      while (i >= 0 || j >= 0 || carry == 1) {
        carry += i >= 0? a[i--] - '0' : 0;
        carry += j >= 0? b[j--] - '0' : 0;
        ret = (char)(carry % 2 + '0') + ret;
        carry /= 2;
      }
      return ret;
    }
};

int main(int argc, char * argv[]) {
  char a, b;
  int c = 100;
  a = (char)48;
  cout << "a = " << a << endl;
  return 0;
}

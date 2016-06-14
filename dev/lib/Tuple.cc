#include <bits/stdc++.h>
using namespace std;


int main(int argc, char * argv[]) {
  tuple<int, int, int> cor_p;
  cor_p = make_tuple(1, 2, 3);
  cout << get<0>(cor_p) << endl;
  cout << get<1>(cor_p) << endl;
  cout << get<2>(cor_p) << endl;
  return 0;
}

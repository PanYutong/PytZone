#include <bits/stdc++.h>
using namespace std;

const long long inf = 1LL << 62;

typedef long long ll;

class Trie {
 public:
  static const int MaxN_ = 100 * 100;
  static const int ChildMax_ = 100;
  int size;
  int trie[MaxN_][ChildMax_];

  Trie(const char * s) {
    memset(trie[0], -1, sizeof(trie[0]));
    size = 1;
    while(*s) {
      insert(s);
      ++s;
    }
  }

  void insert(const char * s) {
    int p = 0;
    while(*s) {
      int i = *s - 'A';
      if (-1 == trie[p][i]) {
        memset(trie[size], -1, sizeof(trie[size]));
        trie[p][i] = size++;
      }
      p = trie[p][i];
      ++s;
    }
  }

  bool search(const char * s) {
    int p = 0;
    while(*s) {
      int i = *s - 'A';
      if (trie[p][i] == -1) return false;
      p = trie[p][i];
      ++s;
    }
    return true;
  }
};

int main (int argc, char * argv[]) {
  string in;
  cin >> in;
  Trie tree(in.c_str());
  string pattern;
  cin >> pattern;
  int n = pattern.size();
  string substr;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      substr += pattern[j];
      cout<<tree.search(substr.c_str())<< ' ' << substr << endl;
    }
    substr.clear();
  }
  return 0;
}

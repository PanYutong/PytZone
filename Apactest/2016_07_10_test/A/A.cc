#include <bits/stdc++.h>
using namespace std;

string leader_decision(vector<string> &can);

int main(int argc, char * argv[]) {
  int case_num = 0;
  cin >> case_num;
  for (int cs = 1; cs <= case_num; ++cs) {
    int name_num = 0;
    scanf("%d ", &name_num);
    int different_alpha = 0;
    int max = 0;
    vector<string> candidates;
    bool bucket[26];
    for (int j = 0; j < 26; ++j) bucket[j] = 0;
    for (int nn = 0; nn < name_num; ++nn) {
      string name;
      getline(cin, name);
      for (int i = 0; i < name.size(); ++i) {
        if (name[i] == ' ') continue;
        if (bucket[(int)name[i] - 65] == 0) {
          bucket[(int)name[i] - 65] = 1;
          ++different_alpha;
        }
      }
      if (different_alpha > max) {
        max = different_alpha;
        candidates.clear();
        candidates.push_back(name);
      } else if (different_alpha == max) {
        candidates.push_back(name);
      } else {
        // do nothing
      }
      for (int j = 0; j < 26; ++j) bucket[j] = 0;
      different_alpha = 0;
    }
    string leader;
    leader = leader_decision(candidates);

    cout << "Case #" << cs << ": " << leader << endl;
  }
  return 0;
}

string leader_decision(vector<string> &can) {
  if (can.size() == 1) {
    return can[0];
  } else {
    sort(can.begin(), can.end());
    return can[0];
  }
}

#include <bits/stdc++.h>
using namespace std;


vector<vector<int> > graph;
vector<vector<int> > gprim;
vector<pair<int, bool> > origin;
int N;
pair<int, int> loc;
const int inf = 1 << 30;


void InitGraph() {
  graph.resize(N);
  gprim.resize(N);
  origin.clear();
  for (int i = 0; i < N; i++) {
    pair<int, bool> insert;
    insert.first = i;
    insert.second = 0;
    origin.push_back(insert);
  }
  for (int i = 0; i < N; i++) {
    graph[i].resize(N);
    gprim[i].resize(N);
  }
  int x, y, dist;
  while(cin >> x) {
    cin >> y >> dist;
    graph[x][y] = graph[y][x] = dist;
  }
  int min = inf;
  origin[0].second = 1;
  for (int i = 0; i < N; i++) {
    if (graph[0][i] != 0 && graph[0][i] < min) {
      min = graph[0][i];
      loc.first = 0; loc.second = i;
    }
  }
  if (min != inf) {
    graph[loc.first][loc.second] = 0; graph[loc.second][loc.first] = 0;
    gprim[loc.first][loc.second] = min; gprim[loc.second][loc.first] = min;
    origin[loc.second].second = 1;
  }
}


void Prim() {
  int size = 1;
  while (size < origin.size()) {
    ++size;
    int min = inf;
    for (int i = 0; i < N; i++) {
      if (origin[i].second) {
        for (int j = 0; j < N; j++) {
          if (origin[j].second) continue;
          if (graph[i][j] != 0 && graph[i][j] < min) {
            min = graph[i][j];
            loc.first = i; loc.second = j;
          }
        }
      }
    }
    if (min != inf) {
      graph[loc.first][loc.second] = graph[loc.second][loc.first] = 0;
      gprim[loc.first][loc.second] = gprim[loc.second][loc.first] = min;
      origin[loc.first].second = origin[loc.second].second = 1;
    }
  }
}
int main() {
  //test for google interview
  cin >> N;
  InitGraph();
  Prim();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << gprim[i][j] << ' ';
    }
    cout << endl;
  }
  return 0;
}

#include <iostream>
#include <string>
#include <cstring>
#include <cfloat>
#include <climits>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int T;
int P;

int main(int argc, char * argv[]) {
  scanf("%d%d", &T, &P);
  vector < vector <double> > graph(T, vector<double>(T));

  //initiate graph
  for (int i = 0; i < T; i++) {
    for (int j = 0; j < T; j++) {
      if (j == i) {
        graph[i][j] = 0;
      } else {
        graph[i][j] = DBL_MAX;
      }
    }
  }

  //define distance between cities
  for (int i = 0; i < P; i++) {
    int x = 0, y = 0;
    double dist = 0;
    cin >> x >> y >> dist;
    graph[x][y] = dist;
  }

  //initiate Floyd Parameters
  vector < vector <double> > min_dist(T, vector<double>(T));
  vector < vector < vector <bool> > > path(T, vector < vector <bool> >(T, vector<bool>(T)));
  for (int v = 0; v < T; v++) {
    for (int w = 0; w < T; w++) {
      min_dist[v][w] = graph[v][w];
      for (int u = 0; u < T; u++) {
        path[v][w][u] = 0;
      }
      if (min_dist[v][w] < DBL_MAX) {
        path[v][w][w] = 1;
        path[v][w][v] = 1;
      }
    }
  }

  //begin Floyd
  for (int u = 0; u < T; u++) {
    for (int v = 0; v < T; v++) {
      for (int w = 0; w < T; w++) {
        if (min_dist[v][u] + min_dist[u][w] < min_dist[v][w]) {
          min_dist[v][w] = min_dist[v][u] + min_dist[u][w];
          for (int i = 0; i < T; i++) {
            path[v][w][i] = path[v][u][i] || path[u][w][i];
          }
        }
      }
    }
  }
  for (int i = 0; i < T; i++) {
    for (int j = 0; j < T; j++) {
      if (min_dist[i][j] < DBL_MAX) {
        printf("shortest path from %d to %d is %lf\n", i, j, min_dist[i][j]);
      } else {
        printf("shortest path from %d to %d is %d\n", i, j, -1);
      }
    }
  }
  return 0;
}

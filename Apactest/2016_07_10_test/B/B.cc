#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int> > Matr;

bool depthfs(int i, int j, Matr height, Matr &full,
    vector<pair<int, int> > &loc);

int Row = 0, Col = 0;
Matr visit;

int minimum = 9999;

int go[4][2] = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};

int main(int argc, char * argv[]) {
  int case_num = 0;
  cin >> case_num;
  for (int cs = 1; cs <= case_num; ++cs) {
    scanf("%d %d ", &Row, &Col);
    Matr height(Row, vector<int>(Col));
    Matr full(Row, vector<int>(Col));
    visit.resize(Row);
    for (int v_re = 0; v_re < Row; ++v_re) {
      visit[v_re].resize(Col);
    }
    for (int i = 0; i < Row; ++i) {
      for (int j = 0; j < Col; ++j) {
        cin >> height[i][j];
      }
    }

    int height_inc = 0;

    int loop_CD = 0;
    while (loop_CD < 10) {
      for (int i = 1; i < Row - 1; ++i) {
        for (int j = 1; j < Col - 1; ++j) {
          vector<pair<int, int> > loc;
          if (!full[i][j]) {
            minimum = 9999;
            depthfs(i, j, height, full, loc);
            for (int visit_rex = 0; visit_rex < Row; ++visit_rex) {
              for (int visit_rey = 0; visit_rey < Col; ++visit_rey) {
                visit[visit_rex][visit_rey] = 0;
              }
            }
          }
          if (loc.size() > 0) {
            for (int x = 0; x < loc.size(); ++x) {
              int inc = minimum - height[loc[x].first][loc[x].second];
              height_inc += inc;
              height[loc[x].first][loc[x].second] = minimum;
            }
          }
        }
      }
      ++loop_CD;
    }
    printf("Case #%d: %d\n", cs, height_inc);
  }
  return 0;
}

bool depthfs(int i, int j, Matr height, Matr &full,
    vector<pair<int, int> > &loc) {
  if (!visit[i][j]) {
    loc.push_back(make_pair(i, j));
    visit[i][j] = 1;
    for (int dir = 0; dir < 4; ++dir) {
      int x = i + go[dir][0];
      int y = j + go[dir][1];
      if (height[x][y] == height[i][j]) {
        if (!full[x][y] && x > 0 && x < Row - 1 && y > 0 && y < Col - 1) {
          if (!depthfs(x, y, height, full, loc)) return 0;
        } else {
          for (int iter = 0; iter < loc.size(); ++iter)
            full[loc[iter].first][loc[iter].second] = 1;
          loc.clear();
          return 0;
        }
      } else if (height[x][y] < height[i][j]) {
        if (!full[x][y] && x > 0 && x < Row - 1 && y > 0 && y < Col - 1) {
          loc.clear();
          return 0;
        } else {
          for (int iter = 0; iter < loc.size(); ++iter)
            full[loc[iter].first][loc[iter].second] = 1;
          loc.clear();
          return 0;
        }
      } else {
        if (height[x][y] < minimum) minimum = height[x][y];
      }
    }
  }
  return 1;
}

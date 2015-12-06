#include <bits/stdc++.h>
#define N 92
bool R[N][N], D[N][N], v[N][N];
int m, n;

void dfs(int r, int c) {
  int d = rand() % 4, dd = rand()%2 ? 1 : 3;
  v[r][c] = true;
  for (int i = 0; i < 4; i++) {
    int rr = r + (int[]){-1,0,1,0}[d],
        cc = c + (int[]){0,-1,0,1}[d];
    if ((unsigned)rr < m && (unsigned)cc < n && ! v[rr][cc]) {
      if (d % 2)
        R[r][c - (d == 1)] = true;
      else
        D[r - (d == 0)][c] = true;
      dfs(rr, cc);
    }
    d = (d + dd) % 4;
  }
}

int main() {
  scanf("%d%d", &m, &n);
  dfs(0, 0);
  for (int c = 0; c < n; c++)
    printf("._");
  printf(".\n");
  for (int r = 0; r < m; r++) {
    printf("|");
    for (int c = 0; c < n; c++) {
      putchar(D[r][c] ? ' ' : '_');
      putchar(R[r][c] ? '.' : '|');
    }
    printf("\n");
  }
}

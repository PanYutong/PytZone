#include <bits/stdc++.h>
using namespace std;

int R,C;
char board[101][101];
bool used[101][101];
int go[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
void dfs(int x,int y){
  used[x][y] = true;
  for(int k=0; k<4; ++k){
    int nx = x + go[k][0];
    int ny = y + go[k][1];
    if(nx>=0&&nx<R && ny>=0&&ny<C && board[nx][ny]=='1' && used[nx][ny]==false)
      dfs(nx,ny);
  }
}
int query(){
  for(int i=0; i<R; ++i)
    for(int j=0; j<C; ++j)
      used[i][j] = false;
  int cnt = 0;
  for(int i=0; i<R; ++i)
    for(int j=0; j<C; ++j)
      if( board[i][j]=='1' && used[i][j] == false){
        cnt++;
        dfs(i,j);
      }

  return cnt;
}
int main(int argc, const char * argv[]) {
  int T,ca=1;
  scanf("%d",&T);
  while(T--){
    scanf("%d%d",&R,&C);
    printf("Case #%d:\n",ca++);
    for(int i=0; i<R; ++i)
      scanf("%s",board[i]);

    int N;
    scanf("%d",&N);
    while(N--){
      char op[5];
      scanf("%s",op);
      if(op[0]=='Q'){
        printf("%d\n",query());
      }
      else{
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        board[x][y] = '0'+z;
      }
    }
  }
  return 0;
}

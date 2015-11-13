#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 1005;
int N,M,Q,V[MAXM],P[MAXN],H[MAXN];

void init(){
  scanf("%d%d%d",&N,&M,&Q);
  for(int i=0; i<M; ++i)
    scanf("%d",&V[i]);

  for(int i=0; i<N; ++i)
    scanf("%d%d",&P[i],&H[i]);
}

int getTime(int p,int v){
  if(p==0) return 0;
  if(v==0) return -1;
  if(p*v>0) return -1;
  int t = p*-1;
  if(t%v==0) return t/v;
  else return t/v + 1;
}

bool check(int m){
  //printf("m=%d\n",m);
  int sumQ = 0;
  for(int i=0; i<N; ++i){
    int t = MAXM+1;
    int j1=0;
    while( H[i]+j1<M ){
      if( getTime(P[i], V[H[i]+j1])!=-1 && getTime(P[i], V[H[i]+j1])<= m ){
        t = min(t,j1);
        break;
      }
      j1++;
    }
    int j2=0;
    while( H[i]-j2>=0 ){
      if( getTime(P[i], V[H[i]-j2])!=-1 && getTime(P[i], V[H[i]-j2]) <=m ){
        t = min(t,j2);
        break;
      }
      j2++;
    }
    //printf("t=%d\n",t);
    if(t>MAXM) return false;
    sumQ += t;
  }
  if(sumQ>Q) return false;
  return true;
}

int main(int argc, const char * argv[]) {
  int T, _case=1;
  scanf("%d",&T);
  while(T--){
    init();
    int l=0, m , r=10000*N;
    int ans = -1;
    while(l<=r){
      m = (l+r)/2;
      if(check(m)){
        ans = m;
        r = m-1;
      } else {
        l = m+1;
      }
    }

    //bool t = check(2);
    if(ans==-1)
      printf("Case #%d: IMPOSSIBLE\n",_case++);
    else
      printf("Case #%d: %d\n",_case++,ans);
  }
  return 0;
}

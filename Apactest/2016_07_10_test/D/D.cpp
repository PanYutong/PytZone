#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>
#include <complex>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <cassert>
#define un using namespace
un std;
#define pb push_back
#define pf pop_front

#define mp make_pair

#define c0 first
#define c1 second
#define sqr(x) ((x)*(x))
#define clr(x) memset(x, 0, sizeof(x))
#define clr1(x) memset(x, -1, sizeof(x))
#define clr80(x) memset(x, 0x80, sizeof(x))
#define clr7F(x) memset(x, 0x7F, sizeof(x))

#define LL long long
#ifdef __unix__
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif
#define pii pair<int, int>
#define pip pair<int, pii>
#define vi vector<int>
#define vpi vector<pii>
#define pq priority_queue

template<typename T>
inline bool chkmin(T &a, T b){return a > b ? a = b, 1 : 0;}
template<typename T>
inline bool chkmax(T &a, T b){return a < b ? a = b, 1 : 0;}

#define P 1000000007


#define getint(x){\
	char __next__char__;bool __nega__int__=0;\
	while(!isdigit(__next__char__=getchar())&&__next__char__!='-');\
	__next__char__=='-'?(x=0,__nega__int__=1):(x=__next__char__-48);\
	while(isdigit(__next__char__=getchar()))x=x*10+__next__char__-48;\
	if(__nega__int__)x=-x;\
}
#define getint2(x1,x2){getint(x1);getint(x2);}
#define getint3(x1,x2,x3){getint(x1);getint(x2);getint(x3);}
#define getint4(x1,x2,x3,x4){getint(x1);getint(x2);getint(x3);getint(x4);}
#define getint5(x1,x2,x3,x4,x5){getint(x1);getint(x2);getint(x3);getint(x4);getint(x5);}
#define getint6(x1,x2,x3,x4,x5,x6){getint(x1);getint(x2);getint(x3);getint(x4);getint(x5);getint(x6);}

int k[12], l[12], a[12][10], c[12][10], m;
LL ans;
map<int, LL> lans, rans;
void dfs(int id, int u, LL v, vector<int> &x, map<int, LL> &xans) {
	if (id == 4) {
		xans[u] = max(xans[u], v);
		return;
	}
	int now = x[id];
	for (int i = 0; i < k[now]; i++) {
		dfs(id + 1, u, v + a[now][i], x, xans);
		u += c[now][i];
		if (u > m)
			return;
	}
}
void solve(vector<int> &x, map<int, LL> &xans) {
	xans.clear();
	dfs(0, 0, 0, x, xans);
	for (map<int, LL>::iterator it = xans.begin(); it != xans.end(); it++) {
		while (1) {
			map<int, LL>::iterator nit = it;
			nit++;
			if (nit == xans.end())
				break;
			if (nit->c1 <= it->c1)
				xans.erase(nit);
			else
				break;
		}
	}
}
LL solve() {
	int n;
	getint2(m, n);
	ans = 0;
	for(int i = 0; i < n; i++) {
		getint2(k[i], l[i]);
		k[i] = k[i] - l[i] + 1;
		for (int j = 0; j < l[i] - 1; j++) {
			int x;
			getint(x);
		}
		for (int j = 0; j < k[i]; j++) {
			getint(a[i][j]);
		}
		for (int j = 0; j < l[i] - 1; j++) {
			int x;
			getint(x);
		}
		for (int j = 0; j < k[i] - 1; j++) {
			getint(c[i][j]);
		}
	}
	for (int i = 0; i < (1 << n); i++) {
		if (__builtin_popcount(i) != 8)
			continue;
		int s = i;
		vector<int> l, r;
		for (int j = 0; j < n; j++) {
			if (s & 1) {
				if (l.size() != 4)
					l.pb(j);
				else
					r.pb(j);
			}
			s >>= 1;
		}
		solve(l, lans);
		solve(r, rans);
		if (rans.empty())
			continue;
		for (map<int, LL>::iterator it = lans.begin(); it != lans.end(); it++) {
			if (m - it->c0 < 0)
				break;
			map<int, LL>::iterator rit = rans.upper_bound(m - it->c0);
			if (rit == rans.begin())
				break;
			rit--;
			chkmax(ans, it->c1 + rit->c1);
		}
	}
	return ans;
}

int main() {
	int T;
	getint(T);
	for (int _ = 1; _ <= T; _++) {
		printf("Case #%d: %lld\n", _, solve());
	}
	return 0;
}

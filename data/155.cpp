#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <stack>
#include <cassert>

#define pb push_back
#define mp make_pair
#define PI 3.1415926535897932384626433832795
#define sqr(x) (x)*(x)
#define forn(i, n) for(int i = 0; i < n; ++i)
#define ALL(x) x.begin(), x.end()
#define sz(x) int((x).size())
#define X irst
#define Y second
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;
typedef pair<int,int> pii;
const int INF = 2147483647;
const ll LLINF = 9223372036854775807LL;
const int maxn = 200010;
int z[maxn];
int t[maxn];
int can[maxn];
int what[maxn];
int tmax[maxn*2];
int n;
void build(int v, int L, int R) {
	if (L==R) tmax[v] = z[L]+L;
	else {
		int m = (L+R)>>1;
		build(v+v+1,L,m);
		build(v+v+2,m+1,R);
		tmax[v]=max(tmax[v+v+1],tmax[v+v+2]);
	}
}
int findpos(int v, int val, int L, int R) {
	if (L==R) {
		if (tmax[v] >= val) return L;
		else return n;
	} else {
		int m = (L+R)>>1;
		if (tmax[v+v+1] >= val) return findpos(v+v+1,val,L,m);
		else return findpos(v+v+2,val,m+1,R);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	string s; cin >> s;
	int l = -1;
	int r = -1;
	n = sz(s);
	for (int i = 0; i < n; ++i) {
		if (i<=r) t[i] = min(r-i+1,t[l+r-i]);
		while (i-t[i]>=0 && i+t[i]<n && s[i+t[i]]==s[i-t[i]]) ++t[i];
		if (i+t[i]-1>r) l = i-t[i]+1, r = i+t[i]-1;
	}
	string p = s;
	reverse(ALL(p));
	p += "#"+s;
	z[0] = 0;
	l = r = -1;
	for (int i = 1; i < sz(p); ++i) {
		if (i<=r) z[i] = min(r-i+1,z[i-l]);
		while (i+z[i]<sz(p) && p[i+z[i]] == p[z[i]]) ++z[i];
		if (i+z[i]-1 > r) l = i, r = i+z[i]-1;
	}
	for (int i = 0; i < n; ++i) z[i] = z[i+n+1];
	for (int i = 0; i < n; ++i) {
		if (i && can[i] < can[i-1]) can[i] = can[i-1], what[i] = what[i-1];
		if (can[i+z[i]] < z[i]) {
			can[i+z[i]] = z[i];
			what[i+z[i]] = i;
		}
	}
	build(0,0,n-1);
	for (int i = 0; i < n; ++i) {
		int pos = findpos(0,i,0,n-1);
		if (pos < i && can[i] < i-pos) {
			can[i] = i-pos;
			what[i] = pos;
		}
	}
	int bestm = -1;
	int bestl = -1;
	int bestlen = -1;
	int bestval = -1;
	for (int i = 0; i < n; ++i) {
		int lpos = i-t[i]+1;
		int rpos = i+t[i]-1;
		int tcan = can[lpos];
		tcan = min(tcan, n-1-rpos);
		int curans = t[i]*2-1+tcan*2;
		if (curans > bestval) {
			bestval = curans;
			bestm = i;
			bestl = what[lpos];
			bestlen = tcan;
		}
	}
	if (bestlen == 0) printf("1\n%d %d\n", bestm-t[bestm]+1+1,t[bestm]*2-1);
	else printf("3\n%d %d\n%d %d\n%d %d\n", bestl+1,bestlen,bestm-t[bestm]+1+1,t[bestm]*2-1,n-1-bestlen+1+1,bestlen);
	return 0;
}
#include <cstdio>
#include <cstring>
#include <algorithm>

#define FOR(i,a,b) for (int i=a; i<=b; ++i)

const int maxn = 100010;

int n, m = 0, ans = 0, 
	pi[maxn], leftMost[maxn], r[maxn], g[maxn], L[3], R[3];
char s[maxn], rev[maxn];

void KMP()
{
	int p = pi[1] = 0;
	FOR(i, 2, n) {
		while (p && rev[p+1] != rev[i])  p = pi[p];
		if (rev[p+1] == rev[i])  ++p;
		pi[i] = p;
	}
	
	p = 0;
	FOR(i, 1, n) {
		while (p && rev[p+1] != s[i])  p = pi[p];
		if (rev[p+1] == s[i])  ++p;
		if (p && !leftMost[p]) {
			leftMost[p] = i;
			m = p;
		}
	}
}

void manacher()
{
	int mx = r[1] = 1, pos = 1;
	FOR(i, 2, n) {
		r[i] = (i >= mx) ? 1 : std :: min(mx-i, r[pos+pos-i]);
		while (s[i+r[i]] == s[i-r[i]])  ++r[i];
		if (i+r[i] > mx) {
			mx = i + r[i];
			pos = i;
		}
	}
}

void init()
{
	scanf("%s", s+1);
	n = strlen(s+1);
	s[n+1] = '$';
	FOR(i, 1, n)  rev[n-i+1] = s[i];
	KMP();
	manacher();
}

void solve()
{
	int p = 0, len;
	FOR(i, 1, n) 
		g[i] = (leftMost[p+1]==i) ? ++p : p;
	FOR(i, 1, n) {
		len = std :: min(g[i-r[i]], n-i-r[i]+1);
		if ((len + r[i]) * 2 - 1 > ans) {
			ans = (len + r[i]) * 2 - 1;
			L[0] = leftMost[len] - len + 1;  R[0] = leftMost[len];
			L[1] = i - r[i] + 1;  R[1] = i + r[i] - 1;
			L[2] = n - len + 1;  R[2] = n;
		}
	}

	int cnt = 0;
	FOR(i, 0, 2)
		if (L[i] <= R[i])  ++cnt;
	printf("%d\n", cnt);
	FOR(i, 0, 2)
		if (L[i] <= R[i]) 
			printf("%d %d\n", L[i], R[i]-L[i]+1);
}

int main()
{
	init();
	solve();
	return 0;
}

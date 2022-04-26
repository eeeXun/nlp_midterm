/*
    Author: Zhouxing Shi
    Created on Mar23, 2015
*/
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define drep(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a, b) for (int i = (a); i < (b); ++i)
#define pb(x) push_back(x)
#define mp(x, y) (make_pair(x, y))
#define clr(x) memset(x, 0, sizeof(x))
#define xx first
#define yy second
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
const int inf = ~0U >> 1;
const ll INF = ~0ULL >> 1;
//***************************

const int maxn = 300000;
int nxt[maxn], best, N, f[maxn], cans;
char s2[maxn], s[maxn];
pii ans[5], pre[maxn];

int main()
{
	scanf("%s", s + 1);
	N = strlen(s + 1);
	memcpy(s2, s, sizeof(s2)); 
	reverse(s2 + 1, s2 + N + 1);	
	int j = 0;
	rep(i, 2, N)
	{
		while (j && s2[i] != s2[j + 1]) j = nxt[j];
		if (s2[i] == s2[j + 1]) j++;
		nxt[i] = j;
	}
	j = 0;
	rep(i, 1, N)
	{
		while (j && s[i] != s2[j + 1]) j = nxt[j];
		if (s[i] == s2[j + 1]) j++;
		pre[i] = max(pre[i - 1], mp(j, i));
	}
	int mx = 0, id;
	s[0] = '$';
	rep(i, 1, N)
	{
		if (mx > i) f[i] = min(f[2 * id - i], f[id] + id - i);
		else f[i] = 1;
		for (; s[i + f[i]] == s[i - f[i]]; ++f[i]);
		if (f[i] + i > mx) mx = f[i] + i, id = i;
	}
	rep(i, 1, N)
	{
		int l = min(pre[i - f[i]].xx, N - (i + f[i] - 1));
		if (f[i] * 2 - 1 + l * 2 > best)
		{
			best = f[i] * 2 - 1 + l * 2;
			if (l)
			{
				cans = 3;
				ans[1] = mp(pre[i - f[i]].yy - l + 1, l);
				ans[2] = mp(i - f[i] + 1, 2 * f[i] - 1);
				ans[3] = mp(N - l + 1, l);
			}
			else ans[cans = 1] = mp(i - f[i] + 1, 2 * f[i] - 1);
		}
	}
	printf("%d\n", cans);
	rep(i, 1, cans) printf("%d %d\n", ans[i].xx, ans[i].yy);
    return 0;
}

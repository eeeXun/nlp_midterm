//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<stack>
#include<cstring>
#include<set>
#include<iterator>
#include<list>
#include<deque>
#include<queue>
#include<map>
#include<cmath>
#include<sstream>
#include<cstdio>
#include<ctime>
#include<iomanip>
#include<unordered_map>
#include<unordered_set>

using namespace std;
#define lowbit(x) ((x)&(-x))
#define REP(i, a, n) for(int i=a;i<=(n);i++)
#define IOS ios::sync_with_stdio(false),cin.tie(0), cout.tie(0)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> P;
const int maxn = 1e5 + 10;
const int N = 2e5 + 10;
const int M = 5e3 + 10;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9 + 7;
const int mod2 = 998244353;
const int mod3 = 1e9 + 9;
const int hash1 = 131;
const int hash2 = 13331;
int r[N];
char a[N], b[N];
int nxt[N], f[N];
int n, m;
void manacher()
{
	int mx = 0, p = 0;
	r[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		r[i] = mx > i ? min(r[2 * p - i], mx - i) : 1;
		while (b[i - r[i]] == b[i + r[i]])
			r[i]++;
		if (i + r[i] > mx)
		{
			mx = i + r[i];
			p = i;
		}
	}
}
void getnext()
{
	nxt[1] = 0;
	for (int i = 2, j = 0; i <= m; i++)
	{
		while (j && a[j + 1] != a[i])
			j = nxt[i];
		if (a[j + 1] == a[i])
			j++;
		nxt[i] = j;
	}
}
void kmp()
{
	for (int i = 1, j = 0; i <= n; i++)
	{
		while (j && (a[j + 1] != b[i] || j == m))
			j = nxt[j];
		if (a[j + 1] == b[i])
			j++;
		f[i] = j;
		//printf("f[%d] == %d\n", i, f[i]);
		if (i == 50)
		{
			cout << " ";
		}
	}
}
int dp[N], tail[N];
int main()
{
	IOS;
	cin >> (b + 1);
	n = m = strlen(b + 1);
	b[0] = '@';
	b[n + 1] = '$';
	manacher();
	for (int i = 1; i <= n; i++)
	{
		a[i] = b[1 + n - i];
	}
	getnext();
	kmp();
	int maxl = 0;
	vector<P> ans;
	for (int i = 1; i <= n; i++)
	{
		if (dp[i - 1] < f[i])
			dp[i] = f[i], tail[i] = i;
		else
			dp[i] = dp[i - 1], tail[i] = tail[i - 1];
		//printf("dp[%d] == %d\n", i, dp[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		int mid = 2 * r[i] - 1;
		int pre = min(dp[i - r[i]], n - (i + r[i] - 1));
		//printf("i == %d r == %d, pre == %d, mid == %d\n", i, r[i], pre,mid);
		if (mid + 2 * pre > maxl)
		{
			maxl = mid + 2 * pre;
			ans.clear();
			if (pre > 0)
				ans.push_back({ tail[i - r[i]] - pre + 1,pre });
			ans.push_back({ i - r[i] + 1,2 * r[i] - 1 });
			if (pre > 0)
				ans.push_back({ n - pre + 1,pre });
		}
	}
	cout << ans.size() << endl;
	for (auto& x : ans)
	{
		cout << x.first << " " << x.second << endl;
	}
	return 0;
}
			  		  		 	 	 							  	 		
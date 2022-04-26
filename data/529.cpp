#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <numeric>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
#define rep(i, a, b) for (register int i = (a); i <= (b); ++i)
#define per(i, a, b) for (register int i = (a); i >= (b); --i)
#define loop(it, v) for (auto it = v.begin(); it != v.end(); it++)
#define cont(i, x) for (register int i = head[x]; i; i = edge[i].nex)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, cnt) memset(a, cnt, sizeof(a))
#define cop(a, b) memcpy(a, b, sizeof(a))
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define SC(t, x) static_cast <t> (x)
#define ub upper_bound
#define lb lower_bound
#define pqueue priority_queue
#define mp make_pair
#define pb push_back
#define pof pop_front
#define pob pop_back
#define fi first
#define se second
#define y1 y1_
#define Pi acos(-1.0)
#define iv inline void
#define enter putchar('\n')
#define siz(x) ((int)x.size())
#define file(x) freopen(x".in", "r", stdin),freopen(x".out", "w", stdout)
typedef double db ;
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int maxn = 2e6 + 100 ;
const int inf = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const ll mod = 1e9 + 7 ;
const double eps = 1e-7 ;
template <class T = int> T read()
{
	T f = 1, a = 0;
	char ch = getchar() ;
	while (!isdigit(ch)) { if (ch == '-') f = -1 ; ch = getchar() ; }
	while (isdigit(ch)) { a =  (a << 3) + (a << 1) + ch - '0' ; ch = getchar() ; }
	return a * f ;
}
 
int n;
 
char s[maxn];
 
ll sufhash[maxn], prehash[maxn], fac[maxn] = {1};
 
pii maxx[maxn], ans;
 
signed main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	rep(i, 1, n) fac[i] = fac[i - 1] * 233 % mod;
	per(i, n, 1) sufhash[i] = (sufhash[i + 1] + fac[(n - i)] * s[i]) % mod;
	rep(i, 1, n) prehash[i] = (prehash[i - 1] + fac[i - 1] * s[i]) % mod;
	rep(i, 1, n)
	{
		int l = 1, r = (n - i + 1) / 2, sum = 0;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			ll hash1 = (prehash[i + mid - 1] + mod - prehash[i - 1]) % mod, hash2 = sufhash[n - mid + 1] * fac[i - 1] % mod;
			if(hash1 == hash2) sum = mid, l = mid + 1;
			else r = mid - 1;
		}
		maxx[i + sum - 1] = max(maxx[i + sum - 1], mp(sum, i));
	}
	per(i, n, 1)
	{
		pii tmp = maxx[i + 1];
		tmp.fi --;
		maxx[i] = max(maxx[i], tmp);
	}
	rep(i, 1, n) maxx[i] = max(maxx[i], maxx[i - 1]);
	rep(i, 1, n)
	{
		int l = 1, r = min(i, n - i + 1), sum;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			ll hash1 = (prehash[i] + mod - prehash[i - mid]) % mod * fac[n - i] % mod, hash2 = (sufhash[i] + mod - sufhash[i + mid]) % mod * fac[i - 1] % mod;
			if(hash1 == hash2) sum = mid, l = mid + 1;
			else r = mid - 1;
		}
		ans = max(ans, mp(sum * 2 - 1 + 2 * min(n - i - sum + 1, maxx[i - sum].fi), i));
	}
	int i = ans.se, l = 1, r = min(i, n - i + 1), sum;
	while(l <= r)
	{
		ll mid = (l + r) >> 1;
		ll hash1 = (prehash[i] + mod - prehash[i - mid]) % mod * fac[n - i] % mod, hash2 = (sufhash[i] + mod - sufhash[i + mid]) % mod * fac[i - 1] % mod;
		if(hash1 == hash2) sum = mid, l = mid + 1;
		else r = mid - 1;
	}
	int len = min(n - i - sum + 1, maxx[i - sum].fi);
	if(!len)
	{
		puts("1");
		printf("%d %d\n", i - sum + 1, 2 * sum - 1);
	}
	else
	{
		puts("3");
		printf("%d %d\n", maxx[i - sum].se, len);
		printf("%d %d\n", i - sum + 1, 2 * sum - 1);
		printf("%d %d\n", n - len + 1, len);
	}
	return 0;
}
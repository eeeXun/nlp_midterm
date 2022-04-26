// tzl ak IOI! 

#include<bits/stdc++.h>

#define HEAP priority_queue
#define rep(i, n) for(int i = 0; i < (n); ++i)
#define per(i, n) for(int i = (n) - 1; i >= 0 ; --i)
#define forn(i, l, r) for(int i = (l); i <= (r); ++i)
#define nrof(i, r, l) for(int i = (r); i >= (l); --i)
#define FOR(a, b) for(auto (a): (b))
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define X first
#define Y second
#define eps 1e-6
#define pi 3.1415926535897932384626433832795
#define SZ(x) (int)x.size()
#define ALL(x) x.begin(), x.end()
#define FILL(a, b) memset((a), (b), sizeof((a)))
#define MCPY(a, b) memcpy((a), (b), sizeof((b)))

using namespace std;

typedef long long LL;
typedef double flt;
typedef vector<int> vi;
typedef vector<LL> vl;
typedef pair<int,int> pii;
typedef pair<int,LL> pil;
typedef pair<LL,int> pli;
typedef pair<LL,LL> pll;
typedef vector<pil> vil;
typedef vector<pii> vii;
typedef vector<pli> vli;
typedef vector<pll> vll;

const int iinf = 1e9 + 7;
const LL linf = 1ll << 60;
const flt dinf = 1e60;

template <typename T>
inline void scf(T &x)
{
	bool f = 0; x = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') { f = 1; c = getchar(); }
	while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	if(f) x = -x; return;
}

template <typename T1, typename T2>
void scf(T1 &x, T2 &y) { scf(x); return scf(y); }

template <typename T1, typename T2, typename T3>
void scf(T1 &x, T2 &y, T3 &z) { scf(x); scf(y); return scf(z); }

template <typename T1, typename T2, typename T3, typename T4>
void scf(T1 &x, T2 &y, T3 &z, T4 &w) { scf(x); scf(y); scf(z); return scf(w); }

inline char mygetchar(){ char c = getchar(); while(c == ' ' || c == '\n') c = getchar(); return c; }

template <typename T>
void chkmax(T &x, const T &y){ if(y > x) x = y; return; }

template <typename T>
void chkmin(T &x, const T &y){ if(y < x) x = y; return; }

#ifdef ONLINE_JUDGE
#define debug(x,c) ;
#else
#define DEBUG
#define debug(x,c) cerr<<#x<<"="<<x<<c;
#endif

//---------------------------head----------------------------

const int N = 2e5 + 100;

int n;
char s[N];
pii dp[N];
vii all;

namespace manacher
{
	char t[N];
	int r[N];

	void solve(char *s)
	{
		int n = 0;
		t[n++] = '#';
		forn(i, 1, ::n) t[n++] = s[i], t[n++] = '$';
		t[n - 1] = '#';

		int rb = 0, rem;
		forn(i, 1, n - 2)
		{
			r[i] = (i > rb) ? 0 : min(r[rem + rem - i], rb - i);
			while(i + r[i] + 1 < n && i - r[i] - 1 >= 0 && t[i + r[i] + 1] == t[i - r[i] - 1]) r[i]++;
			if(i + r[i] > rb) rb = i + r[i], rem = i;
		}

		forn(i, 1, n - 2)
		{
			int lb = (i - r[i]) / 2 + 1, rb = (i + r[i]) / 2;
			if(lb <= rb && (rb - lb + 1) % 2 == 1) all.pb(mp(lb, rb));
		}
		return;
	}
}

namespace kmp
{
	char t[N];
	int border[N];

	void solve(char *s)
	{
		forn(i, 1, n) t[i] = s[n - i + 1];

		border[0] = -1;
		forn(i, 1, n)
		{
			int j = border[i - 1];
			while(~j && t[j + 1] != t[i]) j = border[j];
			border[i] = j + 1;
		}

		int i = 0, j = 0;
		while(i < n)
		{
			++i;
			while(~j && t[j + 1] != s[i]) j = border[j];
			dp[i] = mp((++j), i);
		}

		forn(i, 1, n) chkmax(dp[i], dp[i - 1]);
		return;
	}
}

void TZL()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	manacher::solve(s);
	kmp::solve(s);
	return;
}

void RANK1()
{
	int ans = 0; vii rem;
	for(auto x: all)
	{
		int l = x.X, r = x.Y;
		assert(l >= 1 && r <= n);

		int calc = r - l + 1 + min(dp[l - 1].X, n - r) * 2;
		if(calc > ans)
		{
			ans = calc;
			rem.clear();
			rem.pb(mp(l, r - l + 1));

			int foo = min(dp[l - 1].X, n - r);
			if(foo)
			{
				rem.pb(mp(dp[l - 1].Y - foo + 1, foo));
				rem.pb(mp(n - foo + 1, foo));
			}
		}
	}

	printf("%d\n", SZ(rem));
	sort(ALL(rem));
	for(auto x: rem) printf("%d %d\n", x.X, x.Y);
	return;
}

#define tzl int
#define ak main
#define IOI ()
tzl ak IOI
{
#undef tzl
#undef ak
#undef IOI

	TZL();
	RANK1();

#define tzl return
#define caisi 0
#define myy ;
	tzl caisi myy
#undef tzl
#undef caisi
#undef myy
}

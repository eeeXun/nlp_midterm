#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <utility>
#include <numeric>
#include <memory>
#include <stack>
#include <deque>
#include <queue>
#include <list>
#include <functional>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <bitset>

#define X first
#define Y second
#define MAX(x, y) x = x > (y) ? x : (y)
#define MIN(x, y) x = x > (y) ? (y) : x
#define LOW(x) ((x) & -(x))
#define SQR(x) ((x) * (x))
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define rFOR(i, b, a) for (int i = (b); i > (a); --i)
#define CLEAR(x) memset(x, 0, sizeof(x))
#define FILL(x, p) memset(x, p, sizeof(x))
#define COPY(x, y) memcpy(x, y, sizeof(x))
#define ALL(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<string> VS;

const int INF = 0x3fffffff;
const ll _INF = 0x7ffffffffffffffll;
const double EPS = 1e-9;
const double PI = acos(-1.0);

template<class T, class INT>
inline T pow(T x, INT y)
{
	T res(1);
	for (T tt(x); y; y /= 2)
	{
		if (y & 1) res *= tt;
		tt *= tt;
	}
	return res;
}

template<class T, class INT>
inline T pow(T x, INT y, T p)
{
	T res(1);
	for (T tt(x); y; y /= 2)
	{
		if (y & 1) res = res * tt % p;
		tt = tt * tt % p;
	}
	return res;
}

int toInt(string s)
{
	int x = 0;
	istringstream sin(s);
	sin >> x;
	return x;
}

template<class T>
inline string toString(T x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

template<class INT>
inline INT gcd(INT x, INT y)
{
	return y ? gcd(y, x % y) : x;
}

template<class INT>
inline int calc_bits(INT x)
{
	return x ? (x & 1) + calc_bits(x >> 1) : 0;
}

const int MAXN = 200000 + 10;

string st, s;
int f[MAXN], g[MAXN], n, ans, t[MAXN], _stack[MAXN], midp, midq, fir, sec, top;
bool tr;

void extend_kmp_lcp(string s)
{
	int l = 0, k = 0, n = s.size();
	FOR(i, 1, n)
	{
		int p = k + l > i ? min(k + l - i, f[i - k]) : 0;
		for (; i + p < n && s[i + p] == s[p]; ++p);
		f[i] = p;
		if (i + p > k + l) k = i, l = p;
	}
}

void extend_kmp_lsp(string s)
{
	int l = 0, k = 0, n = s.size();
	g[0] = 1;
	FOR(i, 1, n)
	{
		int p = k + l > i ? min(k + l - i, g[k + k - i]) : 0;
		for (; i + p < n && i + p >= 0 && s[i - p] == s[i + p]; ++p);
		g[i] = p;
		if (i + p > k + l) k = i, l = p; 
	}
}

int calc(int x)
{
	int l = 0, r = top - 1;
	for (; l < r; )
	{
		int mid = (l + r + 1) >> 1;
		if (_stack[mid] > x) r = mid - 1;
		else l = mid;
	}
	return _stack[l];
}

int main(int argc, char* argv[])
{
	cin >> st;
	n = st.size(), s = st;
	reverse(ALL(s));
	s += "_" + st;
	extend_kmp_lcp(s);
	extend_kmp_lsp(s);
	FOR(i, n + 1, n + n + 1) MAX(t[i + f[i]], f[i]);
	_stack[top++] = n + 1;
	FOR(i, n + 2, n + n + 1)
		if (t[i] > t[_stack[top - 1]]) _stack[top++] = i;
	FOR(i, n + 1, n + n + 1)
	{
		int lim = calc(i - g[i] + 1);
		if (2 * (g[i] + min(t[lim], n + n - i - g[i] + 1)) - 1 > ans)
		{
			ans = 2 * (g[i] + min(t[lim], n + n - i - g[i] + 1)) - 1;
			midp = i - g[i] + 1, midq = g[i] - 1;
			if (min(t[lim], n + n - i - g[i] + 1))
			{
				tr = true;
				fir = lim - t[lim], sec = t[lim];
			}
			else tr = false;
		}
	}
	if (tr)
	{
		cout << 3 << endl;
		cout << fir - n << " " << sec << endl;
		cout << midp - n << " " << midq * 2 + 1 << endl;
		cout << n - sec + 1 << " " << sec << endl;
	}
	else
	{
		cout << 1 << endl;
		cout << midp - n << " " << midq * 2 + 1 << endl;
	}
}

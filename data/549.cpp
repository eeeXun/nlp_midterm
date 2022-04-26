#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <ctime>
#include <algorithm>
#define N 201000
#define PII pair<int, int>
#define PLL pair<long long, long long>
#define MP make_pair
#define lowbit(i)((i)&(-(i)))
typedef long long ll;
template <typename T> inline void read(T &x) {
	x = 0; char c = getchar(); bool flag = false;
	while (!isdigit(c)) { if (c == '-')	flag = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	if (flag)	x = -x;
}
using namespace std;
const int P1 = 1e9 + 7;
const int P2 = 1e9 + 9;
const int base = 13331;
inline ll quickpow(ll x, int k, int P) {
	ll res = 1;
	while (k) {
		if (k & 1)	res = res * x % P;
		x = x * x % P;
		k >>= 1;
	}
	return res;
}
inline void MAX(int &a, int b) {
	if (b > a)	a = b;
}
inline void MIN(int &a, int b) {
	if (b < a)	a = b;
}
inline void MAX(ll &a, ll b) {
	if (b > a)	a = b;
}
inline void MIN(ll &a, ll b) {
	if (b < a)	a = b;
}
char s[N];
int n;
ll ha1[N], ah1[N];
ll ha2[N], ah2[N];
ll mi1[N], minv1[N];
ll mi2[N], minv2[N];
inline void Hash() {
	for (register int i = 1; i <= n; ++i) {
		ha1[i] = (ha1[i - 1] * base + s[i]) % P1;
		ha2[i] = (ha2[i - 1] * base + s[i]) % P2;
	}
	for (register int i = n; i; --i) {
		ah1[i] = (ah1[i + 1] * base + s[i]) % P1;
		ah2[i] = (ah2[i + 1] * base + s[i]) % P2;
	}
	mi1[0] = mi2[0] = minv1[0] = minv2[0] = 1;
	for (register int i = 1; i <= n; ++i) {
		mi1[i] = mi1[i - 1] * base % P1;
		minv1[i] = quickpow(mi1[i], P1 - 2, P1);
		mi2[i] = mi2[i - 1] * base % P2;
		minv2[i] = quickpow(mi2[i], P2 - 2, P2);
	}
}
inline PLL get1(int l, int len) {
	int r = l + len - 1;
	ll res1 = ((ha1[r] - ha1[l - 1] * mi1[len]) % P1 + P1) % P1;
	ll res2 = ((ha2[r] - ha2[l - 1] * mi2[len]) % P2 + P2) % P2;
	return MP(res1, res2);
}
inline PLL get2(int l, int len) {
	int r = l + len - 1;
	ll res1 = ((ah1[l] - ah1[r + 1] * mi1[len]) % P1 + P1) % P1;
	ll res2 = ((ah2[l] - ah2[r + 1] * mi2[len]) % P2 + P2) % P2;
	return MP(res1, res2);
}
int pos[N];
struct Seg {
	int l, r;
}seg[N];
bool cmp(const Seg &a, const Seg &b) {
	return a.r > b.r;
}
inline void init() {
	int ptr = 1;
	for (register int i = n; i > (n + 1) >> 1; --i) {
		while (ptr + n - i <= n && get1(ptr, n - i + 1) != get2(i, n - i + 1))	++ptr;
		pos[i] = ptr + (n - i);
	}
	for (register int i = 1; i <= n; ++i) {
		int l = 0, r = min(n - i, i - 1), res = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (get1(i - mid, mid) == get2(i + 1, mid))	res = mid, l = mid + 1;
			else	r = mid - 1;
		}
		seg[i] = (Seg){i - res, i + res};
	}
	sort(seg + 1, seg + 1 + n, cmp);
}
int mx;
PII ans;
int tre[N];
inline void add(int cur, int x) {
	for (register int i = cur; i <= n; i += lowbit(i))
		MAX(tre[i], x);
}
inline int query(int cur) {
	int res = 0;
	for (register int i = cur; i; i -= lowbit(i))
		MAX(res, tre[i]);
	return res;
}
inline void work() {
	int ptr = n;
	for (register int i = 1; i <= n; ++i) {
		int l = seg[i].l, r = seg[i].r;
		while (ptr > (n + 1) >> 1 && ptr > r)	add(pos[ptr], n - ptr + 1), --ptr;
		int tmp = query(l - 1);
		int res = tmp + tmp + r - l + 1;
		if (res > mx)	mx = res, ans = MP(i, tmp);
	}
	int ml = seg[ans.first].l, mr = seg[ans.first].r;
	int rlen = ans.second, rgt = n - rlen + 1;
	int lft = pos[rgt] - rlen + 1, llen = rlen;
	if (rlen) {
		puts("3");
		printf("%d %d\n%d %d\n%d %d\n", lft, llen, ml, mr - ml + 1, rgt, rlen);
	} else {
		puts("1");
		printf("%d %d\n", ml, mr - ml + 1);
	}
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	Hash();
	init();
	work();
	return 0;
}

/*
abacaba
//1  1 7

axbya
//3  1 1  2 1  5 1

xabyczba
//3  2 2  4 1  7 2
*/
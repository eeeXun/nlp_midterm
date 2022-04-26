/*
Author: LJQ
PROG: Codeforces Beta #30 E. Tricky and Clever Password
DATE: 2012.11.18
*/
#include <cstdio>
#include <cstring>

using namespace std;

const int p = 377;
const int maxn = 100005;

typedef long long LL;

LL pop[maxn];
LL hL[maxn], hR[maxn];
char st[maxn];
int lcp[maxn];//lcp between i..n && n..i
int leftmost[maxn];//leftmost[i]..i == n..,
int lbest[maxn], lord[maxn];
int n;
int type, mid, midlen, endlen, lpos;//ans

void init()
{
	scanf("%s", st + 1);
	n = strlen(st + 1);
}

inline LL HL(int t, int len){
	return hL[t] - hL[t - len] * pop[len];
}

inline LL HR(int t, int len){
	return hR[t] - hR[t + len] * pop[len];
}

void work()
{
	//calc fac
	pop[0] = 1;
	for (int i = 1; i <= n; i ++) pop[i] = pop[i - 1] * p;
	//calc hash
	hL[0] = 0;
	for (int i = 1; i <= n; i ++)
		hL[i] = hL[i - 1] * p + st[i];
	hR[n+1] = 0;
	for (int i = n; i >= 1; i --)
		hR[i] = hR[i + 1] * p + st[i];
	//calc lcp
	for (int i = 1; i < n; i ++){
		if (st[i] != st[n]) continue;
		int L = 1, r = (n - i + 1) >> 1;
		while (L < r){
			int mid = (L + r + 1) >> 1;
			if (HR(i, mid) == HL(n, mid)) L = mid;
				else r = mid - 1;
		}
		lcp[i] = L;
	}
	//calc leftmost
	int p = 0;
	for (int i = 1; i < n; i ++){
		while (p <= i && p + lcp[p] - 1 < i) p ++;
		if (p <= i) leftmost[i] = i - p + 1;
	}
	lbest[0] = lord[0] = 0;
	for (int i = 1; i < n; i ++){
		lbest[i] = leftmost[i]; lord[i] = lbest[i] ? i - lbest[i] + 1 : 0;
		if (lbest[i - 1] > lbest[i]){
			lbest[i] = lbest[i - 1], lord[i] = lord[i - 1];
		}
	}
	//check each pos as mid
	int best = 1; mid = 1; midlen = 1; type = 1;
	for (int i = 2; i < n; i ++){
		//find midlen
		int L = 1, r = i;
		if (n - i + 1 < r) r = n - i + 1;
		while (L < r){
			int mid = (L + r + 1) >> 1;
			if (HL(i, mid) == HR(i, mid)) L = mid;
				else r = mid - 1;
		}
		int cur = L;//curr
		if (i + cur > n || i - cur < 1 || lbest[i - cur] <= 0){//only midpart
			if ((cur << 1) - 1 > best){
				best = (cur << 1) - 1; type = 1; mid = i; midlen = cur;
			} continue;
		} else {//find two_end: left in 1 .. i - cur
			int extra = lbest[i - cur];
			if (extra > n - (i + cur - 1)) extra = n - (i + cur - 1);
			if ((cur << 1) - 1 + (extra << 1) > best){
				best = (cur << 1) - 1 + (extra << 1); type = 3; 
				mid = i; midlen = cur; lpos = lord[i - cur]; endlen = extra;
			}
		}
	}
}

void print()
{
	if (type == 1){
		printf("1\n%d %d\n", mid - midlen + 1, (midlen << 1) - 1);
	} else {
		printf("3\n%d %d\n%d %d\n%d %d\n", lpos, endlen, mid - midlen + 1, midlen * 2 - 1, n - endlen + 1, endlen);
	}
}

int main()
{
	init();
	work();
	print();
	return 0;
}

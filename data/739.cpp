
// Codeforces Beta Round #30 (Codeforces format) E Tricky and Clever Password

#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int base = 13331;
const int inf = 1000000000;

int match[200002], minl[100001], maxl[100000], loc[100000], pal[100001];
char str[200002];

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	scanf("%s", str);
	int len = strlen(str);
	
	str[len] = 1;
	int tot = len + 1;
	for (int i = len - 1; i >= 0; i --) str[tot ++] = str[i];
	str[tot ++] = 0;
	for (int i = 0; i < len; i ++) swap(str[i], str[i + len + 1]);
	
	int p = 0;
	match[0] = 0;
	for (int i = 1; i < tot; i ++) {
		if (i + match[i - p] < p + match[p]) {
			match[i] = match[i - p];
		} else {
			int t = max(0, p + match[p] - i);
			while (i + t < tot && str[i + t] == str[t]) t ++;
			match[i] = t;
			p = i;
		}
	}
	
	for (int i = 0; i <= len; i ++) minl[i] = inf;
	for (int i = 0; i < len; i ++) {
		minl[i + match[i + len + 1]] = min(minl[i + match[i + len + 1]], i);
	}
	
	int maxv = 0, t = -1, j = 0;
	for (int i = 0; i < len; i ++) {
		while (j < i && j + match[j + len + 1] < i) j ++;
		if (minl[i] < inf && i - minl[i] > maxv) {
			maxv = i - minl[i];
			t = minl[i];
		}
		if (maxv > i - j) {
			maxl[i] = maxv;
			loc[i] = t;
		} else {
			maxl[i] = i - j;
			loc[i] = j;
		}
	}
	
	p = 0;
	pal[0] = 1;
	for (int i = 1; i < len; i ++) {
		if (2 * p >= i && i + pal[2 * p - i] < p + pal[p]) {
			pal[i] = pal[2 * p - i];
		} else {
			int t = max(0, p + pal[p] - i);
			while (i - t >= 0 && i + t < tot && str[i - t + len + 1] == str[i + t + len + 1]) t ++;
			pal[i] = t;
			p = i;
		}
	}
	
	int ans = 0, p1 = -1, p2 = -1, l = 0;
	for (int i = 0; i < len; i ++) {
		int x = i - pal[i] + 1, y = i + pal[i];
		if (y - x > ans) {
			ans = y - x;
			p1 = -1;
			p2 = x;
			l = 0;
		}
		int tmp = min(maxl[x], len - y);
		if (tmp * 2 + y - x > ans) {
			ans = tmp * 2 + y - x;
			p1 = loc[x];
			p2 = x;
			l = tmp;
		}
	}
	
	if (l == 0) {
		printf("1\n");
		printf("%d %d\n", p2 + 1, ans);
	} else {
		printf("3\n");
		printf("%d %d\n", p1 + 1, l);
		printf("%d %d\n", p2 + 1, ans - l * 2);
		printf("%d %d\n", len - l + 1, l);
	}
	
	return 0;
}

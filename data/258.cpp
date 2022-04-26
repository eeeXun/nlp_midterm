
// Codeforces Beta Round #30 (Codeforces format) E Tricky and Clever Password

#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int base = 13331;
const int inf = 1000000000;
const int modulo1 = 1000000007;
const int modulo2 = 1000000009;

int a[100000], b[100000], minl[100001], maxr[100001];
//long long hash[200002], pow[20];
long long hash1[200002], hash2[200002], pow1[20], pow2[20];
char str[200002];

int lcp(int a, int b, int tot) {
	int lg = 0;
	while (1 << lg <= tot - a && 1 << lg <= tot - b) lg ++;
	int res = 0;
	for (int i = lg - 1; i >= 0; i --) {
		if (a + (1 << i) > tot || b + (1 << i) > tot) continue;
		//long long t1 = hash[a + (1 << i)] - hash[a] * pow[i];
		//long long t2 = hash[b + (1 << i)] - hash[b] * pow[i];
		long long t1 = ((hash1[a + (1 << i)] - hash1[a] * pow1[i]) % modulo1 + modulo1) % modulo1;
		long long t2 = ((hash1[b + (1 << i)] - hash1[b] * pow1[i]) % modulo1 + modulo1) % modulo1;
		long long t3 = ((hash2[a + (1 << i)] - hash2[a] * pow2[i]) % modulo2 + modulo2) % modulo2;
		long long t4 = ((hash2[b + (1 << i)] - hash2[b] * pow2[i]) % modulo2 + modulo2) % modulo2;
		if (t1 == t2 && t3 == t4) {
			a += 1 << i;
			b += 1 << i;
			res += 1 << i;
		}
	}
	return res;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	scanf("%s", str);
	int len = strlen(str);
	
	str[len] = 1;
	int tot = len + 1;
	for (int i = len - 1; i >= 0; i --) str[tot ++] = str[i];
	str[tot ++] = 0;
	/*hash[0] = 0;
	for (int i = 0; i < tot; i ++)
		hash[i + 1] = hash[i] * base + str[i];
	pow[0] = base;
	for (int i = 1; i < 20; i ++)
		pow[i] = pow[i - 1] * pow[i - 1];*/
	
	hash1[0] = hash2[0] = 0;
	for (int i = 0; i < tot; i ++) {
		hash1[i + 1] = (hash1[i] * base + str[i]) % modulo1;
		hash2[i + 1] = (hash2[i] * base + str[i]) % modulo2;
	}
	pow1[0] = pow2[0] = base;
	for (int i = 1; i < 20; i ++) {
		pow1[i] = pow1[i - 1] * pow1[i - 1] % modulo1;
		pow2[i] = pow2[i - 1] * pow2[i - 1] % modulo2;
	}
	
	int ans = 0, p1 = -1, p2 = -1, l = 0;
	for (int i = 0; i <= len; i ++) {
		maxr[i] = 0;
		minl[i] = inf;
	}
	for (int i = 0; i < len; i ++) {
		a[i] = lcp(i, len + 1, tot);
		minl[i + a[i]] = min(minl[i + a[i]], i);
		b[i] = lcp(i, 2 * len - i, tot);
		int x = i + 1 - b[i], y = i + b[i];
		maxr[x] = max(maxr[x], y);
		if (y - x > ans) {
			ans = y - x;
			p2 = x;
		}
	}
	
	int maxv = 0, loc = -1, j = 0;
	for (int i = 0; i < len; i ++) {
		while (j < i && j + a[j] < i) j ++;
		if (minl[i] < inf && i - minl[i] > maxv) {
			maxv = i - minl[i];
			loc = minl[i];
		}
		int tmp = min(len - maxr[i], maxv);
		if (tmp > 0 && tmp * 2 + maxr[i] - i > ans) {
			ans = tmp * 2 + maxr[i] - i;
			p1 = loc;
			p2 = i;
			l = tmp;
		}
		tmp = min(len - maxr[i], i - j);
		if (tmp > 0 && tmp * 2 + maxr[i] - i > ans) {
			ans = tmp * 2 + maxr[i] - i;
			p1 = j;
			p2 = i;
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

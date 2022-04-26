#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <ctime>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#define mp make_pair
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) (a).size())
#define taskname "e"
using namespace std;

const int max_log = 17;
const int N = 1 << 17;
char s[N << 1];
int best, best_pos, best_len, log_2[N], p[N], tmp_z[N << 1], *z = tmp_z + N, t[max_log][N], n;

void concatenate() {
	n = strlen(s);
	s[n] = '#';
	for (int i = 0; i < n; ++i)
		s[n + 1 + i] = s[i];
	reverse(s, s + n);
}

void calc_z(char * s, int n, int * z) {
	z[0] = 0;
	int l = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		if (r < i) l = r = i;
		z[i] = min(r - i, z[i - l]);
		while (s[z[i]] == s[i + z[i]]) ++z[i];
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

void calc_palindromes(char * s, int n, int * p) {
	p[0] = 0;
	int l = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		if (r < i) l = r = i;
		p[i] = min(r - i, p[l + r - i]);
		while (s[i - p[i] - 1] == s[i + p[i] + 1]) ++p[i];
		if (i + p[i] > r) l = i - p[i], r = i + p[i];
	}
}

int max_cmp(int a, int b) {
	return p[a] < p[b] ? b : a;
}

void build_sparse() {
	for (int i = 1; i <= n; ++i) {
		log_2[i] = log_2[i - 1];
		if (i == (1 << (log_2[i] + 1))) ++log_2[i];
	}
	for (int i = 0; i < n; ++i)
		t[0][i] = i;
	for (int j = 1; j < max_log; ++j)
		for (int i = 0; i + (1 << j) <= n; ++i)
			t[j][i] = max_cmp(t[j - 1][i], t[j - 1][i + (1 << (j - 1))]);
}

int get_maxima(int l, int r) {
	int k = log_2[r - l + 1];
	return max_cmp(t[k][l], t[k][r - (1 << k) + 1]);
}

int best_palindrome(int begin, int end) {
	if (begin > end) return -n;
	int l = 0, r = (end - begin + 1 - 1) / 2;
	while (l < r) {
		int q = (l + r + 1) / 2;
		if (p[get_maxima(begin + q, end - q)] >= q) l = q; else r = q - 1;
	}
	return l;
}

void relax_answer(int pos, int len) {
	len = min(len, (n - pos - 1) / 2);
	int p = 2 * len + 2 * best_palindrome(pos + len, n - len - 1) + 1;
	if (p > best) {
		best = p;
		best_pos = pos, best_len = len;
	}
}

void output_answer() {
	if (best_len == 0) {
		int plen = (best - 1) / 2, ppos = get_maxima(best_pos + plen, n - plen - 1);
		printf("1\n");
		printf("%d %d\n", ppos - plen + 1, 2 * plen + 1);
	} else {
		int plen = (best - 2 * best_len - 1) / 2, ppos = get_maxima(best_pos + best_len + plen, n - best_len - plen - 1);
		printf("3\n");
		printf("%d %d\n", best_pos + 1, best_len);
		printf("%d %d\n", ppos - plen + 1, 2 * plen + 1);
		printf("%d %d\n", n - best_len + 1, best_len);
	}
}

int main() {
	//freopen(taskname".in", "r", stdin);
	//freopen(taskname".out", "w", stdout);
	scanf("%s", s);
	concatenate();
	calc_z(s, 2 * n + 1, z - (n + 1));
	calc_palindromes(s + n + 1, n, p);
	build_sparse();
	for (int i = 0; i < n; ++i)
		relax_answer(i, z[i]);
	output_answer();
	return 0;
}
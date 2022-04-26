#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef unsigned long long ulint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
#define endl '\n'
#define next next_
#define fst first
#define sed second
#define pb push_back
#define mp make_pair
#define rint register int
#define newline putchar('\n')
#define leave_space puthchar(' ')
#define all(x) (x).begin(), (x).end()
#define reveal(x) cerr << #x << " = " << (x) << endl
#define rep(it, f, e) for (rint it = f; it <= e; ++it)
#define per(it, f, e) for (rint it = f; it >= e; --it)
const int MAXN = 1e5 + 50;
int mlc[MAXN], n, fail[MAXN], spa[MAXN];
char s[MAXN], t[MAXN];
struct Node {
	int len, k;
	int st[3], le[3];
}	ans;
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	s[0] = '#', s[n + 1] = '$';
	int maxr = 1, mid = 1;
	rep (i, 1, n) {
		if (maxr >= i) {
			mlc[i] = min(mlc[mid * 2 - i], maxr - i);
		}
		while (s[i - mlc[i] - 1] == s[i + mlc[i] + 1]) ++mlc[i];
		if (i + mlc[i] > maxr) {
			maxr = i + mlc[i], mid = i;
		}
	}
	memcpy(t, s, sizeof(s));
	reverse(t + 1, t + n + 1);
	int k = fail[0] = -1;
	char *nt = t + 1;
	nt[n] = '@';
	rep (i, 1, n) {
		while (~k && nt[i - 1] != nt[k]) k = fail[k];
		fail[i] = (++k);
		if (i != n && nt[i] == nt[fail[i]] && ~fail[fail[i]]) fail[i] = fail[fail[i]];
	}
	k = 0;
	rep (i, 1, n) {
		while (~k && s[i] != nt[k]) k = fail[k];
		if (!spa[(++k)]) spa[k] = i;
	}
	rep (i, 1, n) {
		int l = 1, r = n - (i + mlc[i]), ret = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (!spa[mid] || spa[mid] >= i - mlc[i]) {
				r = mid - 1;
			} else {
				l = mid + 1, ret = mid;
			}
		}
		if (mlc[i] * 2 + 1 + ret * 2 > ans.len) {
			if (ret == 0) {
				ans.k = 1;
				ans.len = mlc[i] * 2 + 1;
				ans.st[0] = i - mlc[i];
				ans.le[0] = mlc[i] * 2 + 1;
			} else {
				ans.k = 3;
				ans.len = mlc[i] * 2 + 1 + ret * 2;
				ans.st[0] = spa[ret] - ret + 1;
				ans.le[0] = ret;
				ans.st[1] = i - mlc[i];
				ans.le[1] = mlc[i] * 2 + 1;
				ans.st[2] = n - ret + 1;
				ans.le[2] = ret;
			}
		}
	}
	cout << ans.k << endl;
	rep (i, 0, ans.k - 1) {
		cout << ans.st[i] << ' ' << ans.le[i] << endl;
	}
	return 0;
}
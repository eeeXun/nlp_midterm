#include <bits/stdc++.h>

#define SZ(x) (int)x.size() - 1
#define all(x) x.begin(), x.end()
#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define DF(i, a, b) for (int i = (a); i >= (b); i--)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template <typename T> inline void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> inline void chkmin(T &x, T y) {x = min(x, y); }
template <typename T> inline void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}

const int N = 2e5 + 10;
int r[N], nxt[N];
pair <int, int> mx[N];

void manacher(string st) {
	int p = -1, mx = -1;
	F(i, 0, SZ(st)) {
		if (i <= mx) r[i] = min(mx - i + 1, r[2 * p - i]);
		else r[i] = 1;
		while (i - r[i] >= 0 && i + r[i] <= SZ(st) && st[i - r[i]] == st[i + r[i]]) ++r[i];
		if (i + r[i] - 1 > mx) p = i, mx = i + r[i] - 1;
	}
}

void kmp(string st) {
	nxt[0] = -1;
	F(i, 1, SZ(st)) {
		int j = nxt[i - 1];
		while (j != -1 && st[j + 1] != st[i]) j = nxt[j];
		nxt[i] = j + (st[j + 1] == st[i]);
	}
}

int maxn;
bool tag;
pair <int, int> ans[4];

signed main() {
	string st;
	cin >> st;
	manacher(st);
	string t = st;
	reverse(t.begin(), t.end());
	kmp(t + "!" + st);
	F(i, st.size() + 1, st.size() * 2) mx[i - st.size() - 1] = make_pair(nxt[i] + 1, i - SZ(st));
	F(i, 1, SZ(st)) chkmax(mx[i], mx[i - 1]);
	F(i, 0, SZ(st)) {
		int l = i - ::r[i], r = i + ::r[i];
		// if (2 * r[i] - 1 > maxn) {
		// 	maxn = 2 * r[i] - 1;
		// 	sz = 1;
		// 	ans[1] = make_pair(i - ::r[i] + 1, i + ::r[i] - 1);
		// }
		// while (l < 0 || r > SZ(st)) l++, r--;
		// if (l > r) continue;
		int t = min(l < 0 ? 0 : mx[l].first, SZ(st) - r + 1);
		int len = t * 2 + ::r[i] * 2 - 1;
		if (len > maxn) {
			maxn = len;
			// cout << l << " " << r << endl;
			// if (len == 5) {
			// 	cout << l << " " << r << " " << mx[l].first << " " << mx[l].second << endl;
			// }
			if (t) {
				tag = false;
				ans[1] = make_pair(mx[l].second - t + 1, t);
				ans[2] = make_pair(l + 1, ::r[i] * 2 - 1);
				ans[3] = make_pair(st.size() - t, t);
			} else {
				tag = true;
				ans[1] = make_pair(l + 1, ::r[i] * 2 - 1);
			}
		}
	}
	// if (ans[1].second) cout << 3 << endl;
	// else cout << 1 << endl;
	cout << (tag ? 1 : 3) << endl;
	F(i, 1, tag ? 1 : 3) cout << ans[i].first + 1 << " " << ans[i].second << endl;
	return 0;
}
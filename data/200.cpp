#include <bits/stdc++.h>
#pragma optimize(3, "-Ofast", "inline")
using namespace std;
#define ios_fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define lowbit(x) (x & (-x))
// #define lowbit(x) (__builtin_ctzll(x))  // count tail zero
#define mosbit(x) (63 - __builtin_clzll(x))  // count lead zero
#define ll long long
#define ull unsigned long long
#define lld long double
#define mp make_pair
#define me(a, b) memset(a, (ll)(b), sizeof(a))
#define emp emplace_back
#define PII pair<int, int>
#define PLL pair<ll, ll>
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define ls (ro << 1)
#define rs (ls | 1)
#define mseg ((l + r) >> 1)
const int maxn = 1e6 + 17, maxm = 3e5 + 11, inf_int = 0x3f3f3f3f;
// 注意，inf_int < 2^30, (1<<31)已经超了int
const ll inf_ll = 0x3f3f3f3f3f3f3f, mod = 1e9L + 7;
const double eps = 1e-6;

int n, Mx[maxn], pos[maxn], len[maxn], fail[maxn];
char s[maxn], t[maxn];

inline void initNxt() {
  for (int i = 1; i <= n; i++) t[i] = s[n - i + 1];
  for (int i = 2, k = 0; i <= n; i++) {
    while (k && t[i] != t[k + 1]) k = fail[k];
    if (t[i] == t[k + 1]) k++;
    fail[i] = k;
  }
  for (int i = 1, k = 0; i <= n; i++) {
    while (k && s[i] != t[k + 1]) k = fail[k];
    if (s[i] == t[k + 1]) k++;
    if (k) Mx[i] = k, pos[i] = i - k + 1;
  }
  for (int i = 1; i <= n; i++)
    if (Mx[i] < Mx[i - 1]) Mx[i] = Mx[i - 1], pos[i] = pos[i - 1];
}

inline void solve() {
  cin >> s + 1, n = strlen(s + 1);
  // manacher
  for (int i = 1, id = 0, r = 0; i <= n; i++) {
    len[i] = r > i ? min(r - i, len[2 * id - i]) : 1;
    while (i > len[i] && s[len[i] + i] == s[i - len[i]]) len[i]++;
    if (len[i] + i > r) id = i, r = len[i] + i;
  }
  initNxt();
  vector<PII> ans;
  for (int i = 1, mxLen = 0; i <= n; i++) {
    int l = i - len[i] + 1, r = i + len[i] - 1;
    int add = min(n - r, Mx[l - 1]);
    if (2 * add + (r - l + 1) > mxLen) {
      ans.clear();
      mxLen = 2 * add + (r - l + 1);
      if (add) ans.emp(pos[l - 1], add);
      ans.emp(l, (r - l + 1));
      if (add) ans.emp(n - add + 1, add);
    }
  }
  cout << ans.size() << endl;
  for (auto [x, y] : ans) cout << x << " " << y << endl;
}

int main() {
  ios_fast;
  int TEST = 1;
  // freopen("test_input.txt", "r", stdin);
  // freopen("test_output.txt", "w", stdout);
  // cin >> TEST;
  while (TEST--) solve();
}

/*

 */
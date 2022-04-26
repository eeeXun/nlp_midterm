      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/87.cpp" 2
#pragma optimize(3, "-Ofast", "inline")

# 3 "data/87.cpp"
using namespace std;
# 22 "data/87.cpp"
const int maxn = 1e6 + 17, maxm = 3e5 + 11, inf_int = 0x3f3f3f3f;

const long long inf_ll = 0x3f3f3f3f3f3f3f, mod = 1e9L + 7;
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

  for (int i = 1, id = 0, r = 0; i <= n; i++) {
    len[i] = r > i ? min(r - i, len[2 * id - i]) : 1;
    while (i > len[i] && s[len[i] + i] == s[i - len[i]]) len[i]++;
    if (len[i] + i > r) id = i, r = len[i] + i;
  }
  initNxt();
  vector<pair<int, int> > ans;
  for (int i = 1, mxLen = 0; i <= n; i++) {
    int l = i - len[i] + 1, r = i + len[i] - 1;
    int add = min(n - r, Mx[l - 1]);
    if (2 * add + (r - l + 1) > mxLen) {
      ans.clear();
      mxLen = 2 * add + (r - l + 1);
      if (add) ans.emplace_back(pos[l - 1], add);
      ans.emplace_back(l, (r - l + 1));
      if (add) ans.emplace_back(n - add + 1, add);
    }
  }
  cout << ans.size() << endl;
  for (auto [x, y] : ans) cout << x << " " << y << endl;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int TEST = 1;



  while (TEST--) solve();
}

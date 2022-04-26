
  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/139.cpp" 2

# 2 "data/139.cpp"
using namespace std;
typedef long long lint;
typedef unsigned long long ulint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
# 20 "data/139.cpp"
const int MAXN = 1e5 + 50;
int mlc[MAXN], n, fail[MAXN], spa[MAXN];
char s[MAXN], t[MAXN];
struct Node {
 int len, k;
 int st[3], le[3];
} ans;
int main() {
 scanf("%s", s + 1);
 n = strlen(s + 1);
 s[0] = '#', s[n + 1] = '$';
 int maxr = 1, mid = 1;
 for (register int i = 1; i <= n; ++i) {
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
 for (register int i = 1; i <= n; ++i) {
  while (~k && nt[i - 1] != nt[k]) k = fail[k];
  fail[i] = (++k);
  if (i != n && nt[i] == nt[fail[i]] && ~fail[fail[i]]) fail[i] = fail[fail[i]];
 }
 k = 0;
 for (register int i = 1; i <= n; ++i) {
  while (~k && s[i] != nt[k]) k = fail[k];
  if (!spa[(++k)]) spa[k] = i;
 }
 for (register int i = 1; i <= n; ++i) {
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
 cout << ans.k << '\n';
 for (register int i = 0; i <= ans.k - 1; ++i) {
  cout << ans.st[i] << ' ' << ans.le[i] << '\n';
 }
 return 0;
}

    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/673.cpp" 2

# 2 "data/673.cpp"
using namespace std;
# 11 "data/673.cpp"
const int mxn = 1e5 + 5;
const int sz = 1 << 17;
int n;
char s[mxn], t[mxn << 1];
int z[mxn << 1];
int m[sz];
int suflen[mxn];
pair <int, int> mx[sz << 1];

void Z(char *s, int *z) {
 int n = strlen(s);
 int L = 0, R = 0;
 for (int i = 0; i < int(n); ++ i) if (i) {
  if (i <= R) z[i] = min(z[i - L], R - i + 1);
  while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++ z[i];
  if (i + z[i] - 1 > R) L = i, R = i + z[i] - 1;
 }
}

void M(char *s, int *m) {
 int n = strlen(s);
 int L = 0, R = 0;
 for (int i = 0; i < int(n); ++ i) if (i) {
  if (i <= R) m[i] = min(m[L + (R - i)], R - i);
  while (i - m[i] - 1 >= 0 && i + m[i] + 1 < n && s[i - m[i] - 1] == s[i + m[i] + 1]) ++ m[i];
  if (i + m[i] > R) L = i - m[i], R = i + m[i];
 }
}

void build(int *m) {
 for (int i = 0; i < int(sz); ++ i) mx[i + sz] = make_pair(m[i], i);
 for (int i = sz - 1; i; -- i) mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}

pair <int, int> qry(int l, int r) {
 pair <int, int> ans;
 for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
  if (l & 1) ans = max(ans, mx[l ++]);
  if (r & 1) ans = max(ans, mx[-- r]);
 }
 return ans;
}

pair <int, pair <int, int> > solve(int l, int r) {
 if (l > r) return make_pair(0, make_pair(0, 0));
 int lb = 0, rb = (r - l + 1) / 2;
 while (lb < rb) {
  int md = (lb + rb + 1) >> 1;
  if (l + md <= r - md && qry(l + md, r - md + 1).first >= md) lb = md;
  else rb = md - 1;
 }
 pair <int, int> pr = qry(l + lb, r - lb + 1);
 return make_pair(lb * 2 + 1, make_pair(pr.second - lb, lb * 2 + 1));
}

int main() {
 scanf("%s", s);
 n = strlen(s);
 int c = 0;
 for (int i = n - 1; ~i; -- i) t[c ++] = s[i];
 for (int i = 0; i < int(n); ++ i) t[c ++] = s[i];
 Z(t, z);
 for (int i = 0; i < int(n); ++ i) suflen[i] = max(i ? suflen[i - 1] : 0, z[i + n]);
 M(s, m);
 build(m);
 pair <int, vector <pair <int, int> > > ans;
 for (int l = 0; l * 2 <= n; ++ l) {
  int p = lower_bound(suflen, suflen + n, l) - suflen;
  if (p + l > n - l) break;
  int len = 2 * l;
  vector <pair <int, int> > v;
  if (l) v.push_back(make_pair(p, l));
  int L = p + l;
  int R = n - l - 1;
  pair <int, pair <int, int> > pr = solve(L, R);
  if (pr.first) v.push_back(pr.second), len += pr.first;
  else continue;
  if (l) v.push_back(make_pair(n - l, l));
  ans = max(ans, make_pair(len, v));
 }
 printf("%d\n", (int) ans.second.size());
 for (int i = 0; i < int(ans.second.size()); ++ i) printf("%d %d\n", ans.second[i].first + 1, ans.second[i].second);
 return 0;
}

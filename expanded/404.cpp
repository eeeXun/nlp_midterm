}
struct hexa {
 int a[3], b[3];
 hexa(int a0, int b0, int a1, int b1, int a2, int b2) {
  a[0] = a0, a[1] = a1, a[2] = a2, b[0] = b0, b[1] = b1, b[2] = b2;
 }
}out(0, 0, 0, 0, 0, 0);
char s[N], t[N];
int d[N], pi[N], L[N];

int dn[N * 4];
pair<int, int> ma[N * 4], dp[N];
int a[N];
vector<int> vec[N];
vector<pair<int, int> > B[N], F[N];
void add(int u, int st, int en, int c) {
 dn[u] += c;
 ma[u].first += c;
}

void update(int u) {
 ma[u] = max(ma[2 * u], ma[2 * u + 1]);
}

void down(int u, int st, int en) {
 if(!dn[u]) return;
 int md = st + en >> 1;
 add(2 * u, st, md, dn[u]);
 add(2 * u + 1, md + 1, en, dn[u]);
 dn[u] = 0;
}

void add(int u, int st, int en, int l, int r, int c) {

 if(l <= st && en <= r) {
  add(u, st, en, c);
  return;
 }
 int md = st + en >> 1;
 down(u, st, en);
 if(md >= l) add(2 * u, st, md, l, r, c);
 if(md < r) add(2 * u + 1, md + 1, en, l, r, c);
 update(u);
}

pair<int, int> get(int u, int st, int en, int l, int r) {

 if(l <= st && en <= r) {
  return ma[u];
 }
 int md = st + en >> 1;
 pair<int, int> ret = make_pair(0, 0);
 down(u, st, en);
 if(md >= l) ret = max(ret, get(2 * u, st, md, l, r));
 if(md < r) ret = max(ret, get(2 * u + 1, md + 1, en, l, r));
 update(u);
 return ret;
}

void build(int u, int st, int en) {

 if(st == en) {
  ma[u] = make_pair(a[st], st);
  dn[u] = 0;
  return;
 }

 int md = st + en >> 1;
 build(2 * u, st, md);
 build(2 * u + 1, md + 1, en);
 update(u);
}

int main() {
 scanf("%s", s + 1);
 int len = strlen(s + 1);
 strcpy(t + 1, s + 1);
 reverse(t + 1, t + len + 1);
 int cur = 0;
 for (int i = 1; i < len; i++) {
  for (; cur && t[i + 1] != t[cur + 1]; cur = pi[cur]);
  if (t[i + 1] == t[cur + 1]) cur++;
  pi[i + 1] = cur;
 }
 cur = 0;
 manacher(s + 1, d + 1);
 int ans = 0;
 for (int i = 1; i <= len; i++) {
  if (ans < 2 * d[i] - 1) {
   ans = 2 * d[i] - 1;
   out = hexa(0, 0, i - d[i] + 1, 2 * d[i] - 1, len + 1, 0);
  }
 }
 int pos = 1;
 cur = 0;
 for (int i = 1; i <= len; i++) {
  for (; cur && s[i] != t[cur + 1]; cur = pi[cur]);
  if (s[i] == t[cur + 1]) cur++;
  if (cur == pos) {
   if (len - pos + 1 <= i + 1) break;
   L[pos] = i - pos + 1;
   int l = i + 1, r = len - pos, m = l + r >> 1;
   F[l].push_back(make_pair(m, pos));
   if (m < r) B[r].push_back(make_pair(m + 1, pos));
   pos++;
  }
  if (cur == len) cur = pi[cur];
 }
 for (int i = 1; i < pos; i++) dp[i] = make_pair(-1, i);
 for (int i = 1; i <= len; i++) vec[i].clear();
 for (int i = 1; i <= len; i++) {
  a[i] = min(d[i], i);
  vec[i + 1 - d[i]].push_back(i);
 }
 build(1, 1, len);
 int mm = 0;
 for (int i = 1; i <= len; i++) {
  for (int j = 0; j < F[i].size(); j++) {
   int r = F[i][j].first, id = F[i][j].second;
   pair<int, int> ret = get(1, 1, len, i, r);
   int m = ret.second, dd = ret.first;
   int x = min(mm, r), dx = (x - i + 1) / 2 + 1;
   if (dd >= dx) dp[id] = max(dp[id], make_pair(dd, m));
   else dp[id] = max(dp[id], make_pair(dx, x));
  }
  for (int j = 0; j < vec[i].size(); j++) {
   add(1, 1, len, vec[i][j], vec[i][j], -len);
   mm = max(vec[i][j], mm);
  }
 }
 for (int i = 1; i <= len; i++) vec[i].clear();
 for (int i = 1; i <= len; i++) {
  a[i] = min(d[i], len - i + 1);
  vec[i + d[i] - 1].push_back(i);
 }
 build(1, 1, len);
 mm = len + 1;
 for (int i = len; i >= 1; i--) {
  for (int j = 0; j < B[i].size(); j++) {
   int l = B[i][j].first, id = B[i][j].second;
   pair<int, int> ret = get(1, 1, len, l, i);
   int m = ret.second, dd = ret.first;
   int x = max(l, mm), dx = (i - x + 1) / 2 + 1;
   if (dd >= dx) dp[id] = max(dp[id], make_pair(dd, m));
   else dp[id] = max(dp[id], make_pair(dx, x));
  }
  for (int j = 0; j < vec[i].size(); j++) {
   add(1, 1, len, vec[i][j], vec[i][j], -len);
   mm = min(mm, vec[i][j]);
  }
 }
 for (int i = 1; i < pos; i++) {
  
# 165 "data/404.cpp" 3 4
 (static_cast <bool> (
# 165 "data/404.cpp"
 dp[i].first >= 1
# 165 "data/404.cpp" 3 4
 ) ? void (0) : __assert_fail (
# 165 "data/404.cpp"
 "dp[i].first >= 1"
# 165 "data/404.cpp" 3 4
 , "data/404.cpp", 165, __extension__ __PRETTY_FUNCTION__))
# 165 "data/404.cpp"
                         ;
  if (ans < 2 * i + 2 * dp[i].first - 1) {
   ans = 2 * i + 2 * dp[i].first - 1;
   out = hexa(L[i], i, dp[i].second - dp[i].first + 1, dp[i].first * 2 - 1, len - i + 1, i);
  }
 }
 int cnt = 0;
 for (int i = 0; i < 3; i++) cnt += (!!out.b[i]);
 printf("%d\n", cnt);
 for (int i = 0; i < 3; i++) if (!!out.b[i]) printf("%d %d\n", out.a[i], out.b[i]);
 return 0;
}

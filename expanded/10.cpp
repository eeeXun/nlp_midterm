# 2 "data/10.cpp"
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
char s[maxn];
int n, m, b[maxn], first[maxn];
pair<int,int> st[18][maxn];

int main(){
 scanf("%s", s);
 n = strlen(s);
 for(int i = 0, l = 0, r = -1; i<n; i++) {
  int k = i > r ? 1 : min(st[0][l+r-i].first, r-i+1);
  while(i >= k && i+k < n && s[i-k] == s[i+k]) k++;
  st[0][i] = { k--, i };
  if (i+k > r) r = i+k, l = i-k;
 }
 for(int k = 1; (1<<k) <= n; k++) {
  int dis = 1<<k, d = 1<<(k-1);
  for(int i = 0; i+dis<=n; i++) st[k][i] = max(st[k-1][i], st[k-1][i+d]);
 }
 auto rmq = [&](int l, int r) -> pair<int,int> {
  int k = 31 - __builtin_clz(r-l+1);
  return max(st[k][l], st[k][r-(1<<k)+1]);
 };
 s[n] = '#';
 memcpy(s+n+1, s, n);
 reverse(s, s+n);
 m = n+n+1;

 for(int i = 1, j = 0; i<m; i++) {
  while(j > 0 && s[i] != s[j]) j = b[j-1];
  b[i] = j += (s[i] == s[j]);
 }

 for(int i = m-1; i > n; i--) first[b[i]] = i;
 auto p = rmq(0, n-1);
 int curbest = 2 * p.first - 1;
 vector<pair<int,int>> ans = { make_pair(p.second - p.first + 1, curbest) };
 for(int i = 0; 2*(i+1)<n; i++) {
  int slen = i+1;
  int L = first[slen]-n, R = n-1-slen;
  if (min(L, R) < 0 || L > R) { continue; }
  int l = 1, r = R-L+1;
  while (l < r) {
   int mid = l + (r-l+1) / 2;
   int ql = L+mid-1, qr = R-mid+1;
   if (ql > qr) { r = mid-1; continue; }
   auto p = rmq(ql, qr);
   if (p.first >= mid) l = mid;
   else r = mid -1;
  }
  auto p = rmq(L+l-1, R-l+1);
  int score = l+l-1 + slen + slen;
  if (score > curbest) {
   ans.clear();
   ans.emplace_back(L - slen, slen);
   ans.emplace_back(p.second-l+1, l+l-1);
   ans.emplace_back(R+1, slen);
   curbest = score;
  }
 }
 printf("%zu\n", ans.size());
 for(auto&p: ans) printf("%d %d\n", p.first+1, p.second);
 return 0;
}

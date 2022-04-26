



# 6 "data/156.cpp"
using namespace std;
const int N = 100005;
int n, nxt[N], len[N], z[N << 1], tn, ans;
char s[N], ns[N << 1];
pair<int, int> h[N];
vector< pair<int, int> > Ans;
void kmp() {
 for (int i = 2, j = 0; i <= n; i++) {
  while (j && ns[i] != ns[j + 1]) j = nxt[j];
  if (ns[i] == ns[j + 1]) j++;
  nxt[i] = j;
 }
}
void manacher() {
 tn = n << 1 | 1;
 for (int i = 1; i <= n; i++) ns[i << 1] = s[i];
 for (int i = 0; i <= n; i++) ns[i << 1 | 1] = '#';
 int mxr = 0, mid = 0;
 for (int i = 1; i <= tn; i++) {
  if (i <= mxr) z[i] = min(z[(mid << 1) - i], mxr - i + 1);
  while (i + z[i] <= tn && i - z[i] >= 1 && ns[i + z[i]] == ns[i - z[i]]) z[i]++;
  if (i + z[i] - 1 > mxr) mxr = i + z[i] - 1, mid = i;
 }
}
int main() {
 scanf("%s", s + 1); n = strlen(s + 1);
 for (int i = 1; i <= n; i++) ns[i] = s[n - i + 1];
 kmp();
 for (int i = 1, j = 0; i <= n; i++) {
  while (j && s[i] != ns[j + 1]) j = nxt[j];
  if (s[i] == ns[j + 1]) j++;
  len[i] = j;
 }
 manacher();
 for (int i = 1; i <= n; i++) if (i <= n - len[i]) h[i] = make_pair(len[i], i); else h[i] = make_pair(0, 0);
 for (int i = 1; i <= n; i++) h[i] = max(h[i], h[i - 1]);
 int ans = 0;
 for (int i = 1, l, r, tmp; i <= n; i++) {
  l = i - z[i << 1] / 2 + 1; r = i + z[i << 1] / 2 - 1;
  pair<int, int> now = h[l - 1]; int res = n - r;
  if (now.first > res) now.second -= (now.first - res), now.first = res;
  tmp = (now.first << 1) + r - l + 1;
  if (tmp > ans) {
   ans = tmp; Ans.clear();
   if (now.first) Ans.push_back(make_pair(now.second - now.first + 1, now.first));
   Ans.push_back(make_pair(l, r - l + 1));
   if (now.first) Ans.push_back(make_pair(n - now.first + 1, now.first));
  }
 }
 printf("%d\n", (int) Ans.size());
 for (auto tmp : Ans) printf("%d %d\n", tmp.first, tmp.second);
 return 0;
}

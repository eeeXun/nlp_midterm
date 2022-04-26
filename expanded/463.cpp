




# 8 "data/463.cpp"
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
 for (int i = (0); i <= ((int)st.size() - 1); i++) {
  if (i <= mx) r[i] = min(mx - i + 1, r[2 * p - i]);
  else r[i] = 1;
  while (i - r[i] >= 0 && i + r[i] <= (int)st.size() - 1 && st[i - r[i]] == st[i + r[i]]) ++r[i];
  if (i + r[i] - 1 > mx) p = i, mx = i + r[i] - 1;
 }
}

void kmp(string st) {
 nxt[0] = -1;
 for (int i = (1); i <= ((int)st.size() - 1); i++) {
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
 for (int i = (st.size() + 1); i <= (st.size() * 2); i++) mx[i - st.size() - 1] = make_pair(nxt[i] + 1, i - (int)st.size() - 1);
 for (int i = (1); i <= ((int)st.size() - 1); i++) chkmax(mx[i], mx[i - 1]);
 for (int i = (0); i <= ((int)st.size() - 1); i++) {
  int l = i - ::r[i], r = i + ::r[i];







  int t = min(l < 0 ? 0 : mx[l].first, (int)st.size() - 1 - r + 1);
  int len = t * 2 + ::r[i] * 2 - 1;
  if (len > maxn) {
   maxn = len;




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


 cout << (tag ? 1 : 3) << endl;
 for (int i = (1); i <= (tag ? 1 : 3); i++) cout << ans[i].first + 1 << " " << ans[i].second << endl;
 return 0;
}

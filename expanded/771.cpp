# 2 "data/771.cpp"
using namespace std;

typedef pair<int, int> pii;
const int N = 1e5 + 100, base = 269, MOD = 1000 * 1000 * 1000 + 9;

int sum(int a, int b) {
 a += b;
 if (a < 0)
  a += MOD;
 else if (a >= MOD)
  a -= MOD;
 return a;
}
void _sum(int &a, int b) {
 a = sum(a, b);
}
int mul(int a, int b) {
 return 1LL * a * b % MOD;
}
void _mul(int &a, int b) {
 a = mul(a, b);
}

int n, hash_l[N], hash_r[N], p_base[N], len[N], mx[N];
string s;

int get_l(int l, int r) {
 return sum(hash_l[r + 1], -mul(hash_l[l], p_base[r - l + 1]));
}
int get_r(int l, int r) {
 return sum(hash_r[l], -mul(hash_r[r + 1], p_base[r - l + 1]));
}

void input_ready() {
 cin >> s;
 n = s.length();
 for (int i = 0; i < n; i++)
  hash_l[i + 1] = sum(mul(hash_l[i], base), s[i]);
 for (int i = n - 1; ~i; i--)
  hash_r[i] = sum(mul(hash_r[i + 1], base), s[i]);
 p_base[0] = 1;
 for (int i = 1; i < N; i++)
  p_base[i] = mul(p_base[i - 1], base);
}

void find_len() {
 for (int i = 0; i < n; i++) {
  int l = 0, r = n - i + 1;
  while (r - l > 1) {
   int c = l + r >> 1;
   if (get_l(i, i + c - 1) == get_r(n - c, n - 1))
    l = c;
   else
    r = c;
  }
  len[i] = mx[i] = l;
 }
 for (int i = 1; i < n; i++)
  mx[i] = max(mx[i - 1], mx[i]);
}

int max_pal(int x) {
 int l = 1, r = min(x + 2, n - x + 1);
 while (r - l > 1) {
  int c = l + r >> 1;
  if (get_l(x - c + 1, x) == get_r(x, x + c - 1))
   l = c;
  else
   r = c;
 }
 return l;
}

void solve() {
 int ans = -1;
 vector<pii> vec;
 for (int i = 0; i < n; i++) {
  int l = max_pal(i);
  int val = 2 * l - 1;
  int s = 0, e = min(i + 1 - l, n - (i + l)) + 1;
  while (e - s > 1) {
   int mid = s + e >> 1;
   if (mx[i - l - mid + 1] >= mid)
    s = mid;
   else
    e = mid;
  }
  val += 2 * s;
  if (val > ans) {
   ans = val;
   vec.clear();
   if (s) {
    for (int i = 0;; i++)
     if (len[i] >= s) {
      vec.push_back(pii(i, s));
      break;
     }
   }
   vec.push_back(pii(i - l + 1, 2 * l - 1));
   if (s)
    vec.push_back(pii(n - s, s));
  }
 }
 cout << vec.size() << '\n';
 for (pii p: vec)
  cout << p.first + 1 << ' ' << p.second << '\n';
}

int main() {
 ios::sync_with_stdio(false), cin.tie(0);
 input_ready();
 find_len();
 solve();
}

# 2 "data/711.cpp"
using namespace std;

int const N = 2e5 + 10;

string s, t;
int z[N], p[N], q[N];
int pre[N], idx[N];

void Z(const string &s, int const n) {
 for (int i=1,l=0,r=0; i<n; ++i) {
  if (i <= r) z[i] = min(z[i-l], r-i+1);
  else z[i] = 0;
  while (i + z[i] < n && s[i+z[i]] == s[z[i]]) ++z[i];
  if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
 }
 int m = n >> 1;
 for (int i=0; i<m; ++i) {
  int L = z[i+m+1], ed = i + L - 1;
  q[ed] = max(q[ed], L);
 }
 for (int i=m-1; i>=0; --i) {
  q[i] = max(q[i+1]-1, q[i]);
 }
 for (int i=0; i<m; ++i) {
  if (i > 0) pre[i] = pre[i-1], idx[i] = idx[i-1];
  if (i >= m - q[i]) continue;
  if (q[i] > pre[i]) pre[i] = q[i], idx[i] = i;
 }
}

void M(const string &s, int const n) {
 for (int i=0,k=0,r=0; i<n; ++i) {
  if (i <= r) p[i] = min(p[2*k-i], r-i+1);
  else p[i] = 0;
  while (i - p[i] >= 0 && i + p[i] < n && s[i+p[i]] == s[i-p[i]]) ++p[i];
  if (i + p[i] - 1 > r) k = i, r = i + p[i] - 1;
 }
}

int main() {
 ios_base::sync_with_stdio(false);
 cin >> s;
 int n = (int)s.length();
 t = s;
 reverse(begin(t), end(t));
 t += "#" + s;
 Z(t, n<<1|1);
 M(s, n);
 int mx = 0;
 vector <pair<int,int>> o;
 for (int i=0; i<n; ++i) {
  int cc = 2 * p[i] - 1, j = i - p[i] + 1;
  if (j > 0) {
   --j;
   int a = pre[j];
   if (i + p[i] - 1 >= n - pre[j]) a = n - (i + p[i]);
   cc = a + cc + a;
   if (cc > mx) {
    o.clear();
    mx = cc;
    if (a > 0) o.push_back({idx[j]-pre[j]+1, a});
    o.push_back({j+1, 2*p[i]-1});
    if (a > 0) o.push_back({n-a, a});
   }
  } else {
   if (cc > mx) {
    mx = cc;
    o.clear();
    o.push_back({j, cc});
   }
  }
 }



 printf("%d\n", (int)o.size());
 for (auto &p: o) printf("%d %d\n", p.first+1, p.second);
 return 0;
}

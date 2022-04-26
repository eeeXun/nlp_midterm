# 2 "data/789.cpp"
using namespace std;

using lli = long long;

inline bool minimise(int &x, int y) {
 if (x > y) { x = y; return true; }
 return false;
}

inline bool maximise(int &x, int y) {
 if (x < y) { x = y; return true; }
 return false;
}

template <class T>
void compress(T *arr, T *arr_fin) {
 vector<lli> val(arr, arr_fin);
 sort(val.begin(), val.end());
 for (T *it = arr; it != arr_fin; it++)
  *it = lower_bound(val.begin(), val.end(), *it) - val.begin();
}

template <class T, int MAX, int LOG_MAX = 20>
class RangeQuery {
private:
 int n, LOG_2[MAX];
 T rmq[LOG_MAX][MAX];

public:
 void init(int _n, int seq[]) {
  n = _n;
  LOG_2[0] = -1;
  for (int i = 1; i <= n; i++) LOG_2[i] = LOG_2[i >> 1] + 1;
  copy(seq, seq + n, rmq[0]);

  for (int j = 1; j < LOG_MAX; j++)
   for (int i = 0; i + (1 << j) <= n; i++)
    rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
 }

 inline T get_min(int l, int r) {
  int j = LOG_2[r - l + 1];
  return min(rmq[j][l], rmq[j][r - (1 << j) + 1]);
 }
};

template <int MAX, int LOG_MAX = 20>
class SuffixArray {
private:
 int n, sa[MAX];
 lli rnk[MAX], old_rnk[MAX];

 int lcp[MAX];
 RangeQuery<int, MAX> rmq_lcp;

public:
 void init(const string &str) {
  n = str.size();
  for (int i = 0; i < n; i++) rnk[i] = str[i];
  compress(rnk, rnk + n);

  for (int j = 1; j < LOG_MAX; j++) {
   copy(rnk, rnk + n, old_rnk);
   for (int i = 0; i < n; i++)
    rnk[i] = old_rnk[i] * n + old_rnk[(i + (1 << (j - 1))) % n];
   compress(rnk, rnk + n);
  }

  iota(sa, sa + n, 0);
  sort(sa, sa + n, [&](int i, int j) { return rnk[i] < rnk[j]; });

  for (int i = 0, val = 0; i < n; i++) if (rnk[i] != n - 1) {
   int j = sa[rnk[i] + 1];
   while (str[i + val] == str[j + val]) val++;
   lcp[rnk[i]] = val;

   if (val > 0) val--;
  }

  rmq_lcp.init(n - 1, lcp);
 }

 int get_lcp_sa(int l, int r) {
  if (l == r) return n - 1 - sa[l];
  return rmq_lcp.get_min(l, r - 1);
 }

 int get_lcp(int i, int j) {
  int l = rnk[i], r = rnk[j];
  if (l > r) swap(l, r);
  if (l == r) return n - 1 - i;
  return rmq_lcp.get_min(l, r - 1);
 }

 inline int get_rnk(int i) {
  return rnk[i];
 }
};

const int INF = 1e9;
const int MAX = 1e5 + 7;
int n;
string str, str_rev, T;
SuffixArray<2 * MAX> SA;

inline int INDEX(int j, int i) {
 if (j == 0) return i;
 if (i == n) return 2 * n + 1;
 return 2 * n - i;
}

inline int cost(vector<pair<int, int>> sol) {
 int sum = 0;
 for (const auto &e : sol) sum += e.second;
 return sum;
}

void input() {
 cin >> str;
 n = str.length();

 str_rev = str;
 reverse(str_rev.begin(), str_rev.end());

 T = str + "@" + str_rev + "$";
 SA.init(T);
}

int left_most_prefix[MAX];
pair<int, int> mid_seg[MAX];

void solve() {
 vector<pair<int, int>> ans;

 left_most_prefix[0] = 0;
 for (int len = 1; len <= n; len++) {
  int x = n - len;
  int sta = left_most_prefix[len - 1];
  while (sta < n) {
   if (SA.get_lcp(INDEX(0, x), INDEX(1, sta + len - 1)) >= len)
    break;

   sta++;
  }

  left_most_prefix[len] = sta;
 }

 for (int m = 0; m < n; m++) {
  int mid_half_len = SA.get_lcp(INDEX(0, m), INDEX(1, m)) - 1;
  int l = m - mid_half_len, r = m + mid_half_len;
  mid_seg[m] = {l, r};

  int l_slen = 0, r_slen = min(l, n - r - 1);
  int side_len = -1, sta = -1;

  while (l_slen <= r_slen) {
   int m_slen = (l_slen + r_slen) / 2;
   int cur_sta = left_most_prefix[m_slen];

   if (cur_sta < n and cur_sta + m_slen <= l) {
    sta = cur_sta;
    side_len = m_slen;
    l_slen = m_slen + 1;
   }
   else
    r_slen = m_slen - 1;
  }

  vector<pair<int, int>> cur_ans(1, {l, r - l + 1});
  if (side_len > 0) {
   cur_ans.emplace_back(sta, side_len);
   cur_ans.emplace_back(n - side_len, side_len);
  }

  if (cost(ans) < cost(cur_ans))
   ans = cur_ans;
 }

 sort(ans.begin(), ans.end());
 cout << ans.size() << "\n";
 for (const auto &e : ans)
  cout << e.first + 1 << " " << e.second << "\n";
}

int main(void) {
 ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

 input();
 solve();

 return 0;
}

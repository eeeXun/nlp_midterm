# 4 "data/930.cpp" 2



# 6 "data/930.cpp"
using namespace std;

const int inf = 1000000000;

string str, z_str;
vector<int> z, d1, logs;
vector< vector< pair<int, int> > > sparse_table;
int i;

void logs_calc() {
 logs.resize(str.size() + 1);

 int cur = 2;

 for (int i = 2; i < logs.size(); i++) {
  if (i < cur) {
   logs[i] = logs[i - 1];
  } else {
   logs[i] = logs[i - 1] + 1;
   cur *= 2;
  }
 }
}

void build(vector<int> &d1) {
 logs_calc();

 sparse_table.resize(logs[d1.size()] + 1, vector< pair<int, int> > (d1.size()));

 int i, j;

 for (i = 0; i < sparse_table[0].size(); i++) {
  sparse_table[0][i] = make_pair(d1[i], i);
 }

 for (i = 1; i < sparse_table.size(); i++) {
  for (j = 0; j < sparse_table[i].size() - (1 << (i - 1)); j++) {
   sparse_table[i][j] = max(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
  }
 }
}

pair<int, int> get_max(int l, int r, int x) {
 int len = r - l;

 if (len <= 0) {
  return make_pair(inf, inf);
 }

 int lg = logs[len];

 pair<int, int> a = max(sparse_table[lg][l], sparse_table[lg][r - (1 << lg)]);

 if (a.first >= x) {
  return a;
 } else {
  return make_pair(inf, inf);
 }
}

void z_func(string &str, vector<int> &z) {
 z.resize(str.size());

 for (int i = 1, l = 0, r = 0; i < str.size(); i++) {
  if (i <= r) {
   z[i] = min(z[i - l], r - i + 1);
  }

  while (z[i] + i < str.size() && str[z[i] + i] == str[z[i]]) {
   z[i]++;
  }

  if (z[i] + i - 1 > r) {
   l = i;
   r = z[i] + i - 1;
  }
 }
}

void palindroms(string &str, vector<int> &d1) {
 d1.resize(str.size());

 int l = 0, r = -1, i;

 for (i = 0; i < d1.size(); i++) {
  int k;

  if (i > r) {
   k = 1;
  } else {
   k = min(r - i, d1[l + r - i]);
  }

  while (i + k < d1.size() && i - k >= 0 && str[i + k] == str[i - k]) {
   k++;
  }

  d1[i] = k;

  if (i + k > r) {
   l = i - k;
   r = i + k;
  }
 }

 for (i = 0; i < d1.size(); i++) {
  d1[i] = d1[i] * 2 - 1;
 }
}

pair<int, int> bins(int l, int r, int x, int y) {
 int pr_x = -1;

 while (y - x > 1) {
  int m = (y + x) / 2;

  pair<int, int> a = get_max(l + m / 2, r - m / 2, m);

  if (a.first != inf) {
   x = m;
   pr_x = a.second;
  } else {
   y = m;
  }
 }


 return make_pair(x, pr_x);
}

int main(int argc, const char * argv[]) {


 cin >> str;

 z_str = "#" + str;

 reverse(str.begin(), str.end());

 z_str = str + z_str;

 reverse(str.begin(), str.end());

 palindroms(str, d1);

 z_func(z_str, z);

 z_str.clear();

 build(d1);

 int n = (int) str.size() + 1;
 int l_p = 0, l_m = 0;
 int x_p = 0, x_s = 0, x_m = 0;

 for (i = n; i < z.size(); i++) {
  int len = min(z[i], (n - 1) / 2);
  int pref_start = i - n;
  int suff_start = n - 1 - len;

  if (suff_start >= pref_start + len) {

   pair<int, int> a = bins(i - n + len, n - 1 - len, 0, suff_start - pref_start + 1);

   int pol_len;

   (a.first == -1) ? pol_len = 0 : pol_len = a.first;

   if (pol_len == 0) {
    len--;
    a = bins(i - n + len, n - 1 - len, 0, suff_start - pref_start + 1);
    (a.first == -1) ? pol_len = 0 : pol_len = a.first;
    suff_start++;
   }

   if ( len * 2 + pol_len > l_m + l_p * 2) {
    l_p = len;
    l_m = max(0, pol_len);
    x_p = pref_start;
    x_s = suff_start;
    x_m = a.second - pol_len / 2;
   }
  }
 }

 int cnt = 0;

 if (l_m != 0) {
  cnt++;
 }

 if (l_p != 0) {
  cnt += 2;
 }

 cout << cnt << endl;

 if (l_p != 0) {
  cout << x_p + 1 << ' ' << l_p << endl;

  if (l_m != 0) {
   cout << x_m + 1 << ' ' << l_m << endl;
  }

  cout << x_s + 1<< ' ' << l_p;
 } else if (l_m != 0) {
  cout << x_m + 1 << ' ' << l_m;
 }
}

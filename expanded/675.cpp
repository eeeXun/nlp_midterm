

}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/675.cpp" 2
# 10 "data/675.cpp"

# 10 "data/675.cpp"
typedef long long num;

using namespace std;

int mx;
string s, rs;
vector<int> d, z, pre, fm;
vector< pair<int, int> > ans;

void inline z_init(string s, vector<int> &z) {
 z.resize(s.size());
 fill(z.begin(), z.end(), 0);
 for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
  i <= r && (z[i] = min(r - i + 1, z[i - l]));
  for (; i + z[i] < s.size() && s[z[i]] == s[i + z[i]]; ++z[i]);
  i + z[i] - 1 > r && (l = i, r = i + z[i] - 1);
 }
}

void inline manacher_init(string s, vector<int> &d) {
 d.resize(s.size());
 fill(d.begin(), d.end(), 0);
 for (int i = 0, l = 0, r = 0; i < s.size(); ++i) {
  i <= r && (d[i] = min(r - i + 1, d[r + l - i]));
  for (; i - d[i] >= 0 && i + d[i] < s.size() && s[i - d[i]] == s[i + d[i]]; ++d[i]);
  i + d[i] - 1 > r && (l = i - d[i] + 1, r = i + d[i] - 1);
 }
}

int main() {
 ios::sync_with_stdio(0);
 cin >> s;
 rs = s;
 reverse(rs.begin(), rs.end());
 z_init(rs + '#' + s, z);
 manacher_init(s, d);
 for (int i = 0; i < s.size(); ++i) {
  z[i] = z[i + s.size() + 1];
 }
 z.resize(s.size());
 for (int i = z.size() - 1; i >= 0; --i) {
  if (z[i] <= 1) continue;
  z[i + z[i] - 1] = z[i];
  z[i] = 0;
 }
 pre.push_back(z[0]);
 fm.push_back(0);
 for (int i = 1; i <= (int) z.size() - 1; ++i) {
  pre.push_back(max(pre[i - 1], z[i]));
  fm.push_back(pre[i] == pre[i - 1] ? fm[i - 1] : i);
 }
 for (int i = 0; i < s.size(); ++i) {
  int l = i - d[i] + 1, r = i + d[i] - 1, len = min((int) s.size() - r - 1, l ? pre[l - 1] : 0), cur = d[i] * 2 - 1 + len * 2;
  if (cur > mx) {
   mx = cur;
   ans.clear();
   if (len) {
    ans.push_back(make_pair(fm[l - 1] - len + 2, len));
    ans.push_back(make_pair(s.size() - len + 1, len));
   }
   ans.push_back(make_pair(l + 1, d[i] * 2 - 1));
  }
 }
 sort(ans.begin(), ans.end());
 cout << ans.size() << '\n';
 for (int i = 0; i < ans.size(); ++i) {
  cout << ans[i].first << ' ' << ans[i].second << '\n';
 }
}



}
# 8 "data/500.cpp" 2




# 11 "data/500.cpp"
using namespace std;


const int MAXN = 100010;
const int INF = 1000000000;

int n;
string s;
int lpos[MAXN];
int rpos[MAXN];
int query[MAXN];
int pal[MAXN];

void calc_pos() {


 string t = string (s.rbegin(), s.rend()) + '#' + s;
 vector<int> pi (t.length());
 for (size_t i=1; i<t.length(); ++i) {
  pi[i] = pi[i-1];
  while (pi[i] && t[pi[i]] != t[i])
   pi[i] = pi[pi[i]-1];
  if (t[pi[i]] == t[i])
   ++pi[i];
 }

 for (int i=0; i<MAXN; ++i)
  rpos[i] = INF;
 rpos[0] = 0;

 for (size_t i=0; i<s.length(); ++i) {
  size_t j = s.length() + 1 + i;
  if (rpos[pi[j]] == INF)
   rpos[pi[j]] = (int)i;
 }


 for (int i=0; i<MAXN; ++i)
  if (rpos[i] == INF)
   lpos[i] = INF;
  else
   lpos[i] = rpos[i] - (i - 1);
}

void calc_query() {


 int j = 0;
 for (int i=0; i<n; ++i) {
  while (rpos[j+1] <= i)
   ++j;
  query[i] = j;
 }
}

void calc_pal() {


 int l = 0, r = -1;
 for (int i=0; i<n; ++i) {
  int len = i<=r ? min(pal[r-i+l],r-i) : 0;
  while (i-len-1>=0 && i+len+1<n && s[i-len-1] == s[i+len+1])
   ++len;
  pal[i] = len;

  if (i+len > r)
   l = i-len, r = i+len;
 }
}

int calc_ans (int pos, vector < pair<int,int> > & ans) {


 int max_lt = pos - pal[pos] - 1,
  min_rt = pos + pal[pos] + 1,
  len = max_lt>=0 ? min (query[max_lt], n-min_rt) : 0,
  result = 2 * len + pal[pos] * 2 + 1;

 ans.clear();
 if (len)
  ans.push_back (make_pair (lpos[len], len));
 ans.push_back (make_pair (pos-pal[pos], pal[pos]*2+1));
 if (len)
  ans.push_back (make_pair (n-len, len));

 return result;
}


int main() {

 static char buf[MAXN];
 gets (buf);
 s = buf;
 n = (int) s.length();

 calc_pos();
 calc_query();
 calc_pal();

 vector < pair<int,int> > ans, cans;
 int ans_len = -1;
 for (int i=0; i<n; ++i) {
  int len = calc_ans (i, cans);
  if (len > ans_len) {
   ans_len = len;
   swap (ans, cans);
  }
 }

 printf ("%d\n", ans.size());
 for (size_t i=0; i<ans.size(); ++i)
  printf ("%d %d\n", ans[i].first+1, ans[i].second);

}

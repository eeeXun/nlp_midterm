
  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/650.cpp" 2

# 2 "data/650.cpp"
using namespace std;
# 15 "data/650.cpp"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, ans;
int pa[N << 1], ns[N], nt[N], ma[N], pos[N];
vector<pii> res;
char s[N], sr[N];

void Manacher(char *s,int n,int *pa){
 pa[0] = 1;
 for(int i=1,j=0;i<(n<<1)-1;++i){
  int p = i >> 1 , q = i - p , r = ((j + 1)>>1) + pa[j] - 1;
  pa[i] = r < q ? 0 : min(r - q + 1 , pa[(j<<1) - i]);
  while(0 <= p - pa[i] && q + pa[i] < n && s[p - pa[i]] == s[q + pa[i]])
   pa[i]++;
  if(q + pa[i] - 1 > r) j = i;
 }
 for(int i = (0); i < (n); ++i) pa[i] = pa[i << 1];
}

void kmp(char *s,int *ns,char *t,int *nt){
 int lens = strlen(s);
 int lent = strlen(t);
 nt[0] = -1;
 for(int i=0,j=-1;i<lens;++i){
  while(j >= 0 && s[i] != t[j + 1]) j = nt[j];
  if(s[i] == t[j + 1]) ++j;
  ns[i] = j;
  if(j + 1 == lent) j = nt[j];
 }
}

int main() {
 std::ios::sync_with_stdio(0);
 std::cin.tie(0);
 cin >> s;
 n = strlen(s);
 Manacher(s, n, pa);
 for(int i = (0); i < (n); ++i) sr[i] = s[n - 1 - i];sr[n] = '\0';
 kmp(sr + 1, nt + 1, sr, nt);
 kmp(s, ns, sr, nt);
 for(int i = (0); i < (n); ++i) if(~ns[i]) ++ns[i];
 ma[0] = ns[0];
 pos[0] = 0;
 for(int i = (1); i < (n); ++i) {
  ma[i] = ma[i - 1];
  pos[i] = pos[i - 1];
  if(ma[i] < ns[i]) {
   ma[i] = ns[i];
   pos[i] = i;
  }
 }
 for(int i = (0); i < (n); ++i) {
  int k = i - pa[i];
  int t = max(0, min(k < 0 ? 0 : ma[k], n - i - pa[i]));
  int c = pa[i] * 2 - 1 + t * 2;
  if(ans < c) {
   ans = c;
   res.clear();
   res.push_back(make_pair(i - pa[i] + 1, pa[i] * 2 - 1));
   if(t) {
    res.push_back(make_pair(n - t, t));
    int o = pos[k] - 2 * ns[pos[k]] + t + 1;
    res.push_back(make_pair(o, t));
   }
  }
 }
 sort(res.begin(), res.end());
 cout << (int)res.size() << "\n";
 for(auto u : res) cout << u.first + 1 << " " << u.second << "\n";
 return 0;
}

      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/519.cpp" 2


# 3 "data/519.cpp"
using namespace std;
# 25 "data/519.cpp"
typedef pair < int ,int > pii;

typedef long long ll;

const long long linf = 1e18+5;
const int mod = (int) 1e9 + 7;
const int logN = 17;
const int inf = 1e9;
const int N = 2e5 + 5;

int mx, n, m, x, y, hash1[N], hash2[N], P[N], GO[N], k, t;
char str[N];
pii ans[4];

int get1(int x, int y) { return hash1[y] - hash1[x-1] * P[y-x+1]; }
int get2(int x, int y) { return hash2[x] - hash2[y+1] * P[y-x+1]; }

int get(int l, int r) {
 int bas = r+1, son = n;
 while(bas < son) {
  int orta = bas + son >> 1;
  if(GO[orta] >= l) bas = orta + 1;
  else son = orta;
 }
 if(GO[bas] < l) return n-bas+1;
 return 0;
}

void solve(int x) {
 int bas = 1, son = min(x, n-x+1);
 while(bas < son) {
  int orta = bas + son >> 1;
  if(orta == bas) orta++;
  if(get1(x-orta+1, x+orta-1) == get2(x-orta+1,x+orta-1)) bas = orta;
  else son = orta - 1;
 }
 int l = x-bas+1, r = x+bas-1;
 int sz = get(l, r), w = n - sz + 1;
 if(2 * sz + bas * 2 - 1 > mx) {
  mx = 2 * sz + bas * 2 - 1;
  k = (sz != 0) * 2 + 1;
  if(sz) { ans[3] = make_pair(w, sz); ans[1] = make_pair(GO[w]-sz+1, sz); ans[2] = make_pair(l, r-l+1); }
  else ans[1] = make_pair(l, r-l+1);
 }
}

int main() {

 scanf("%s", str+1);
 n = strlen(str+1);

 P[0] = 1;
 for(int i=1;i<=n;i++) P[i] = P[i-1] * 29;
 for(int i=1;i<=n;i++) hash1[i] = hash1[i-1] * 29 + str[i] - 'a';
 for(int i=n;i>=1;i--) hash2[i] = hash2[i+1] * 29 + str[i] - 'a';

 int j = 1;

 for(int i=n;i>=1;i--) {
  while(get1(i, n) != get2(j, j+n-i) && j < n) j++;
  GO[i] = j + n - i;
 }

 for(int i=1;i<=n;i++)
  solve(i);

 cout << k << '\n';

 for(int i=1;i<=k;i++)
  cout << ans[i].first << ' ' << ans[i].second << '\n';

 return 0;
}

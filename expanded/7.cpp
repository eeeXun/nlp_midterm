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
# 4 "data/7.cpp" 2
# 23 "data/7.cpp"

# 23 "data/7.cpp"
using namespace std;

typedef long long LL;
typedef double flt;
typedef vector<int> vi;
typedef vector<LL> vl;
typedef pair<int,int> pii;
typedef pair<int,LL> pil;
typedef pair<LL,int> pli;
typedef pair<LL,LL> pll;
typedef vector<pil> vil;
typedef vector<pii> vii;
typedef vector<pli> vli;
typedef vector<pll> vll;

const int iinf = 1e9 + 7;
const LL linf = 1ll << 60;
const flt dinf = 1e60;

template <typename T>
inline void scf(T &x)
{
 bool f = 0; x = 0; char c = getchar();
 while((c < '0' || c > '9') && c != '-') c = getchar();
 if(c == '-') { f = 1; c = getchar(); }
 while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
 if(f) x = -x; return;
}

template <typename T1, typename T2>
void scf(T1 &x, T2 &y) { scf(x); return scf(y); }

template <typename T1, typename T2, typename T3>
void scf(T1 &x, T2 &y, T3 &z) { scf(x); scf(y); return scf(z); }

template <typename T1, typename T2, typename T3, typename T4>
void scf(T1 &x, T2 &y, T3 &z, T4 &w) { scf(x); scf(y); scf(z); return scf(w); }

inline char mygetchar(){ char c = getchar(); while(c == ' ' || c == '\n') c = getchar(); return c; }

template <typename T>
void chkmax(T &x, const T &y){ if(y > x) x = y; return; }

template <typename T>
void chkmin(T &x, const T &y){ if(y < x) x = y; return; }
# 78 "data/7.cpp"
const int N = 2e5 + 100;

int n;
char s[N];
pii dp[N];
vii all;

namespace manacher
{
 char t[N];
 int r[N];

 void solve(char *s)
 {
  int n = 0;
  t[n++] = '#';
  for(int i = (1); i <= (::n); ++i) t[n++] = s[i], t[n++] = '$';
  t[n - 1] = '#';

  int rb = 0, rem;
  for(int i = (1); i <= (n - 2); ++i)
  {
   r[i] = (i > rb) ? 0 : min(r[rem + rem - i], rb - i);
   while(i + r[i] + 1 < n && i - r[i] - 1 >= 0 && t[i + r[i] + 1] == t[i - r[i] - 1]) r[i]++;
   if(i + r[i] > rb) rb = i + r[i], rem = i;
  }

  for(int i = (1); i <= (n - 2); ++i)
  {
   int lb = (i - r[i]) / 2 + 1, rb = (i + r[i]) / 2;
   if(lb <= rb && (rb - lb + 1) % 2 == 1) all.push_back(make_pair(lb, rb));
  }
  return;
 }
}

namespace kmp
{
 char t[N];
 int border[N];

 void solve(char *s)
 {
  for(int i = (1); i <= (n); ++i) t[i] = s[n - i + 1];

  border[0] = -1;
  for(int i = (1); i <= (n); ++i)
  {
   int j = border[i - 1];
   while(~j && t[j + 1] != t[i]) j = border[j];
   border[i] = j + 1;
  }

  int i = 0, j = 0;
  while(i < n)
  {
   ++i;
   while(~j && t[j + 1] != s[i]) j = border[j];
   dp[i] = make_pair((++j), i);
  }

  for(int i = (1); i <= (n); ++i) chkmax(dp[i], dp[i - 1]);
  return;
 }
}

void TZL()
{
 scanf("%s", s + 1);
 n = strlen(s + 1);
 manacher::solve(s);
 kmp::solve(s);
 return;
}

void RANK1()
{
 int ans = 0; vii rem;
 for(auto x: all)
 {
  int l = x.first, r = x.second;
  
# 159 "data/7.cpp" 3 4
 (static_cast <bool> (
# 159 "data/7.cpp"
 l >= 1 && r <= n
# 159 "data/7.cpp" 3 4
 ) ? void (0) : __assert_fail (
# 159 "data/7.cpp"
 "l >= 1 && r <= n"
# 159 "data/7.cpp" 3 4
 , "data/7.cpp", 159, __extension__ __PRETTY_FUNCTION__))
# 159 "data/7.cpp"
                         ;

  int calc = r - l + 1 + min(dp[l - 1].first, n - r) * 2;
  if(calc > ans)
  {
   ans = calc;
   rem.clear();
   rem.push_back(make_pair(l, r - l + 1));

   int foo = min(dp[l - 1].first, n - r);
   if(foo)
   {
    rem.push_back(make_pair(dp[l - 1].second - foo + 1, foo));
    rem.push_back(make_pair(n - foo + 1, foo));
   }
  }
 }

 printf("%d\n", (int)rem.size());
 sort(rem.begin(), rem.end());
 for(auto x: rem) printf("%d %d\n", x.first, x.second);
 return;
}




int main ()
{




 TZL();
 RANK1();




 return 0 ;



}


  template<typename... _Types>
    struct hash<variant<_Types...>>
    : private __detail::__variant::_Variant_hash_base<
 variant<_Types...>, std::index_sequence_for<_Types...>>,
      public __variant_hash_call_base<_Types...>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = variant<_Types...>;
    };

  template<>
    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
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
# 35 "data/117.cpp" 2


# 36 "data/117.cpp"
using namespace std;
# 50 "data/117.cpp"
typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template <class A, class B> ostream& operator << (ostream& out, const pair<A, B> &a) {
 return out << "(" << a.first << ", " << a.second << ")";
}

template <class A> ostream& operator << (ostream& out, const vector<A> &v) {
 out << "[";
 for(int i = 0; i < int(int(v.size())); i++) {
  if(i) out << ", ";
  out << v[i];
 }
 return out << "]";
}

mt19937 rnd(time(
# 67 "data/117.cpp" 3 4
                __null
# 67 "data/117.cpp"
                    ));

const int INF = int(1e9);
const li INF64 = li(1e18);
const int MOD = int(1e9) + 7;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

const int N = 100 * 1000 + 13;
const int LOGN = 18;

int n;
string s;

bool read () {
 static char buf[N];
 if (scanf("%s", buf) != 1)
  return false;
 s = buf;
 n = int(s.size());
 return true;
}

vector<int> zfunction(const string& s) {
 int n = int(s.size());
 vector<int> z(n);
 int l = 0, r = 0;
 for(int i = int(1); i < int(n); i++) {
  if (i <= r) z[i] = min(z[i - l], r - i + 1);
  while (i + z[i] < n && s[z[i]] == s[i + z[i]])
   ++z[i];
  if (i + z[i] - 1 > r) {
   l = i;
   r = i + z[i] - 1;
  }
 }
 return z;
}

int st[LOGN][N];
int pw[N];

int get(int l, int r){
 int len = pw[r - l];
 return max(st[len][l], st[len][r - (1 << len)]);
}

void solve() {
 vector<int> d1(n);
 for (int i = 0, l = 0, r = -1; i < n; i++) {
  int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
  while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
   k++;
  }
  d1[i] = k--;
  if (i + k > r) {
   l = i - k;
   r = i + k;
  }
 }
 for(int i = 0; i < int(n); i++) --d1[i];

 for(int i = 0; i < int(n); i++) st[0][i] = d1[i];
 for(int j = int(1); j < int(LOGN); j++) for(int i = 0; i < int(n); i++){
  st[j][i] = st[j - 1][i];
  if (i + (1 << (j - 1)) < n)
   st[j][i] = max(st[j][i], st[j - 1][i + (1 << (j - 1))]);
 }
 pw[0] = pw[1] = 0;
 for(int i = int(2); i < int(N); i++) pw[i] = pw[i / 2] + 1;

 string t = s;
 reverse(t.begin(), t.end());
 vector<int> zf = zfunction(t + "#" + s);
 int j = 0;
 int ans = 1;
 for(int i = int(1); i < int((n + 1) / 2); i++){
  while (j + i < n - i && zf[int(t.size()) + 1 + j] < i) ++j;
  int L = j + i, R = n - i - 1;
  if (L > R) break;
  int l = 0, r = (R - L) / 2;
  int res = 0;
  while (l <= r){
   int m = (l + r) / 2;
   if (get(L + m, R - m + 1) >= m){
    res = m;
    l = m + 1;
   }
   else{
    r = m - 1;
   }
  }
  ans = max(ans, 2 * i + 2 * res + 1);
 }

 if (*max_element(d1.begin(), d1.end()) * 2 + 1 >= ans){
  int pos = max_element(d1.begin(), d1.end()) - d1.begin();
  printf("1\n%d %d\n", pos - d1[pos] + 1, d1[pos] * 2 + 1);
  return;
 }

 cerr << ans << endl;
 j = 0;
 for(int i = int(1); i < int((n + 1) / 2); i++){
  while (j + i < n - i && zf[int(t.size()) + 1 + j] < i) ++j;
  int L = j + i, R = n - i - 1;
  if (L > R) break;
  int l = 0, r = (R - L) / 2;
  int res = 0;
  while (l <= r){
   int m = (l + r) / 2;
   if (get(L + m, R - m + 1) >= m){
    res = m;
    l = m + 1;
   }
   else{
    r = m - 1;
   }
  }
  if (2 * i + 2 * res + 1 == ans){
   puts("3");
   printf("%d %d\n", j + 1, i);
   for(int k = int(L + res); k < int(R - res + 1); k++) if (d1[k] >= res){
    printf("%d %d\n", k - res + 1, res * 2 + 1);
    break;
   }
   printf("%d %d\n", n - i + 1, i);
   return;
  }
 }
 
# 197 "data/117.cpp" 3 4
(static_cast <bool> (
# 197 "data/117.cpp"
false
# 197 "data/117.cpp" 3 4
) ? void (0) : __assert_fail (
# 197 "data/117.cpp"
"false"
# 197 "data/117.cpp" 3 4
, "data/117.cpp", 197, __extension__ __PRETTY_FUNCTION__))
# 197 "data/117.cpp"
             ;
}

int main() {
# 209 "data/117.cpp"
 cerr.precision(15);
 cout.precision(15);
 cerr << fixed;
 cout << fixed;







 while(read()) {

  solve();






 }
}

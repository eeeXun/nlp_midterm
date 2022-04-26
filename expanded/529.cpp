template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
min_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
min_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);

template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
max_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
max_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);

template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 19 "data/529.cpp" 2


# 20 "data/529.cpp"
using namespace std ;
# 46 "data/529.cpp"
typedef double db ;
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int maxn = 2e6 + 100 ;
const int inf = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const ll mod = 1e9 + 7 ;
const double eps = 1e-7 ;
template <class T = int> T read()
{
 T f = 1, a = 0;
 char ch = getchar() ;
 while (!isdigit(ch)) { if (ch == '-') f = -1 ; ch = getchar() ; }
 while (isdigit(ch)) { a = (a << 3) + (a << 1) + ch - '0' ; ch = getchar() ; }
 return a * f ;
}

int n;

char s[maxn];

ll sufhash[maxn], prehash[maxn], fac[maxn] = {1};

pii maxx[maxn], ans;

signed main()
{
 scanf("%s", s + 1);
 n = strlen(s + 1);
 for (register int i = (1); i <= (n); ++i) fac[i] = fac[i - 1] * 233 % mod;
 for (register int i = (n); i >= (1); --i) sufhash[i] = (sufhash[i + 1] + fac[(n - i)] * s[i]) % mod;
 for (register int i = (1); i <= (n); ++i) prehash[i] = (prehash[i - 1] + fac[i - 1] * s[i]) % mod;
 for (register int i = (1); i <= (n); ++i)
 {
  int l = 1, r = (n - i + 1) / 2, sum = 0;
  while(l <= r)
  {
   int mid = (l + r) >> 1;
   ll hash1 = (prehash[i + mid - 1] + mod - prehash[i - 1]) % mod, hash2 = sufhash[n - mid + 1] * fac[i - 1] % mod;
   if(hash1 == hash2) sum = mid, l = mid + 1;
   else r = mid - 1;
  }
  maxx[i + sum - 1] = max(maxx[i + sum - 1], make_pair(sum, i));
 }
 for (register int i = (n); i >= (1); --i)
 {
  pii tmp = maxx[i + 1];
  tmp.first --;
  maxx[i] = max(maxx[i], tmp);
 }
 for (register int i = (1); i <= (n); ++i) maxx[i] = max(maxx[i], maxx[i - 1]);
 for (register int i = (1); i <= (n); ++i)
 {
  int l = 1, r = min(i, n - i + 1), sum;
  while(l <= r)
  {
   int mid = (l + r) >> 1;
   ll hash1 = (prehash[i] + mod - prehash[i - mid]) % mod * fac[n - i] % mod, hash2 = (sufhash[i] + mod - sufhash[i + mid]) % mod * fac[i - 1] % mod;
   if(hash1 == hash2) sum = mid, l = mid + 1;
   else r = mid - 1;
  }
  ans = max(ans, make_pair(sum * 2 - 1 + 2 * min(n - i - sum + 1, maxx[i - sum].first), i));
 }
 int i = ans.second, l = 1, r = min(i, n - i + 1), sum;
 while(l <= r)
 {
  ll mid = (l + r) >> 1;
  ll hash1 = (prehash[i] + mod - prehash[i - mid]) % mod * fac[n - i] % mod, hash2 = (sufhash[i] + mod - sufhash[i + mid]) % mod * fac[i - 1] % mod;
  if(hash1 == hash2) sum = mid, l = mid + 1;
  else r = mid - 1;
 }
 int len = min(n - i - sum + 1, maxx[i - sum].first);
 if(!len)
 {
  puts("1");
  printf("%d %d\n", i - sum + 1, 2 * sum - 1);
 }
 else
 {
  puts("3");
  printf("%d %d\n", maxx[i - sum].second, len);
  printf("%d %d\n", i - sum + 1, 2 * sum - 1);
  printf("%d %d\n", n - len + 1, len);
 }
 return 0;
}

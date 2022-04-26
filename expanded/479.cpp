


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
# 9 "data/479.cpp" 2






# 14 "data/479.cpp"
typedef long long ll;
template <typename T> inline void read(T &x) {
 x = 0; char c = getchar(); bool flag = false;
 while (!isdigit(c)) { if (c == '-') flag = true; c = getchar(); }
 while (isdigit(c)) { x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
 if (flag) x = -x;
}
using namespace std;
const int P1 = 1e9 + 7;
const int P2 = 1e9 + 9;
const int base = 13331;
inline ll quickpow(ll x, int k, int P) {
 ll res = 1;
 while (k) {
  if (k & 1) res = res * x % P;
  x = x * x % P;
  k >>= 1;
 }
 return res;
}
inline void MAX(int &a, int b) {
 if (b > a) a = b;
}
inline void MIN(int &a, int b) {
 if (b < a) a = b;
}
inline void MAX(ll &a, ll b) {
 if (b > a) a = b;
}
inline void MIN(ll &a, ll b) {
 if (b < a) a = b;
}
char s[201000];
int n;
ll ha1[201000], ah1[201000];
ll ha2[201000], ah2[201000];
ll mi1[201000], minv1[201000];
ll mi2[201000], minv2[201000];
inline void Hash() {
 for (register int i = 1; i <= n; ++i) {
  ha1[i] = (ha1[i - 1] * base + s[i]) % P1;
  ha2[i] = (ha2[i - 1] * base + s[i]) % P2;
 }
 for (register int i = n; i; --i) {
  ah1[i] = (ah1[i + 1] * base + s[i]) % P1;
  ah2[i] = (ah2[i + 1] * base + s[i]) % P2;
 }
 mi1[0] = mi2[0] = minv1[0] = minv2[0] = 1;
 for (register int i = 1; i <= n; ++i) {
  mi1[i] = mi1[i - 1] * base % P1;
  minv1[i] = quickpow(mi1[i], P1 - 2, P1);
  mi2[i] = mi2[i - 1] * base % P2;
  minv2[i] = quickpow(mi2[i], P2 - 2, P2);
 }
}
inline pair<long long, long long> get1(int l, int len) {
 int r = l + len - 1;
 ll res1 = ((ha1[r] - ha1[l - 1] * mi1[len]) % P1 + P1) % P1;
 ll res2 = ((ha2[r] - ha2[l - 1] * mi2[len]) % P2 + P2) % P2;
 return make_pair(res1, res2);
}
inline pair<long long, long long> get2(int l, int len) {
 int r = l + len - 1;
 ll res1 = ((ah1[l] - ah1[r + 1] * mi1[len]) % P1 + P1) % P1;
 ll res2 = ((ah2[l] - ah2[r + 1] * mi2[len]) % P2 + P2) % P2;
 return make_pair(res1, res2);
}
int pos[201000];
struct Seg {
 int l, r;
}seg[201000];
bool cmp(const Seg &a, const Seg &b) {
 return a.r > b.r;
}
inline void init() {
 int ptr = 1;
 for (register int i = n; i > (n + 1) >> 1; --i) {
  while (ptr + n - i <= n && get1(ptr, n - i + 1) != get2(i, n - i + 1)) ++ptr;
  pos[i] = ptr + (n - i);

 }
 for (register int i = 1; i <= n; ++i) {
  int l = 0, r = min(n - i, i - 1), res = 0;
  while (l <= r) {
   int mid = (l + r) >> 1;
   if (get1(i - mid, mid) == get2(i + 1, mid)) res = mid, l = mid + 1;
   else r = mid - 1;
  }
  seg[i] = (Seg){i - res, i + res};
 }
 sort(seg + 1, seg + 1 + n, cmp);
}
int mx;
pair<int, int> ans;
int tre[201000];
inline void add(int cur, int x) {
 for (register int i = cur; i <= n; i += ((i)&(-(i))))
  MAX(tre[i], x);
}
inline int query(int cur) {
 int res = 0;
 for (register int i = cur; i; i -= ((i)&(-(i))))
  MAX(res, tre[i]);
 return res;
}
inline void work() {
 int ptr = n;
 for (register int i = 1; i <= n; ++i) {
  int l = seg[i].l, r = seg[i].r;

  while (ptr > (n + 1) >> 1 && ptr > r) add(pos[ptr], n - ptr + 1), --ptr;


  int tmp = query(l - 1);
  int res = tmp + tmp + r - l + 1;
  if (res > mx) mx = res, ans = make_pair(i, tmp);
 }
 int ml = seg[ans.first].l, mr = seg[ans.first].r;
 int rlen = ans.second, rgt = n - rlen + 1;
 int lft = pos[rgt] - rlen + 1, llen = rlen;

 if (rlen) {
  puts("3");
  printf("%d %d\n%d %d\n%d %d\n", lft, llen, ml, mr - ml + 1, rgt, rlen);
 } else {
  puts("1");
  printf("%d %d\n", ml, mr - ml + 1);
 }
}
int main() {
 scanf("%s", s + 1);
 n = strlen(s + 1);
 Hash();

 init();

 work();
 return 0;
}

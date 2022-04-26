






namespace std __attribute__ ((__visibility__ ("default")))
{




  template<size_t _Nb>
    struct hash<std::bitset<_Nb>>
    : public __hash_base<size_t, std::bitset<_Nb>>
    {
      size_t
      operator()(const std::bitset<_Nb>& __b) const noexcept
      {
 const size_t __clength = (_Nb + 8 - 1) / 8;
 return std::_Hash_impl::hash(__b._M_getdata(), __clength);
      }
    };

  template<>
    struct hash<std::bitset<0>>
    : public __hash_base<size_t, std::bitset<0>>
    {
      size_t
      operator()(const std::bitset<0>&) const noexcept
      { return 0; }
    };


}
# 26 "data/98.cpp" 2
# 41 "data/98.cpp"

# 41 "data/98.cpp"
using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<string> VS;

const int INF = 0x3fffffff;
const ll _INF = 0x7ffffffffffffffll;
const double EPS = 1e-9;
const double PI = acos(-1.0);

template<class T, class INT>
inline T pow(T x, INT y)
{
 T res(1);
 for (T tt(x); y; y /= 2)
 {
  if (y & 1) res *= tt;
  tt *= tt;
 }
 return res;
}

template<class T, class INT>
inline T pow(T x, INT y, T p)
{
 T res(1);
 for (T tt(x); y; y /= 2)
 {
  if (y & 1) res = res * tt % p;
  tt = tt * tt % p;
 }
 return res;
}

int toInt(string s)
{
 int x = 0;
 istringstream sin(s);
 sin >> x;
 return x;
}

template<class T>
inline string toString(T x)
{
 ostringstream sout;
 sout << x;
 return sout.str();
}

template<class INT>
inline INT gcd(INT x, INT y)
{
 return y ? gcd(y, x % y) : x;
}

template<class INT>
inline int calc_bits(INT x)
{
 return x ? (x & 1) + calc_bits(x >> 1) : 0;
}

const int MAXN = 200000 + 10;

string st, s;
int f[MAXN], g[MAXN], n, ans, t[MAXN], _stack[MAXN], midp, midq, fir, sec, top;
bool tr;

void extend_kmp_lcp(string s)
{
 int l = 0, k = 0, n = s.size();
 for (int i = (1); i < (n); ++i)
 {
  int p = k + l > i ? min(k + l - i, f[i - k]) : 0;
  for (; i + p < n && s[i + p] == s[p]; ++p);
  f[i] = p;
  if (i + p > k + l) k = i, l = p;
 }
}

void extend_kmp_lsp(string s)
{
 int l = 0, k = 0, n = s.size();
 g[0] = 1;
 for (int i = (1); i < (n); ++i)
 {
  int p = k + l > i ? min(k + l - i, g[k + k - i]) : 0;
  for (; i + p < n && i + p >= 0 && s[i - p] == s[i + p]; ++p);
  g[i] = p;
  if (i + p > k + l) k = i, l = p;
 }
}

int calc(int x)
{
 int l = 0, r = top - 1;
 for (; l < r; )
 {
  int mid = (l + r + 1) >> 1;
  if (_stack[mid] > x) r = mid - 1;
  else l = mid;
 }
 return _stack[l];
}

int main(int argc, char* argv[])
{
 cin >> st;
 n = st.size(), s = st;
 reverse((s).begin(), (s).end());
 s += "_" + st;
 extend_kmp_lcp(s);
 extend_kmp_lsp(s);
 for (int i = (n + 1); i < (n + n + 1); ++i) t[i + f[i]] = t[i + f[i]] > (f[i]) ? t[i + f[i]] : (f[i]);
 _stack[top++] = n + 1;
 for (int i = (n + 2); i < (n + n + 1); ++i)
  if (t[i] > t[_stack[top - 1]]) _stack[top++] = i;
 for (int i = (n + 1); i < (n + n + 1); ++i)
 {
  int lim = calc(i - g[i] + 1);
  if (2 * (g[i] + min(t[lim], n + n - i - g[i] + 1)) - 1 > ans)
  {
   ans = 2 * (g[i] + min(t[lim], n + n - i - g[i] + 1)) - 1;
   midp = i - g[i] + 1, midq = g[i] - 1;
   if (min(t[lim], n + n - i - g[i] + 1))
   {
    tr = true;
    fir = lim - t[lim], sec = t[lim];
   }
   else tr = false;
  }
 }
 if (tr)
 {
  cout << 3 << endl;
  cout << fir - n << " " << sec << endl;
  cout << midp - n << " " << midq * 2 + 1 << endl;
  cout << n - sec + 1 << " " << sec << endl;
 }
 else
 {
  cout << 1 << endl;
  cout << midp - n << " " << midq * 2 + 1 << endl;
 }
}

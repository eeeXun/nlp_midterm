# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 4 "data/919.cpp" 2

# 4 "data/919.cpp"
using namespace std;

const int N = int(1e5) + 5, MG = 10007;

char S[N];
int hval[N], rval[N], pow[N], rad[N], n;

inline int ghash (int l, int r) { return hval[r] - hval[l - 1] * pow[r - l + 1]; }
inline int rhash (int l, int r) { return rval[l] - rval[r + 1] * pow[r - l + 1]; }

int getrad (int c)
{
 int l = 0, r = min(c - 1, n - c) + 1;
 while (l + 1 < r)
 {
  int m = (l + r) / 2;
  if (ghash(c + 1, c + m) == rhash(c - m, c - 1)) l = m; else r = m;
 }
 return l;
}
void init ()
{
 pow[0] = 1;
 for (int i = 1; i <= n; ++i) pow[i] = pow[i - 1] * MG;
 for (int i = 1; i <= n; ++i) hval[i] = hval[i - 1] * MG + S[i];
 for (int i = n; i >= 1; --i) rval[i] = rval[i + 1] * MG + S[i];
 for (int i = 1; i <= n; ++i) rad[i] = getrad(i);
}

int check3 (int m, int &sp)
{
 int fl(0);
 for (int l = 1, r = m, re = n - m + 1; !fl && r < re; ++l, ++r)
  if (rhash(l, r) == ghash(n - m + 1, n)) { sp = l; fl = 1; }
 return fl;
}

int get3 (int &sp, int &len, int &mpos, int &mlen)
{
 static int res3[N], maxRP = 0;
 for (int i = 1; i <= n; maxRP = ++i)
  if (! check3(i, res3[i])) break;
 --maxRP;
 int res(0);
 for (int c = 1; c <= n; ++c)
 {
  int lo = 0, hi = n - (c + rad[c]) + 1;
  while (lo + 1 < hi)
  {
   int m = (lo + hi) / 2;
   if (m <= maxRP && res3[m] + m - 1 < c - rad[c]) lo = m;
   else hi = m;
  }
  int cl = rad[c] * 2 + 1 + lo * 2;
  if (cl > res)
  {
   res = cl; mlen = rad[c] * 2 + 1;
   mpos = c; len = lo; sp = res3[lo];
  }
 }
 return res;
}

int get1 ()
{
 int res = 0;
 for (int c = n; c >= 1; --c)
  if (c + rad[c] == n) res = max(res, rad[c] * 2 + 1);
 return res;
}

int main ()
{



 scanf("%s", S + 1);
 n = strlen(S + 1);
 init();
 int sp, len, mpos, mlen, a = get1(), b = get3(sp, len, mpos, mlen);
 if (a >= b)
  printf("1\n%d %d\n", n - a + 1, a);
 else
 {
  if (len)
   printf("3\n%d %d\n%d %d\n%d %d\n", sp, len, mpos - (mlen - 1) / 2, mlen, n - len + 1, len);
  else printf("1\n%d %d\n", mpos - (mlen - 1) / 2, mlen);
 }
 return 0;
}

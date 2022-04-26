}
# 6 "data/338.cpp" 2

# 6 "data/338.cpp"
using namespace std;

namespace zyt
{
 const int N = 1e5 + 10, B = 17;
 template<typename T>
 inline void read(T &x)
 {
  bool f = false;
  char c;
  x = 0;
  do
   c = getchar();
  while (c != '-' && !isdigit(c));
  if (c == '-')
   f = true, c = getchar();
  do
   x = x * 10 + c - '0', c = getchar();
  while (isdigit(c));
  if (f)
   x = -x;
 }
 inline void read(char *const s)
 {
  scanf("%s", s);
 }
 inline void read(string &s)
 {
  static char buf[N];
  read(buf);
  s = buf;
 }
 template<typename T>
 inline void write(T x)
 {
  static char buf[20];
  char *pos = buf;
  if (x < 0)
   putchar('-'), x = -x;
  do
   *pos++ = x % 10 + '0';
  while (x /= 10);
  while (pos > buf)
   putchar(*--pos);
 }
 int n, len[N], ans, pos[3], length[3];
 bool flag;
 namespace Manacher
 {
  int p[N << 1];
  string s;
  void work(const string &str)
  {
   int right = 0, id = 0;
   s = "#";
   for (int i = 0; i < str.size(); i++)
    s += str[i], s += '#';
   for (int i = 0; i < s.size(); i++)
   {
    if (i < right)
     p[i] = min(p[id * 2 - i], right - i);
    else
     p[i] = 1;
    while (i - p[i] >= 0 && i + p[i] < s.size() && s[i - p[i]] == s[i + p[i]])
     ++p[i];
    if (i + p[i] > right)
     right = i + p[i], id = i;
   }
   for (int i = 0; i < str.size(); i++)
   {
    p[i] = p[(i << 1) | 1] / 2;
    if ((p[i] << 1) - 1 > ans)
     ans = length[0] = (p[i] << 1) - 1, pos[0] = i - p[i] + 1;
   }
  }
 }
 namespace KMP
 {
  int fail[N];
  inline void get_fail(const string &s)
  {
   fail[0] = fail[1] = 0;
   for (int i = 1; i < s.size(); i++)
   {
    int tmp = fail[i];
    while (tmp && s[tmp] != s[i])
     tmp = fail[tmp];
    fail[i + 1] = (s[tmp] == s[i] ? tmp + 1 : 0);
   }
  }
  inline void query(const string &s1, const string &s2)
  {
   get_fail(s2);
   int tmp = 0;
   for (int i = 0; i < s1.size(); i++)
   {
    while (tmp && s2[tmp] != s1[i])
     tmp = fail[tmp];
    if (s2[tmp] == s1[i])
     ++tmp;
    len[i] = tmp;
   }
  }
 }
 namespace ST
 {
  int lg2[N], st[N][B];
  inline int _max(const int a, const int b)
  {
   using Manacher::p;
   return p[a] > p[b] ? a : b;
  }
  inline void build()
  {
   int tmp = 0;
   for (int i = 1; i <= n; i++)
   {
    lg2[i] = tmp;
    if (i == (1 << (tmp + 1)))
     ++tmp;
   }
   for (int i = n - 1; i >= 0; i--)
   {
    st[i][0] = i;
    for (int j = 1; j < B; j++)
     if (i + (1 << j) - 1 < n)
      st[i][j] = _max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
     else
      break;
   }
  }
  inline int query(const int a, const int b)
  {
   int len = b - a + 1;
   return _max(st[a][lg2[len]], st[b - (1 << lg2[len]) + 1][lg2[len]]);
  }
 }
 int work()
 {
  static string s1, s2;
  read(s1);
  n = s1.size();
  Manacher::work(s1);
  ST::build();
  for (int i = 0; i < n; i++)
   s2 += s1[n - i - 1];
  KMP::query(s1, s2);
  for (int i = 0; i < n; i++)
  {
   using Manacher::p;
   if (i >= n - len[i])
    continue;
   int l = 1, r = (n - len[i] - i - 1) >> 1, midlen = 0;
   while (l <= r)
   {
    int mid = (l + r) >> 1;
    if (p[ST::query(i + mid, n - len[i] - mid)] >= mid)
     l = mid + 1, midlen = mid;
    else
     r = mid - 1;
   }
   int anss = (midlen << 1) - 1 + (len[i] << 1);
   if (anss > ans)
   {
    int tmp = ST::query(i + midlen, n - len[i] - midlen);
    ans = anss, flag = true;
    pos[0] = i - len[i] + 1, pos[1] = tmp - midlen + 1, pos[2] = n - len[i];
    length[0] = length[2] = len[i], length[1] = (midlen << 1) - 1;
   }
  }
  if (flag)
  {
   write(3), putchar('\n');
   for (int i = 0; i < 3; i++)
   {
    write(pos[i] + 1), putchar(' ');
    write(length[i]), putchar('\n');
   }
  }
  else
  {
   write(1), putchar('\n');
   write(pos[0] + 1), putchar(' ');
   write(length[0]);
  }
  return 0;
 }
}
int main()
{
 return zyt::work();
}

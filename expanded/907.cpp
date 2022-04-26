}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 14 "data/907.cpp" 2

# 14 "data/907.cpp"
using namespace std;
typedef long long LL;
inline int read()
{
 int x = 0; char ch = getchar(); bool positive = 1;
 for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') positive = 0;
 for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
 return positive ? x : -x;
}

int N;
char a[100005], b[100005];
int next[100005], f[100005], g[100005], h[100005];

int main()
{

 freopen("a.in", "r", 
# 31 "data/907.cpp" 3 4
                     stdin
# 31 "data/907.cpp"
                          );
 freopen("a.out", "w", 
# 32 "data/907.cpp" 3 4
                      stdout
# 32 "data/907.cpp"
                            );


 scanf("%s", a + 1);
 N = strlen(a + 1);
 for (int i = 1; i <= N; ++ i) b[N - i + 1] = a[i];

 a[0] = '$'; a[N + 1] = '%';
 next[1] = 0;
 for (int i = 2, p = 0; i <= N; ++ i)
 {
  while (p && b[p + 1] != b[i]) p = next[p];
  p += (b[p + 1] == b[i]);
  next[i] = p;
 }
 f[0] = 0;
 for (int i = 1, p = 0; i <= N; ++ i)
 {
  while (p && b[p + 1] != a[i]) p = next[p];
  p += (b[p + 1] == a[i]);
  f[i] = p;
  h[i] = h[i - 1];
  if (f[i] > f[h[i]]) h[i] = i;
 }

 int ans = 1, resx = 1, resy = 0;
 for (int i = 1, x = 1; i <= N; ++ i)
 {
  int j = x + x - i;
  int p = min(g[j], j - (x - g[x]));
  while (a[i - p - 1] == a[i + p + 1]) ++ p;
  g[i] = p;
  if (i + g[i] > x + g[x]) x = i;

  int y = h[i - g[i] - 1];
  int calc = g[i] + g[i] + 1 + min(N - (i + g[i]), f[y]) * 2;
  if (calc > ans) ans = calc, resx = i, resy = y;
 }

 int x = resx, y = resy, l = min(f[y], N - (x + g[x]));
 printf("%d\n", 1 + (l ? 2 : 0));
 if (l) printf("%d %d\n", y - f[y] + 1, l);
 printf("%d %d\n", x - g[x], g[x] + g[x] + 1);
 if (l) printf("%d %d\n", N - l + 1, l);

 return 0;
}

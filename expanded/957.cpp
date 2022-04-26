# 4 "data/957.cpp" 2

# 4 "data/957.cpp"
int len[200005], st[200005][25], nxt[200005], mn[200005], bit[200005], mxp, n;
char str[200005], rev[200005];
inline void manacher()
{
 for (int i = n - 1; i >= 0; i--)
 {
  str[i * 2 + 2] = str[i];
  str[i * 2 + 3] = '*';
 }
 str[0] = '#';
 str[1] = '*';
 int mx = 0, idx;
 for (int i = 1; i < 2 * n + 2; i++)
 {
  if (mx > i)
   len[i] = std::min(mx - i, len[idx * 2 - i]);
  else
   len[i] = 1;
  while (str[i - len[i]] == str[i + len[i]])
   len[i]++;
  if (i + len[i] > mx)
  {
   mx = i + len[i];
   idx = i;
  }
 }
 for (int i = 0; i < n; i++)
  len[i] = len[i * 2 + 2] >> 1;
}
inline void kmp()
{
 nxt[0] = -1;
 for (int i = 1, j = -1; i < n; i++)
 {
  while (~j && rev[i] != rev[j + 1])
   j = nxt[j];
  j += rev[i] == rev[j + 1];
  nxt[i] = j;
 }
 for (int i = 0, j = -1; i < n; i++)
 {
  while (~j && str[i] != rev[j + 1])
   j = nxt[j];
  j += str[i] == rev[j + 1];
  mn[j + 1] = std::min(mn[j + 1], i + 1);
 }
}
inline int calc(int x, int y)
{
 return len[x] > len[y] ? x : y;
}
inline void init()
{
 for (int i = 0; i < n; i++)
  st[i][0] = i;
 for (int i = 1; i < 20; i++)
 {
  for (int j = 0; j + (1 << i) <= n; j++)
   st[j][i] = calc(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
 }
}
inline int query(int l, int r)
{
 if (l > r)
  return -1;
 int lg = bit[r - l + 1];
 mxp = calc(st[l][lg], st[r - (1 << lg) + 1][lg]);
 return len[mxp];
}
int main()
{

 scanf("%s", str);
 n = strlen(str);
 for (int i = 2; i < 100005; i++)
  bit[i] = bit[i >> 1] + 1;
 for (int i = 1; i <= n; i++)
  mn[i] = n;
 std::reverse_copy(str, str + n, rev);
 kmp();
 manacher();
 init();
 int ans = -1, pos = 0;
 for (int i = 0; i <= n; i++)
 {
  int x = mn[i], y = n - i - 1, l = 0, r = y - x + 1, res = -1;
  while (l <= r)
  {
   int m = l + r >> 1;
   if (query(x + m - 1, y - m + 1) >= m)
   {
    res = m;
    l = m + 1;
   }
   else
    r = m - 1;
  }
  if (res > 0 && (res + i << 1) > ans)
  {
   ans = (res + i << 1) - 1;
   pos = i;
  }
 }
 int x = mn[pos], y = n - pos - 1, res = (ans - (pos << 1) + 1) >> 1;
 query(x + res - 1, y - res + 1);
 if (pos)
  printf("3\n%d %d\n%d %d\n%d %d\n", x - pos + 1, pos, mxp - res + 2, res - 1 << 1 | 1, n - pos + 1, pos);
 else
  printf("1\n%d %d\n", mxp - res + 2, res - 1 << 1 | 1);
 return 0;
}

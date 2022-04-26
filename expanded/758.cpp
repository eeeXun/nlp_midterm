# 40 "/usr/include/c++/11.2.0/cstdio" 3
# 5 "data/758.cpp" 2

# 5 "data/758.cpp"
using namespace std;
char str[200005], rev[200005];
int len[200005], nxt[200005], mn[200005], st[200005][25], mxp[200005][25], bit[200005], res_pos, n;
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
  mn[j + 1] = min(mn[j + 1], i + 1);
 }
}
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
   len[i] = min(mx - i, len[idx * 2 - i]);
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
 {
  st[i][0] = len[i * 2 + 2] >> 1;
  mxp[i][0] = i;
 }
 for (int i = 1; i < 20; i++)
 {
  for (int j = 0; j + (1 << i) <= n; j++)
  {
   if (st[j][i - 1] > st[j + (1 << i - 1)][i - 1])
    mxp[j][i] = mxp[j][i - 1];
   else
    mxp[j][i] = mxp[j + (1 << i - 1)][i - 1];
   st[j][i] = max(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
  }
 }
}
inline int query(int l, int r)
{
 if (l > r)
  return -1;
 int len = bit[r - l + 1];
 if (st[l][len] > st[r - (1 << len) + 1][len])
  res_pos = mxp[l][len];
 else
  res_pos = mxp[r - (1 << len) + 1][len];
 return max(st[l][len], st[r - (1 << len) + 1][len]);
}
int main()
{

 scanf("%s", str);
 n = strlen(str);
 for (int i = 2; i < 200005; i++)
  bit[i] = bit[i >> 1] + 1;
 for (int i = 1; i <= n; i++)
  mn[i] = n;
 memcpy(rev, str, sizeof(str));
 reverse(rev, rev + n);
 kmp();
 manacher();
 int ans = -1, pos;
 for (int i = 0; i <= n; i++)
 {
  int st = mn[i], en = n - i - 1;
  if (st > en)
   continue;
  int l = 0, r = en - st + 1, res = -1;
  while (l <= r)
  {
   int m = l + r >> 1;
   if (query(st + m - 1, en - m + 1) >= m)
   {
    res = m;
    l = m + 1;
   }
   else
    r = m - 1;
  }
  if (res > 0 && (res << 1) + (i << 1) > ans)
  {
   ans = (res << 1) + (i << 1) - 1;
   pos = i;
  }
 }
 int lp = mn[pos], rp = n - pos - 1, d = (ans - pos * 2 + 1) / 2;
 query(lp + d - 1, rp - d + 1);
 printf("%d\n", pos ? 3 : 1);
 if (pos)
  printf("%d %d\n", mn[pos] - pos + 1, pos);
 printf("%d %d\n", res_pos - d + 2, d * 2 - 1);
 if (pos)
  printf("%d %d\n", n - pos + 1, pos);
 return 0;
}

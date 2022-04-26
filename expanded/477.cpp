using namespace std;
char s[100010];
char t[100010];
int ans, p, mx, id;
int nxt[100010], r[100010], f[100010], g[100010];
int main() {
 scanf("%s", s + 1);
 int n = strlen(s + 1);
 s[n + 1] = '.';
 for (int i = 1;i <= n;i++) {
  r[i] = (mx > i) ? min(r[2 * id - i], mx - i) : 1;
  while (s[i + r[i]] == s[i - r[i]])
  {
   r[i]++;
  }
  if (r[i] + i > mx)
  {
   mx = r[i] + i;
   id = i;
  }
 }
 for (int i = 1;i <= n;i++)
 {
  t[i] = s[n + 1 - i];
 }
 nxt[0] = nxt[1] = 0;
 for (int i = 2, j = 0; i <= n; i++) {
  while (j && t[j + 1] != t[i])
  {
   j = nxt[j];
  }
  if (t[j + 1] == t[i])
  {
   nxt[i] = ++j;
  }
 }
 for (int i = 1, j = 0; i <= n; i++) {
  while (j && t[j + 1] != s[i])
  {
   j = nxt[j];
  }
  if (t[j + 1] == s[i])
  {
   f[i] = ++j;
  }
  if (f[i] == n)
  {
   j = nxt[j];
  }
  if (f[i])
  {
   g[i] = i - f[i] + 1;
  }
 }
 for (int i = 1;i <= n;i++)
 {
  if (f[i - 1] > f[i])
  {
   f[i] = f[i - 1];
   g[i] = g[i - 1];
  }
 }
 bool flag = false;
 for (int i = 1;i <= n;i++)
 {
  if (2 * r[i] - 1 > ans)
  {
   ans = 2 * r[i] - 1;
   p = i - r[i] + 1;
  }
 }
 for (int i = 1;i <= n;i++) {
  int x = i - r[i];
  if (2 * min(f[x], n - (i + r[i] - 1)) + 2 * r[i] - 1 > ans)
  {
   flag = true;
   ans = 2 * min(f[x], n - (i + r[i] - 1)) + 2 * r[i] - 1;
   p = i;
  }
 }
 if (!flag)
 {
  printf("1\n%d %d", p, ans);
 }
 else
 {
  printf("3\n%d %d\n%d %d\n%d %d", g[p - r[p]], f[p - r[p]], p - r[p] + 1, 2 * r[p] - 1, n - f[p - r[p]] + 1, f[p - r[p]]);
 }
 return 0;
}

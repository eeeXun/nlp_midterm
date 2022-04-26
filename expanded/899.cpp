
# 4 "data/899.cpp"
using namespace std;

const int MAXN = 2e5 + 5;

char s[MAXN], t[MAXN];
int d[MAXN], pi[MAXN], f[MAXN];

int main() {
 scanf("%s", s + 1);
 int n = strlen(s + 1), m = (n << 1) + 1;
 for (int i = 1; i <= n; i++)
  t[n - i + 1] = t[n + i + 1] = s[i];
 t[n + 1] = '|';

 for (int i = 1, l = 0, r = 0; i <= n; i++) {
  d[i] = 1;
  if (i <= r) d[i] = min(d[l + r - i], r - i + 1);
  for (; i > d[i] && i + d[i] <= n && s[i - d[i]] == s[i + d[i]]; d[i]++);
  if (i + d[i] - 1 > r) l = i - d[i] + 1, r = i + d[i] - 1;
 }

 for (int i = 2; i <= m; i++) {
  int j = pi[i - 1];
  for (; j && t[j + 1] != t[i]; j = pi[j]);
  pi[i] = j + (int)(t[j + 1] == t[i]);
  if (i > n)
   f[i] = pi[i] > pi[f[i - 1]] ? i : f[i - 1];
 }

 int best = 0, mid = 0, pos = 0;
 for (int i = 1; i <= n; i++) {
  int mlen = (d[i] << 1) - 1;
  int slen = min(pi[f[i - d[i] + n + 1]], n - (i + d[i] - 1));
  if (mlen + (slen << 1) > best) {
   best = mlen + (slen << 1);
   mid = i, pos = f[i - d[i] + n + 1];
  }
 }

 if (pos == 0)
  printf("1\n%d %d\n", mid - d[mid] + 1, (d[mid] << 1) - 1);
 else {
  int slen = min(pi[pos], n - (mid + d[mid] - 1));
  printf("3\n");
  printf("%d %d\n", pos - slen - n, slen);
  printf("%d %d\n", mid - d[mid] + 1, (d[mid] << 1) - 1);
  printf("%d %d\n", n - slen + 1, slen);
 }

 return 0;
}

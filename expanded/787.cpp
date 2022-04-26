# 4 "data/787.cpp" 2




# 7 "data/787.cpp"
const int maxn = 100010;

int n, m = 0, ans = 0,
 pi[maxn], leftMost[maxn], r[maxn], L[3], R[3];
char s[maxn], rev[maxn];

void KMP()
{
 int p = pi[1] = 0;
 for (int i=2; i<=n; ++i) {
  while (p && rev[p+1] != rev[i]) p = pi[p];
  if (rev[p+1] == rev[i]) ++p;
  pi[i] = p;
 }

 p = 0;
 for (int i=1; i<=n; ++i) {
  while (p && rev[p+1] != s[i]) p = pi[p];
  if (rev[p+1] == s[i]) ++p;
  if (p && !leftMost[p]) {
   leftMost[p] = i;
   m = p;
  }
 }
}

void manacher()
{
 int mx = r[1] = 1, pos = 1;
 for (int i=2; i<=n; ++i) {
  r[i] = (i >= mx) ? 1 : std :: min(mx-i, r[pos+pos-i]);
  while (s[i+r[i]] == s[i-r[i]]) ++r[i];
  if (i+r[i] > mx) {
   mx = i + r[i];
   pos = i;
  }
 }
}

void init()
{
 scanf("%s", s+1);
 n = strlen(s+1);
 s[n+1] = '$';
 for (int i=1; i<=n; ++i) rev[n-i+1] = s[i];
 KMP();
 manacher();
}

void solve()
{
 for (int i=1; i<=n; ++i) {
  int low = 0, high = m, mid;
  while (low < high) {
   mid = (low + high + 1) >> 1;
   if (leftMost[mid] <= i-r[i] && i+r[i] <= n-mid+1)
    low = mid;
   else
    high = mid - 1;
  }
  if ((low + r[i]) * 2 - 1 > ans) {
   ans = (low + r[i]) * 2 - 1;
   L[0] = leftMost[low] - low + 1; R[0] = leftMost[low];
   L[1] = i - r[i] + 1; R[1] = i + r[i] - 1;
   L[2] = n - low + 1; R[2] = n;
  }
 }

 int cnt = 0;
 for (int i=0; i<=2; ++i)
  if (L[i] <= R[i]) ++cnt;
 printf("%d\n", cnt);
 for (int i=0; i<=2; ++i)
  if (L[i] <= R[i])
   printf("%d %d\n", L[i], R[i]-L[i]+1);
}

int main()
{
 init();
 solve();
 return 0;
}

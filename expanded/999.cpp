# 4 "data/999.cpp" 2

# 4 "data/999.cpp"
using namespace std;

char a[100011], b[100011];
int n, rad[100011], p[100011], rec[100011], ans;
vector<pair<int, int>> o;






int main()
{
 scanf("%s", a + 1);
 a[0] = '#';
 n = strlen(a + 1);
 for (int i = 1, j = 0, k; i <= n; )
 {
  for (; a[i+j+1] == a[i-j-1]; ++j);
  rad[i] = j;
  for (k = 1; k <= j && rad[i-k] != rad[i] - k; ++k)
   rad[i+k] = min(rad[i-k], rad[i] - k);
  i += k;
  j = max(0, j - k);
 }
 for (int i = 1; i <= n; ++i)
  b[i] = a[n-i+1];
 p[1] = 0;
 for (int i = 2, j = 0; i <= n; ++i)
 {
  for (; j && b[j+1] != b[i]; j = p[j]);
  p[i] = b[j+1] == b[i] ? ++j : 0;
 }
 for (int i = 1, j = 0; i <= n; ++i)
 {
  for (; j && b[j+1] != a[i]; j = p[j]);
  (j += a[i] == b[j+1]) && !rec[j] ? rec[j] = i : 0;
 }
 for (int i = 1; i <= n; ++i)
  !rec[i] ? rec[i] = n + 1 : 0;
 for (int i = 1; i <= n; ++i)
 {
  int pl = i - rad[i], pr = i + rad[i];
  int L = 0, R = n - pr, mid;
  while (L < R)
  {
   mid = (L + R + 1) >> 1;
   rec[mid] < pl ? L = mid : R = mid - 1;
  }
  if (L + L + rad[i] + rad[i] + 1 > ans)
  {
   ans = L + L + rad[i] + rad[i] + 1;
   o.clear();
   if (L) o.push_back(make_pair(rec[L] - L + 1, L));
   o.push_back(make_pair(pl, rad[i] + rad[i] + 1));
   if (L) o.push_back(make_pair(n - L + 1, L));
  }
 }
 printf("%d\n", o.size());
 for (auto i : o)
  printf("%d %d\n", i.first, i.second);
 return 0;
}

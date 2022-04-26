}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 7 "data/194.cpp" 2




# 10 "data/194.cpp"
using namespace std;

const int maxn = 2e5 + 10;

char str[maxn];
int R[maxn], next[maxn], b[maxn], f[maxn], idx[maxn];
char s[maxn];

pair<int, int> stack[101];

int main( )
{
 scanf("%s", str + 1);
 int n = (int )strlen(str + 1);
 str[0] = '#';
 int mx = 0, id = 0;
 for (int i = 1; i <= n; i ++)
 {
  if (mx >= i) R[i] = min(mx - i, R[2 * id - i]);
  while (str[i + R[i] + 1] == str[i - R[i] - 1]) ++ R[i];
  if (i + R[i] > mx) mx = i + R[i], id = i;
 }
 for (int i = 0; i < n; i ++)
  s[i] = str[n - i];
 s[n] = '\0';
 for (int i = 1; i < n; i ++)
 {
  int j = f[i];
  while (j && s[j] != s[i]) j = f[j];
  f[i + 1] = s[j] == s[i] ? j + 1 : 0;
 }
 int j = 0;
 for (int i = 1; i <= n; i ++)
 {
  while (j && s[j] != str[i]) j = f[j];
  if (s[j] == str[i])
  {
   ++ j;
   if (j > b[i - 1]) idx[i] = i, b[i] = j;
   else idx[i] = idx[i - 1], b[i] = b[i - 1];
  }
  else b[i] = b[i - 1], idx[i] = idx[i - 1];
 }

 int ans = 0;
 for (int i = 1; i <= n; i ++)
 {
  int l1 = 2 * R[i] + 1;
  int l2 = min(b[i - R[i] - 1], n - i - R[i]);
  if (l1 + 2 * l2 > ans)
  {
   ans = l1 + 2 * l2;
   stack[1] = make_pair(idx[i - R[i] - 1] - l2 + 1, idx[i - R[i] - 1]);
   stack[2] = make_pair(i - R[i], i + R[i]);
   stack[3] = make_pair(n - l2 + 1, n);
  }
 }
 int cnt = 0;
 for (int i = 1; i <= 3; i ++)
  if (stack[i].first <= stack[i].second) ++ cnt;
 printf("%d\n", cnt);
 for (int i = 1; i <= 3; i ++)
  if (stack[i].first <= stack[i].second)
   printf("%d %d\n", stack[i].first, stack[i].second - stack[i].first + 1);

 return 0;
}

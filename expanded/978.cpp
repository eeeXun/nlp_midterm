# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/978.cpp" 2

# 5 "data/978.cpp"
using namespace std;

const int N = 100010;
char str[N], inv[N];
int rad[N], kmp[N], match[N], opt[N], qry[N];

int main ()
{
 scanf("%s", str);
 int len = strlen(str);
 for (int i = 0, j = 0, k; i < len; i += k, j = max(j - k, 0))
 {
     while (i - j >= 0 && i + j < len && str[i - j] == str[i + j]) ++j;
     rad[i] = j;
     for (k = 1; i - k >= 0 && rad[i] - k > 0 && rad[i - k] != rad[i] - k; ++k)
         rad[i + k] = min(rad[i - k], rad[i] - k);
 }
 for (int i = 0; i < len; i++) inv[len - 1 - i] = str[i];
 kmp[0] = -1, kmp[1] = 0;
 for (int i = 2; i < len; i++)
 {
  int j = kmp[i - 1];
  while (j != -1 && inv[i - 1] != inv[j]) j = kmp[j];
  kmp[i] = j + 1;
 }
 int t = 0;
 for (int i = 0; i < len; i++)
 {
  while (t != -1 && str[i] != inv[t]) t = kmp[t];
  match[i] = ++t;
  if (t == len) t = kmp[t];
 }
 memset(opt, -1, sizeof opt);
 for (int i = 0; i < len; i++) if (match[i])
 {
  int s = i - match[i] + 1;
  if (opt[match[i]] == -1) opt[match[i]] = s;
 }
 memset(qry, -1, sizeof qry);
 for (int i = 1; i <= len; i++) qry[opt[i]] = i;
 if (qry[0] == -1) qry[0] = 0;
 for (int i = 1; i < len; i++)
 {
  if (qry[i] == -1) qry[i] = qry[i - 1];
 }
 int maxl = 0, k; int st[3], sl[3];
 for (int i = 0; i < len; i++)
 {

  int lm = i - rad[i] + 1, rm = i + rad[i] - 1; int ll = 0, ss;
  if (lm - 1 >= 0)
  {
   ll = qry[lm - 1];
   if (ll)
   {
    ss = opt[ll];
    ll = min(ll, lm - ss);
    ll = min(ll, len - rm - 1);

   }
  }
  if (ll == 0)
  {
   if (rm - lm + 1 > maxl)
   {
    maxl = rm - lm + 1;
    k = 1;
    st[0] = lm;
    sl[0] = maxl;
   }
  }
  else
  {
   if (rm - lm + 1 + ll * 2 > maxl)
   {
    maxl = rm - lm + 1 + ll * 2;
    k = 3;
    st[0] = ss, sl[0] = ll;
    st[1] = lm, sl[1] = rm - lm + 1;
    st[2] = len - ll, sl[2] = ll;
   }
  }
 }
 printf("%d\n", k);
 for (int i = 0; i < k; i++)
  printf("%d %d\n", st[i] + 1, sl[i]);

 return 0;
}

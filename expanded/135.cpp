    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 6 "data/135.cpp" 2
# 15 "data/135.cpp"

# 15 "data/135.cpp"
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int inf = ~0U >> 1;
const ll INF = ~0ULL >> 1;


const int maxn = 300000;
int nxt[maxn], best, N, f[maxn], cans;
char s2[maxn], s[maxn];
pii ans[5], pre[maxn];

int main()
{
 scanf("%s", s + 1);
 N = strlen(s + 1);
 memcpy(s2, s, sizeof(s2));
 reverse(s2 + 1, s2 + N + 1);
 int j = 0;
 for (int i = (2); i <= (N); ++i)
 {
  while (j && s2[i] != s2[j + 1]) j = nxt[j];
  if (s2[i] == s2[j + 1]) j++;
  nxt[i] = j;
 }
 j = 0;
 for (int i = (1); i <= (N); ++i)
 {
  while (j && s[i] != s2[j + 1]) j = nxt[j];
  if (s[i] == s2[j + 1]) j++;
  pre[i] = max(pre[i - 1], (make_pair(j, i)));
 }
 int mx = 0, id;
 s[0] = '$';
 for (int i = (1); i <= (N); ++i)
 {
  if (mx > i) f[i] = min(f[2 * id - i], f[id] + id - i);
  else f[i] = 1;
  for (; s[i + f[i]] == s[i - f[i]]; ++f[i]);
  if (f[i] + i > mx) mx = f[i] + i, id = i;
 }
 for (int i = (1); i <= (N); ++i)
 {
  int l = min(pre[i - f[i]].first, N - (i + f[i] - 1));
  if (f[i] * 2 - 1 + l * 2 > best)
  {
   best = f[i] * 2 - 1 + l * 2;
   if (l)
   {
    cans = 3;
    ans[1] = (make_pair(pre[i - f[i]].second - l + 1, l));
    ans[2] = (make_pair(i - f[i] + 1, 2 * f[i] - 1));
    ans[3] = (make_pair(N - l + 1, l));
   }
   else ans[cans = 1] = (make_pair(i - f[i] + 1, 2 * f[i] - 1));
  }
 }
 printf("%d\n", cans);
 for (int i = (1); i <= (cans); ++i) printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}

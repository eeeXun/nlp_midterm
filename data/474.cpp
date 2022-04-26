#include <bits/stdc++.h>
using namespace std;
const int N = 100010, MP = 20, INF = 0x3f3f3f3f;
char s[N],t[N];
int n,len[N << 1],nex[N],val[N],mx[N][MP],ln[N];
struct data {
  int p[3],l[3];
  data(int a=0,int b=-1,int c=0,int d=-1,int e=0,int f=-1) {
    p[0] = a; p[1] = c; p[2] = e;
    l[0] = b - a + 1; l[1] = d - c + 1; l[2] = f - e + 1;
  }
  bool operator < (const data& x) const {
    return l[0] + l[1] + l[2] < x.l[0] + x.l[1] + x.l[2];
  }
} ans;
void manacher() {
  for (int i = 2 ; i <= (n << 1) ; ++ i) {
    int l = i >> 1, r = (i + 1) >> 1;
    while (s[l - len[i]] == s[r + len[i]] && l - len[i] >= 1 && r + len[i] <= n)
      ++ len[i];
    l = i - 1, r = i + 1;
    while ((l >> 1) - len[l] > (i >> 1) - len[i] && l >= 1 && r <= (n << 1))
      len[r++] = len[l--];
    len[r] = ((i + 1) >> 1) + len[i] - ((r + 1) >> 1);
    i = r - 1;
  }
}
int query(int l,int r) {
  if (l > r) return 0;
  int len = ln[r - l + 1];
  return val[mx[r][len]] > val[mx[l + (1 << len) - 1][len]] ? \
    mx[r][len] : mx[l + (1 << len) - 1][len];
}
int main() {
  scanf("%s",s+1);
  n = strlen(s+1);
  manacher();
  for (int i = 1 ; i <= n ; ++ i)
    t[i] = s[n - i + 1];
  nex[0] = -1;
  for (int i = 2, j = 0 ; i <= n ; ++ i) {
    while (j >= 0 && t[j+1] != t[i])
      j = nex[j];
    nex[i] = ++j;
  }
  for (int i = 1 ; i <= n ; ++ i)
    val[i] = len[i<<1];
  for (int i = 1 ; i <= n ; ++ i) {
    mx[i][0] = i;
    for (int j = 1 ; (1 << j) <= i ; ++ j)
      mx[i][j] = val[mx[i][j-1]] > val[mx[i - (1 << j >> 1)][j-1]] ? \
	mx[i][j-1] : mx[i - (1 << j >> 1)][j-1];
  }
  for (int i = 2 ; i <= n ; i <<= 1) ln[i] = 1;
  for (int i = 1 ; i <= n ; ++ i) ln[i] += ln[i-1];
  for (int i = 1 ; i <= n ; ++ i)
    ans = max(ans,data(i - val[i] + 1,i + val[i] - 1,0,-1,0,-1));
  for (int k = 1, j = 0, cur = 0, i = n ; k <= n ; ++ k, -- i) {
    for (++ j ; cur < k && j <= n ; ++ j) {
      while (cur >= 0 && s[j] != t[cur+1])
	cur = nex[cur];
      ++ cur;
    }
    -- j;
    if (j >= i) break;
    int l = 0, r = (i - j) >> 1, ret = 0, mid;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (val[query(j + mid, i - mid)] >= mid) ret = mid, l = mid + 1;
      else r = mid - 1;
    }
    if (!ret) continue;
    int tmp = query(j + ret, i - ret);
    ans = max(ans,data(j - k + 1, j, tmp - ret + 1, tmp + ret - 1, i , n));
  }
  int ret = 0;
  for (int i = 0 ; i < 3 ; ++ i)
    if (ans.l[i] > 0) ++ ret;
  printf("%d\n",ret);
  for (int i = 0 ; i < ret ; ++ i)
    printf("%d %d\n",ans.p[i],ans.l[i]);
  return 0;
}

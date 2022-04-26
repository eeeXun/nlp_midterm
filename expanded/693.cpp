# 3 "data/693.cpp"
using namespace std;
const long long N = 2e5 + 30, INF = 1e9;

struct node{
 long long val, l, pos, mid;
}ans;
long long n, mid, d[N], z[N], pos[N], res, mx;
char s[N], tmp[N];

bool check(long long x, long long p){
 if(p + d[p] <= pos[x] - x) return true;
 return false;
}

signed main(){
 scanf("%s", tmp + 1); n = strlen(tmp + 1);
 for(long long i = 1; i <= n; ++i) pos[i] = -INF;
 for(long long i = 1; i <= n; ++i) s[i] = tmp[n - i + 1];
 s[n + 1] = '#';
 for(long long i = n + 2; i <= 2 * n + 1; ++i) s[i] = s[2 * (n + 1) - i];
 mid = n + 1; n = 2 * n + 1;
 for(long long i = 1, pos = 0, r = 0; i < mid; ++i){
  if(i < r) d[i] = min(r - i, d[(pos << 1) - i]);
  while(i + d[i] < n && i - d[i] > 1 && s[i + d[i] + 1] == s[i - d[i] - 1]) d[i]++;
  if(i + d[i] > r){
   r = i + d[i];
   pos = i;
  }
 }
 for(long long i = 2, l = 0, r = 0; i <= n; ++i){
  if(i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
  while(i + z[i] <= n && s[i + z[i]] == s[1 + z[i]]) z[i]++;
  if(i + z[i] - 1 > r){
   r = i + z[i] - 1;
   l = i;
  }
 }
 for(long long i = mid + 1; i <= n; ++i)
  pos[z[i]] = max(pos[z[i]], (mid << 1) - i);
 for(long long i = mid - 2; i >= 1; --i) pos[i] = max(pos[i], pos[i + 1]);
 for(long long i = 1, l, r, m; i < mid; ++i){
  res = d[i] * 2 + 1; l = 0, r = i - d[i] - 1;
  while(l + 1 < r){
   m = (l + r) >> 1;
   if(check(m, i)) l = m;
   else r = m;
  }
  if(check(r, i)) mx = r;
  else mx = l;
  if(res + mx * 2 > ans.val){
   ans.val = res + mx * 2;
   ans.mid = mid - i;
   ans.l = mx;
   if(mx == 0) ans.pos = -1;
   else ans.pos = mid - pos[mx];
  }
 }
 if(ans.pos == -1){
  puts("1");
  printf("%lld %lld\n", ans.mid - d[mid - ans.mid], ans.val);
 }else{
  puts("3");
  printf("%lld %lld\n", ans.pos, ans.l);
  printf("%lld %lld\n", ans.mid - d[mid - ans.mid], d[mid - ans.mid] * 2 + 1);
  printf("%lld %lld\n", mid - ans.l, ans.l);
 }
 return 0;
}

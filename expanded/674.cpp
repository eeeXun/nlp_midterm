# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 4 "data/674.cpp" 2


# 5 "data/674.cpp"
using namespace std;
const int maxn = 100005<<1;
char s[maxn], t[maxn];
int n, match[maxn], mm[maxn], next[maxn], d[maxn];

void manacher(int n, char *s) {
 int id = 0, mx = 0;
 for(int i=1; i<=n; ++i) {
  d[i] = i<mx ? min(d[id*2-i], mx-i) : 1;
  while(s[i-d[i]]==s[i+d[i]]) ++d[i];
  if(i+d[i]>mx) mx = i+d[i], id = i;
 }


}

void getnext(int n, char *s) {
 next[1] = 0;
 int i = 1, t = 0;
 while(i<=n+1) {
  while(t && s[i]!=s[t]) t = next[t];
  ++i, ++t;
  next[i] = t;
 }


}

int main() {


 scanf("%s", s+1);
 n = strlen(s+1);

 s[0] = '$';
 manacher(n, s);

 for(int i=1; i<=n; ++i)
  t[n-i+1] = t[i+n+1] = s[i];
 t[n+1] = '%';
 getnext(n<<1|1, t);
 for(int i=1; i<=n; ++i)
  match[i] = next[i+n+2]-1;
 for(int i=1; i<=n; ++i)
  mm[i] = max(match[i], mm[i-1]);





 int ans = 0;
 for(int i=1; i<=n; ++i) {
  int l = i-d[i]+1, r = i+d[i]-1;
  int mt = min(mm[l-1], n-r);
  ans = max(ans, mt*2+(r-l+1));

 }

 for(int i=1; i<=n; ++i) {
  int l = i-d[i]+1, r = i+d[i]-1;
  int mt = min(mm[l-1], n-r);
  if(mt*2+(r-l+1)==ans) {
   if(mt==0)
    printf("%d\n%d %d\n", 1, l, r-l+1);
   else {
    int p = 0;
    for(int i=l-1; !p && i; --i)
     if(match[i]>=mt) p = i;
    printf("3\n%d %d\n%d %d\n%d %d\n", p-mt+1, mt, l, r-l+1, n-mt+1, mt);
   }
   break;
  }
 }
 getchar(), getchar();
 return 0;
}

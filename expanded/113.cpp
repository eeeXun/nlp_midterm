    : public uses_allocator<_Seq, _Alloc>::type { };



}
# 62 "/usr/include/c++/11.2.0/stack" 2 3
# 9 "data/113.cpp" 2








# 16 "data/113.cpp"
using namespace std;

int read()
{
 int x=0,f=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
 return x*f;
}

unsigned long long h[2][100005], po[100005];
char s[100005];
int n, f[100005], g[100005], m[100005], q[100005];
unsigned long long Hash(int typ, int l, int r)
{
 return h[typ][r] - h[typ][l] * po[abs(r - l)];

}
int Calc(int x)
{
    int s = x - f[x] + 1;
 int e = x + f[x] - 1;
    return f[x] * 2 - 1 + min(g[m[s-1]], n - e) * 2;
}
int main()
{
 scanf("%s", s + 1);
 n = strlen(s + 1);
 h[0][0] = h[1][n + 1] = 0;
 for(int i=1;i<=n;i++)
  h[0][i] = h[0][i - 1] * 29 + s[i] - 'a';
 for(int i=n;i>=1;i--)
  h[1][i] = h[1][i + 1] * 29 + s[i] - 'a';
 po[0] = 1;
 for(int i=1;i<=n;i++)
  po[i] = po[i - 1] * 29;
 for(int i=1;i<=n;i++)
 {
  int l = 1, ans = 1;
  int r = min(i, n - i + 1);
  while (l <= r)
  {
   int mid = (l + r) >> 1;
   if (Hash(0, i, i + mid - 1) == Hash(1, i, i - mid + 1))
    l = mid + 1, ans = mid;
   else r = mid - 1;
  }
  f[i] = ans;
 }



 int l = 1, r = 0;
 for(int i=1;i<=n;i++)
 {
  if (s[i] == s[n]) q[++ r] = i;
  while (l <= r && Hash(0, q[l], i) != Hash(1, n, n - (i - q[l])) && n - (i - q[l]) > i)
   l ++;
  if (l > r) g[i] = 0;
  else g[i] = i - q[l] + 1;
 }



 for(int i=1;i<=n;i++)
 {
  m[i] = m[i - 1];
  if (g[m[i]] < g[i])
   m[i] = i;
 }
 int ans = 0;
 for(int i=1;i<=n;i++)
  ans = max(ans, Calc(i));
 for (int i=1;i<=n;i++)
        if (ans==Calc(i))
        {
           int s=i-f[i]+1;
           int e=i+f[i]-1;
           int j=min(g[m[s-1]],n-e);
           int k=m[s-1]-g[m[s-1]]+1;
           if (j) cout << 3 << endl
                       << k << " " << j << endl
                       << s << " " <<e-s+1 << endl
                       << n-j+1 << " " << j << endl;
           else cout << 1 << endl << s << " " << e-s+1 << endl;
           return 0;
        }
 return 0;
}

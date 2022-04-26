using std::strtol;
using std::strtoul;
using std::system;

using std::wcstombs;
using std::wctomb;
# 11 "data/902.cpp" 2


# 12 "data/902.cpp"
using namespace std;
char s[100005],s2[100005];
int n,nxt[100005],r[100005],f[100005],g[100005],ans,x,mx,y;
int main() {
 cin>>s+1;
 n=strlen(s+1);
 s[n+1]='#';
 for(int i=1; i<=n; i++)
 {
  r[i]=(mx>i)?min(r[2*y-i],mx-i):1;
  while(s[i+r[i]]==s[i-r[i]])
  r[i]++;
  if(r[i]+i>mx)
  mx=r[i]+i,y=i;
 }
 for(int i=1;i<=n;i++)
 s2[i]=s[n+1-i];
 nxt[0]=nxt[1]=0;
 for(int i=2,j=0;i<=n;i++)
 {
  while(j&&s2[j+1]!=s2[i])
  j=nxt[j];
  if(s2[j+1]==s2[i])
  nxt[i]=++j;
 }
 for(int i=1,j=0;i<=n;i++)
 {
  while (j&&s2[j+1]!=s[i])
  j=nxt[j];
  if(s2[j+1]==s[i])
  f[i]=++j;
  if(f[i]==n)
  j=nxt[j];
  if(f[i])
  g[i]=i-f[i]+1;
 }
 for(int i=1;i<=n;i++)
 if(f[i-1]>f[i])
 f[i]=f[i-1],g[i]=g[i-1];
 bool b=0;
 for(int i=1;i<=n;i++)
 if(2*r[i]-1>ans)
 ans=2*r[i]-1,x=i-r[i]+1;
 for(int i=1;i<=n;i++)
 {
  int t=i-r[i];
  if(2*min(f[t],n-(i+r[i]-1))+2*r[i]-1>ans)
  b=1,ans=2*min(f[t],n-(i+r[i]-1))+2*r[i]-1,x=i;
 }
 if(!b)
 printf("1\n%d %d",x,ans);
 else
 printf("3\n%d %d\n%d %d\n%d %d",g[x-r[x]],f[x-r[x]],x-r[x]+1,2*r[x]-1,n-f[x-r[x]]+1,f[x-r[x]]);
 return 0;
}

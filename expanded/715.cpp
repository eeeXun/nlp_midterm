
# 4 "data/715.cpp"
using namespace std;


const int N=100000+10;
int n,ans,l,k,ma[N],nxt[N],a[N],b[N];
char s[N];
void manacher()
{
 int mx=0,k=0;
 for(int i=1;i<=n;i++)
 {
  for(ma[i]=i>=mx?0:min(mx-i,ma[2*k-i]);s[i-ma[i]-1]==s[i+ma[i]+1];ma[i]++);
  if(i+ma[i]>mx)mx=i+ma[i],k=i;
 }
}
void kmp()
{
 int j=nxt[n+1]=n+2;
 for(int i=n;i>=1;i--)
 {
  for(;j<=n+1&&s[i]!=s[j-1];j=nxt[j]);
  nxt[i]=--j;
 }
 j=n+1;
 for(int i=1;i<=n;i++)
 {
  for(;j<=n+1&&s[i]!=s[j-1];j=nxt[j]);
  a[i]=--j;
 }
}
int main()
{
 scanf("%s",s+1);n=strlen(s+1);s[0]='$';
 manacher();kmp();
 for(int i=1;i<=n;i++)
 {
  a[i]=n+1-a[i];
  if(a[i]<a[i-1])a[i]=a[i-1],b[i]=b[i-1];else b[i]=i-a[i]+1;
 }
 for(int i=1;i<=n;i++)if(ans<(l=ma[i]*2+1+min(a[i-ma[i]-1],n-i-ma[i])*2))ans=l,k=i;
 l=min(a[k-ma[k]-1],n-k-ma[k]);
 if(l)printf("3\n%d %d\n%d %d\n%d %d\n",b[k-ma[k]-1],l,k-ma[k],ma[k]*2+1,n-l+1,l);
  else printf("1\n%d %d\n",k-ma[k],ma[k]*2+1);
}

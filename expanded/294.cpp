# 5 "data/294.cpp" 2

# 5 "data/294.cpp"
using namespace std;
const long long p=1000000000007LL;
char buf[100010];
int n;
long long hsh[100010],pwr[100010];
long long suf[100010];
int to[100010];
int g[100010];
int m[100010];
int f[100010];
int ans,mx;
inline long long gethsh(int l,int r){return hsh[r]-hsh[l-1]*pwr[r+1-l];}
int main()
{
 scanf("%s",buf+1);
 n=strlen(buf+1);
 pwr[0]=1LL;
 for(int i=1;i<=n;i++)hsh[i]=hsh[i-1]*p+buf[i],pwr[i]=pwr[i-1]*p;
 for(int i=n;i>=1;i--)suf[n+1-i]=suf[n-i]*p+buf[i];
 int pos=1;
 for(int i=1;i<=n;i++)
 {
  int l=1,r=n+1-i;
  while(l<=r)
  {
   int mid=(l+r)>>1;
   if(gethsh(i,i+mid-1)==suf[mid])l=mid+1;else r=mid-1;
  }
  to[i]=i+l-2;
  while(pos<=i && to[pos]<i)pos++;
  g[i]=i+1-pos;
  if(!m[i-1] || g[m[i-1]]<g[i])m[i]=i;else m[i]=m[i-1];
 }
 pos=0;int r=0;
 for(int i=1;i<=n;i++)
 {
  if(r>=i)f[i]=min(r-i,f[pos+pos-i]);
  while(i>f[i]+1 && i+f[i]+1<=n && buf[i-f[i]-1]==buf[i+f[i]+1])f[i]++;
  if(i+f[i]>r)r=i+f[i],pos=i;
  int tmp=f[i]+f[i]+1+min(n-i-f[i],g[m[i-f[i]-1]])*2;
  if(tmp>mx)mx=tmp,ans=i;
 }
 int len=min(n-ans-f[ans],g[m[ans-f[ans]-1]]);
 if(!len)printf("1\n%d %d",ans-f[ans],f[ans]+f[ans]+1);
 else printf("3\n%d %d\n%d %d\n%d %d",m[ans-f[ans]-1]-g[m[ans-f[ans]-1]]+1,len,ans-f[ans],f[ans]+f[ans]+1,n-len+1,len);
 return 0;
}

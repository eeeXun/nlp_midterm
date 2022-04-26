# 2 "data/682.cpp"
using namespace std;

const long long N=100005,M1=1e9+7,P1=3846961,M2=998244353,P2=3072127;
char s[N];
long long f[N],g[N],fac1[N],fac2[N],v1[N],v2[N],v3[N],v4[N];
signed main(){
 scanf("%s",s+1);
 long long n=strlen(s+1),id=0,Max=0;
 reverse(s+1,s+n+1);
 for (long long i=1;i<=n;i++){
  if (id+Max>=i)f[i]=min(f[id*2-i],id+Max-i);
  while (i-f[i]-1>0&&i+f[i]+1<=n&&s[i-f[i]-1]==s[i+f[i]+1])f[i]++;
  if (id+Max<i+f[i])id=i,Max=f[i];
 }
 fac1[0]=fac2[0]=1;
 for (long long i=1;i<=n;i++)fac1[i]=fac1[i-1]*P1%M1,fac2[i]=fac2[i-1]*P2%M2;
 for (long long i=1;i<=n;i++)v1[i]=(v1[i-1]*P1+s[i])%M1,v2[i]=(v2[i-1]*P2+s[i])%M2;
 for (long long i=n;i;i--)v3[i]=(v3[i+1]*P1+s[i])%M1,v4[i]=(v4[i+1]*P2+s[i])%M2;
 for (long long i=1;i<=n;i++){
  long long l=0,r=i/2;
  while (l<r){
   long long mid=(l+r+1)/2;
   if (v1[mid]==(v3[i-mid+1]-v3[i+1]*fac1[mid]%M1+M1)%M1&&v2[mid]==(v4[i-mid+1]-v4[i+1]*fac2[mid]%M2+M2)%M2)l=mid;
   else r=mid-1;
  }
  g[l]=max(g[l],i);
 }
 g[0]=n+1;
 for (long long i=n-1;i>=0;i--)g[i]=max(g[i],g[i+1]);
 Max=0;long long ans1=0,ans2=0,ans3=0,ans4=0,ans5=0,ans6=0;
 for (long long i=1;i<=n;i++){
  long long l=0,r=i-f[i]-1;
  while (l<r){
   long long mid=(l+r+1)/2;
   if (i+f[i]<g[mid]-mid+1)l=mid;
   else r=mid-1;
  }
  if (Max<2*f[i]+1+l*2){
   Max=2*f[i]+1+l*2;
   ans1=l;ans2=l;
   ans3=i+f[i];ans4=f[i]*2+1;
   ans5=g[l];ans6=l;
  }
 }
 long long cnt=0;
 if (ans2>0)cnt++;
 if (ans4>0)cnt++;
 if (ans6>0)cnt++;
 printf("%lld\n",cnt);
 if (ans2>0)printf("%lld %lld\n",n-ans5+1,ans6);
 if (ans4>0)printf("%lld %lld\n",n-ans3+1,ans4);
 if (ans6>0)printf("%lld %lld\n",n-ans1+1,ans2);
 return 0;
}

# 2 "data/129.cpp"
using namespace std;

const long long NR=1e5+10;
const long long bas[]={1724,1826};
const long long mod[]={998244353,19260817};
long long n;
long long f[NR],g[NR];
long long t[2],Pow[2][NR];
long long Hash1[2][NR],Hash2[2][NR];
pair<long long,long long>ans[5];
char s[NR];
void iniths(){
 for(long long k=0;k<2;k++){
  Pow[k][0]=1;
  for(long long i=1;i<=n;i++)Pow[k][i]=Pow[k][i-1]*bas[k]%mod[k];
 }
 for(long long k=0;k<2;k++){
  for(long long i=1;i<=n;i++)Hash1[k][i]=(Hash1[k][i-1]*bas[k]+s[i])%mod[k];
  for(long long i=n;i;--i)Hash2[k][i]=(Hash2[k][i+1]*bas[k]+s[i])%mod[k];
 }
}
pair<long long,long long> getHash1(long long l,long long r){
 for(long long k=0;k<2;k++)
  t[k]=(Hash1[k][r]-Hash1[k][l-1]*Pow[k][r-l+1]%mod[k]+mod[k])%mod[k];
 return make_pair(t[0],t[1]);
}
pair<long long,long long> getHash2(long long l,long long r){
 for(long long k=0;k<2;k++)
  t[k]=(Hash2[k][l]-Hash2[k][r+1]*Pow[k][r-l+1]%mod[k]+mod[k])%mod[k];
 return make_pair(t[0],t[1]);
}

signed main(){
 scanf("%s",s+1);
    n=strlen(s+1);iniths();
 for(long long i=1;i<=n;i++){
  long long l=1,r=min(i,n-i+1);f[i]=1;
  while(l<=r){
   long long mid=(l+r)>>1;
   if(getHash1(i-mid+1,i)==getHash2(i,i+mid-1))f[i]=mid,l=mid+1;
   else r=mid-1;
  }
 }
 for(long long i=1;i<=n;i++){
  long long maxlen=0,l=1,r=n-i+1;
  while(l<=r){
   long long mid=(l+r)>>1;
   if(getHash1(i,i+mid-1)==getHash2(n-mid+1,n))maxlen=mid,l=mid+1;
   else r=mid-1;
  }
  if(maxlen)for(long long j=maxlen;j&&!g[j];j--)g[j]=i;
 }
 long long anslen=0;
 for(long long k=0;k<3;k++)ans[k]=make_pair(-1,-1);
 for(long long i=1;i<=n;i++){
  if(f[i]*2-1>anslen){
   anslen=f[i]*2-1;
   ans[0]=ans[2]=make_pair(-1,-1);
            ans[1]=make_pair(i-f[i]+1,i+f[i]-1);
  }
  long long l=1,r=min(i,n-i+1),maxlen=0;
  while(l<=r){
   long long mid=(l+r)>>1;
   if(n-mid+1>i+f[i]-1&&g[mid]&&g[mid]+mid-1<i-f[i]+1)maxlen=mid,l=mid+1;
   else r=mid-1;
  }
  if(maxlen){
   if(maxlen*2+f[i]*2-1>anslen){
    anslen=maxlen*2+f[i]*2-1;
    ans[0]=make_pair(g[maxlen],g[maxlen]+maxlen-1);
                ans[1]=make_pair(i-f[i]+1,i+f[i]-1);
                ans[2]=make_pair(n-maxlen+1,n);
   }
  }
 }
 if(!~ans[0].first)printf("1\n%lld %lld",ans[1].first,ans[1].second-ans[1].first+1);
 else{
  puts("3");
  for(long long k=0;k<3;k++)printf("%lld %lld\n",ans[k].first,ans[k].second-ans[k].first+1);
 }
 return 0;
}

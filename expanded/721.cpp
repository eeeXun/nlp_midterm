}
# 5 "data/721.cpp" 2

# 5 "data/721.cpp"
using namespace std;
typedef unsigned long long qword;
const int maxn=100010,seed=137;
int n;
char s[maxn];
int f[maxn];
int g[maxn];
qword h[maxn],r[maxn],pow[maxn];
void getMaxLen(){

 int p=0;
 for(int i=1;i<=n;++i)
  if(i>p+f[p]){
   for(f[i]=1;(0<(i-f[i])&&(i-f[i])<=n)&&(0<(i+f[i])&&(i+f[i])<=n)&&s[i-f[i]]==s[i+f[i]];++f[i]);
   --f[i];
   p=i;
  }else{
   int j=p-(i-p);
   f[i]=f[j];
   if(i+f[j]>=p+f[p]){
    for(f[i]=p+f[p]-i+1;(0<(i-f[i])&&(i-f[i])<=n)&&(0<(i+f[i])&&(i+f[i])<=n)&&s[i-f[i]]==s[i+f[i]];++f[i]);
    --f[i];
   }
   if(i+f[i]>p+f[p])
    p=i;
  }
}
inline qword getHashVal(qword*a,int p,int q,int len){
 return a[q]-a[p]*pow[len];
}
void getMinPre(){
 pow[0]=1;
 for(int i=1;i<=n;++i){
  h[i]=h[i-1]*seed+s[i];
  pow[i]=pow[i-1]*seed;
 }
 for(int i=n;i;--i)
  r[i]=r[i+1]*seed+s[i];
 g[n+1]=0;
 for(int i=n,p=0;i;--i)
  if(g[i+1]==p&&p<n&&s[p+1]==s[i])
   g[i]=++p;
  else{
   qword cmp=getHashVal(r,n+1,i,n-i+1);
   for(g[i]=p+1;g[i]<=n&&getHashVal(h,g[i]-(n-i+1),g[i],n-i+1)!=cmp;)
    ++g[i];
   p=g[i];
  }
}
int getMaxLen(int p,int q,vector<pair<int,int> >&tmp){
 tmp.clear();
 int l=0,r=n-q,ans=0;
 while(l<=r){
  int mid=l+r>>1;
  if(g[n-mid+1]<p)
   ans=mid,l=mid+1;
  else
   r=mid-1;
 }
 if(ans){
  tmp.push_back(make_pair(g[n-ans+1]-ans+1,g[n-ans+1]));
  tmp.push_back(make_pair(p,q));
  tmp.push_back(make_pair(n-ans+1,n));
 }else
  tmp.push_back(make_pair(p,q));
 return (ans<<1)+q-p+1;
}
int main(){

 scanf("%s",s+1);
 n=strlen(s+1);
 getMaxLen();
 getMinPre();
 int ans=0;
 vector<pair<int,int> > bst,tmp;
 for(int i=1;i<=n;++i){
  int p=getMaxLen(i-f[i],i+f[i],tmp);
  if(p>ans)
   ans=p,bst=tmp;
 }
 printf("%d\n",bst.size());
 for(int i=0;i<bst.size();++i)
  printf("%d %d\n",bst[i].first,bst[i].second-bst[i].first+1);
}

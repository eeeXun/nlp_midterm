# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 6 "data/761.cpp" 2

# 6 "data/761.cpp"
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
const int maxn = 1e5+5,bas = 29,mod = 1e9+7;
int n,pw[maxn];char s[maxn],t[maxn<<1];
int p[maxn<<1];
void Manacher(){
 int tn = n;t[0] = '~',t[1] = '@';
 for(int i=1;i<=n;++i)t[2*i] = s[i],t[2*i+1] = '@';
 n = 2*n+1;
 for(int i=1,maxx=0,mid=0;i<=n;++i){
  if(i<=maxx)p[i] = min(maxx-i,p[2*mid-i]);
  while(t[i-p[i]-1]==t[i+p[i]+1])++p[i];
  if(i+p[i]>maxx)maxx = i+p[i],mid = i;
 }
 n = tn;
 for(int i=1;i<=n;++i)p[i] = (p[2*i]+1)/2;
}
std :: vector <int> op[maxn];
int mx[maxn],pmx[maxn],stp[maxn];
struct Hashing{
 int pre[maxn];char s[maxn];
 void init(){for(int i=1;i<=n;++i)pre[i] = (1ll*pre[i-1]*bas+s[i]-'a')%mod;}
 int Hash(int l,int r){return (pre[r]-1ll*pre[l-1]*pw[r-l+1]%mod+mod)%mod;}
}fr,bk;
void getmx(){
 memcpy(fr.s,s,sizeof(s)),memcpy(bk.s,s,sizeof(s)),std :: reverse(bk.s+1,bk.s+n+1);
 pw[0] = 1;for(int i=1;i<=n;++i)pw[i] = 1ll*pw[i-1]*bas%mod;
 fr.init(),bk.init();
 for(int i=1;i<=n;++i){
  int l = 0,r = n-i+1,ans = 0;
  while(l<=r){
   int mid = l+r>>1;
   if(fr.Hash(i,i+mid-1) == bk.Hash(1,mid))ans = mid,l = mid+1;
   else r = mid-1;
  }mx[i] = ans;
 }
 for(int i=1;i<=n;++i)
  if(mx[i])op[i].push_back(i),op[i+mx[i]].push_back(-i);
 std :: set <int> st;
 for(int i=1;i<=n;++i){
  for(int v:op[i]){
   if(v<0)st.erase(-v);
   else st.insert(v);
  }
  if(st.size())pmx[i] = i+1-*st.begin(),stp[i] = *st.begin();
 }
 for(int i=1;i<=n;++i)
  if(pmx[i]<pmx[i-1])
   pmx[i] = pmx[i-1],stp[i] = stp[i-1];
}
void getans(){
 int p1,p2,p3,l1,l2,l3,ty = 0,maxl = 0;
 for(int i=1;i<=n;++i){
  int l = i-p[i]+1,r = i+p[i]-1,mx = min(n-r,pmx[l-1]);
  if(mx == 0){
   if(r-l+1>maxl)maxl = r-l+1,ty = 0,p1 = l,l1 = r-l+1;
  }else{
   if(r-l+1+2*mx>maxl){
    maxl = r-l+1+2*mx,ty = 1;
    l1 = mx,l2 = r-l+1,l3 = mx;
    p1 = stp[l-1]+(pmx[l-1]-mx),p2 = l,p3 = n-mx+1;
   }
  }
 }
 if(ty == 0)printf("1\n%d %d\n",p1,l1);
 else printf("3\n%d %d\n%d %d\n%d %d\n",p1,l1,p2,l2,p3,l3);
}
int main(){return scanf("%s",s+1),n = strlen(s+1),Manacher(),getmx(),getans(),0;}

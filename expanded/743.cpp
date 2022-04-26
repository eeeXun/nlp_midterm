
  template<>
    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 14 "data/743.cpp" 2


# 15 "data/743.cpp"
using namespace std;
# 30 "data/743.cpp"
typedef double db;
typedef long long ll;
typedef long double ldb;
typedef pair<int,int> pii;

const int INF=1e9+7;
const int maxn=2e5+5;
const int logn=22;

namespace SA{
 int len;
 int lcp[maxn],rk[maxn],sa[maxn],tmp[maxn],lg[maxn];
 int st[maxn][logn];
 char s[maxn];
 pii elm[maxn];
 inline bool cmp(const int &i,const int &j){return elm[i]<elm[j];}
 inline void calcSa(){
  for(int i=(0);i<=(len);++i) sa[i]=i,rk[i]=s[i];
  for(int k=1;k<=len;k<<=1){
   for(int i=(0);i<=(len);++i) elm[i]=make_pair(rk[i],(i+k<=len)?(rk[i+k]):(-1));
   sort(sa,sa+len+1,cmp);
   tmp[sa[0]]=0;
   for(int i=(1);i<=(len);++i) tmp[sa[i]]=tmp[sa[i-1]]+cmp(sa[i-1],sa[i]);
   for(int i=(0);i<=(len);++i) rk[i]=tmp[i];
  }
  return;
 }
 inline void calcLcp(){
  int h=0;
  lcp[0]=0;
  for(int i=(0);i<=(len);++i){
   int j=sa[rk[i]-1];
   for(h-=(h)?(1):(0);i+h<len&&j+h<len&&s[i+h]==s[j+h];++h);
   lcp[rk[i]-1]=h;
  }
  return;
 }
 inline void calcRmq(){
  lg[1]=0;
  for(int i=(2);i<=(len);++i) lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i);
  for(int i=(0);i<=(len);++i) st[i][0]=lcp[i];
  for(int j=(1);j<(logn);++j){
   for(int i=(0);i<=(len);++i){
    if(i+(1<<j)>len) st[i][j]=st[i][j-1];
    else st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
   }
  }
  return;
 }
 inline void init(char *s,int len){
  SA::len=len;
  for(int i=(0);i<(len);++i) SA::s[i]=s[i];
  calcSa();
  calcLcp();
  calcRmq();
  return;
 }
 inline int query(int x,int y){

  x=rk[x];y=rk[y];
  if(x>y) swap(x,y);
  --y;

  return min(st[x][lg[y-x+1]],st[y-(1<<lg[y-x+1])+1][lg[y-x+1]]);
 }
}

int n,ans;
int pos[maxn];
char s[maxn];
vector<pii> vans;

inline void calcPos(){
 int p=SA::rk[0],h;
 h=n;
 for(int i=(0);i<(SA::len);++i) pos[i]=INF;
 for(int i=p-1;i>=0;--i){
  h=min(h,SA::lcp[i]);

  if(SA::sa[i]>n) pos[h]=min(pos[h],SA::sa[i]-n-1);
 }
 h=SA::lcp[p];
 for(int i=(p+1);i<=(SA::len);++i){

  if(SA::sa[i]>n) pos[h]=min(pos[h],SA::sa[i]-n-1);
  h=min(h,SA::lcp[i]);
 }
 return;
}

inline int getPre(int l,int r){
 int lb=0,rb=n;
 while(lb+1<rb){
  int md=(lb+rb)>>1;
  if(md+pos[md]-1<l&&n-md>r) lb=md;
  else rb=md;
 }
 return lb;
}

int main(){
 scanf("%s",s);
 n=strlen(s);
 s[n]='$';
 for(int i=(n+1);i<=(n<<1);++i) s[i]=s[i-n-1];
 reverse(s,s+n);
 SA::init(s,n<<1|1);






   calcPos();
 for(int i=n-1;i>=0;--i) pos[i]=min(pos[i],pos[i+1]);


 for(int i=(0);i<(n);++i){
  int len=SA::query(i+n+1,n-i-1);

  int pre=getPre(i-len+1,i+len-1);

  if((pre<<1)+((len<<1)-1)>ans){
   vans.clear();
   ans=(pre<<1)+((len<<1)-1);
   if(!pre){
    vans.push_back(make_pair(i-len+1,(len<<1)-1));
   }else{
    vans.push_back(make_pair(pos[pre],pre));
    vans.push_back(make_pair(i-len+1,(len<<1)-1));
    vans.push_back(make_pair(n-pre,pre));
   }
  }
 }
 printf("%d\n",vans.size());
 for(int i=(0);i<(vans.size());++i) printf("%d %d\n",vans[i].first+1,vans[i].second);
 return 0;
}

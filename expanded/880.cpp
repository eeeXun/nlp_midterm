    };

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
# 14 "data/880.cpp" 2


# 15 "data/880.cpp"
using namespace std;
# 30 "data/880.cpp"
typedef double db;
typedef long long ll;
typedef long double ldb;
typedef pair<int,int> pii;

const int INF=1e9+7;
const int maxn=2e5+5;
const int logn=25;

class SparseTable{
private:
 int lg[maxn];
 int table[maxn][logn];
public:
 inline void init(int *dat,int len){
  for(int i=(2);i<(maxn);++i) lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i);
  for(int i=(0);i<(len);++i) table[i][0]=dat[i];
  for(int j=(1);j<(logn);++j){
   for(int i=(0);i<(len);++i){
    if(i+(1<<j)>=len) table[i][j]=table[i][j-1];
    else table[i][j]=max(table[i][j-1],table[i+(1<<j-1)][j-1]);
   }
  }
  return;
 }
 inline int query(int l,int r){
  int len=r-l+1;
  return max(table[l][lg[len]],table[r-(1<<lg[len])+1][lg[len]]);
 }
}st;

int n,ans;
int lft[maxn],p[maxn],z[maxn];
pii ansx,ansy,ansz;

inline void manacher(char *s,int len){
 int l=-1,r=-1;
 for(int i=(0);i<(len);++i){

  if(i<=r) p[i]=min(r-i+1,p[l+r-i]);
  for(;i+p[i]<len&&i-p[i]>=0&&s[i+p[i]]==s[i-p[i]];++p[i]);
  if(i+p[i]-1>r) l=i-p[i]+1,r=i+p[i]-1;
 }
 return;
}

inline void zMatch(char *s,int len){
 int l=-1,r=-1;
 z[0]=n;
 for(int i=(1);i<=(len);++i){
  if(i<=r) z[i]=min(r-i+1,z[i-l]);
  for(;i+z[i]<len&&s[i+z[i]]==s[z[i]];++z[i]);
  if(i+z[i]-1>r) l=i,r=i+z[i]-1;
 }
 return;
}

inline int getPalin(int l,int r){
 int lb=0,rb=n;
 while(lb+1<rb){
  int md=(lb+rb)>>1;
  if(l+md-1>r-md+1){
   rb=md;
   continue;
  }
  if(st.query(l+md-1,r-md+1)>=md) lb=md;
  else rb=md;
 }

 return lb;
}

char s[maxn];

int main(){
 scanf("%s",s);
 n=strlen(s);
 manacher(s,n);




 st.init(p,n);
 s[n]='$';for(int i=(n+1);i<=(n<<1);++i) s[i]=s[i-n-1];
 reverse(s,s+n);

 zMatch(s,n<<1|1);


 for(int i=(0);i<=(n);++i) lft[i]=INF;
 for(int i=(n+1);i<(n<<1|1);++i) lft[z[i]]=min(lft[z[i]],i-n-1);
 for(int i=n-1;i>=0;--i) lft[i]=min(lft[i],lft[i+1]);


 ansx=ansy=ansz=make_pair(-1,-1);
 for(int i=(0);i<(n);++i) if(ansy.second<(p[i]<<1)-1) ansy=make_pair(i-p[i]+1,(p[i]<<1)-1);
 ans=ansy.second;
 for(int i=(0);i<=(n);++i){
  if(lft[i]==INF) continue;
  int l=lft[i]+i,r=n-i-1;
  if(l>r) continue;
  int x=getPalin(l,r);

  if((i<<1)+(x<<1)-1>ans){
   ans=(i<<1)+(x<<1)-1;
   ansx=make_pair(lft[i],i);
   ansz=make_pair(n-i,i);
   ansy.second=(x<<1)-1;
  }
 }
 if(ansx.first!=-1){
  int l=ansx.first+ansx.second+((ansy.second+1)>>1)-1;
  int r=ansz.first-((ansy.second+1)>>1);
  for(int i=(l);i<=(r);++i) if((p[i]<<1)-1>=ansy.second) ansy.first=i-((ansy.second+1)>>1)+1;
 }
 if(ansx.first==-1){
  puts("1");
  printf("%d %d\n",ansy.first+1,ansy.second);
  return 0;
 }
 puts("3");
 printf("%d %d\n",ansx.first+1,ansx.second);
 printf("%d %d\n",ansy.first+1,ansy.second);
 printf("%d %d\n",ansz.first+1,ansz.second);
 return 0;
}

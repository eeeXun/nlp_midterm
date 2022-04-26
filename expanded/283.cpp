    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/283.cpp" 2

# 2 "data/283.cpp"
using namespace std;
namespace Sakurajima_Mai{
# 18 "data/283.cpp"
 typedef long long ll;
 typedef unsigned long long ull;
 typedef double db;
 const int infi=2e9;
 const ll infl=4e18;
 inline ll ceil_div(ll a,ll b){ return (a+b-1)/b; }

}
using namespace Sakurajima_Mai;
namespace Fast_Read{
 inline int qi(){
     int f=0,fu=1; char c=getchar();
     while(c<'0'||c>'9'){ if(c=='-')fu=-1; c=getchar(); }
     while(c>='0'&&c<='9'){ f=(f<<3)+(f<<1)+c-48; c=getchar(); }
     return f*fu;
 }
 inline ll ql(){
  ll f=0;int fu=1; char c=getchar();
     while(c<'0'||c>'9'){ if(c=='-')fu=-1; c=getchar(); }
     while(c>='0'&&c<='9'){ f=(f<<3)+(f<<1)+c-48; c=getchar(); }
     return f*fu;
 }
 inline db qd(){
     char c=getchar();int flag=1;double ans=0;
     while((!(c>='0'&&c<='9'))&&c!='-') c=getchar();
     if(c=='-') flag=-1,c=getchar();
     while(c>='0'&&c<='9') ans=ans*10+(c^48),c=getchar();
     if(c=='.'){c=getchar();for(register int Bit=10;c>='0'&&c<='9';Bit=(Bit<<3)+(Bit<<1)) ans+=(double)(c^48)*1.0/Bit,c=getchar();}
     return ans*flag;
 }
}
namespace Read{






}
namespace Out{




}
namespace DeBug{






}
using namespace Fast_Read;
using namespace Read;
using namespace Out;
using namespace DeBug;
const int MAX_N=2e5+5;
const int MAX_S=2e5+5;
const int MAX_M=2e5+5;
char s[MAX_N],t[MAX_N<<1];
int dia[MAX_N<<1],lp;
int Manacher(char *s)
{
 int pos=0,i=0;
 t[pos]='%',lp=strlen(s+1);
 while(i<lp) t[++pos]='#',t[++pos]=s[++i];
 t[++pos]='#';
 int rm=0,id=0,ans=0;
 lp=pos;
 for(register int i=2,bbb=lp;i<=bbb;++i){
  dia[i]=i<rm?min(rm-i,dia[2*id-i]):1;
  while(t[i-dia[i]]==t[i+dia[i]]) dia[i]++;
  if(dia[i]+i-1>rm) id=i,rm=dia[i]+i-1;
 }
 for(register int i=1,bbb=lp;i<=bbb;++i) --dia[i],ans=max(ans,dia[i]);
 return ans;
}
int match[MAX_N];
int dp[MAX_N],st[MAX_N];
struct KMP{
 char s[MAX_S],mode[MAX_M];
 int ls,lm,nxt[MAX_M];
 void build_next()
 {
  lm=strlen(mode+1);
  nxt[1]=0;
  for(int i=2,j=0;i<=lm;i++){
   while(j&&mode[i]!=mode[j+1]) j=nxt[j];
   nxt[i]=(mode[j+1]==mode[i]?++j:j);
  }
 }
 void find()
 {
  ls=strlen(s+1);
  for(int i=1,j=0;i<=ls;i++){
   while(j&&s[i]!=mode[j+1]) j=nxt[j];
   if(s[i]==mode[j+1]) j++;
   match[i]=j;
   if(j==lm){ j=nxt[j]; }
  }
 }
}kmp;
typedef pair<int,int> P;
vector<P> rec;
int main()
{
 scanf("%s",s+1); int len=strlen(s+1);
 Manacher(s);
 reverse(s+1,s+1+len);
 for(register int i=1,bbb=len+1;i<=bbb;++i) kmp.mode[i]=s[i];
 kmp.build_next();
 reverse(s+1,s+1+len);
 for(register int i=1,bbb=len+1;i<=bbb;++i) kmp.s[i]=s[i];
 kmp.find();
 for(register int i=1,bbb=len;i<=bbb;++i){
  if(match[i]>dp[i-1]) dp[i]=match[i],st[i]=i-match[i]+1;
  else dp[i]=dp[i-1],st[i]=st[i-1];
 }
 int ans=0;
 vector<P> rec;
 for(register int i=1,bbb=len;i<=bbb;++i){
  int middle=dia[2*i],lb=i-middle/2-1,rb=i+middle/2+1;
  int ps=min(dp[lb],len-rb+1);
  if(2*ps+middle>ans){
   ans=2*ps+middle; rec.clear();
   if(ps) rec.push_back(P(st[lb],ps));
   rec.push_back(P(lb+1,middle));
   if(ps) rec.push_back(P(len-ps+1,ps));
  }
 }
 printf("%d",rec.size()),puts("");
 for(auto x:rec) printf("%d",x.first),printf("%c",' '),printf("%d",x.second),puts("");
 return 0;
}

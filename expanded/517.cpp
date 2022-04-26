using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline ll read()
{
 ll s=0; bool f=0; char ch=' ';
 while(!isdigit(ch)) {f|=(ch=='-'); ch=getchar();}
 while(isdigit(ch)) {s=(s<<3)+(s<<1)+(ch^48); ch=getchar();}
 return (f)?(-s):(s);
}

inline void write(ll x)
{
 if(x<0) {putchar('-'); x=-x;}
 if(x<10) {putchar(x+'0'); return;}
 write(x/10); putchar((x%10)+'0');
}


const int N=100005;
const ull bas[]={31,37},Mod[]={998244353,19260817};
int n,pip[N],pmx[N],wzmx[N],Next[N];
ull has1[2][N],has2[2][N],bin[2][N];
char S[N],T[N];
struct node{int k,len,c1,c2,c3,p1,p2,p3;}jyl,jzx;
inline bool operator<(node p,node q){return p.len<q.len;}
inline void kmp()
{
 int i,j;
 for(i=1;i<=n;i++) T[n-i+1]=S[i];
 for(Next[1]=0,j=0,i=2;i<=n;i++)
 {
  while(j&&T[j+1]!=T[i]) j=Next[j];
  if(T[j+1]==T[i]) j++; Next[i]=j;
 }
 for(j=0,i=1;i<=n;i++)
 {
  while(j&&T[j+1]!=S[i]) j=Next[j];
  if(T[j+1]==S[i]) j++; pip[i]=j;
 }
}
inline void pre_has()
{
 int o,i;
 for(o=0;o<2;o++)
 {
  for(bin[o][0]=1,i=1;i<=n;i++) bin[o][i]=1ll*bin[o][i-1]*bas[o]%Mod[o];
  for(has1[o][0]=0,i=1;i<=n;i++) has1[o][i]=(1ll*has1[o][i-1]*bas[o]%Mod[o]+(S[i]-'a'+1))%Mod[o];
 }
 for(o=0;o<2;o++)
 {
  for(has2[o][n+1]=0,i=n;i>=1;i--) has2[o][i]=(1ll*has2[o][i+1]*bas[o]%Mod[o]+(S[i]-'a'+1))%Mod[o];
 }
}
inline bool chk(int pp,int len)
{
 int o,l1=pp-len,r1=pp-1,l2=pp+1,r2=pp+len;
 ll tp1[2]={0,0},tp2[2]={0,0};
 for(o=0;o<2;o++)
 {
  tp1[o]=1ll*(has1[o][r1]-has1[o][l1-1]*bin[o][len]%Mod[o]+Mod[o])%Mod[o];
  tp2[o]=1ll*(has2[o][l2]-has2[o][r2+1]*bin[o][len]%Mod[o]+Mod[o])%Mod[o];
  if(tp1[o]!=tp2[o]) return false;
 }
 return true;
}
int main()
{
 int i,l1,r1,mid,tmp,pos,oo;
 scanf("%s",S+1); n=strlen(S+1);
 kmp();
 pre_has();
 for(pmx[0]=wzmx[0]=0,i=1;i<=n;i++)
 {
  if(pip[i]>pmx[i-1]) pmx[i]=pip[i],wzmx[i]=i;
  else pmx[i]=pmx[i-1],wzmx[i]=wzmx[i-1];
 }
 jyl.len=0;
 for(i=1;i<=n;i++)
 {
  l1=0; r1=min(i-1,n-i); tmp=0;
  while(l1<=r1)
  {
   mid=(l1+r1)>>1; if(chk(i,mid)) tmp=mid,l1=mid+1; else r1=mid-1;
  }
  jzx.c2=tmp*2+1; pos=i-tmp-1; jzx.p2=i-tmp;
  if((!pos)||(!pmx[pos]))
  {
   jzx.k=1;
   jzx.c1=jzx.c3=0;
   jzx.len=jzx.c2;
  }
  else
  {
   jzx.k=3;
   oo=min(pmx[pos],n-(i+tmp));
   jzx.c1=jzx.c3=oo;
   jzx.p1=wzmx[pos]-pmx[pos]+1; jzx.p3=n-pmx[pos]+1;
   jzx.len=jzx.c2+jzx.c1*2;
  }
  if(jyl<jzx) jyl=jzx;
 }
 write(jyl.k),putchar('\n');
 if(jyl.k==1)
 {
  write(jyl.p2),putchar(' '); write(jyl.c2),putchar('\n');
 }
 else
 {
  write(jyl.p1),putchar(' '); write(jyl.c1),putchar('\n');
  write(jyl.p2),putchar(' '); write(jyl.c2),putchar('\n');
  write(jyl.p3),putchar(' '); write(jyl.c3),putchar('\n');
 }
 return 0;
}

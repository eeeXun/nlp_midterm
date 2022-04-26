# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/779.cpp" 2



# 7 "data/779.cpp"
using namespace std;
namespace Luitaryi {
const int N=100010,B=147;
int n,m;
char a[N<<1],s[N],t[N];
int len[N<<1],f[N],pos[N],nxt[N],ans,P;
inline void manacher() {
 register int l=-1,mx=0,id=0;
 a[++l]='$';
 for(register int i=1;i<=n;++i) a[++l]='#',a[++l]=s[i];
 a[++l]='#';
 for(register int i=1;i<=l;++i) {
  if(mx>i) len[i]=min(len[2*id-i],mx-i);
  else len[i]=1;
  while(a[i+len[i]]==a[i-len[i]]) ++len[i];
  if(len[i]+i>mx) mx=len[i]+i,id=i;
 }
 for(register int i=1;i<=n;++i) len[i]=(len[i<<1]-1)>>1;
}
inline void main() {
 scanf("%s",s+1),n=strlen(s+1);
 memcpy(t,s,sizeof s);
 reverse(t+1,t+n+1);
 for(register int i=2,j=0;i<=n;++i) {
  while(j&&t[i]!=t[j+1]) j=nxt[j];
  if(t[i]==t[j+1]) ++j; nxt[i]=j;
 }
 for(register int i=1,j=0;i<=n;++i) {
  while(j&&(j==m||s[i]!=t[j+1])) j=nxt[j];
  if(s[i]==t[j+1]) ++j;
  if(j>=f[i-1]) {
   f[i]=j,pos[i]=i-j+1;
  } else f[i]=f[i-1],pos[i]=pos[i-1];
 }
 manacher();
 for(register int i=1,tmp;i<=n;++i) {
  tmp=len[i]*2+1+2*min(f[i-len[i]-1],n-i-len[i]);
  if(tmp>ans) ans=tmp,P=i;
 }
 register int tmp=min(f[P-len[P]-1],n-P-len[P]);
 if(!tmp) {
  puts("1");
  printf("%d %d\n",P-len[P],len[P]*2+1);
 } else {
  puts("3");
  printf("%d %d\n%d %d\n%d %d\n",
   pos[P-len[P]-1],tmp,
   P-len[P],len[P]*2+1,
   n-tmp+1,tmp);
 }
}
} signed main() {Luitaryi::main(); return 0;}

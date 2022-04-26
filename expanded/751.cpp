# 5 "data/751.cpp" 2



# 7 "data/751.cpp"
using namespace std;
const int N=1e6+5;
char s[N],S[N];
int n,Next[N],r[N],ans,rig,cen,f[N],g[N],flag,p;
int main(){
 scanf("%s",s+1); n=strlen(s+1);
 for(int i=1;i<=n;i++) S[n-i+1]=s[i]; s[n+1]='#';
 for(int i=2,j=0;i<=n;i++){
  while(j&&S[j+1]!=S[i]) j=Next[j];
  if(S[j+1]==S[i]) Next[i]=++j;
 }
 for(int i=1;i<=n;i++){
  r[i]=rig>i?min(r[2*cen-i],rig-i):1;
  while(s[i+r[i]]==s[i-r[i]]) r[i]++;
  if(r[i]+i>rig) rig=r[i]+i,cen=i;
 }
 for(int i=1,j=0;i<=n;i++){
  while(j&&S[j+1]!=s[i]) j=Next[j];
  if(S[j+1]==s[i]) f[i]=++j;
  if(j==n) j=Next[j];
  if(f[i]) g[i]=i-f[i]+1;
 }
 for(int i=1;i<=n;i++) if(f[i]<f[i-1]) f[i]=f[i-1],g[i]=g[i-1];
 for(int i=1;i<=n;i++) if(r[i]*2-1>ans) ans=r[i]*2-1,p=i-r[i]+1;
 for(int i=1;i<=n;i++){
  int t=i-r[i],val=2*min(f[t],n-(i+r[i]-1))+2*r[i]-1;
  if(val>ans) flag=1,ans=val,p=i;
 }
 if(!flag) printf("1\n%d %d",p,ans);
 else printf("3\n%d %d\n%d %d\n%d %d",g[p-r[p]],f[p-r[p]],p-r[p]+1,2*r[p]-1,n-f[p-r[p]]+1,f[p-r[p]]);
 return 0;
}

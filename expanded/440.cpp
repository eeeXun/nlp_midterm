



# 6 "data/440.cpp"
using namespace std;
const int N=1e6+5;
char s[N],s1[N],s2[N];
int idx,p[N],ans1,ans2,ans3,cnt,kmp[N],emx[N],pv[N],pp[N],ans;
inline void qr() {
 char S=getchar();
 s[0]='^'; s[1]='|'; idx=1;
 while(S<'a'||S>'z'){S=getchar();}
 while(S>='a'&&S<='z'){s[++idx]=S;s1[++cnt]=S;s[++idx]='|';S=getchar();}
}
int n;
inline void solve() {
 qr();
 for(int t=1,mid=0,r=0;t<=idx;t++) {
  if(t<=r) p[t]=min(p[(mid<<1)-t],r-t+1);
  while(s[t-p[t]]==s[t+p[t]]) p[t]++;
  if(p[t]+t>r) r=p[t]+t-1,mid=t;
  if(!(t&1)) ans1=max(ans1,p[t]);
 }
 ans1--;
 if(ans1==cnt) return(void)(printf("1\n1 %d\n",cnt));
 for(int i=(1);i<=(cnt);i++) s2[i]=s1[cnt-i+1];
 for(int i=2,j=0;i<=cnt;i++) {
  while(j&&s2[i]!=s2[j+1]) j=kmp[j];
  if(s2[i]==s2[j+1]) j++;
  kmp[i]=j;
 }
 for(int i=1,j=0;i<=cnt;i++) {
  while(j&&s1[i]!=s2[j+1]) j=kmp[j];
  if(s1[i]==s2[j+1]) j++;
  emx[i]=min(j,cnt-i);
 }
 for(int i=(1);i<=(cnt);i++) {
  if(emx[i]>pv[i-1]) pv[i]=emx[i],pp[i]=i;
  else pv[i]=pv[i-1],pp[i]=pp[i-1];
 }
 for(int i=(1);i<=(cnt);i++) {
  int pos=i*2;
  if((p[pos]/2)==i) continue;
  int tmp=p[pos]-1,L=(i-(p[pos]/2)),R=(i+(p[pos]/2)); L++; R--;
  if(L==1||R==n) continue;
  L--;
  tmp+=min(pv[L],cnt-R)*2;
  ans3=max(ans3,tmp);
 }
 ans=max(ans1,ans3);
 if(ans1==ans) for(int i=(1);i<=(cnt);i++) if((p[i*2]-1)==ans) return(void)(printf("1\n%d %d\n",i-(ans/2),ans));
 if(ans3==ans) {
  for(int i=(1);i<=(cnt);i++) {
   int pos=i*2;
   if((p[pos]/2)==i) continue;
   int tmp=p[pos]-1,L=(i-(p[pos]/2)),R=(i+(p[pos]/2)); L++; R--;
   if(L==1||R==n) continue;
   L--; int len=min(pv[L],cnt-R);
   tmp+=len*2;
   if(tmp==ans) return(void)(printf("3\n%d %d\n%d %d\n%d %d\n",pp[L]-len+1,len,i-(p[pos]/2)+1,p[pos]-1,cnt-len+1,len));
  }
 }
}
int main() {

 solve();
}

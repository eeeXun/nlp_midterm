
# 4 "data/785.cpp"
using namespace std;
typedef long long ll;
const int NR=2e5+10;
int n,ans;
int p1,p2;
char s[NR],s1[NR],s2[NR];
int d[NR],nxt[NR];
int f1[NR],f2[NR],f3[NR];
void manacher() {
 d[1]=1; int mid=1,maxr=1;
 for(int i=2,len=n*2;i<=len;i++) {
  if(i<maxr) d[i]=min(d[mid*2-i],d[mid]-i+mid);
  else d[i]=1;
  while(s1[i-d[i]]==s1[i+d[i]]) d[i]++;
  if(i+d[i]>maxr) maxr=i+d[i],mid=i;
 }
 for(int i=3;i<=n*2;i+=2) {
  if(s1[i+d[i]]=='#') d[i]--;
  else d[i]-=2;
  d[i/2+1]=d[i]+1;
 }
}
int main() {
 scanf("%s",s+1);
 n=strlen(s+1);
 for(int i=1;i<=n;i++)
  s1[i*2-1]=s[i],s1[i*2]='#';
 manacher();
 for(int i=1,up=n/2;i<=up;i++)
  s2[i]=s[n+1-i],s2[n+1-i]=s[i];
 for(int i=2,t=0;i<=n;i++) {
  while(s2[t+1]!=s2[i]&&t) t=nxt[t];
  if(s2[t+1]==s2[i]) t++,nxt[i]=t;
  else nxt[i]=0;
 }
 for(int i=1,t=0;i<=n;i++) {
  while(s2[t+1]!=s[i]&&t) t=nxt[t];
  if(s2[t+1]==s[i]) t++,f1[i]=t;
  else f1[i]=0;
 }
 for(int i=1;i<=n;i++) {
  if(f1[i]>=f2[i-1]) f2[i]=f1[i],f3[i]=i;
  else f2[i]=f2[i-1],f3[i]=f3[i-1];
 }
 for(int i=1;i<=n;i++) {
  if(ans<d[i]+min(f2[i-(d[i]/2)-1],n-i-d[i]/2)*2) {
   p1=f3[i-d[i]/2-1];
   p2=i;
   ans=d[i]+min(f2[i-d[i]/2-1],n-i-d[i]/2)*2;
  }
 }
 if(n-p2-d[p2]/2&&p1&&f1[p1]) {
  puts("3");
  int len=min(f1[p1],n-p2-d[p2]/2);
  printf("%d %d\n",p1-len+1,len);
  printf("%d %d\n",p2-d[p2]/2,d[p2]);
  printf("%d %d\n",n-len+1,len);
 }
 else {
  puts("1");
  printf("%d %d\n",p2-d[p2]/2,d[p2]);
 }
 return 0;
}

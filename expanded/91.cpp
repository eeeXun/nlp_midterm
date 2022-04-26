# 3 "data/91.cpp"
using namespace std;
inline int read(){
 int x=0,f=1;
 char ch=getchar();
 while(ch<'0'||ch>'9'){
  if(ch=='-') f=-1;
  ch=getchar();
 }
 while(ch>='0'&&ch<='9'){
  x=x*10+ch-'0';
  ch=getchar();
 }
 return x*f;
}
char s[2000005],t[2000005],v[2000005];
int tot,n;
void Init(){
 t[tot++]='@';
 for (int i=1;i<=n;++i) t[tot++]=s[i];
 t[tot++]='#';
}
int r[2000005];
void Manacher(){
 int mx=0,id=0;
 for (int i=0;i<tot;++i){
  r[i]=mx>i?min(mx-i,r[2*id-i]):1;
  while (t[i-r[i]]==t[i+r[i]]) r[i]++;
  if (r[i]+i>mx){
   mx=r[i]+i;
   id=i;
  }
 }
}
int nxt[2000005];
inline int kmp(int p,char c){

 while (p&&v[p+1]!=c) p=nxt[p];
 if (v[p+1]==c) p++;
 return p;
}
int f[2000005],pos[2000005];
int main(){
 scanf("%s",s+1);
 n=strlen(s+1);
 Init();
 Manacher();
 for (int i=1;i<=n;++i){
  v[i]=s[n-i+1];
 }
 for (int i=2;i<=n;++i) nxt[i]=kmp(nxt[i-1],v[i]);
 for (int i=1,j=0;i<=n;++i){
  j=kmp(j,s[i]);
  f[i]=j;
  if (j==n) j=nxt[j];
  if (f[i]) pos[i]=i-f[i]+1;
 }
 for (int i=1;i<=n;++i){
  if (f[i-1]>f[i]){
   f[i]=f[i-1];
   pos[i]=pos[i-1];
  }
 }


 int ans=0,id=0;
 for (int i=1;i<=n;++i){
  int L=i-r[i],R=i+r[i];
  int now=2*(r[i]+min(f[L],n-R+1))-1;
  if (ans<now) ans=now,id=i;

 }

 if (ans==2*r[id]-1){
  printf("1\n");
  printf("%d %d\n",id-r[id]+1,ans);
 }
 else {
  printf("3\n");
  int p=pos[id-r[id]];
  int l=f[id-r[id]];
  printf("%d %d\n",p,l);
  printf("%d %d\n",id-r[id]+1,2*r[id]-1);
  printf("%d %d\n",n-l+1,l);
 }
}

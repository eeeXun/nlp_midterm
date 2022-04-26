
# 3 "data/166.cpp"
using namespace std;
inline int get(){
 char c; bool f=0;
 while(!isdigit(c=getchar()))f|=c=='-';
 int v=c-48; while(isdigit(c=getchar()))v=v*10+c-48;
 return f?-v:v;
}
const int maxn=100005;
char str[maxn];
int n,r[maxn],f[maxn],g[maxn];
unsigned h1[maxn],h2[maxn],fa[maxn];
bool cmp(int p1,int p2,int len){
 if(p1<=0||p2<=0||p1+len-1>n||p2+len-1>n)return 0;
 return (h1[p1+len-1]-h1[p1-1])*fa[n-p1]==
  (h2[p2]-h2[p2+len])*fa[n-1];
}
int main(){
 scanf("%s",str+1);
 n=strlen(str+1);
 r[1]=1;
 str[0]='%'; str[n+1]='&';
 for(int i=2,mx=1,p=1;i<=n;++i){
  r[i]=i<=mx?min(mx-i+1,r[2*p-i]):1;
  while(str[i+r[i]]==str[i-r[i]])++r[i];
  if(mx<i+r[i]-1){
   mx=i+r[i]-1;
   p=i;
  }
 }
 fa[0]=1;
 for(int i=1;i<=n;++i){
  fa[i]=fa[i-1]*233;
  h1[i]=h1[i-1]+str[i]*fa[i];
 }
 for(int i=n;i>=1;--i)h2[i]=h2[i+1]+str[i]*fa[n-i+1];
 for(int i=1,w=1;i<=n;++i){
  while(w<n-i+1&&!cmp(w-i+1,n-i+1,i))++w;
  if(w>=n-i+1)break;
  f[w]=i;
 }
 for(int i=1;i<=n;++i){
  g[i]=i;
  if(f[i]<f[i-1]){
   f[i]=f[i-1];
   g[i]=g[i-1];
  }
 }
 int ans=0,x1,x2,x3,t1,t2,t3;
 for(int i=1,s,t,tmp;i<=n;++i){
  s=i-r[i]+1;
  t=i+r[i]-1;
  if(n-f[s-1]+1<=t){
   tmp=2*r[i]-1+2*(n-t);
   if(tmp>ans){
    x1=g[s]; t1=n-t;
    x2=s; t2=2*r[i]-1;
    x3=t+1; t3=n-t;
    ans=tmp;
   }
  }
  else {
   tmp=r[i]*2-1+2*f[s-1];
   if(tmp>ans){
    x1=g[s-1]-f[s-1]+1; t1=f[s-1];
    x2=s; t2=2*r[i]-1;
    x3=n-f[s-1]+1; t3=f[s-1];
    ans=tmp;
   }
  }
 }
 if(t1)printf("%d\n%d %d\n%d %d\n%d %d\n",3,x1,t1,x2,t2,x3,t3);
 else printf("%d\n%d %d\n",1,x2,t2);
 return 0;
}

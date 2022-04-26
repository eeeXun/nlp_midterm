# 4 "data/383.cpp" 2

# 4 "data/383.cpp"
using namespace std;
const unsigned dw=20031219;
int ans;
int id[100010];
char s[100010];
int n;
int len[100010];
unsigned w[100010],f[100010],g[100010];
int k,x[5],y[5];
int h[100010];
inline int cmp(int x,int y,int k)
{
 return (g[x]-g[x-k]*w[k])*w[y-k+1]==(f[y]-f[y-k]);
}
int main()
{
 scanf("%s",s+1);
 n=strlen(s+1);
 int maxn=0,pos=0;
 for (int i=1;i<=n;i++)
 {
  if (maxn>=i) len[i]=min(maxn-i+1,len[2*pos-i]);
  else len[i]=1;
  while (i+len[i]<=n&&i-len[i]>0&&s[i-len[i]]==s[i+len[i]]) len[i]++;
  if (i+len[i]-1>maxn) maxn=i+len[i]-1,pos=i;
 }
 w[0]=1;
 for (int i=1;i<=n;i++) w[i]=w[i-1]*dw;
 for (int i=1;i<=n;i++)
 {
  int c=s[i]-'a'+1;
  f[i]=f[i-1]+c*w[i];
  g[i]=g[i-1]*dw+c;
 }
 for (int i=1;i<=n;i++)
 {
  int l=0,r=n-i+1;
  while (l<r)
  {
   int mid=(l+r+1)>>1;
   if (cmp(i+mid-1,n,mid)) l=mid; else r=mid-1;
  }
  h[i+l-1]=max(h[i+l-1],l);
 }
 for (int i=n;i;i--) h[i]=max(h[i],h[i+1]-1);
 for (int i=1;i<=n;i++)
  if (h[i-1]<h[i]) id[i]=i; else h[i]=h[i-1],id[i]=id[i-1];
 for (int i=1;i<=n;i++)
 {
  int d=min(h[id[i-len[i]]],n-(i+len[i])+1);
  int lens=d*2+len[i]*2-1;
  if (lens>ans)
  {
   ans=lens;
   if (d)
   {
    k=3;
    x[1]=id[i-len[i]]-d+1; y[1]=d;
    x[2]=i-len[i]+1; y[2]=len[i]*2-1;
    x[3]=n-d+1; y[3]=d;
   } else k=1,x[1]=i-len[i]+1,y[1]=len[i]*2-1;
  }
 }
 printf("%d\n",k);
 for (int i=1;i<=k;i++) printf("%d %d\n",x[i],y[i]);
}

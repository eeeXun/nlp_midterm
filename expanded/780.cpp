# 4 "data/780.cpp" 2

# 4 "data/780.cpp"
using namespace std;



char s[100010]={'!'};
int n,m,k,R,p[100010],ex[100010],f[100010],w[100010],ans,tmp;
int main()
{
 scanf("%s",s+1);
 n=strlen(s+1);
 for(int i=1;i<=n;i++)
 {
  ex[i]=(i<R)?min(R-i,ex[2*m-i]):0;
  while (s[i-ex[i]-1] == s[i+ex[i]+1]) ex[i]++;
  if (i+ex[i]>R) R=i+ex[m=i];
 }
 p[n+1]=k=n+2;
 for(int i=n;i;i--)
 {
  while (k<=n+1 && s[i]!=s[k-1]) k=p[k];
  p[i]=--k;
 }
 k=n+1;
 for(int i=1;i<=n;i++)
 {
  while (k<=n+1 && s[i]!=s[k-1]) k=p[k];
  f[i]=--k;
 }
 for(int i=1;i<=n;i++)
 {
  f[i]=n+1-f[i];
  if (f[i-1]>f[i])
  {
   f[i]=f[i-1];
   w[i]=w[i-1];
  }
  else w[i]=i-f[i]+1;
 }
 for(int i=1;i<=n;i++)
 {
  tmp=ex[i]*2+1+min(f[i-ex[i]-1],n-i-ex[i])*2;
  if (tmp>ans) ans=tmp,k=i;
 }
 m=min(f[k-ex[k]-1],n-k-ex[k]);
 printf("%d\n",m?3:1);
 if (m)
  printf("%d %d\n%d %d\n%d %d\n",w[k-ex[k]-1],m,k-ex[k],ex[k]*2+1,n-m+1,m);
 else
     printf("%d %d\n",k-ex[k],ex[k]*2+1);
 return 0;
}

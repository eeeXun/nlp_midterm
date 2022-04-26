# 4 "data/45.cpp" 2

# 4 "data/45.cpp"
using namespace std;
int n;
char a[100005],b[200005];
int r[200005];
int f[100005];
char a1[100005];
int s[100005],s2[100005],bh[100005];
int main()
{
 scanf("%s",a+1);
 for (n=1;a[n]!='\0';n++) ;
 n--;
 for (int i=1;i<=n*2+1;i++)
 {
  if (i==1) b[i]='$';
  else if (i==n*2+1) b[i]='@';
  else if (i%2==0) b[i]=a[i/2];
  else b[i]='#';
 }
 int rx=1,mx=1;
 r[1]=0;
 for (int i=2;i<=n*2+1;i++)
 {
  if (mx<i)
  {
   while (i+r[i]+1<=n*2+1&&i-r[i]-1>=1)
   {
    if (b[i+r[i]+1]==b[i-r[i]-1]) r[i]++;
    else break;
   }
  }
  else if (rx*2-i-r[rx*2-i]>rx-r[rx]) r[i]=r[rx*2-i];
  else
  {
   r[i]=mx-i;
   while (i+r[i]+1<=n*2+1&&i-r[i]-1>=1)
   {
    if (b[i+r[i]+1]==b[i-r[i]-1]) r[i]++;
    else break;
   }
  }
  if (i+r[i]>mx) rx=i,mx=i+r[i];
 }



 for (int i=1,j=n;i<=n;i++,j--) a1[i]=a[j];
 f[1]=0;
 for (int i=2;i<=n;i++)
 {
  int j=f[i-1]+1;
  while (a1[i]!=a1[j]&&j!=1) j=f[j-1]+1;
  if (a1[i]==a1[j]) f[i]=j;
  else f[i]=0;
 }
 for (int i=1,j=1;i<=n;i++)
 {
  if (a[i]==a1[j]) s[i]=j,j++;
  else
  {
   j=f[j-1]+1;
   while (a[i]!=a1[j]&&j!=1) j=f[j-1]+1;
   if (a[i]==a1[j]) s[i]=j,j++;
   else s[i]=0;
  }
 }
 for (int i=1;i<=n;i++)
 {
  s2[i]=max(s2[i-1],s[i]);
  if (s2[i]==s[i]) bh[i]=i;
  else bh[i]=bh[i-1];
 }




 rx=0; mx=0;
 for (int i=1;i<=n;i++)
 {

  int x=(i*2-r[i*2]-1)/2;

  if (x==0||i*2-x>n)
  {

   if (i*2-x-1-x-1+1>mx) rx=i,mx=i*2-x-1-x-1+1;
  }
  else
  {
   if (n-s2[x]+1>=i*2-x)
   {

    if (s2[x]*2+i*2-x-1-x-1+1>mx) rx=i,mx=s2[x]*2+i*2-x-1-x-1+1;
   }
   else
   {

    if ((n-i*2+x+1)*2+i*2-x-1-x-1+1>mx) rx=i,mx=(n-i*2+x+1)*2+i*2-x-1-x-1+1;
   }
  }
 }

 int i=rx,x=(i*2-r[i*2]-1)/2;
 if (x==0||i*2-x>n||!s2[x])
 {
  printf("1\n");
  printf("%d %d\n",x+1,i*2-x-1-x-1+1);
 }
 else
 {
  printf("3\n");
  if (n-s2[x]+1>=i*2-x)
  {
   printf("%d %d\n%d %d\n%d %d\n",bh[x]-s2[x]+1,s2[x],x+1,i*2-x-1-x-1+1,n-s2[x]+1,s2[x]);
  }
  else
  {
   printf("%d %d\n%d %d\n%d %d\n",i*2-x-n+bh[x],n-i*2+x+1,x+1,i*2-x-1-x-1+1,i*2-x,n-i*2+x+1);
  }
 }
 return 0;
}

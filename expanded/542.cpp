
# 4 "data/542.cpp"
using namespace std;
char a[200001];
int s1[200001],s2[200001],da[200001];
int b[200001],f[200001][21],t[21];
int zz;
int xx[10],yy[10];
int i,j,k,n,m,p,l,r,mid,ans,x,y,mx,h,ll,rr,len,tt;


void work()
{
 t[0]=1;
 for (i=1;i<=20;i++)t[i]=t[i-1]*2;
 for (i=1;i<=n;i++)
  {
   l=0;
   r=i;
   while (l<=r)
    {
     mid=(l+r)>>1;
     if (s1[i]-s1[i-mid]*da[mid]==s2[i]-s2[i+mid]*da[mid])
  l=mid+1;else r=mid-1;
    }
   b[i]=((l+r)>>1)-1;
  }
 for (i=1;i<=n;i++)f[i][0]=b[i];
 for (j=1;j<=20;j++)
  for (i=1;i<=n;i++)
   if (i+t[j]-1<=n)
    f[i][j]=max(f[i][j-1],f[i+t[j-1]][j-1]);
}

int done(int i,int j)
{
 k=i;
 h=20;
 mx=0;
 while (k<=j)
  {
   while (k+t[h]-1>j)h--;
   mx=max(mx,f[k][h]);
   k=k+t[h];
  }
  return mx;
}
int calc(int i,int j)
{
 ll=1;
 rr=(j-i)/2;
 while (ll<=rr)
  {
   mid=(ll+rr)>>1;
   if (done(i+mid,j-mid)>=mid)
    ll=mid+1;else rr=mid-1;
  }
 return (ll+rr)>>1;
}


int main()
{
 gets(a);
 n=strlen(a);
 p=136999;
 for (i=n;i>=1;i--)a[i]=a[i-1];
 s1[0]=0;
 for (i=1;i<=n;i++)s1[i]=s1[i-1]*p+a[i];
 s2[n+1]=0;
 for (i=n;i>=1;i--)s2[i]=s2[i+1]*p+a[i];
 da[0]=1;
 for (i=1;i<=n;i++)da[i]=da[i-1]*p;
 work();
 ans=0;
 zz=1;
 for (i=1;i<=n;i++)
  if (b[i]*2+1>ans)xx[1]=i-b[i],yy[1]=b[i]*2+1,ans=b[i]*2+1;
 i=1;
 j=n;
 while (i<=j)
  {
   if (s2[j]==s1[i]-s1[i-n+j-1]*da[n-j+1] && i<=j)
    {
  i++;j--;
  if (i<=j)len=calc(i,j);
     if (i>j && (n-j)*2-1>ans)
      {zz=1;xx[1]=i-(n-j);yy[1]=(n-j)*2-1;ans=(n-j)*2-1;}
     if (i<=j && len*2+1+(n-j)*2>ans)
      {zz=3;xx[1]=i-(n-j);yy[1]=n-j;
    xx[3]=j+1;yy[3]=n-j;ans=len*2+1+(n-j)*2;
    tt=len*2+1;}
    }
    else i++;
  }

 printf("%d\n",zz);
 if (zz==1)printf("%d %d\n",xx[1],yy[1]);
 else
 {
  for (i=xx[1]+yy[1];i<xx[3];i++)
   if (i-tt/2>xx[1]+yy[1]-1 && i+tt/2<xx[3] && 2*b[i]+1>=tt)
    xx[2]=i-tt/2,yy[2]=tt;
  for (i=1;i<=3;i++)printf("%d %d\n",xx[i],yy[i]);
 }
 return 0;
}

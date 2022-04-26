




# 8 "data/38.cpp"
long long ha1[100010],hr1[100010],mi1[100010];
long long ha2[100010],hr2[100010],mi2[100010];
long long getha1(int l,int r)
{
 long long rt=ha1[r];
 if(l>0)
  rt=(rt-ha1[l-1]*mi1[r-l+1]%1000000007 +1000000007)%1000000007;
 return rt;
}
long long gethr1(int l,int r)
{
 long long rt=hr1[r];
 if(l>0)
  rt=(rt-hr1[l-1]*mi1[r-l+1]%1000000007 +1000000007)%1000000007;
 return rt;
}
long long getha2(int l,int r)
{
 long long rt=ha2[r];
 if(l>0)
  rt=(rt-ha2[l-1]*mi2[r-l+1]%998244353 +998244353)%998244353;
 return rt;
}
long long gethr2(int l,int r)
{
 long long rt=hr2[r];
 if(l>0)
  rt=(rt-hr2[l-1]*mi2[r-l+1]%998244353 +998244353)%998244353;
 return rt;
}
void manacher(char zf[100010],int n,int cd[100010])
{
 int ma=-1,wz=-1;
 for(int i=0;i<n;i++)
 {
  cd[i]=1;
  if(i<=ma)
   cd[i]=cd[wz-(i-wz)];
  if(i+cd[i]-1>ma)
   cd[i]=ma-i+1;
  while(i-cd[i]>=0&&i+cd[i]<n&&zf[i-cd[i]]==zf[i+cd[i]])
   cd[i]+=1;
  if(i+cd[i]-1>ma)
  {
   ma=i+cd[i]-1;
   wz=i;
  }
 }
}
int lg[100010],zd[17][100010],wz[17][100010];
void yuclrmq(int cd[100010],int n)
{
 lg[1]=0;
 for(int i=2;i<=n;i++)
  lg[i]=lg[i>>1]+1;
 for(int i=0;i<n;i++)
 {
  zd[0][i]=cd[i];
  wz[0][i]=i;
 }
 for(int i=1;i<=lg[n];i++)
 {
  for(int j=0;j+(1<<i)<=n;j++)
  {
   zd[i][j]=zd[i-1][j+(1<<(i-1))];
   wz[i][j]=wz[i-1][j+(1<<(i-1))];
   if(zd[i-1][j]>zd[i][j])
   {
    zd[i][j]=zd[i-1][j];
    wz[i][j]=wz[i-1][j];
   }
  }
 }
}
int rmq(int l,int r,int &w)
{
 int t=lg[r-l+1];
 int rt=zd[t][r-(1<<t)+1];
 w=wz[t][r-(1<<t)+1];
 if(zd[t][l]>rt)
 {
  rt=zd[t][l];
  w=wz[t][l];
 }
 return rt;
}
int check(int l,int r,int s)
{
 l=l+s-1;
 r=r-s+1;
 if(l>r)
  return -1;
 int w;
 if(rmq(l,r,w)>=s)
  return w;
 else
  return -1;
}
int gethuiwen(int x,int y,int &w)
{
 int l=1,r=(y-x+2)/2;
 while(l<r)
 {
  int m=(l+r+1)>>1;
  w=check(x,y,m);
  if(w!=-1)
   l=m;
  else
   r=m-1;
 }
 w=check(x,y,l);
 return l;
}
char zf[100010];
int cd[100010];
int main()
{
 scanf("%s",zf);
 int n=strlen(zf);
 for(int i=0;i<n;i++)
 {
  if(i==0)
  {
   ha1[i]=zf[i];
   hr1[i]=zf[n-1-i];
  }
  else
  {
   ha1[i]=(ha1[i-1]*1313131 +zf[i])%1000000007;
   hr1[i]=(hr1[i-1]*1313131 +zf[n-1-i])%1000000007;
  }
 }
 for(int i=0;i<n;i++)
 {
  if(i==0)
  {
   ha2[i]=zf[i];
   hr2[i]=zf[n-1-i];
  }
  else
  {
   ha2[i]=(ha2[i-1]*29 +zf[i])%998244353;
   hr2[i]=(hr2[i-1]*29 +zf[n-1-i])%998244353;
  }
 }
 mi1[0]=1;
 for(int i=1;i<=n;i++)
  mi1[i]=mi1[i-1]*1313131%1000000007;
 mi2[0]=1;
 for(int i=1;i<=n;i++)
  mi2[i]=mi2[i-1]*29%998244353;
 manacher(zf,n,cd);
 yuclrmq(cd,n);
 int ma=-1,mx=-1,mw=-1,zi=-1;
 for(int x=0,i=0;x<n;x++)
 {
  if(x>0)
  {
   while(i+x<=n-1-x&&(getha1(i,i+x-1)!=gethr1(0,x-1)||getha2(i,i+x-1)!=gethr2(0,x-1)))
    i+=1;
  }
  if(i+x>n-1-x)
   break;
  int w;
  int rt=gethuiwen(i+x,n-1-x,w);
  if(rt*2+x+x>ma)
  {
   ma=rt*2+x+x;
   mx=x;
   mw=w;
   zi=i;
  }
 }
 int bj=(ma-mx-mx)/2;
 if(mx==0)
  printf("1\n%d %d",mw-bj+2,bj+bj-1);
 else
  printf("3\n%d %d\n%d %d\n%d %d",zi+1,mx,mw-bj+2,bj+bj-1,n-mx+1,mx);
 return 0;
}

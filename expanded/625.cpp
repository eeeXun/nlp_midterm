}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 7 "data/625.cpp" 2

# 7 "data/625.cpp"
using namespace std;
const int p1=233,p2=433,mod1=1000000007,mod2=1000000009;
char a[101010];
int p[101010],hsh1[101010],hsh2[101010],t1[101010],t2[101010];
int mx[100101][25],pll[101001][25];
int ans,pl1,pl2,pl3,pl,n;
void geths(int l,int r,int &hs1,int &hs2)
{
 hs1=(hsh1[r]-(long long)hsh1[l-1]*t1[r-l+1]%mod1+mod1)%mod1;
 hs2=(hsh2[r]-(long long)hsh2[l-1]*t2[r-l+1]%mod2+mod2)%mod2;
}
void manacher(int n)
{
 int id,mx,i,j;
 id=1,mx=1,ans=p[1]=1;
 pl2=1;
 for(i=2;i<=n;i++)
 {
  j=id+id-i;
  if(i<mx)
   p[i]=min(p[j],mx-i+1);

  while(i-p[i]>0&&i+p[i]<=n&&a[i+p[i]]==a[i-p[i]])
   p[i]++;
  if(i+p[i]-1>mx)
   mx=i+p[i]-1,id=i;
  if(p[i]+p[i]-1>ans)
   ans=p[i]+p[i]-1,pl2=i;
 }
}
int querymax(int l,int r)
{
 int tmp;
 tmp=log2(r-l+1);
 pl=mx[l][tmp]>mx[r-(1<<tmp)+1][tmp]?pll[l][tmp]:pll[r-(1<<tmp)+1][tmp];
 return max(mx[l][tmp],mx[r-(1<<tmp)+1][tmp]);
}
int main()
{
 int i,j,hss1,hss2,l,l1,r1,ll,rr,sum,h1,h2,tmp;


 scanf("%s",a+1);
 n=strlen(a+1);
 t1[0]=1,t2[0]=1;
 for(i=1;i<=n;i++)
 {
  hsh1[i]=((long long)hsh1[i-1]*p1+a[i]-'a'+1)%mod1;
  hsh2[i]=((long long)hsh2[i-1]*p2+a[i]-'a'+1)%mod2;
  t1[i]=(long long)t1[i-1]*p1%mod1;
  t2[i]=(long long)t2[i-1]*p2%mod2;
 }
 manacher(n);



 for(i=1;i<=n;i++)
  mx[i][0]=p[i],pll[i][0]=i;
 for(j=1;j<=20;j++)
  for(i=1;i+(1<<j-1)<=n;i++)
  {
   mx[i][j]=max(mx[i][j-1],mx[i+(1<<j-1)][j-1]);
   pll[i][j]=mx[i][j-1]>mx[i+(1<<j-1)][j-1]?pll[i][j-1]:pll[i+(1<<j-1)][j-1];
  }
 tmp=1,hss1=0,hss2=0,l=0;
 for(i=n;i>=1;i--)
 {
  hss1=((long long)hss1*p1+a[i]-'a'+1)%mod1;
  hss2=((long long)hss2*p2+a[i]-'a'+1)%mod2;
  l++;
  while(tmp<=n)
  {
   if(tmp+l-1>=i)
    break;
   geths(tmp,tmp+l-1,h1,h2);

   if(h1==hss1&&h2==hss2)
    break;
   tmp++;
  }

  if(tmp+l-1>=i)
   break;
  l1=tmp+l-1,r1=i;
  ll=1,rr=(r1-l1)/2;

  while(ll<=rr)
  {
   int mid=ll+rr>>1;
   if(querymax(l1+mid,r1-mid)>=mid)
    ll=mid+1;
   else
    rr=mid-1;
  }
  querymax(l1+rr,r1-rr);

  if(rr*2-1+l+l>ans)
   ans=rr*2-1+l+l,pl1=tmp,pl2=pl,pl3=i;
 }

 sum=0;
 if(pl1!=0)
  sum++;
 if(pl2!=0)
  sum++;
 if(pl3!=0)
  sum++;
 printf("%d\n",sum);
 if(pl1!=0)
  printf("%d %d\n",pl1,n-pl3+1);
 if(pl2!=0)
  printf("%d %d\n",pl2-p[pl2]+1,p[pl2]*2-1);
 if(pl3!=0)
  printf("%d %d\n",pl3,n-pl3+1);
 return 0;
}

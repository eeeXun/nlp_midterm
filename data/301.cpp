// powered by xpd1  /i love shimokawa_mikuni and i haven't touch my devc for 3 months. 
// All of these left only broken history after 12.4.22. sacrifice for my dPXq love.
// on 2012-10-
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <ctype.h>
#include <memory>
#include <fstream>
#include <string>
#include <utility>
#include <iomanip>

#include <map>
#include <queue>
#include <vector>
#include <list>
#include <set>
//#include <conio.h>
#define oo 2000000000
#define ol 200000000000000000ll //=2E17
#define ooo 1E14
#define EPS 1E-10
#define mp make_pair
#define pb push_back
#define eps EPS
#define mem(x,y) (memset((x),y,sizeof((x))))
#define debug(x) cout << #x<<" = "<<x<<endl;
#ifdef __int64
 #define fmt64 "%I64d"
#else 
 #define fmt64 "%lld"
#endif
using namespace std;
using namespace rel_ops;
const double PI=acos((double)-1);
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
int ts,ts2,ts3,ts4;
int n;
LL gcd(LL x,LL y){LL t;for(;y!=0;){t=x%y;x=y;y=t;}return x;}
int hl[100005],hr[100005],f[100005],g[100005],m[100005],pawa[100005];
char c[100005];
int geth(int l,int r)  //不包括 l这个位置 
{
  if (l<=r) return hl[r]-hl[l]*pawa[r-l];
  else return hr[r]-hr[l]*pawa[l-r];
}
int ans;
int getans(int x)  
{  
    int l=x-f[x]+1,r=x+f[x]-1;  
    return f[x]*2-1+min(g[m[l-1]],n-r)*2;  
}  
  
int main()
{
  int i,j,k,l,t1,t2,t3,t4,t5,t6,t7,t8,t9,t,nw;
  int tt1,tt2,tt3,tt4;
  double u1,u2,u3,u4,u5,u6,u7,u8,u9;
  char c1,c2,c3;
  srand((unsigned)time(0));//srand(72888306);
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
  #endif
  scanf("%s",c+1); n =strlen(c+1);
  for (i=1;i<=n;i++) hl[i]=hl[i-1]*31+c[i];  
  for (i=n;i>=1;i--) hr[i]=hr[i+1]*31+c[i];  
  for (pawa[0]=1,i=1;i<=n;i++)pawa[i]=pawa[i-1]*31;
  int r;
  for(i=1;i<=n;i++)
  {
   l=1,r= min(i,n-i+1);
   for(;l<=r;)
   {
    int mid = (l+r)/2;
    if (geth(i,i+mid-1) != geth(i,i-mid+1))
     r=mid-1;
     else l=mid+1;
   }
   f[i]=r;
  }
  t1=0;
  for(i=1;i<=n;i++)
  {
   for(;t1<=i && geth(t1,i) != geth(n+1,n-(i-t1-1)) &&n-(i-t1-1)>i ;t1++);
   g[i]= i-t1;
  }
  for(i=1;i<=n;i++)
  {
   m[i]=m[i-1];
   if (g[m[i]]<g[i])m[i]=i;
  }
  t2=0;
  for(i=1;i<=n;i++)
  {
   t1= getans(i);
    if (t1 >ans) ans=t1, t2=i;
  }
  i=t2;
  
  t3 =min(g[m[i-f[i]]],n-(i+f[i]-1));
  l = i-f[i]+1;
  if (t3 >0)
  printf("3\n%d %d\n%d %d\n%d %d\n",m[l-1]-g[m[l-1]]+1,t3,i-f[i]+1,f[i]*2-1,n-(t3)+1,t3);
  else printf("1\n%d %d\n",i-f[i]+1,f[i]*2-1);
  return 0;
}

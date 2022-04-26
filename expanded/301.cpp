      { return __set._M_t; }

      static auto&
      _S_get_tree(std::multiset<_Val, _Cmp2, _Alloc>& __set)
      { return __set._M_t; }
    };



}
# 63 "/usr/include/c++/11.2.0/set" 2 3
# 71 "/usr/include/c++/11.2.0/set" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

  namespace pmr
  {
    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 23 "data/301.cpp" 2
# 38 "data/301.cpp"

# 38 "data/301.cpp"
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
int geth(int l,int r)
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
  srand((unsigned)time(0));

  freopen("input.txt","r",
# 69 "data/301.cpp" 3 4
                         stdin
# 69 "data/301.cpp"
                              );freopen("output.txt","w",
# 69 "data/301.cpp" 3 4
                                                         stdout
# 69 "data/301.cpp"
                                                               );

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

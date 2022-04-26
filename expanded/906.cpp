# 36 "/usr/include/c++/11.2.0/stdlib.h" 3
# 1 "/usr/include/c++/11.2.0/cstdlib" 1 3
# 39 "/usr/include/c++/11.2.0/cstdlib" 3
       
# 40 "/usr/include/c++/11.2.0/cstdlib" 3
# 37 "/usr/include/c++/11.2.0/stdlib.h" 2 3

using std::abort;
using std::atexit;
using std::exit;


  using std::at_quick_exit;


  using std::quick_exit;




using std::div_t;
using std::ldiv_t;

using std::abs;
using std::atof;
using std::atoi;
using std::atol;
using std::bsearch;
using std::calloc;
using std::div;
using std::free;
using std::getenv;
using std::labs;
using std::ldiv;
using std::malloc;

using std::mblen;
using std::mbstowcs;
using std::mbtowc;

using std::qsort;
using std::rand;
using std::realloc;
using std::srand;
using std::strtod;
using std::strtol;
using std::strtoul;
using std::system;

using std::wcstombs;
using std::wctomb;
# 55 "data/906.cpp" 2


# 56 "data/906.cpp"
using namespace std;
const long long base=233;
const long long Mod=1000000007;
char s[100010];
long long h1[100010],h2[100010],p[100010];
int f[100010],g[100010];
long long get1(int l,int r)
{
 long long res=(h1[r+1]-h1[l]*p[r+1-l]%Mod+Mod)%Mod;
 return res;
}
long long get2(int l,int r)
{
 long long res=(h2[l]-h2[r+1]*p[r+1-l]%Mod+Mod)%Mod;
 return res;
}
int main()
{
 scanf("%s",&s);
 int len=strlen(s);
 h1[0]=0;
 for (int i=0;i<len;i++)
 {
  h1[i+1]=h1[i]*base+s[i];
  h1[i+1]%=Mod;
 }
 h2[len]=0;
 for (int i=len-1;i>=0;i--)
 {
  h2[i]=h2[i+1]*base+s[i];
  h2[i]%=Mod;
 }
 p[0]=1;
 for (int i=1;i<=len;i++)
 {
  p[i]=p[i-1]*base%Mod;
 }
 for (int i=0;i<=len;i++)
 {
  f[i]=1e9;
 }
 for (int i=0;i<len;i++)
 {
  int l=0,r=(len-i)/2,m;
  while (l<r)
  {
   m=(l+r+1)>>1;
   if (get1(i,i+m-1)==get2(len-m,len-1))
   {
    l=m;
   }
   else
   {
    r=m-1;
   }
  }
  f[l]=min(f[l],i-1);
 }
 g[len]=f[len];
 for (int i=len-1;i>=0;i--)
 {
  g[i]=min(g[i+1],f[i]);
 }
 for (int i=1;i<=len;i++)
 {
  g[i]+=i;
 }
 int ans=0,x1,l1,x2,l2,x3,l3;
 for (int i=0;i<len;i++)
 {
  int l=0,r=min(i,len-i-1),m;
  while (l<r)
  {
   m=(l+r+1)>>1;
   if (get1(i-m,i)==get2(i,i+m))
   {
    l=m;
   }
   else
   {
    r=m-1;
   }
  }
  int L=l;
  l=0,r=len-(i+L)-1;
  while (l<r)
  {
   m=(l+r+1)>>1;
   if (g[m]<i-L)
   {
    l=m;
   }
   else
   {
    r=m-1;
   }
  }
  if (L*2+1+2*l>ans)
  {
   ans=L*2+1+2*l;
   x1=g[l]-l+2;
   l1=l;
   x2=i-L+1;
   l2=L*2+1;
   x3=len-l+1;
   l3=l;
  }
 }
 if (l1)
 {
  puts("3");
  printf("%d %d\n%d %d\n%d %d\n",x1,l1,x2,l2,x3,l3);
 }
 else
 {
  puts("1");
  printf("%d %d\n",x2,l2);
 }
    return 0;
}

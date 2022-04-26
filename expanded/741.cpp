# 71 "/usr/include/c++/11.2.0/cstring" 3
extern "C++"
{
namespace std __attribute__ ((__visibility__ ("default")))
{


  using ::memchr;
  using ::memcmp;
  using ::memcpy;
  using ::memmove;
  using ::memset;
  using ::strcat;
  using ::strcmp;
  using ::strcoll;
  using ::strcpy;
  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;
# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 17 "data/741.cpp" 2
#pragma comment(linker, "/STACK:16777216")

# 18 "data/741.cpp"
using namespace std;
# 40 "data/741.cpp"
int a,b,c,d,i,j,n,m,k,ans,bo;
vector<pair<int,int> > abl;
char str[111111];
int len[111111];
const int MX=1<<17;
int mx1[MX*2];
inline void update1(int l,int a)
{
 l+=MX;
 for (mx1[l]=a;l>>=1;) mx1[l]=max(mx1[l*2],mx1[l*2+1]);
}
inline int fnd1(int l,int r)
{
 int ans=-1000000000;
 for (l+=MX,r+=MX;l<=r;l=(l+1)/2,r=(r-1)/2) ans=max(ans,max(mx1[l],mx1[r]));
 return ans;
}
unsigned long long h1[111111],h2[111111],pw[111111],so;
const int pp=37;
inline void check(int beg,char *str,unsigned long long *h1,unsigned long long *h2,unsigned long long sub,int n)
{
 int l=0,r=n/2;
 while (r-l>1)
 {
  int xx=(r+l)/2;
  if (h1[xx]-sub*pw[xx+1]==h2[n-xx-1]) l=xx; else
  r=xx;
 }
 if (h1[r]-sub*pw[r+1]==h2[n-r-1]) l=r;
 if (h1[l]-sub*pw[l+1]==h2[n-l-1]) ++l; else
 l=0;
 int bl=l;
 int fl=bl,fr=n-l-1;

 l=0,r=fr-fl+1;
 while (r-l>1)
 {
  int xx=(r+l)/2;
  int nl=fl+xx,nr=fr-xx;
  if (fnd1(nl+beg,nr+beg)>=xx) l=xx; else
  r=xx;
 }
 if (fnd1(fl+r+beg,fr-r+beg)>=r) l=r;
 if (2*bl+2*l+1>ans)
 {
  ans=2*bl+2*l+1;
  bo=beg;
  so=sub;
 }
}
inline void build(int beg,char *str,unsigned long long *h1,unsigned long long *h2,unsigned long long sub,int n)
{
 int l=0,r=n/2;
 while (r-l>1)
 {
  int xx=(r+l)/2;
  if (h1[xx]-sub*pw[xx+1]==h2[n-xx-1]) l=xx; else
  r=xx;
 }
 if (h1[r]-sub*pw[r+1]==h2[n-r-1]) l=r;
 if (h1[l]-sub*pw[l+1]==h2[n-l-1]) ++l; else
 l=0;
 l=min(l,n/2);
 if (l==n/2 && n%2==0) --l;
 int bl=l;
 int fl=bl,fr=n-l-1;
 abl.clear();
 for (int _n(fr), i(fl); i <= _n; i++)
 {
  int rr=len[i+beg];
  rr=min(rr,i-fl);
  rr=min(rr,fr-i);
  int cur=2*bl+2*rr+1;
  if (cur==ans)
  {
   abl.push_back(make_pair(beg+1,bl));
   abl.push_back(make_pair(i+beg-rr+1,2*rr+1));
   abl.push_back(make_pair(n+beg-bl+1,bl));
   return;
  }
 }
}
int main()
{


 gets(str);
 n=(int)strlen(str);
 {
  int l=0, r=-1;
  for (int i=0; i<n; ++i) {
   int k = (i>r ? 0 : min (len[l+r-i], r-i)) + 1;
   while (i+k < n && i-k >= 0 && str[i+k] == str[i-k]) ++k;
   len[i] = --k;
   if (i+k > r)
    l = i-k, r = i+k;
   update1(i,len[i]);
  }
 }
 for (int _n((n)-1), i(0); i <= _n; i++)
 {
  if (!i) h1[i]=str[i]-'a'+1; else
  h1[i]=h1[i-1]*pp+str[i]-'a'+1;
 }
 for(int i=(n-1),_b=(0);i>=_b;i--)
 {
  if (i==n-1) h2[i]=str[i]-'a'+1; else
  h2[i]=h2[i+1]*pp+str[i]-'a'+1;
 }
 pw[0]=1;
 for (int _n((n)), i(1); i <= _n; i++) pw[i]=pw[i-1]*pp;
 ans=0;
 unsigned long long sub=0;
 for (int _n((n)-1), i(0); i <= _n; i++)
 {
  check(i,str+i,h1+i,h2+i,sub,n-i);
  sub=sub*pp+str[i]-'a'+1;
 }
 build(bo,str+bo,h1+bo,h2+bo,so,n-bo);
 a=0;
 for (int _n(((int)((abl).size()))-1), i(0); i <= _n; i++) if (abl[i].second!=0) ++a;
 printf("%d\n",a);
 for (int _n(((int)((abl).size()))-1), i(0); i <= _n; i++) if (abl[i].second!=0) printf("%d %d\n",abl[i].first,abl[i].second);
}

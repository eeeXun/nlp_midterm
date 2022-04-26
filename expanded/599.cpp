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
# 15 "data/599.cpp" 2
# 25 "data/599.cpp"

# 25 "data/599.cpp"
using namespace std;

inline long long read()
{
 long long f=1,sum=0;
 char c=getchar();
 while (!isdigit(c)){if (c=='-') f=-1;c=getchar();}
 while (isdigit(c)){sum=sum*10+c-'0';c=getchar();}
 return sum*f;
}
const int MAXN=100010;
char s[MAXN];
int p[MAXN],n;
void manacher()
{
 int mx=0,id=0;
 for (int i=1;i<=n;i++)
 {
  if (i<mx)
   p[i]=min(mx-i,p[2*id-i]);
  else
   p[i]=1;
  while (s[i+p[i]]==s[i-p[i]]) p[i]++;
  if (i+p[i]>mx)
   mx=i+p[i],id=i;
 }
}
int f[MAXN*4];
void build(int root,int left,int right)
{
 if (left==right)
 {
  f[root]=left;
  return ;
 }
 int mid=(left+right)>>1;
 build(2*root,left,mid);
 build(2*root+1,mid+1,right);
 f[root]=(p[f[2*root]]>=p[f[2*root+1]])?f[2*root]:f[2*root+1];
}
int query(int root,int left,int right,int qleft,int qright)
{
 if (qleft<=left && right<=qright)
  return f[root];
 int mid=(left+right)>>1;
 if (qright<=mid)
  return query(2*root,left,mid,qleft,qright);
 else if (qleft>mid)
  return query(2*root+1,mid+1,right,qleft,qright);
 else
 {
  int ans1,ans2;
  ans1=query(2*root,left,mid,qleft,mid);
  ans2=query(2*root+1,mid+1,right,mid+1,qright);
  return (p[ans1]>=p[ans2])?ans1:ans2;
 }
}

unsigned long long po[MAXN],hsh[MAXN];
vector <pair<int,int> > ans;
unsigned long long get_hsh(int l,int len)
{
 return hsh[l+len-1]-hsh[l-1]*po[len];
}


long long PO[MAXN],HSH[MAXN];
long long get_HSH(int l,int len)
{
 return (HSH[l+len-1]-HSH[l-1]*PO[len]%1000000007 +1000000007)%1000000007;
}
int main()
{

 scanf("%s",s+1);
 n=strlen(s+1);
 s[n+1]='$';
 po[0]=1;
 for (int i=1;i<=n;i++)
  po[i]=po[i-1]*2333;
 PO[0]=1;
 for (int i=1;i<=n;i++)
  PO[i]=PO[i-1]*233,PO[i]%=1000000007;
 manacher();
 build(1,1,n);
 for (int i=1;i<=n;i++)
  hsh[i]=hsh[i-1]*2333 +s[i]-'a'+1;
 for (int i=1;i<=n;i++)
  HSH[i]=HSH[i-1]*233%1000000007 +s[i]-'a'+1,HSH[i]%=1000000007;
 int pos=query(1,1,n,1,n);
 int anslen=p[pos]*2-1;
 ans.push_back(make_pair(pos-p[pos]+1,anslen));
 int l1=1;
 unsigned long long hsh2=0;
 long long HSH2=0;
 for (int i=n;(n-i+1)*2<n;i--)
 {
  int l2=i,r2=n,len=r2-l2+1;
  hsh2=hsh2*2333 +s[i]-'a'+1;
  HSH2=(HSH2*233%1000000007 +s[i]-'a'+1)%1000000007;
  while ((get_hsh(l1,len)!=hsh2 || get_HSH(l1,len)!=HSH2) && l1<=n) l1++;
  int ed=l1+len-1;
  if (ed>=i) break;
  int l=1,r=(i-ed)/2,mid,anss=0,npos;
  while (l<=r)
  {
   mid=(l+r)>>1;
   if (i-mid>=ed+mid && p[(pos=query(1,1,n,ed+mid,i-mid))]>=mid)
    anss=mid,l=mid+1,npos=pos;
   else
    r=mid-1;
  }


  if (anslen<len*2+anss*2-1)
  {
   ans.clear();
   ans.push_back(make_pair(l1,len));
   ans.push_back(make_pair(npos-anss+1,anss*2-1));
   ans.push_back(make_pair(i,len));
   anslen=len*2+anss*2-1;
  }
 }
 printf("%d\n",(int)ans.size());
 for (int i=0;i<(int)ans.size();i++)
  printf("%d %d\n",ans[i].first,ans[i].second);
 return 0;
}

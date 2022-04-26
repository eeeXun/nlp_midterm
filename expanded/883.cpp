
template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
max_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);

template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 8 "data/883.cpp" 2

# 8 "data/883.cpp"
using namespace std;

const int MAXN=100005;
const unsigned long long seed=13331;
char a[MAXN];
int n;
unsigned long long ex[MAXN],hash1[MAXN],hash2[MAXN];
int ans=0;
int k=0,res[5][2];
int ll[MAXN];
int fst[MAXN];

inline bool chk(int p,int l)
{
 return hash1[p]-hash1[p-l-1]*ex[l+1]==hash2[p]-hash2[p+l+1]*ex[l+1];
}
inline bool chk2(int p,int l)
{
 return hash1[p+l-1]-hash1[p-1]*ex[l]==hash2[n-l+1];
}

int main()
{
 scanf("%s",a+1);
 n=strlen(a+1);
 ex[0]=1;
 for(int i=1;i<=n;i++) ex[i]=ex[i-1]*seed;
 for(int i=1;i<=n;i++) hash1[i]=hash1[i-1]*seed+a[i];
 for(int i=n;i>=1;i--) hash2[i]=hash2[i+1]*seed+a[i];
 for(int i=1;i<=n;i++)
 {
  int l=0,r=n-i+1;
  while(l<r)
  {
   int mid=(l+r+1)>>1;
   if(chk2(i,mid)) l=mid;
   else r=mid-1;
  }
  ll[i]=l;
 }
 memset(fst,1,sizeof(fst));
 for(int i=1;i<=n;i++)
 {
  if(fst[n+1-ll[i]]>i)
  fst[n+1-ll[i]]=i;
 }
 for(int i=1;i<=n;i++)
 {
  if(fst[i]<fst[i+1])
  fst[i+1]=fst[i];
 }
 for(int i=1;i<=n;i++)
 {
  int l=0,r=min(n-i,i-1);
  while(l<r)
  {
   int mid=(l+r+1)>>1;
   if(chk(i,mid)) l=mid;
   else r=mid-1;
  }
  int t=l;
  l=0,r=n-(i+t);
  while(l<r)
  {
   int mid=(l+r+1)>>1;
   if(fst[n-mid+1]+mid-1<i-t) l=mid;
   else r=mid-1;
  }
  if(l*2+t*2+1>ans)
  {
   ans=l*2+t*2+1;
   if(l==0)
   {
    k=1;
    res[1][0]=i-t,res[1][1]=2*t+1;
   }
   else
   {
    k=3;
    res[1][0]=fst[n-l+1];res[1][1]=l;
    res[2][0]=i-t;res[2][1]=2*t+1;
    res[3][0]=n-l+1;res[3][1]=l;
   }
  }
 }
 cout<<k<<endl;
 for(int i=1;i<=k;i++)
 cout<<res[i][0]<<' '<<res[i][1]<<endl;

 return 0;
}

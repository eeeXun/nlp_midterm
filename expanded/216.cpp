    = typename iterator_traits<_InputIterator>::value_type,
    typename _Compare = less<_ValT>,
    typename _Container = vector<_ValT>,
    typename = _RequireInputIter<_InputIterator>,
    typename = _RequireNotAllocator<_Compare>,
    typename = _RequireNotAllocator<_Container>>
    priority_queue(_InputIterator, _InputIterator, _Compare = _Compare(),
     _Container = _Container())
    -> priority_queue<_ValT, _Container, _Compare>;

  template<typename _Compare, typename _Container, typename _Allocator,
    typename = _RequireNotAllocator<_Compare>,
    typename = _RequireNotAllocator<_Container>,
    typename = _RequireAllocator<_Allocator>>
    priority_queue(_Compare, _Container, _Allocator)
    -> priority_queue<typename _Container::value_type, _Container, _Compare>;





  template<typename _Tp, typename _Sequence, typename _Compare>
    inline


    typename enable_if<__and_<__is_swappable<_Sequence>,
         __is_swappable<_Compare>>::value>::type



    swap(priority_queue<_Tp, _Sequence, _Compare>& __x,
  priority_queue<_Tp, _Sequence, _Compare>& __y)
    noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y); }

  template<typename _Tp, typename _Sequence, typename _Compare,
    typename _Alloc>
    struct uses_allocator<priority_queue<_Tp, _Sequence, _Compare>, _Alloc>
    : public uses_allocator<_Sequence, _Alloc>::type { };



}
# 65 "/usr/include/c++/11.2.0/queue" 2 3
# 5 "data/216.cpp" 2


# 6 "data/216.cpp"
using namespace std;

long long mod=1000000007;
long long p=163;

int maxPal(const string &pal, int k){
 int left=k-1,right=k+1;
 int count=0;
 while(left>=0 && right<=pal.length()-1 && pal[left]==pal[right]){
  count++;
  left--;
  right++;
 }
 return count;
}

long long calcHash(const vector<long long> &h,const vector<long long> &pow,int l,int r){
 if (r==pow.size()-1)
  return h[l];
 else{

  return ((h[l]-h[r+1]*pow[r-l+1])%mod+mod)%mod;
 }
}

int main(){
 string input;
 cin>>input;
 int n=input.length();
 vector<int> maxL(n,0);
 vector<long long> hash(n,0);
 vector<long long> hashR(n,0);
 vector<long long> pow(n,0);
 for(int x=0; x<n; x++){
  if (x==0){
   hash[n-1]=input[n-1];
   hashR[n-1]=input[0];
   pow[x]=1;
  }else{
   pow[x]=(pow[x-1]*p)%mod;
   hash[n-1-x]=(input[n-1-x]+hash[n-x]*p)%mod;
   hashR[n-1-x]=(input[x]+hashR[n-x]*p)%mod;
  }
 }
 for (int x=0; x<n; x++){

 }


 for (int x=0; x<n; x++){
  int low=0;
  int high=min(x,n-1-x);
  int mid=(low+high)/2;
  while (low<high){
   if (calcHash(hash,pow,x-mid,x+mid)==calcHash(hashR,pow,n-1-x-mid,n-1-x+mid)){
    low=mid+1;
   }
   else{
    high=mid;
   }
   mid=(low+high)/2;
  }
  if (calcHash(hash,pow,x-mid,x+mid)!=calcHash(hashR,pow,n-1-x-mid,n-1-x+mid)){
   mid--;
  }
  maxL[x]=mid;
 }
 vector<int> firstPre(n,n);
 vector<int> firstPreR(n,n);
 int i=0;
 int maxPre;
 for (int x=0; x<n; x++){
  while (true){
   if (i+x>=n)
    break;
   if (calcHash(hashR,pow,0,x) == calcHash(hash,pow,i,i+x)){
    firstPre[x]=i;
    firstPreR[x]=i+x;
    break;
   }
   i++;
  }
  if (i+x>=n){
   maxPre=x;
   break;
  }
 }

 for(int x=0; x<n; x++){

 }

 int curBest=0;
 int pl=0;
 int pi=0;
 int mi=0;
 for (int x=0; x<n; x++){
  int searchIndex=x-maxL[x]-1;
  int append=0;
  int preInd=0;
  if (searchIndex>=firstPreR[0] && n-1-x-maxL[x]-1>=0){
   int low=0;
   int high=min(maxPre,n-1-x-maxL[x]-1);
   int mid=(low+high)/2;
   while(low<high){
    if(searchIndex<firstPreR[mid]){
     high=mid-1;
    }
    else{
     low=mid+1;
    }
    mid=(low+high)/2;
   }
   if (searchIndex<firstPreR[mid])
    mid--;
   append=mid+1;
   preInd=firstPreR[mid]-mid;
  }
  int nextLength=2*append+1+2*maxL[x];
  if (nextLength>curBest){
   curBest=nextLength;
   pl=append;
   pi=preInd;
   mi=x;
  }
 }


 if (pl==0){
  cout<<1<<endl;
  cout<<mi-maxL[mi]+1<<" "<<2*maxL[mi]+1<<endl;
 }
 else{
  cout<<3<<endl;
  cout<<pi+1<<" "<<pl<<endl;
  cout<<mi-maxL[mi]+1<<" "<<2*maxL[mi]+1<<endl;
  cout<<n-pl+1<<" "<<pl<<endl;
 }
# 189 "data/216.cpp"
}

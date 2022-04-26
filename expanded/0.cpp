  template<typename Key,
    typename Mapped,
    class Eq_Fn = typename detail::default_eq_fn<Key>::type,
    class Update_Policy = detail::default_update_policy::type,
    class _Alloc = std::allocator<char> >
  class list_update : public detail::container_base_dispatch<Key, Mapped, _Alloc, list_update_tag, typename __gnu_cxx::typelist::create2<Eq_Fn, Update_Policy>::type>::type
  {
  private:
    typedef typename detail::container_base_dispatch<Key, Mapped, _Alloc, list_update_tag, typename __gnu_cxx::typelist::create2<Eq_Fn, Update_Policy>::type>::type base_type;

  public:
    typedef list_update_tag container_category;
    typedef Eq_Fn eq_fn;
    typedef Update_Policy update_policy;

    list_update() { }




    template<typename It>
    list_update(It first, It last)
    { base_type::copy_from_range(first, last); }

    list_update(const list_update& other)
    : base_type((const base_type&)other) { }

    virtual
    ~list_update() { }

    list_update&
    operator=(const list_update& other)
    {
      if (this !=& other)
 {
   list_update tmp(other);
   swap(tmp);
 }
      return *this;
    }

    void
    swap(list_update& other)
    { base_type::swap(other); }
  };




}
# 4 "data/0.cpp" 2
# 36 "data/0.cpp"

# 36 "data/0.cpp"
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    std::cerr << name << " : " << arg1 << "\n";
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');std::cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}

template<typename T, typename U> static inline void amin(T &x, U y)
{
    if (y < x)
        x = y;
}
template<typename T, typename U> static inline void amax(T &x, U y)
{
    if (x < y)
        x = y;
}

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
# 78 "data/0.cpp"
std::pair<int, int> operator+(std::pair<int, int> a, std::pair<int, int> b)
{
 return {a.first+b.first,a.second+b.second};
}
std::pair<long long, long long> operator+(std::pair<long long, long long> a, std::pair<long long, long long> b)
{
 return {a.first+b.first,a.second+b.second};
}
std::ostream& operator<<(std::ostream& out,std::pair<int, int> a)
{
 out<<a.first<<" "<<a.second<<"\n";
 return out;
}
std::ostream& operator<<(std::ostream& out,std::pair<long long, long long> a)
{
 out<<a.first<<" "<<a.second<<"\n";
 return out;
}
std::istream& operator>>(std::istream& in,std::pair<int, int> &a)
{
    in>>a.first>>a.second;
    return in;
}
std::istream& operator>>(std::istream& in,std::pair<long long, long long> &a)
{
    in>>a.first>>a.second;
    return in;
}

using namespace std;
using namespace __gnu_pbds;
const int MAXN=100005;
const int MAX_LOGN=18;
class SparseTable{
 int dp[MAX_LOGN][MAXN];
public:
 void build(vector<int> b)
 {
  int n=(int)b.size();
  for (int i = 0; i < n; ++i)
  {
   dp[0][i]=b[i];
  }
  int t=n;
  int log=0;
  while(t>1)
   log++,t>>=1;
  for (int i = 1; i <=log; ++i)
  {
   for (int j = 0; j < n; ++j)
   {
    dp[i][j]=dp[i-1][j];
    if(j+(1<<(i-1))<n)
    {
     amax(dp[i][j],dp[i-1][j+(1<<(i-1))]);
    }
   }
  }
 }
 int query(int l,int r)
 {
  if(l>r)return 0;
  int len=(r-l+1);
  int log=0;
  while(len>1)
   log++,len>>=1;
  return max(dp[log][l],dp[log][r-(1<<log)+1]);
 }
};
long long modInverse(long long a, long long m)
{
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1)
      return 0;

    while (a > 1)
    {

        long long q = a / m;
        long long t = m;



        m = a % m, a = t;
        t = y;


        y = x - q * y;
        x = t;
    }


    if (x < 0)
       x += m0;

    return x;
}
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
void meow()
{
 string x;
 cin>>x;
 long long p1=937;
 long long p2=991;
 long long pp1[(int)x.length()]={1};
 long long pp2[(int)x.length()]={1};
 long long mp1[(int)x.length()]={1};
 long long mp2[(int)x.length()]={1};
 for (int i = 1; i < (int)x.length(); ++i)
 {
  pp1[i]=(pp1[i-1]*p1)%1000000007;
  pp2[i]=(pp2[i-1]*p2)%1000000007;
  mp1[i]=modInverse(pp1[i],1000000007);
  mp2[i]=modInverse(pp2[i],1000000007);
 }
 long long prefh1[(int)x.length()]={x[0]};
 long long prefh2[(int)x.length()]={x[0]};
 long long suffh1[(int)x.length()];
 long long suffh2[(int)x.length()];
 suffh1[(int)x.length()-1]=x[(int)x.length()-1];
 suffh2[(int)x.length()-1]=x[(int)x.length()-1];
 for(int i = 1; (int)x.length()-1>=1?((int)x.length()-1>=i):((int)x.length()-1<=i); i+=(-1+2*((int)x.length()-1>=1)))
 {
  prefh1[i]=(prefh1[i-1] + pp1[i]*x[i])%1000000007;
  prefh2[i]=(prefh2[i-1] + pp2[i]*x[i])%1000000007;
 }
 for(int i = (int)x.length()-2; 0>=(int)x.length()-2?(0>=i):(0<=i); i+=(-1+2*(0>=(int)x.length()-2)))
 {
  suffh1[i]=(suffh1[i+1] + pp1[(int)x.length()-i-1]*x[i])%1000000007;
  suffh2[i]=(suffh2[i+1] + pp2[(int)x.length()-i-1]*x[i])%1000000007;
 }




 int maxp[(int)x.length()];
 for (int i = 0; i < (int)x.length(); ++i)
 {
  int low=0;
  int high=min(i,(int)x.length()-i-1);
  while(high-low>0)
  {
   int mid=(high+low+1)/2;
   long long fh1,fh2,bh1,bh2;

   fh1=(prefh1[i+mid])%1000000007;
   fh2=(prefh2[i+mid])%1000000007;
   if(i-mid-1>=0)
   {
    fh1=(fh1-prefh1[i-mid-1]+1000000007)%1000000007;
    fh2=(fh2-prefh2[i-mid-1]+1000000007)%1000000007;
   }
   bh1=(suffh1[i-mid])%1000000007;
   bh2=(suffh2[i-mid])%1000000007;
   if(i+mid+1<(int)x.length())
   {
    bh1=(bh1-suffh1[i+mid+1]+1000000007)%1000000007;
    bh2=(bh2-suffh2[i+mid+1]+1000000007)%1000000007;
   }
   fh1=(fh1*mp1[i-mid])%1000000007;
   fh2=(fh2*mp2[i-mid])%1000000007;

   bh1=(bh1*mp1[(int)x.length()-1-(i+mid)])%1000000007;
   bh2=(bh2*mp2[(int)x.length()-1-(i+mid)])%1000000007;
   int flag=(fh1==bh1)&&(fh2==bh2);
   if(flag)
    low=mid;
   else high=mid-1;
  }
  maxp[i]=low;
 }

 string y="";
 for (int i = 0; i < (int)x.length(); ++i)
 {
  y+=x[(int)x.length()-1-i];
 }
 vector<int> z=z_function(y + '$' + x);


 vector<int> zz((int)x.length(),0);
 for (int i = (int)x.length()+1; i < 2*(int)x.length()+1; ++i)
 {
  amax(zz[i+z[i]-(int)x.length()-2],z[i]);
 }
 for(int i = (int)x.length()-2; 0>=(int)x.length()-2?(0>=i):(0<=i); i+=(-1+2*(0>=(int)x.length()-2)))
 {
  amax(zz[i],zz[i+1]-1);
 }

 int prefs,preflen,mids,midlen;
 int maxl=0;
 SparseTable st;
 st.build(zz);
 int leftmostocc[(int)x.length()+1];
 for (int xxx=0;xxx<(int)x.length()+1;++xxx) leftmostocc[xxx]=1000000007;
 for (int i = 0; i < (int)x.length(); ++i)
 {
  amin(leftmostocc[zz[i]],i);
 }

 for (int i = 0; i < (int)x.length(); ++i)
 {
  int midl=maxp[i]*2 + 1;
  int prefl=0;
  if(i-maxp[i]>0)
   prefl=min(i-maxp[i],st.query(0,i-maxp[i]-1));
  amin(prefl,(int)x.length()-(i+maxp[i])-1);
  amax(maxl,2*prefl+midl);

  if(maxl==(2*prefl+midl))
  {
   prefs=leftmostocc[prefl]-prefl+2;
   preflen=prefl;
   mids=i-maxp[i]+1;
   midlen=midl;
  }
 }

 if(preflen==0)
 {
  cout<<1<<"\n";
  cout<<mids<<" "<<midlen;
 }else{
  cout<<3<<"\n";
  cout<<prefs<<" "<<preflen<<"\n";
  cout<<mids<<" "<<midlen<<"\n";
  cout<<((int)x.length()-preflen+1)<<" "<<preflen<<"\n";
 }
}
int main()
{
    std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);;
    int testcases=1;

    for(int i=0;i<testcases;++i)
    {
     meow();
    }
    return 0;
}

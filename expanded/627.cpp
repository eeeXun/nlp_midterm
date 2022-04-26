      return *this;
    }

    void
    swap(trie& other)
    { base_type::swap(other); }
  };
# 810 "/usr/include/c++/11.2.0/ext/pb_ds/assoc_container.hpp" 3
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
# 4 "data/627.cpp" 2


# 5 "data/627.cpp"
using namespace std;
using namespace __gnu_pbds;


#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")



typedef long long ll;
typedef long double ld;
typedef long double f80;
typedef pair<long long, long long> pii;
typedef gp_hash_table<long long, long long> umap;
typedef tree<long long, null_type, less<long long>, rb_tree_tag,
        tree_order_statistics_node_update> oset;
typedef pair<pii, long long> piii;
typedef vector<long long> vi;
typedef vector<pii> vii;
# 85 "data/627.cpp"
mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
inline bool equals(double a, double b) { return fabs(a - b) < 1e-9; }
ll modpow(ll b, ll e, ll mod=1000000007) {
    ll ans=1; for(;e;b=b*b%mod,e/=2) if(e&1) ans=ans*b%mod; return ans; }




vector<ll> findd1(string s)
{
    ll n=s.length();
    vector<long long> d1(n);
    for (long long i = 0, l = 0, r = -1; i < n; i++) {
        long long k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return d1;
}
ll suf[100005];
ll n;
ll find(ll l,ll r)
{
    ll ans=0;
    ll z=n-1-r;
    ll lx=1,rx=z;
    while(lx<=rx)
    {
        ll m=(lx+rx)/2;
        if(suf[m]<l)
        {
            ans=m;
            lx=m+1;
        }
        else
        {
            rx=m-1;
        }
    }
    return ans;
}

void solve()
{
    string s;
    cin>>s;
    vector<ll>d1=findd1(s);
    n = (long long)s.length();
    for (long long i = 0, _n = (n+1); i < _n; i++)
    {
        suf[i]=1000000000000000000ll;
    }
    string sx=s;
    reverse(sx.begin(), sx.end());
    sx=sx+'#'+s;

    vector<long long> pi(2*n+1);
    for (long long i = 1; i < 2*n+1; i++) {
        long long j = pi[i-1];
        while (j > 0 && sx[i] != sx[j])
            j = pi[j-1];
        if (sx[i] == sx[j])
            j++;
        pi[i] = j;

        if(i>n)
        {
            suf[j]=min(suf[j],i-n-1);
        }
    }




    set<pair<ll,ll>>an,an1;
    ll cur=0;
    for(long long i=0;i<n;i++)
    {
        ll x=d1[i];

        ll z=x-1;
        ll l=i-z;
        ll r=i+z;
        ll ans=find(l,r);


        if(r-l+1+ans*2>cur)
        {
            cur=r-l+1+ans*2;
            an.clear();
            if(ans!=0)
            {
                an.insert(make_pair(suf[ans]+2-ans,suf[ans]+1));
                an.insert(make_pair(n+1-ans,n));
            }
            an.insert(make_pair(l+1,r+1));
        }
    }
    pair<ll,ll> last={-2,-2};
    cout<<an.size()<<'\n';
    for(auto z:an)
    {
        cout<<z.first<<' '<<z.second-z.first+1<<'\n';
    }



}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0), cout.precision(15); cout<<fixed;





    long long t=1;

    for (long long i = (1), _b = (t); i <= _b; i++)
    {

        solve();
    }
    ;
}

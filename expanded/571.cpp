

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
# 19 "data/571.cpp" 2
# 54 "data/571.cpp"

# 54 "data/571.cpp"
using namespace std;
using namespace __gnu_pbds;
using namespace std::chrono;
typedef tree<long long,null_type,less<long long>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;

const long double pi=acos(-1.0);


auto Compare = [](pair<long long,long long> &a, pair<long long,long long> &b) { return a.first>b.first; };

bool comp(pair<long long,long long> &a, pair<long long,long long> &b) {
    if(a.first==b.first) return a.second>b.second;
    return a.first<b.first;
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {

        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

long long binpow(long long a, long long b, long long mod) {
    if(a==0) return 0;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a%mod;
        a = a * a%mod;
        b >>= 1;
    }
    return res;
}
long long invpow(long long a, long long mod)
{
    return binpow(a,mod-2,mod);
}

vector<long long> odd_pal;

void manacher(string s)
{
    long long n = s.size();
    odd_pal.resize(n);
    for (long long i = 0, l = 0, r = -1; i < n; i++) {
        long long k = (i > r) ? 1 : min(odd_pal[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        odd_pal[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
}

vector<long long> calc_rpos(string s)
{
    long long n = s.size();
    vector<long long> lpos(n,0);
    long long hash[n];
    long long pr = 31;
    long long p_pow[n];
    p_pow[0] = 1;
    for(long long i=1;i<n;++i) p_pow[i]=(p_pow[i-1]*pr)%1000000007;
    hash[0] = (s[0]-'a'+1);
    for(long long i=1;i<n;++i)
    {
        hash[i] = (hash[i-1]+(s[i]-'a'+1)*p_pow[i]%1000000007)%1000000007;
    }
    long long cur_hash = 0;
    for(long long i=n-1;i>=0;--i)
    {
        if(i==n-1) lpos[n-1-i] = 0;
        else lpos[n-1-i] = lpos[n-i-2];
        cur_hash = (cur_hash+(s[i]-'a'+1)*p_pow[n-1-i]%1000000007)%1000000007;

        while(lpos[n-1-i]<i+1&&cur_hash*p_pow[i]%1000000007!=(hash[lpos[n-1-i]+n-i-1]+1000000007 -(lpos[n-1-i]?hash[lpos[n-1-i]-1]:0))*p_pow[i-lpos[n-1-i]]%1000000007)
        {
            lpos[n-1-i]++;
        }
    }


    vector<long long> rpos(n);
    for(long long i=0;i<n;++i) rpos[i]=lpos[i]+i;
    return rpos;
}

void DJ()
{
    string s;
    cin>>s;
    manacher(s);
    long long l=0, m=0, r=0, l_ind = -1, m_ind = -1, r_ind = -1;
    vector<long long> rpos = calc_rpos(s);
    for(long long i=0;i<s.size();++i)
    {
        long long left = 0, right = s.size() - odd_pal[i] - i - 1;
        long long ans = -1;
        while(left<=right)
        {
            long long mid = (left+right)/2;
            if(rpos[mid]>=i-odd_pal[i]+1)
            {
                right = mid-1;
            }
            else
            {
                left = mid + 1;
                ans = mid;
            }
        }
        if(ans==-1)
        {
            if(l+m+r<2*odd_pal[i]-1)
            {
                m_ind = i - odd_pal[i] + 1;
                m = 2*odd_pal[i] - 1;
                l_ind = -1;
                r_ind = -1;
                l = 0;
                r = 0;
            }
        }
        else
        {
            if(l+m+r<2*odd_pal[i]-1+2*ans+2)
            {
                l_ind = rpos[ans] - ans;
                r_ind = s.size() - ans - 1;
                m_ind = i-odd_pal[i]+1;
                l = r = ans+1;
                m = 2*odd_pal[i] - 1;
            }
        }
    }
    if(l_ind==-1)
    {
        cout<<1<<'\n';
        cout<<m_ind+1<<' '<<m<<'\n';
    }
    else
    {
        cout<<3<<'\n';
        cout<<l_ind+1<<' '<<l<<'\n';
        cout<<m_ind+1<<' '<<m<<'\n';
        cout<<r_ind+1<<' '<<r<<'\n';
    }
}

signed main()
{

     auto start = high_resolution_clock::now();
     freopen("input.txt", "r", 
# 218 "data/571.cpp" 3 4
                              stdin
# 218 "data/571.cpp"
                                   );

     freopen("output.txt", "w", 
# 220 "data/571.cpp" 3 4
                               stdout
# 220 "data/571.cpp"
                                     );


    ios_base::sync_with_stdio(false);
    cin.tie(
# 224 "data/571.cpp" 3 4
           __null
# 224 "data/571.cpp"
               );
    cout.tie(
# 225 "data/571.cpp" 3 4
            __null
# 225 "data/571.cpp"
                );

    long long t=1;






    while(t--) DJ();


    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\n" << "Runtime: "
         << duration.count()/1000000.0 << " seconds" << "\n";


    return 0;
}

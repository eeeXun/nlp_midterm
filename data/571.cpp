/*//DJ aka Dvij Joshi
 
            **************            *********************
            ****************          *********************
            ******      ******                   *****
            ******        ******                 *****
            ******        ******                 *****
            ******        ******                 *****
            ******        ******                 *****
            ******        ******       *****     *****
            ******       ******        *****     *****
            ******      ******         *****     *****
            ****************           ******* *******
            **************              *************
*/
//HEADERS---------------------------------
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<chrono>
//MACROS---------------------------------
#define pb push_back
// #define mp make_pair
#define eb emplace_back
#define ff first
#define ss second
#define len(v) ((int)v.size())
#define all(v) v.begin(), v.end()
#define omset tree<pair<int, int>,null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
#define hell 1000000007
#define M 998244353 
#define vi  vector<int>
#define vii vector<pair<int,int>>
#define vll vector<long long>
#define vc  vector<char>
#define vs  vector<string>
#define mii map<int,int>
#define mll map<long long,long long>
#define mci map<char,int>
#define pii pair<int,int>
#define msi map<string,int>
#define loop(i,a,b) for(i=a;i<b;++i)
#define rloop(i,a,b) for(i=a;i>b;--i)
#define in(i,a,n) for(i=0;i<n;++i) cin>>a[i];
#define out(i,a,n) for(i=0;i<n;++i) cout<<a[i]<<" ";
#define ll long long
#define sp(n) setprecision(n)
#define fin freopen( "input.txt", "r", stdin );
#define fout freopen( "output.txt", "w", stdout );
#define outall(a) loop(i,0,sizeof(a)/sizeof(a[0])) cout<<a[i]<<" "; cout<<endl
#define endl "\n"
#define EPS 2.718281828
#define int long long
using namespace std;
using namespace __gnu_pbds;
using namespace std::chrono;
typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;
//GLOBALS--------------------------------------
const long double pi=acos(-1.0);

//FUNCTIONS------------------------------------
auto Compare = [](pair<int,int> &a, pair<int,int> &b) { return a.first>b.first; };

bool comp(pii &a, pii &b) { 
    if(a.first==b.first) return a.second>b.second;
    return a.first<b.first;
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
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

long long binpow(long long a, long long b, int mod) {
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
long long invpow(long long a, int mod)
{
    return binpow(a,mod-2,mod);
}

vector<int> odd_pal;

void manacher(string s)
{
    int n = s.size();
    odd_pal.resize(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(odd_pal[l + r - i], r - i + 1);
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

vector<int> calc_rpos(string s)
{
    int n = s.size();
    vector<int> lpos(n,0);
    int hash[n];
    int pr = 31;
    int p_pow[n];
    p_pow[0] = 1;
    for(int i=1;i<n;++i) p_pow[i]=(p_pow[i-1]*pr)%hell;
    hash[0] = (s[0]-'a'+1);
    for(int i=1;i<n;++i)
    {
        hash[i] = (hash[i-1]+(s[i]-'a'+1)*p_pow[i]%hell)%hell;
    }
    int cur_hash = 0;
    for(int i=n-1;i>=0;--i)
    {
        if(i==n-1) lpos[n-1-i] = 0;
        else lpos[n-1-i] = lpos[n-i-2];
        cur_hash = (cur_hash+(s[i]-'a'+1)*p_pow[n-1-i]%hell)%hell;
        // len = n-i;
        while(lpos[n-1-i]<i+1&&cur_hash*p_pow[i]%hell!=(hash[lpos[n-1-i]+n-i-1]+hell-(lpos[n-1-i]?hash[lpos[n-1-i]-1]:0))*p_pow[i-lpos[n-1-i]]%hell)
        {
            lpos[n-1-i]++;
        }
    }
    // for(int x:lpos) cout<<x<<' ';
    //     cout<<endl;
    vector<int> rpos(n);
    for(int i=0;i<n;++i) rpos[i]=lpos[i]+i;
    return rpos;
}

void DJ()
{
    string s;
    cin>>s;
    manacher(s);
    int l=0, m=0, r=0, l_ind = -1, m_ind = -1, r_ind = -1;
    vector<int> rpos = calc_rpos(s);
    for(int i=0;i<s.size();++i)
    {
        int left = 0, right = s.size() - odd_pal[i] - i - 1;
        int ans = -1;
        while(left<=right)
        {
            int mid = (left+right)/2;
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
//MAIN FUNCTION--------------------------------
signed main()
{
    #ifndef ONLINE_JUDGE
     auto start = high_resolution_clock::now();
     freopen("input.txt", "r", stdin);

     freopen("output.txt", "w", stdout);
    #endif 

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t=1;
    // fact[0]=1;
    // for(int i=1;i<=200004;++i)
    // {
    //     fact[i]=(fact[i-1]*i)%M;
    // }
    // cin>>t;
    while(t--) DJ();

    #ifndef ONLINE_JUDGE
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);
  
    cout << endl << "Runtime: "
         << duration.count()/1000000.0 << " seconds" << endl;
    #endif

    return 0;
}
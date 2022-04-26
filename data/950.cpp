#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

#include<bits/stdc++.h>
using namespace std;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int rnd(int x, int y) {return (rng() % (y-x +1)) + x;};

#define ll long long
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define ull unsigned long long
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define ff first
#define ss second
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#define nl "\n"
#define sz(a) (int)(a).size()
#define all(a) (a).begin(),(a).end()
#define fl(a,x) memset(a,x,sizeof(a));
#define pt(a,x) cout << get<x>(a) << " " ;
#define mt make_tuple
#define vec vector
#define mxe max_element
#define mne max_element
#define present(c, x) (c.find(x) != c.end())
#define printall(a) for(auto i : a) cout << i << " " ; cout << nl ;

#define int long long

typedef vector<int> vii;
typedef vector<ll> vll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
typedef vector<vii> vvi;
typedef vector<vll> vvl;

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const int mod = (int) 1e9 + 7 ;
const int MOD = (int) 998244353 ;
const ll INF = (ll) 1e18;

inline int add(int a, int b) {return (a + b >= mod ? a + b - mod : a + b);}
inline int mul(int a, int b) {return (ll) a * b % mod ; }

void count_sort(vector<pii> &b, int bits) { // (optional)
    //this is just 3 times faster than stl sort for N=10^6
    int mask = (1 << bits) - 1;
    rep(it,0,2) {
        int move = it * bits;
        vii q(1 << bits), w(sz(q) + 1);
        rep(i,0,sz(b))
            q[(b[i].first >> move) & mask]++;
        partial_sum(q.begin(), q.end(), w.begin() + 1);
        vector<pii> res(b.size());
        rep(i,0,sz(b))
            res[w[(b[i].first >> move) & mask]++] = b[i];
        swap(b, res);
    }
}
struct SuffixArray {
    vii a;
    string s;
    SuffixArray(const string& _s) : s(_s + '\0') {
        int N = sz(s);
        vector<pii> b(N);
        a.resize(N);
        rep(i,0,N) {
            b[i].first = s[i];
            b[i].second = i;
        }

        int q = 8;
        while ((1 << q) < N) q++;
        for (int moc = 0;; moc++) {
            count_sort(b, q); // sort(all(b)) can be used as well
            a[b[0].second] = 0;
            rep(i,1,N)
                a[b[i].second] = a[b[i - 1].second] +
                    (b[i - 1].first != b[i].first);

            if ((1 << moc) >= N) break;
            rep(i,0,N) {
                b[i].first = (ll)a[i] << q;
                if (i + (1 << moc) < N)
                    b[i].first += a[i + (1 << moc)];
                b[i].second = i;
            }
        }
        rep(i,0,sz(a)) a[i] = b[i].second;
    }
    vii lcp() {
        // longest common prefixes: res[i] = lcp(a[i], a[i-1])
        int n = sz(a), h = 0;
        vii inv(n), res(n);
        rep(i,0,n) inv[a[i]] = i;
        rep(i,0,n) if (inv[i] > 0) {
            int p0 = a[inv[i] - 1];
            while (s[i + h] == s[p0 + h]) h++;
            res[inv[i]] = h;
            if(h > 0) h--;
        }
        return res;
    }
};

template <typename T> 
struct SparseTable {
    int n, type, K; 
    vector<vector<T>> st ;
    vector<int> lg ;  
    SparseTable(int _n, vector<T> &a) {
        n = _n ;
        K = 25 ;  
        st.resize(n+1, vector<T>(K+1)) ; 
        lg.resize(n+1) ;
        for(int i = 0 ; i < n ; ++i) st[i][0] = a[i] ; 
        for(int j = 1 ; j <= K ; ++j) {
            for(int i = 0 ; i + (1<<j) <= n ; ++i) {
                st[i][j] = merge(st[i][j-1], st[i+(1<<(j-1))][j-1]) ; 
            }
        }
        lg[0] = 1 ;
        for(int i = 2 ; i <= n ; ++i) lg[i] = lg[i/2] + 1 ; 
    }
    inline T merge(T a, T b) {return min(a,b) ;}
    T query(int l, int r) {
        int j = lg[r-l+1] ; 
        return merge(st[l][j], st[r-(1<<j)+1][j]) ;  
    }
};

void solve() {

    string s; cin >> s; 
    string t = s; 
    reverse(all(t)) ; 
    s += "$" + t ;
    SuffixArray S(s) ;
    vii a = S.lcp() ;
    SparseTable<int> st(sz(a), a); 

    vii pos(sz(S.a));
    for(int i = 0 ; i < sz(S.a) ; ++i) {
        pos[S.a[i]] = i ;
    }

    int n = sz(t) ;

    vii lpos(n + 1, INF), rpos(n + 1, INF), rpos2(n+1, INF);
    int idx = 0;
    while(idx < sz(t) && s[idx] != t[0]) ++idx;
    lpos[1] = idx;
    rpos[1] = idx;
    rpos2[1] = n-1;
    lpos[0] = rpos[0] = rpos2[0] = -1 ;
    for(int  len = 2 ; idx < n && len <= sz(t) ; ++len) {
        int l = pos[idx] ;
        int r = pos[n+1] ;
        if(l > r) swap(l, r) ;
        int lcp = st.query(l+1, r) ;
        if(lcp >= len && 2 * lcp <= n-idx) {
            lpos[len] = idx ;
            rpos[len] = lpos[len] + len - 1;
            rpos2[len] = n-len;
        }
        else {
            --len ;
            ++idx;
        }
    }

    int mx = 0, m_len, m_pos;
    vpi ans(2);
    for(int i = 0 ; i < n ; ++i) {
        int l = pos[i] ;
        int r = pos[2 * n - i] ;
        if(l > r) swap(l, r) ;
        int lcp = st.query(l+1, r) ;
        if(2 * lcp - 1 > mx) {
            mx = 2 * lcp - 1;
            m_len = 2 * lcp- 1 ;
            m_pos = i-lcp + 1;
            ans[0].ss = 0;
        }
        int t_pos = i - lcp + 1;
        int lo = 1, hi = n ;
        while(lo <= hi) {
            int mid = lo + hi >> 1;
            if(rpos[mid] < t_pos && rpos2[mid] >= t_pos + 2 * lcp - 1) lo = mid + 1;
            else hi = mid - 1;
        }
        if(lo-1 > 0) {
            if(2 * lcp - 1 + 2 * (lo-1) > mx) {
                mx = 2 * lcp - 1 + 2 * (lo-1) ;
                ans[0].ff = lpos[lo-1] ;
                ans[1].ff = rpos2[lo-1] ;
                ans[0].ss = ans[1].ss = lo-1;
                m_len = 2 * lcp - 1 ;
                m_pos = t_pos;
            }
        }
    }
    if(ans[0].ss == 0) {
        cout << 1 << nl << m_pos + 1 << " " << m_len << nl ;
    }
    else {
        cout << 3 << nl ;
        cout << ans[0].ff + 1 << " " << ans[0].ss << nl ;
        cout << m_pos + 1 << " " << m_len << nl ;
        cout << ans[1].ff + 1 << " " << ans[1].ss << nl; 
    }
}

int32_t main() {
    fast;
    // int t; cin >> t ; rep(i,0,t) 
        solve() ;
    // cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}

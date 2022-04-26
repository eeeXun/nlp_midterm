    struct hash<variant<_Types...>>
    : private __detail::__variant::_Variant_hash_base<
 variant<_Types...>, std::index_sequence_for<_Types...>>,
      public __variant_hash_call_base<_Types...>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = variant<_Types...>;
    };

  template<>
    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 6 "data/222.cpp" 2

# 6 "data/222.cpp"
using namespace std;
# 37 "data/222.cpp"
typedef vector<long long> vii;
typedef vector<long long> vll;
typedef pair<long long,long long> pii;
typedef pair<long long,long long> pll;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
typedef vector<vii> vvi;
typedef vector<vll> vvl;



void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const long long mod = (long long) 1e9 + 7 ;
const long long MOD = (long long) 998244353 ;
const long long INF = (long long) 1e18;

inline long long add(long long a, long long b) {return (a + b >= mod ? a + b - mod : a + b);}
inline long long mul(long long a, long long b) {return (long long) a * b % mod ; }

void count_sort(vector<pii> &b, long long bits) {

    long long mask = (1 << bits) - 1;
    for (__typeof(2) it = (0) - ((0) > (2)); it != (2) - ((0) > (2)); it += 1 - 2 * ((0) > (2))) {
        long long move = it * bits;
        vii q(1 << bits), w((long long)(q).size() + 1);
        for (__typeof((long long)(b).size()) i = (0) - ((0) > ((long long)(b).size())); i != ((long long)(b).size()) - ((0) > ((long long)(b).size())); i += 1 - 2 * ((0) > ((long long)(b).size())))
            q[(b[i].first >> move) & mask]++;
        partial_sum(q.begin(), q.end(), w.begin() + 1);
        vector<pii> res(b.size());
        for (__typeof((long long)(b).size()) i = (0) - ((0) > ((long long)(b).size())); i != ((long long)(b).size()) - ((0) > ((long long)(b).size())); i += 1 - 2 * ((0) > ((long long)(b).size())))
            res[w[(b[i].first >> move) & mask]++] = b[i];
        swap(b, res);
    }
}
struct SuffixArray {
    vii a;
    string s;
    SuffixArray(const string& _s) : s(_s + '\0') {
        long long N = (long long)(s).size();
        vector<pii> b(N);
        a.resize(N);
        for (__typeof(N) i = (0) - ((0) > (N)); i != (N) - ((0) > (N)); i += 1 - 2 * ((0) > (N))) {
            b[i].first = s[i];
            b[i].second = i;
        }

        long long q = 8;
        while ((1 << q) < N) q++;
        for (long long moc = 0;; moc++) {
            count_sort(b, q);
            a[b[0].second] = 0;
            for (__typeof(N) i = (1) - ((1) > (N)); i != (N) - ((1) > (N)); i += 1 - 2 * ((1) > (N)))
                a[b[i].second] = a[b[i - 1].second] +
                    (b[i - 1].first != b[i].first);

            if ((1 << moc) >= N) break;
            for (__typeof(N) i = (0) - ((0) > (N)); i != (N) - ((0) > (N)); i += 1 - 2 * ((0) > (N))) {
                b[i].first = (long long)a[i] << q;
                if (i + (1 << moc) < N)
                    b[i].first += a[i + (1 << moc)];
                b[i].second = i;
            }
        }
        for (__typeof((long long)(a).size()) i = (0) - ((0) > ((long long)(a).size())); i != ((long long)(a).size()) - ((0) > ((long long)(a).size())); i += 1 - 2 * ((0) > ((long long)(a).size()))) a[i] = b[i].second;
    }
    vii lcp() {

        long long n = (long long)(a).size(), h = 0;
        vii inv(n), res(n);
        for (__typeof(n) i = (0) - ((0) > (n)); i != (n) - ((0) > (n)); i += 1 - 2 * ((0) > (n))) inv[a[i]] = i;
        for (__typeof(n) i = (0) - ((0) > (n)); i != (n) - ((0) > (n)); i += 1 - 2 * ((0) > (n))) if (inv[i] > 0) {
            long long p0 = a[inv[i] - 1];
            while (s[i + h] == s[p0 + h]) h++;
            res[inv[i]] = h;
            if(h > 0) h--;
        }
        return res;
    }
};

template <typename T>
struct SparseTable {
    long long n, type, K;
    vector<vector<T>> st ;
    vector<long long> lg ;
    SparseTable(long long _n, vector<T> &a) {
        n = _n ;
        K = 25 ;
        st.resize(n+1, vector<T>(K+1)) ;
        lg.resize(n+1) ;
        for(long long i = 0 ; i < n ; ++i) st[i][0] = a[i] ;
        for(long long j = 1 ; j <= K ; ++j) {
            for(long long i = 0 ; i + (1<<j) <= n ; ++i) {
                st[i][j] = merge(st[i][j-1], st[i+(1<<(j-1))][j-1]) ;
            }
        }
        lg[0] = 1 ;
        for(long long i = 2 ; i <= n ; ++i) lg[i] = lg[i/2] + 1 ;
    }
    inline T merge(T a, T b) {return min(a,b) ;}
    T query(long long l, long long r) {
        long long j = lg[r-l+1] ;
        return merge(st[l][j], st[r-(1<<j)+1][j]) ;
    }
};

void solve() {

    string s; cin >> s;
    string t = s;
    reverse((t).begin(),(t).end()) ;
    s += "$" + t ;
    SuffixArray S(s) ;
    vii a = S.lcp() ;
    SparseTable<long long> st((long long)(a).size(), a);

    vii pos((long long)(S.a).size());
    for(long long i = 0 ; i < (long long)(S.a).size() ; ++i) {
        pos[S.a[i]] = i ;
    }

    long long n = (long long)(t).size() ;

    vii lpos(n + 1, INF), rpos(n + 1, INF), rpos2(n+1, INF);
    long long idx = 0;
    while(idx < (long long)(t).size() && s[idx] != t[0]) ++idx;
    lpos[1] = idx;
    rpos[1] = idx;
    rpos2[1] = n-1;
    lpos[0] = rpos[0] = rpos2[0] = -1 ;
    for(long long len = 2 ; idx < n && len <= (long long)(t).size() ; ++len) {
        long long l = pos[idx] ;
        long long r = pos[n+1] ;
        if(l > r) swap(l, r) ;
        long long lcp = st.query(l+1, r) ;
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

    long long mx = 0, m_len, m_pos;
    vpi ans(2);
    for(long long i = 0 ; i < n ; ++i) {
        long long l = pos[i] ;
        long long r = pos[2 * n - i] ;
        if(l > r) swap(l, r) ;
        long long lcp = st.query(l+1, r) ;
        if(2 * lcp - 1 > mx) {
            mx = 2 * lcp - 1;
            m_len = 2 * lcp- 1 ;
            m_pos = i-lcp + 1;
            ans[0].second = 0;
        }
        long long t_pos = i - lcp + 1;
        long long lo = 1, hi = n ;
        while(lo <= hi) {
            long long mid = lo + hi >> 1;
            if(rpos[mid] < t_pos && rpos2[mid] >= t_pos + 2 * lcp - 1) lo = mid + 1;
            else hi = mid - 1;
        }
        if(lo-1 > 0) {
            if(2 * lcp - 1 + 2 * (lo-1) > mx) {
                mx = 2 * lcp - 1 + 2 * (lo-1) ;
                ans[0].first = lpos[lo-1] ;
                ans[1].first = rpos2[lo-1] ;
                ans[0].second = ans[1].second = lo-1;
                m_len = 2 * lcp - 1 ;
                m_pos = t_pos;
            }
        }
    }
    if(ans[0].second == 0) {
        cout << 1 << "\n" << m_pos + 1 << " " << m_len << "\n" ;
    }
    else {
        cout << 3 << "\n" ;
        cout << ans[0].first + 1 << " " << ans[0].second << "\n" ;
        cout << m_pos + 1 << " " << m_len << "\n" ;
        cout << ans[1].first + 1 << " " << ans[1].second << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);;

        solve() ;

    return 0;
}

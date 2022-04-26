
extern void __assert (const char *__assertion, const char *__file, int __line)
     noexcept (true) __attribute__ ((__noreturn__));


}
# 45 "/usr/include/c++/11.2.0/cassert" 2 3
# 18 "data/830.cpp" 2


# 19 "data/830.cpp"
using namespace std;
# 31 "data/830.cpp"
template<typename T> inline T abs(T a){ return ((a < 0) ? -a : a); }
template<typename T> inline T sqr(T a){ return a * a; }

typedef long long li;
typedef unsigned long long uli;
typedef long double ld;
typedef pair<li, li> pt;

const int N = 200009;
const int logN = 22;
const int sqrN = 450;
const int MOD = 1000000007;
const int INF = 1e9 + 100;
const li INF64 = 1e14;
const ld PI = 3.1415926535897932384626433832795;
const ld eps = 1e-9;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int len;
string s, ns;
int z[N], d[N];
int mx[N], t[4 * N];

void z_func(string s) {
    int n = (int)(s.size());
    for (int i = 1, l = 0, r = 0; i < n; ++i){
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if(i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}

void Manacher (string s){
    int l = 0, r = -1, k;
    int n = (int)(s.size());
    for(int i = 0; i < (int)(n); ++i){
        if(i > r)
            k = 1;
        else
            k = min(d[l + r - i], r - i);
        while(i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d[i] = k;
        if(i + k - 1 > r)
        r = i + k - 1, l = i - k + 1;
    }
}

void build(int v, int l, int r){
    if(l == r){
        t[v] = mx[l];
        return;
    }

    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m + 1, r);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
}

int getMax(int v, int l, int r, int L, int R){
    if(L > R)
        return 0;
    if(l == L && r == R)
        return t[v];

    int m = (l + r) / 2;
    if(R <= m)
        return getMax(v * 2 + 1, l, m, L, R);
    if(L > m)
        return getMax(v * 2 + 2, m + 1, r, L, R);
    return max(getMax(v * 2 + 1, l, m, L, m), getMax(v * 2 + 2, m + 1, r, m + 1, R));
}

int main(){





    srand(time(
# 115 "data/830.cpp" 3 4
              __null
# 115 "data/830.cpp"
                  ));
    cout << setprecision(10) << fixed;
    cerr << setprecision(10) << fixed;

    cin >> s;
    len = (int)(s.size());
    reverse(s.begin(), s.end()); ns += s;
    ns += "#";
    reverse(s.begin(), s.end()); ns += s;

    z_func(ns);
    Manacher(ns);
    for(int i = 0; i < (int)((int)(ns.size())); ++i) if(d[i]) --d[i];

    for(int i = len + 1; i < (int)(ns.size()); ++i){
        int pos = z[i] + i - 1;
        mx[pos] = max(mx[pos], z[i]);
    }

    build(0, 0, (int)(ns.size()) - 1);

    int maxAns = 0, lenRg;
    pt mid;
    for(int i = len + 1; i < (int)(ns.size()); ++i){
        int L = i - d[i], R = i + d[i];
        int curAns = R - L + 1;
        int curAns2 = min((int)(ns.size()) - R - 1, getMax(0, 0, (int)(ns.size()) - 1, len + 1, L - 1));
        if(maxAns < curAns + 2 * curAns2){
            maxAns = curAns + 2 * curAns2;
            mid = make_pair(i, d[i]);
            lenRg = curAns2;
        }
    }

    if(lenRg){
        for(int i = len + 1; i < (int)(ns.size()); ++i){
            int pos = z[i] + i - 1;
            if(pos < mid.first - mid.second && z[i] == lenRg){
                cout << "3\n";
                cout << i - len << ' ' << z[i] << endl;
                cout << mid.first - mid.second - len << ' ' << mid.second * 2 + 1 << endl;
                cout << (int)(ns.size()) - z[i] - len << ' ' << z[i] << endl;
                return 0;
            }
        }
        
# 160 "data/830.cpp" 3 4
       (static_cast <bool> (
# 160 "data/830.cpp"
       false
# 160 "data/830.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 160 "data/830.cpp"
       "false"
# 160 "data/830.cpp" 3 4
       , "data/830.cpp", 160, __extension__ __PRETTY_FUNCTION__))
# 160 "data/830.cpp"
                    ;
    }

    cout << "1\n";
    cout << mid.first - mid.second - len << ' ' << mid.second * 2 + 1 << endl;

    return 0;
}

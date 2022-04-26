#include<iostream>
#include<cstdio>

#include<string>
#include<vector>
#include<set>
#include<map>
#include<unordered_map>
#include<queue>
#include<deque>
#include<stack>

#include<iomanip>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<cassert>

using namespace std;

#define forn(i, n) for(int i = 0; i < (int)(n); ++i)
#define correct(x, y, n, m) (0 <= x && x < n && 0 <= y && y < m)
#define X first
#define Y second
#define all(a) a.begin(), a.end()
#define pb push_back
#define mp make_pair
#define sz(v) (int)(v.size())
#define hash hash_

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
    int n = sz(s);
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
    int n = sz(s);
    forn(i, n){
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
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
     
    srand(time(NULL));
    cout << setprecision(10) << fixed;
    cerr << setprecision(10) << fixed;          

    cin >> s;
    len = sz(s);
    reverse(all(s)); ns += s;
    ns += "#";
    reverse(all(s)); ns += s;
    
    z_func(ns);
    Manacher(ns);
    forn(i, sz(ns)) if(d[i]) --d[i];

    for(int i = len + 1; i < sz(ns); ++i){
        int pos = z[i] + i - 1;
        mx[pos] = max(mx[pos], z[i]);
    }

    build(0, 0, sz(ns) - 1);

    int maxAns = 0, lenRg;
    pt mid;
    for(int i = len + 1; i < sz(ns); ++i){
        int L = i - d[i], R = i + d[i];
        int curAns = R - L + 1;
        int curAns2 = min(sz(ns) - R - 1, getMax(0, 0, sz(ns) - 1, len + 1, L - 1));
        if(maxAns < curAns + 2 * curAns2){
            maxAns = curAns + 2 * curAns2;
            mid = mp(i, d[i]);
            lenRg = curAns2;
        }
    }
    
    if(lenRg){
        for(int i = len + 1; i < sz(ns); ++i){
            int pos = z[i] + i - 1;
            if(pos < mid.X - mid.Y && z[i] == lenRg){
                cout << "3\n";
                cout << i - len << ' '  << z[i] << endl;
                cout << mid.X - mid.Y - len << ' ' << mid.Y * 2 + 1 << endl;
                cout << sz(ns) - z[i] - len << ' '  << z[i] << endl;
                return 0;
            }
        }
        assert(false);
    }

    cout << "1\n";
    cout << mid.X - mid.Y - len << ' ' << mid.Y * 2 + 1 << endl;
    
    return 0;
}
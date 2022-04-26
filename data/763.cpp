#include <bits/stdc++.h>
#define f first
#define s second
#define sz(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define pb push_back

using namespace std;
using ll = long long;

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

template<class T, class T2> inline bool chkmax(T &x, const T2 & y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 & y) { return x > y ? x = y, 1 : 0; }
template<class T>           inline void sortl(T &a) { sort(a.begin(), a.end()); }
template<class T>           inline void sortg(T &a) { sort(a.begin(), a.end(), greater<int>()); }
template<class T, class T2> inline istream &operator>>(istream &is,       pair<T, T2> &p)             { is>>p.f>>p.s;      return is; }
template<class T, class T2> inline ostream &operator<<(ostream &os, const pair<T, T2> &p)             { os<<p.f<<' '<<p.s; return os; }
template<class T>           inline istream &operator>>(istream &is,       vector<T> &v)               { for (auto &curr : v) is>>curr;      return is; }
template<class T>           inline ostream &operator<<(ostream &os, const vector<T> &v)               { for (auto curr : v)  os<<curr<<' '; return os; }
template<class T, class T2> inline ostream &operator<<(ostream &os, const map<T, T2> &m)              { auto id = m.begin();   while (id != m.end())   os<<(*id).f<<' '<<(*(id++)).s; return os; }
template<class T, class T2> inline ostream &operator<<(ostream &os, const unordered_map<T, T2> &um)   { auto id = um.begin();  while (id != um.end())  os<<(*id).f<<' '<<(*(id++)).s; return os; }
template<class T>           inline ostream &operator<<(ostream &os, const list<T> &l)                 { auto id = l.begin();   while (id != l.end())   os<<*(id++)<<' '; return os; }
template<class T>           inline ostream &operator<<(ostream &os, const set<T> &s)                  { auto id = s.begin();   while (id != s.end())   os<<*(id++)<<' '; return os; }
template<class T>           inline ostream &operator<<(ostream &os, const unordered_set<T> &us)       { auto id = us.begin();  while (id != us.end())  os<<*(id++)<<' '; return os; }
template<class T>           inline ostream &operator<<(ostream &os, const multiset<T> &ms)            { auto id = ms.begin();  while (id != ms.end())  os<<*(id++)<<' '; return os; }
template<class T>           inline ostream &operator<<(ostream &os, const unordered_multiset<T> &mus) { auto id = mus.begin(); while (id != mus.end()) os<<*(id++)<<' '; return os; }
template<class T>           inline void inArray (T a[], const int &n) { for (int i=0; i<n; i++) cin>>a[i];       }
template<class T>           inline void outArray(T a[], const int &n) { for (int i=0; i<n; i++) cout<<a[i]<<' '; }
const bool hasTests = 0;

const int mod = 1e9 + 7;
const int p = 31;
string s;
int n;
vector<int> dp, dp2, mx;
vector<ll> ppow, hsh, rhsh;
int ans;
int k;
pair<int, int> pref, mid, suf;

void input() {
    cin>>s;
    n = sz(s);
}

void output() {
    cout<<k<<'\n';
    if (k == 1) {
        cout<<mid<<'\n';
    } else {
        cout<<pref<<'\n';
        cout<<mid<<'\n';
        cout<<suf<<'\n';
    }
}

void preKMP() {
    dp.resize(n);
    dp[n-1] = n-1;
    for (int i=n-2; i>=0; i--) {
        int p = dp[i+1];
        while (p < n-1 && s[p] != s[i]) {
            p = dp[p+1];
        }
        if (s[p] == s[i]) {
            p--;
        }
        dp[i] = p;
    }
    //cerr<<dp<<endl;
}

void KMP() {
    dp2.resize(n);
    int p = n-1;

    for (int i=0; i<n; i++) {
        while (p < n-1 && (s[p] != s[i] || i+n-p >= n)) {
            p = dp[p+1];
        }
        if (s[p] == s[i]) {
            p--;
        }
        dp2[i] = n-1-p;
    }
    //cerr<<dp2<<endl;
}

void calcMax() {
    mx.resize(n);
    mx[0] = 0;
    for (int i=1; i<n; i++) {
        mx[i] = i;
        if (dp2[mx[i]] <= dp2[mx[i-1]]) {
            mx[i] = mx[i-1];
        }
    }
    //cerr<<mx<<endl;
}

void calcPowers() {
    ppow.resize(n);
    ppow[0] = 1;
    for (int i=1; i<n; i++) {
        ppow[i] = ppow[i-1]*p % mod;
    }
}

void hashString() {
    hsh.resize(n);
    hsh[0] = s[0] - 'a' + 1;
    for (int i=1; i<n; i++) {
        hsh[i] = ((s[i]-'a'+1)*ppow[i] + hsh[i-1]) % mod;
    }

    rhsh.resize(n);
    rhsh[n-1] = s[n-1] - 'a' + 1;
    for (int i=n-2; i>=0; i--) {
        rhsh[i] = ((s[i]-'a'+1)*ppow[n-1-i] + rhsh[i+1]) % mod;
    }
}

bool checkIfPalindrom(int curr, int sz) {
    int l = curr-1, r = curr+1;
    sz--;
    ll lh = ((rhsh[l-sz] + mod - rhsh[l+1]) % mod) * ppow[r] % mod;
    ll rh = ((hsh[r+sz] + mod - hsh[r-1]) % mod) * ppow[n-1-l] % mod;
    return lh == rh;
}

int maxPalindromFor(int curr) {
    //cerr<<"here: "<<curr<<endl;
    int l = 1, r = min(curr, n-1-curr);

    while (l < r) {
        int mid = (l+r) / 2;
        if (checkIfPalindrom(curr, mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if (curr-l >= 0 && checkIfPalindrom(curr, l)) {
        l++;
    }

    return l;
}

void solve() {
    ans = 1;
    k = 1;
    mid = {1, 1};

    if (n == 1) {
        return;
    }
    preKMP();
    KMP();
    calcMax();
    calcPowers();
    hashString();
    //cerr<<checkIfPalindrom(3, 1)<<endl;

    for (int i=0; i<n; i++) {
        int pal = maxPalindromFor(i);
        if (i - pal < 0 || dp2[mx[i-pal]] == 0) {
            int curr = pal*2 - 1;
            if (curr > ans) {
                k = 1;
                mid = {i-pal+2, pal*2-1};
                ans = curr;
            }
            continue;
        }

        int mn = min(dp2[mx[i - pal]], n-i-pal);
        int curr = pal*2 - 1 + 2*mn;
        if (curr > ans) {
            k = 3;
            pref = {mx[i-pal]-mn+2, mn};
            mid = {i-pal+2, pal*2-1};
            suf = {n-mn+1, mn};
            ans = curr;
        }
        //cerr<<pal<<' ';
    }//cerr<<endl;
}

void start() {
    int t = 1;
    if (hasTests)
        cin>>t;
    for (int i=1; i<=t; i++) {
        input();
        solve();
        //cout<<"Case #"<<i<<": ";
        output();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    start();
    return 0;
}



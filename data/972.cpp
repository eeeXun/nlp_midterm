#include<bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 2e5 + 5, mod = 1e9 + 7, K = 25;
int sp[N][K], lg[N];

void build(vector<int> &v) {
    int n = v.size();
    lg[1] = 0;
    for (int i = 2; i < N; i++)
        lg[i] = lg[i / 2] + 1;
    for (int i = 0; i < n; i++) sp[i][0] = v[i];
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            sp[i][k] = min(sp[i][k - 1], sp[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int query(int l, int r) {
    assert(l <= r);
    int len = r - l + 1;
    return min(sp[l][lg[len]], sp[r + 1 - (1 << lg[len])][lg[len]]);
}

void sort(vector<int> &p, vector<int> &c, int n) {
    vector<int> pos(n + 1, 0), pn(n);
    for (auto it : c) pos[it + 1]++;
    for (int i = 1; i < n; i++) pos[i] += pos[i - 1];
    for (int i = 0; i < n; i++) pn[pos[c[p[i]]]++] = p[i];
    p = pn;
}

vector<int> getSuffixArray(string s, vector<int> &lcp, vector<int> &c) {
    s += '$';
    int n = s.size();
    vector<int> cn(n), p(n);
    vector<pair<int, int> > tmp(n);
    for (int i = 0; i < n; i++) tmp[i] = {s[i], i};
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < n; i++) p[i] = tmp[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
        c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    int k = 0;
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        sort(p, c, n);
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++)
            cn[p[i]] = cn[p[i - 1]] + (make_pair(c[p[i]], c[(p[i] + (1 << k)) % n]) !=
                                       make_pair(c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]));
        k++;
        c = cn;
    }
    k = 0;
    for (int i = 0; i < n - 1; i++) {
        while (s[i + k] == s[p[c[i] - 1] + k]) k++;
        lcp[c[i] - 1] = k;
        k = max(0, k - 1);
    }
    build(lcp);
    return p;
}

int maxPal[N], L[N];
vector<int> ranges[N], pals[N];

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string s, ss;
    cin >> s;
    int n = s.size();
    ss = s + '*';
    reverse(s.begin(), s.end());
    ss += s;
    reverse(s.begin(), s.end());
    /////
    int m = ss.size();
    vector<int> p(m + 1), pos(m + 1), lcp(m);
    p = getSuffixArray(ss, lcp, pos);
    /////
    for (int i = 0; i < n; i++) {
        int i2 = n - 1 - i;
        i2 += n + 1; // cuz it's the second string
        int l = pos[i], r = pos[i2];
        if (r < l) swap(l, r);
        maxPal[i] = (query(l, r - 1) - 1) * 2 + 1;
        pals[i - (maxPal[i] / 2)].push_back(maxPal[i]);
    }
    /////
    for (int i = 0; i < N; i++) L[i] = 1e9;
    for (int i = 0; i <= m; i++) {
        if (p[i] < n) {
            int LL = i, RR = pos[n + 1] ;
            if (LL > RR) swap(LL, RR);
            RR--;
            int len = query(LL, RR);
            ranges[p[i] + len].push_back(n - len);
            L[n - len] = min(p[i], L[n - len]);
        }
    }
    /////
    set<int> Rs;
    pair<int, int> ans[3];
    int Ans = 0;
    for (int i = 0; i < n; i++) {
        for (auto it : ranges[i])
            Rs.insert(it);
        for (auto it : pals[i]) {
            if (it > Ans) {
                Ans = it;
                memset(ans, 0, sizeof ans);
                ans[0] = {i, it};
            }
            ///
            int r = i + it - 1;
            auto IT = Rs.upper_bound(r);
            if (IT != Rs.end()) {
                int len = n - *IT;
                if (len * 2 + it > Ans) {
                    memset(ans, 0, sizeof ans);
                    Ans = len * 2 + it;
                    ans[0] = {L[*IT], len};
                    ans[1] = {i, it};
                    ans[2] = {*IT, len};
                }
            }
        }
    }
    vector<int> a;
    int z = 1;
    if (ans[1].second)
        z = 3;
    cout << z << "\n";
    for (int i = 0; i < z; i++)
        cout << ans[i].first + 1 << ' ' << ans[i].second << "\n";
    return 0;
}
/*
 * create a string ss = s + '*' + reverse(s)
 * find lcp
 * for each position find the maximum odd palindrome using the built lcp
 * finding max pal at i: LCP between i in the first string and s.size() - 1 - i in the second string
 * for each substring in the first string find the lcp with the reversed string, then find
 * for each i find the minimum r that fit with this palindrome
 */

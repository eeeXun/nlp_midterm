#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#include <cmath>
#define ff first
#define ss second
#define MAXN 100005
#define INF 1000000001000000001LL
#define int long long

using namespace std;

const int mod = 1000000007;
int n, i, j, mx, sz, len[MAXN], d[MAXN], revh[MAXN], h[MAXN], pw[MAXN];
pair <int, int> ans[3];
string s;

int t[MAXN * 4], ind[MAXN * 4], IND;

void build(int v, int tl, int tr){
    int m = (tl + tr) / 2;

    if(tl == tr){
        t[v] = d[tl];
        ind[v] = tl;
        return;
    }

    build(v * 2, tl, m);
    build(v * 2 + 1, m + 1, tr);

    t[v] = max(t[v * 2], t[v * 2 + 1]);

    if(t[v * 2] > t[v * 2 + 1])
        ind[v] = ind[v * 2];
    else
        ind[v] = ind[v * 2 + 1];

}

int get(int v, int tl, int tr, int l, int r){
    int m = (tl + tr) / 2;

    if(l > r)
        return -1;

    if(tl == l && tr == r){
        if(IND == -1 || d[IND] < d[ind[v]])
            IND = ind[v];

        return t[v];
    }

    return max(get(v * 2, tl, m, l, min(r, m)),
            get(v * 2 + 1, m + 1, tr, max(l, m + 1), r));
}

int f(int l1, int r1, int l2, int r2){
    int h1 = (h[r1] - ((l1)? h[l1 - 1] : 0) + mod) % mod;
    int h2 = (revh[l2] - revh[r2 + 1] + mod) % mod;
    return (h1 * pw[n - 1 - r2]) % mod == (h2 * pw[l1]) % mod;
}

main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base :: sync_with_stdio(false);
    cin.tie();

    cin >> s; n = s.size();

    reverse(s.begin(), s.end());

    for(i = 0; i < n; i++){
        pw[i] = ((i)? pw[i - 1] * 37 : 1) % mod;
        h[i] = (((i)? h[i - 1] : 0) + pw[i] * (s[i] - 'a' + 1)) % mod;
    }

    for(i = n - 1; i >= 0; i--)
        revh[i] = (revh[i + 1] + pw[n - 1 - i] * (s[i] - 'a' + 1)) % mod;

    for(i = 0; i < n; i++){
        if(s[i] != s[0])
            continue;

        int l = 1, r = i + 1;

        while(l < r){
            int m = (l + r + 1) / 2;

            if(!f(0, m - 1, i - m + 1, i))
                r = m - 1;
            else
                l = m;
        }

        len[i] = l;
    }

    for(i = 0; i < n; i++){
        int l = 1, r = min(i + 1, n - i);

        while(l < r){
            int m = (l + r + 1) / 2;

            if(!f(i - m + 1, i + m - 1, i - m + 1, i + m - 1))
                r = m - 1;
            else
                l = m;
        }

        d[i] = l - 1;

        if(d[i] * 2 + 1 > mx){
            mx = d[i] * 2 + 1; sz = 1;
            ans[0] = {i + d[i], mx};
        }
    }
    //cout << endl;

    build(1, 0, n - 1);

    j = n - 1;
    for(i = 0; i < n; i++){
        while(j >= 0 && len[j] < i + 1)
            j--;

        int l1 = i + 1, r1 = j - i - 1;

        if(l1 > r1)
            break;

        //cout << l1 << " " << r1 << " " << mx << endl;

        int l = 0, r = (r1 - l1) / 2;

        while(l < r){
            int m = (l + r + 1) / 2;

            if(get(1, 0, n - 1, l1 + m, r1 - m) < m)
                r = m - 1;
            else
                l = m;
        }

        int res = (i + 1) * 2 + l * 2 + 1;

        if(res > mx){
            mx = res; sz = 3;
            ans[0] = {i, i + 1};
            ans[1] = {j, i + 1};
            IND = -1;
            get(1, 0, n - 1, l1 + l, r1 - l);
            ans[2] = {IND + l, 2 * l + 1};
        }
    }

    sort(ans, ans + sz);

    cout << sz << endl;

    for(i = sz - 1; i >= 0; i--){
        cout << n - ans[i].ff << " " << ans[i].ss << endl;
    }

    return 0;
}





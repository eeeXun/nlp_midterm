      return std::__detail::__hyperg<__type>(__a, __b, __c, __x);
    }



}


#pragma GCC visibility pop
# 1928 "/usr/include/c++/11.2.0/cmath" 2 3


}
# 13 "data/913.cpp" 2







# 19 "data/913.cpp"
using namespace std;

const long long mod = 1000000007;
long long n, i, j, mx, sz, len[100005], d[100005], revh[100005], h[100005], pw[100005];
pair <long long, long long> ans[3];
string s;

long long t[100005 * 4], ind[100005 * 4], IND;

void build(long long v, long long tl, long long tr){
    long long m = (tl + tr) / 2;

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

long long get(long long v, long long tl, long long tr, long long l, long long r){
    long long m = (tl + tr) / 2;

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

long long f(long long l1, long long r1, long long l2, long long r2){
    long long h1 = (h[r1] - ((l1)? h[l1 - 1] : 0) + mod) % mod;
    long long h2 = (revh[l2] - revh[r2 + 1] + mod) % mod;
    return (h1 * pw[n - 1 - r2]) % mod == (h2 * pw[l1]) % mod;
}

main(){


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

        long long l = 1, r = i + 1;

        while(l < r){
            long long m = (l + r + 1) / 2;

            if(!f(0, m - 1, i - m + 1, i))
                r = m - 1;
            else
                l = m;
        }

        len[i] = l;
    }

    for(i = 0; i < n; i++){
        long long l = 1, r = min(i + 1, n - i);

        while(l < r){
            long long m = (l + r + 1) / 2;

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


    build(1, 0, n - 1);

    j = n - 1;
    for(i = 0; i < n; i++){
        while(j >= 0 && len[j] < i + 1)
            j--;

        long long l1 = i + 1, r1 = j - i - 1;

        if(l1 > r1)
            break;



        long long l = 0, r = (r1 - l1) / 2;

        while(l < r){
            long long m = (l + r + 1) / 2;

            if(get(1, 0, n - 1, l1 + m, r1 - m) < m)
                r = m - 1;
            else
                l = m;
        }

        long long res = (i + 1) * 2 + l * 2 + 1;

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
        cout << n - ans[i].first << " " << ans[i].second << endl;
    }

    return 0;
}

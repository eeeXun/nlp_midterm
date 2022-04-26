    vector <long long> pos(n);
    for (long long i = 1; i < n; i++) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    vector <long long> p_new(n);
    for (long long i = 0; i < n; i++) {
        p_new[pos[c[p[i]]]++] = p[i];
    }
    p = p_new;
}

void build_suf(string& s, vector <long long>& p, vector <long long>& lcp) {
    long long n = (long long) s.size();
    vector <long long> c(n);
    {
        vector <pair <char, long long> > a(n);
        for (long long i = 0; i < n; i++) {
            a[i] = {s[i], i};
        }
        sort(a.begin(), a.end());
        for (long long i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        for (long long i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
        }
    }
    long long k = 0;
    while ((1 << k) < n) {
        for (long long i = 0; i < n; i++) {
            p[i] = (p[i] - (1 << k) + n) % n;
        }
        count_sort(p, c);
        vector <long long> c_new(n);
        for (long long i = 1; i < n; i++) {
            pair <long long, long long> curr = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair <long long, long long> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i - 1]] + (curr != prev);
        }
        c = c_new;
        k++;
    }
    k = 0;
    for (long long i = 0; i < n - 1; i++) {
        long long j = p[c[i] - 1];
        while (s[i + k] == s[j + k]) {
            k++;
        }
        lcp[c[i]] = k;
        k = max(k - 1, 0ll);
    }
}

const long long maxn = 2e5 + 3, x1 = 37, x2 = 43, b1 = 1e9 + 7, b2 = 1e9 + 9;

pair <long long, long long> h[maxn], x_pow[maxn], rh[maxn];

void build_hash(string& s) {
    long long n = (long long) s.size();
    h[0] = {s[0], s[0]};
    x_pow[0] = {1, 1};
    for (long long i = 1; i <= n; i++) {
        x_pow[i] = {x_pow[i - 1].first * x1 % b1, x_pow[i - 1].second * x2 % b2};
    }
    for (long long i = 1; i < n; i++) {
        h[i] = {(h[i - 1].first * x1 + s[i]) % b1, (h[i - 1].second * x2 + s[i]) % b2};
    }
    rh[n - 1] = {s[n - 1], s[n - 1]};
    for (long long i = n - 2; i >= 0; i--) {
        rh[i] = {(rh[i + 1].first * x1 + s[i]) % b1, (rh[i + 1].second * x2 + s[i]) % b2};
    }
}

long long n, n1;

pair <long long, long long> get_hash(long long l, long long r) {
    if (l == 0) {
        return h[r];
    }
    return {(h[r].first - h[l - 1].first * x_pow[r - l + 1].first % b1 + b1) % b1, (h[r].second - h[l - 1].second * x_pow[r - l + 1].second % b2 + b2) % b2};
}

pair <long long, long long> get_rhash(long long l, long long r) {
    if (r == n - 1) {
        return rh[l];
    }
    return {(rh[l].first - rh[r + 1].first * x_pow[r - l + 1].first % b1 + b1) % b1, (rh[l].second - rh[r + 1].second * x_pow[r - l + 1].second % b2 + b2) % b2};
}

long long pal[maxn];

void build_pal() {
    for (long long i = 0; i < n1; i++) {
        long long l = 0, r = min(i, n1 - 1 - i);
        while (r - l > 1) {
            long long m = (r + l) >> 1;
            if (get_hash(i - m, i) == get_rhash(i, i + m)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        for (long long j = min(min(i, n1 - 1 - i), r + 1); j >= 0; j--) {
            if (get_hash(i - j, i) == get_rhash(i, i + j)) {
                pal[i] = j;
                break;
            }
        }
    }
}

const long long L = 19;

long long lg[maxn], lcp_min[maxn][L], p_min[maxn][L], pal_max[maxn][L];

long long max_pal(long long a, long long b) {
    return (pal[a] > pal[b] ? a : b);
}

void build_st(vector <long long>& p, vector <long long>& lcp) {
    for (long long i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }
    for (long long i = 0; i < n; i++) {
        lcp_min[i][0] = lcp[i];
        p_min[i][0] = p[i];
        pal_max[i][0] = i;
    }
    for (long long i = 1; i < L; i++) {
        for (long long j = 0; j + (1 << i) <= n; j++) {
            lcp_min[j][i] = min(lcp_min[j][i - 1], lcp_min[j + (1 << (i - 1))][i - 1]);
            p_min[j][i] = min(p_min[j][i - 1], p_min[j + (1 << (i - 1))][i - 1]);
            pal_max[j][i] = max_pal(pal_max[j][i - 1], pal_max[j + (1 << (i - 1))][i - 1]);
        }
    }
}

long long get_lcp(long long l, long long r) {
    long long j = lg[r - l + 1];
    return min(lcp_min[l][j], lcp_min[r - (1 << j) + 1][j]);
}

long long get_p(long long l, long long r) {
    if (l > r){
        return -2;
    }
    long long j = lg[r - l + 1];
    return min(p_min[l][j], p_min[r - (1 << j) + 1][j]);
}

long long get_pal(long long l, long long r) {
    
# 162 "data/728.cpp" 3 4
   (static_cast <bool> (
# 162 "data/728.cpp"
   l <= r
# 162 "data/728.cpp" 3 4
   ) ? void (0) : __assert_fail (
# 162 "data/728.cpp"
   "l <= r"
# 162 "data/728.cpp" 3 4
   , "data/728.cpp", 162, __extension__ __PRETTY_FUNCTION__))
# 162 "data/728.cpp"
                 ;
    long long j = lg[r - l + 1];
    return max_pal(pal_max[l][j], pal_max[r - (1 << j) + 1][j]);
}

long long get_left(long long pos, long long x) {
    long long l = 0, r = pos;
    while (r - l > 1) {
        long long m = (r + l) >> 1;
        if (get_lcp(pos - m, pos) >= x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    for (long long i = min(pos, r + 1); i >= 0; i--) {
        if (get_lcp(pos - i, pos) >= x) {
            return pos - i - 1;
        }
    }
    return pos;
}

long long get_right(long long pos, long long x) {
    long long l = 1, r = n - pos - 1;
    while (r - l > 1) {
        long long m = (r + l) >> 1;
        if (get_lcp(pos + 1, pos + m) >= x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    for (long long i = min(n - pos - 1, r + 1); i >= 1; i--) {
        if (get_lcp(pos + 1, pos + i) >= x) {
            return pos + i;
        }
    }
    return pos;
}


int32_t main() {
    string t;
    cin >> t;
    n1 = (long long) t.size();
    string s = t;
    reverse(s.begin(), s.end());
    s = t + "{" + s + "$";
    n = (long long) s.size();
    vector <long long> p(n), lcp(n), ind(n);
    build_suf(s, p, lcp);
    for (long long i = 0; i < n; i++) {
        ind[p[i]] = i;
    }
    build_hash(s);
    build_pal();
    build_st(p, lcp);
    long long max_pal = 0;
    for (long long i = 0; i < n; i++) {
        if (pal[i] > pal[max_pal]) {
            max_pal = i;
        }
    }
    long long ans_len = 0, p1, p2, p3, p4, p5, p6;
    for (long long i = (long long) t.size() - 1; i >= 0; i--) {
        long long len = t.size() - i;
        long long l = get_left(ind[n1 + 1], len), r = get_right(ind[n1 + 1], len);
        long long p = get_p(l, r);
        if (p + len >= i) {
            continue;
        }
        l = 1, r = (i - (p + t.size() - i - 1) - 1) / 2;
        while (r - l > 1) {
            long long m = (r + l) >> 1;
            if (pal[get_pal(p + len - 1 + m, i - m)] >= m - 1) {
                l = m;
            } else {
                r = m;
            }
        }
        for (long long j = min((i - (p + t.size() - i - 1) - 1) / 2, r + 1); j >= 1; j--) {
            if (pal[get_pal(p + len - 1 + j, i - j)] >= j - 1) {
                long long curr = len * 2 + (j - 1) * 2 + 1;
                if (curr > ans_len) {
                    ans_len = curr;
                    p1 = p;
                    p2 = len;
                    p3 = get_pal(p + len - 1 + j, i - j) - j + 1;
                    p4 = (j - 1) * 2 + 1;
                    p5 = i;
                    p6 = len;
                }
                break;
            }
        }
    }
    if (pal[max_pal] * 2 + 1 >= ans_len) {
        cout << "1\n" << max_pal - pal[max_pal] + 1 << " " << pal[max_pal] * 2 + 1;
    } else {
        cout << "3\n" << p1 + 1 << " " << p2 << "\n" << p3 + 1 << " " << p4 << "\n" << p5 + 1 << " " << p6;
    }
    return 0;
}

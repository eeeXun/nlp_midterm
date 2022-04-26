

pii range_max(int i, int j) {
    int sz = j-i+1;
    int lg = 31 - __builtin_clz(sz);
    return max(jump[lg][i], jump[lg][j+1-(1<<lg)]);
}


bool can_get_between(int i, int j, int l) {
    int ii = i+l/2;
    int jj = j-l/2;
    if (ii > jj) return false;

    auto rm = range_max(ii, jj);
    return rm.first >= l;
}



pii get_between(int i, int j) {
    
# 73 "data/798.cpp" 3 4
   (static_cast <bool> (
# 73 "data/798.cpp"
   i<=j
# 73 "data/798.cpp" 3 4
   ) ? void (0) : __assert_fail (
# 73 "data/798.cpp"
   "i<=j"
# 73 "data/798.cpp" 3 4
   , "data/798.cpp", 73, __extension__ __PRETTY_FUNCTION__))
# 73 "data/798.cpp"
                ;
    int lo = 1;
    int hi = N;
    while (lo < hi) {
        int m = (lo+hi+1)/2;
        if (can_get_between(i, j, m)) {
            lo = m;
        } else {
            hi = m-1;
        }
    }
    
# 84 "data/798.cpp" 3 4
   (static_cast <bool> (
# 84 "data/798.cpp"
   lo%2 == 1
# 84 "data/798.cpp" 3 4
   ) ? void (0) : __assert_fail (
# 84 "data/798.cpp"
   "lo%2 == 1"
# 84 "data/798.cpp" 3 4
   , "data/798.cpp", 84, __extension__ __PRETTY_FUNCTION__))
# 84 "data/798.cpp"
                     ;

    int ii = i+lo/2;
    int jj = j-lo/2;

    auto rm = range_max(ii, jj);
    rm.first = min(rm.first, min((rm.second-i)*2+1, (j-rm.second)*2+1));
    rm.second = rm.second-rm.first/2;

    return rm;
}

struct solution {
    pii x, y, z;
    int parts, length;
    solution() :parts(0), length(0) {}
    solution(pii a): parts(1), x(a), length(a.second) {}
    solution(pii a, pii b, pii c): parts(3), x(a), y(b), z(c), length(a.second+b.second+c.second) {}
    void print() {
        
# 103 "data/798.cpp" 3 4
       (static_cast <bool> (
# 103 "data/798.cpp"
       parts != 0
# 103 "data/798.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 103 "data/798.cpp"
       "parts != 0"
# 103 "data/798.cpp" 3 4
       , "data/798.cpp", 103, __extension__ __PRETTY_FUNCTION__))
# 103 "data/798.cpp"
                         ;
        cout << parts << "\n";
        cout << x.first << " " << x.second << "\n";
        if (parts > 1) {
            cout << y.first << " " << y.second << "\n";
            cout << z.first << " " << z.second << "\n";
        }
    }
    bool operator < (const solution& o) const {
        if (length == o.length) return parts < o.parts;
        return length < o.length;
    }
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> s;



    n = s.size();
    t = s;
    reverse(s.begin(), s.end());
    t += '$';
    t += s;
    reverse(s.begin(), s.end());
    sa = suff_array(t);


    for (int i=0; i<n; ++i) {
        int x = sa.lcp(i, 2*n-i);
        len[i] = x*2-1;
    }

    setup();

    solution ans;
# 150 "data/798.cpp"
    for (int i=0; i<n; ++i) {
        int lcp = sa.lcp(i, n+1);
        if (lcp == n-i) {
            ans = max(ans, solution(pii(i+1, lcp)));
            auto q = solution(pii(i+1, lcp));
            continue;
        }

        int lo = i+lcp;
        int hi = n-1-lcp;
        
# 160 "data/798.cpp" 3 4
       (static_cast <bool> (
# 160 "data/798.cpp"
       hi >= lo
# 160 "data/798.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 160 "data/798.cpp"
       "hi >= lo"
# 160 "data/798.cpp" 3 4
       , "data/798.cpp", 160, __extension__ __PRETTY_FUNCTION__))
# 160 "data/798.cpp"
                       ;

        pii rm = get_between(lo, hi);

        ans = max(solution(pii(i+1, lcp), pii(rm.second+1, rm.first), pii(n-lcp+1, lcp)), ans);
    }


    if (ans.length%2 == 0) {
        
# 169 "data/798.cpp" 3 4
       (static_cast <bool> (
# 169 "data/798.cpp"
       ans.parts == 1
# 169 "data/798.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 169 "data/798.cpp"
       "ans.parts == 1"
# 169 "data/798.cpp" 3 4
       , "data/798.cpp", 169, __extension__ __PRETTY_FUNCTION__))
# 169 "data/798.cpp"
                             ;
        int p = ans.x.first;
        int k = ans.x.second;
        int q = (k-1)/2;
        ans = solution(pii(p, q), pii(p+q, 1), pii(p+k-q, q));
    }

    if (ans.length%2 == 1 && ans.x.second == 0) {
        ans = solution(ans.y);
    }

    ans.print();

    return 0;
}

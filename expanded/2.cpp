    typename enable_if<is_integral<T>::value, T>::type floor(T n, T d) {
        
# 117 "data/2.cpp" 3 4
       (static_cast <bool> (
# 117 "data/2.cpp"
       d != 0
# 117 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 117 "data/2.cpp"
       "d != 0"
# 117 "data/2.cpp" 3 4
       , "data/2.cpp", 117, __extension__ __PRETTY_FUNCTION__))
# 117 "data/2.cpp"
                     ;
        if (d < 0) tie(n, d) = make_pair(-n, -d);
        return n / d - ((n < 0) && (n % d));
    }
    template<typename T>
    typename enable_if<is_integral<T>::value, T>::type ceil(T n, T d) {
        
# 123 "data/2.cpp" 3 4
       (static_cast <bool> (
# 123 "data/2.cpp"
       d != 0
# 123 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 123 "data/2.cpp"
       "d != 0"
# 123 "data/2.cpp" 3 4
       , "data/2.cpp", 123, __extension__ __PRETTY_FUNCTION__))
# 123 "data/2.cpp"
                     ;
        if (d < 0) tie(n, d) = make_pair(-n, -d);
        return n / d + ((n > 0) && (n % d));
    }
};
using namespace __numeric;

namespace __algorithm {
    template<typename T> void dedup(vector<T>& v) {
        sort((v).begin(), (v).end()); v.erase(unique((v).begin(), (v).end()), v.end());
    }
    template<typename T> typename vector<T>::iterator find(vector<T>& v, const T& x) {
        auto it = lower_bound((v).begin(), (v).end(), x); return it != v.end() && *it == x ? it : v.end();
    }
    template<typename T> size_t index(vector<T>& v, const T& x) {
        auto it = find(v, x); 
# 138 "data/2.cpp" 3 4
                             (static_cast <bool> (
# 138 "data/2.cpp"
                             it != v.end() && *it == x
# 138 "data/2.cpp" 3 4
                             ) ? void (0) : __assert_fail (
# 138 "data/2.cpp"
                             "it != v.end() && *it == x"
# 138 "data/2.cpp" 3 4
                             , "data/2.cpp", 138, __extension__ __PRETTY_FUNCTION__))
# 138 "data/2.cpp"
                                                              ; return it - v.begin();
    }
    template<typename C, typename T, typename OP> vector<T> prefixes(const C& v, T id, OP op) {
        vector<T> r(int((v).size())+1, id); for (int i = 0; i < (int((v).size())); i++) r[i+1] = op(r[i], v[i]); return r;
    }
    template<typename C, typename T, typename OP> vector<T> suffixes(const C& v, T id, OP op) {
        vector<T> r(int((v).size())+1, id); for (int i = (int((v).size()))-1; i >= 0; i--) r[i] = op(v[i], r[i+1]); return r;
    }
}
using namespace __algorithm;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
struct monostate {
    friend istream& operator>>(istream& is, const monostate& ms) { return is; }
    friend ostream& operator<<(ostream& os, const monostate& ms) { return os; }
    friend monostate operator+(const monostate& a, const monostate& b) { return a; }
} ms;
#pragma GCC diagnostic pop

namespace __io {
    void setIn(string second) { freopen(second.c_str(),"r",
# 159 "data/2.cpp" 3 4
                                                stdin
# 159 "data/2.cpp"
                                                     ); }
    void setOut(string second) { freopen(second.c_str(),"w",
# 160 "data/2.cpp" 3 4
                                                 stdout
# 160 "data/2.cpp"
                                                       ); }
    void setIO(string second = "") {
        ios_base::sync_with_stdio(0); cin.tie(0);
        cout << fixed << setprecision(15);
        if (int((second).size())) { setIn(second+".in"), setOut(second+".out"); }
    }
}
using namespace __io;



template<typename T, typename F> struct sparse_table {
    int SZ;
    F tt;
    vector<vector<T>> table;

    sparse_table() : SZ(0) {}
    template<typename I> sparse_table(int SZ_, F tt_, I init) : SZ(SZ_), tt(tt_) {
        const int L = 32 - __builtin_clz(max(SZ - 1, 1));
        table.resize(L, vector<T>(SZ));

        for (int i = 0; i < SZ; i++) table[0][i] = init(i);

        for (int l = 0; l + 1 < L; l++)
            for (int i = 0; i + (2 << l) <= SZ; i++)
                table[l+1][i] = tt(table[l][i], table[l][i + (1 << l)]);
    }


    T operator()(int i, int j) const {
        
# 190 "data/2.cpp" 3 4
       (static_cast <bool> (
# 190 "data/2.cpp"
       0 <= i && i < j && j <= SZ
# 190 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 190 "data/2.cpp"
       "0 <= i && i < j && j <= SZ"
# 190 "data/2.cpp" 3 4
       , "data/2.cpp", 190, __extension__ __PRETTY_FUNCTION__))
# 190 "data/2.cpp"
                                         ;
        int l = j - i - 1 ? 31 - __builtin_clz(j - i - 1) : 0;
        return tt(table[l][i], table[l][j - (1 << l)]);
    }
};


struct palindromes {
    int SZ;
    vector<int> width;

    template<typename I>
    palindromes(I begin, I end) {
        SZ = int(end - begin);
        width.resize(max(2 * SZ - 1, 0));

        auto match = [&](int c, int r) {
            if ((c - r) < -1 || (c + r) > int(width.size())) return false;
            return (c - r)&1 || *(begin + (c - r)/2) == *(begin + (c + r)/2);
        };

        for (int cen = 0, lim = -1, ref; cen < int(width.size()); cen++) {
            if (lim > cen)
                width[cen] = min(width[2 * ref - cen], lim - cen);
            while (match(cen, width[cen] + 1))
                width[cen]++;
            if (cen + width[cen] > lim) {
                lim = cen + width[cen];
                ref = cen;
            }
        }
    }

    int longest_with_center_at(int index) const {
        
# 224 "data/2.cpp" 3 4
       (static_cast <bool> (
# 224 "data/2.cpp"
       0 <= index && index < SZ
# 224 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 224 "data/2.cpp"
       "0 <= index && index < SZ"
# 224 "data/2.cpp" 3 4
       , "data/2.cpp", 224, __extension__ __PRETTY_FUNCTION__))
# 224 "data/2.cpp"
                                       ;
        return width[2 * index];
    }

    int longest_with_center_right_of(int index) const {
        
# 229 "data/2.cpp" 3 4
       (static_cast <bool> (
# 229 "data/2.cpp"
       0 <= index && index < SZ - 1
# 229 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 229 "data/2.cpp"
       "0 <= index && index < SZ - 1"
# 229 "data/2.cpp" 3 4
       , "data/2.cpp", 229, __extension__ __PRETTY_FUNCTION__))
# 229 "data/2.cpp"
                                           ;
        return width[2 * index + 1];
    }

    static struct greater {
        int operator()(int x, int y) const { return max(x, y); }
    } rad_cmp;
    mutable sparse_table<int, greater> width_rmq;

    int longest_within_substring(int pos, int len) const {
        
# 239 "data/2.cpp" 3 4
       (static_cast <bool> (
# 239 "data/2.cpp"
       0 <= pos && pos + len <= SZ
# 239 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 239 "data/2.cpp"
       "0 <= pos && pos + len <= SZ"
# 239 "data/2.cpp" 3 4
       , "data/2.cpp", 239, __extension__ __PRETTY_FUNCTION__))
# 239 "data/2.cpp"
                                          ;
        if (!width_rmq.SZ)
            width_rmq = sparse_table<int, greater>(int(width.size()), rad_cmp,
                    [&](int i) { return width[i]; });

        int lo = 0, hi = len + 1;
        while (hi - lo > 1) {
            int mi = lo + (hi - lo) / 2;
            int min_c = min(2 * (pos + mi / 2), 2 * (pos + (mi - 2 + 1) / 2) + 1);
            int max_c = max(2 * (pos + len - mi / 2) - 1, 2 * (pos + len - (mi + 1) / 2));
            if (min_c < max_c && width_rmq(min_c, max_c) >= mi)
                lo = mi;
            else
                hi = mi;
        }
        return lo;
    }
};


enum BACKFILL { CYCLIC, NEG_INF, POS_INF };
template<BACKFILL FILL>
struct suffix_array {
    int SZ;
    vector<vector<int>> rank_of;
    vector<int> by_rank;

    vector<int> lcp;
    static struct smaller {
        int operator()(int x, int y) const { return min(x, y); }
    } lcp_cmp;
    sparse_table<int, smaller> lcp_rmq;

    template<typename I>
    suffix_array(I begin, I end) {
        vi input;
        for (I iter = begin; iter != end; iter = next(iter))
            input.push_back(*iter);

        SZ = int(input.size());

        vi uniq = input;
        sort(uniq.begin(), uniq.end());
        uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
        for (int &val : input)
            val = (lower_bound(uniq.begin(), uniq.end(), val) - uniq.begin());

        rank_of.push_back(input);

        vi ct(SZ);
        for (int i = 0; i < SZ; i++) ct[input[i]]++;
        for (int i = 0; i < SZ - 1; i++) ct[i + 1] += ct[i];

        by_rank.resize(SZ);
        for (int i = SZ - 1; i >= 0; i--) by_rank[--ct[input[i]]] = i;

        vector<int> by_rank_updated(SZ);
        for (int len = 1; len < SZ; len *= 2) {
            int tail = 0;
            if (FILL == NEG_INF)
                for (int i = SZ - len; i < SZ; i++)
                    by_rank_updated[tail++] = i;
            for (int rank = 0; rank < SZ; rank++)
                if (by_rank[rank] >= len)
                    by_rank_updated[tail++] = by_rank[rank] - len;
                else if (FILL == CYCLIC)
                    by_rank_updated[tail++] = by_rank[rank] - len + SZ;
            if (FILL == POS_INF)
                for (int i = SZ - len; i < SZ; i++)
                    by_rank_updated[tail++] = i;
            swap(by_rank, by_rank_updated);

            fill(ct.begin(), ct.end(), 0);
            for (int i = 0; i < SZ; i++) ct[rank_of.back()[i]]++;
            for (int i = 0; i < SZ - 1; i++) ct[i + 1] += ct[i];

            for (int i = SZ - 1; i >= 0; i--)
                by_rank_updated[--ct[rank_of.back()[by_rank[i]]]] = by_rank[i];
            swap(by_rank, by_rank_updated);

            vi new_ranks(SZ);
            pair<int, int> prev = { rank(by_rank[0]), rank(by_rank[0] + len) };
            for (int i = 1; i < SZ; i++) {
                pair<int, int> cur = { rank(by_rank[i]), rank(by_rank[i] + len) };
                new_ranks[by_rank[i]] = new_ranks[by_rank[i - 1]] + (prev != cur);
                prev = cur;
            }
            rank_of.push_back(new_ranks);
        }

        lcp.resize(SZ - 1);
        for (int i = 0, len = 0; i < SZ; i++) {
            if (rank(i) == SZ - 1)
                continue;
            int j = by_rank[rank(i) + 1];
            while (i + len < SZ && j + len < SZ && input[i + len] == input[j + len])
                len++;
            lcp[rank(i)] = len;
            if (len) --len;
        }
        lcp_rmq = sparse_table<int, smaller>(int(lcp.size()), lcp_cmp,
                [&](int i) { return lcp[i]; });
    }

    int rank(int i) const {
        if (i < SZ) {
            return rank_of.back()[i];
        } else switch (FILL) {
            case CYCLIC: return rank_of.back()[i - SZ];
            case NEG_INF: return -1;
            case POS_INF: return SZ;
        }
    }

    int suffix_at_rank(int r) const { return by_rank[r]; }

    int longest_common_prefix(int i, int j) const {
        
# 356 "data/2.cpp" 3 4
       (static_cast <bool> (
# 356 "data/2.cpp"
       0 <= i && i < SZ && 0 <= j && j < SZ
# 356 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 356 "data/2.cpp"
       "0 <= i && i < SZ && 0 <= j && j < SZ"
# 356 "data/2.cpp" 3 4
       , "data/2.cpp", 356, __extension__ __PRETTY_FUNCTION__))
# 356 "data/2.cpp"
                                                   ;
        if (i == j) return SZ - i;
        i = rank(i);
        j = rank(j);
        if (i > j) swap(i, j);
        return lcp_rmq(i, j);
    }

    pair<int, int> ranks_with_prefix(int pos, int len) {
        
# 365 "data/2.cpp" 3 4
       (static_cast <bool> (
# 365 "data/2.cpp"
       0 <= pos && pos + len <= SZ
# 365 "data/2.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 365 "data/2.cpp"
       "0 <= pos && pos + len <= SZ"
# 365 "data/2.cpp" 3 4
       , "data/2.cpp", 365, __extension__ __PRETTY_FUNCTION__))
# 365 "data/2.cpp"
                                          ;
        auto less_than = [&](int other_pos, int arg) { return longest_common_prefix(pos, other_pos) < arg; };
        auto geq = [&](int other_pos, int arg) { return longest_common_prefix(pos, other_pos) >= arg; };
        return make_pair(
            lower_bound(by_rank.begin(), by_rank.begin() + rank(pos), len, less_than) - by_rank.begin(),
            lower_bound(by_rank.begin() + rank(pos), by_rank.end(), len, geq) - by_rank.begin()
        );
    }
};


int main() {
    setIO();

    string second; re(second);

    palindromes pal((second).begin(), (second).end());

    for (int i = 0; i < (int((second).size()) - 1); i++) pal.width[2 * i + 1] = 0;

    vi str;
    for (auto& c : second) str.push_back(c - 'a');
    str.push_back(26);
    reverse((second).begin(), (second).end());
    for (auto& c : second) str.push_back(c - 'a');
    reverse((second).begin(), (second).end());

    suffix_array<POS_INF> sa((str).begin(), (str).end());

    sparse_table<int, suffix_array<POS_INF>::smaller> inx_rmq(int((str).size()), sa.lcp_cmp,
            [&](int i) { return sa.by_rank[i]; });

    int x = -1, y = 0, p = -1;

    for (int suff = 0; suff < ((int((second).size()) - 1) / 2 + 1); suff++) {
        pair<int, int> pref_range = sa.ranks_with_prefix(int((second).size()) + 1, suff);
        int earliest = inx_rmq(pref_range.first, pref_range.second);

        if (earliest + 2 * suff <= int((second).size())) {
            int pos = earliest + suff;
            int len = int((second).size()) - earliest - 2 * suff;
            int mid = pal.longest_within_substring(pos, len);






            if (2 * suff + mid > 2 * x + y) {
                p = earliest;
                x = suff;
                y = mid;
            }
        }
    }


    int begin = -1;
    for (int c = 0; c < (int((pal.width).size())); c++) {
        if (pal.width[c] < y) continue;

        begin = c/2 - y/2;
        if (p + x > begin)
            continue;

        break;
    }

    if (x == 0) {
        ps(1);
        ps(begin + 1, y);
    } else {
        ps(3);
        ps(p + 1, x);
        ps(begin + 1, y);
        ps(int((second).size()) - x + 1, x);
    }



    return 0;
}

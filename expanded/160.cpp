    typename enable_if<is_integral<T>::value, T>::type floor(T n, T d) {
        
# 117 "data/160.cpp" 3 4
       (static_cast <bool> (
# 117 "data/160.cpp"
       d != 0
# 117 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 117 "data/160.cpp"
       "d != 0"
# 117 "data/160.cpp" 3 4
       , "data/160.cpp", 117, __extension__ __PRETTY_FUNCTION__))
# 117 "data/160.cpp"
                     ;
        if (d < 0) tie(n, d) = make_pair(-n, -d);
        return n / d - ((n < 0) && (n % d));
    }
    template<typename T>
    typename enable_if<is_integral<T>::value, T>::type ceil(T n, T d) {
        
# 123 "data/160.cpp" 3 4
       (static_cast <bool> (
# 123 "data/160.cpp"
       d != 0
# 123 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 123 "data/160.cpp"
       "d != 0"
# 123 "data/160.cpp" 3 4
       , "data/160.cpp", 123, __extension__ __PRETTY_FUNCTION__))
# 123 "data/160.cpp"
                     ;
        if (d < 0) tie(n, d) = make_pair(-n, -d);
        return n / d + ((n > 0) && (n % d));
    }
}
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
# 138 "data/160.cpp" 3 4
                             (static_cast <bool> (
# 138 "data/160.cpp"
                             it != v.end() && *it == x
# 138 "data/160.cpp" 3 4
                             ) ? void (0) : __assert_fail (
# 138 "data/160.cpp"
                             "it != v.end() && *it == x"
# 138 "data/160.cpp" 3 4
                             , "data/160.cpp", 138, __extension__ __PRETTY_FUNCTION__))
# 138 "data/160.cpp"
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
# 159 "data/160.cpp" 3 4
                                                stdin
# 159 "data/160.cpp"
                                                     ); }
    void setOut(string second) { freopen(second.c_str(),"w",
# 160 "data/160.cpp" 3 4
                                                 stdout
# 160 "data/160.cpp"
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
        
# 190 "data/160.cpp" 3 4
       (static_cast <bool> (
# 190 "data/160.cpp"
       0 <= i && i < j && j <= SZ
# 190 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 190 "data/160.cpp"
       "0 <= i && i < j && j <= SZ"
# 190 "data/160.cpp" 3 4
       , "data/160.cpp", 190, __extension__ __PRETTY_FUNCTION__))
# 190 "data/160.cpp"
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

    int longest_centered_at(int index) const {
        
# 225 "data/160.cpp" 3 4
       (static_cast <bool> (
# 225 "data/160.cpp"
       0 <= index && index < SZ
# 225 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 225 "data/160.cpp"
       "0 <= index && index < SZ"
# 225 "data/160.cpp" 3 4
       , "data/160.cpp", 225, __extension__ __PRETTY_FUNCTION__))
# 225 "data/160.cpp"
                                       ;
        return width[2 * index];
    }

    int longest_centered_right_of(int index) const {
        
# 230 "data/160.cpp" 3 4
       (static_cast <bool> (
# 230 "data/160.cpp"
       0 <= index && index < SZ - 1
# 230 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 230 "data/160.cpp"
       "0 <= index && index < SZ - 1"
# 230 "data/160.cpp" 3 4
       , "data/160.cpp", 230, __extension__ __PRETTY_FUNCTION__))
# 230 "data/160.cpp"
                                           ;
        return width[2 * index + 1];
    }

    static struct greater {
        int operator()(int x, int y) const { return max(x, y); }
    } rad_cmp;
    mutable sparse_table<int, greater> width_rmq;

    int longest_within_substring(int pos, int len) const {
        
# 240 "data/160.cpp" 3 4
       (static_cast <bool> (
# 240 "data/160.cpp"
       0 <= pos && pos + len <= SZ
# 240 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 240 "data/160.cpp"
       "0 <= pos && pos + len <= SZ"
# 240 "data/160.cpp" 3 4
       , "data/160.cpp", 240, __extension__ __PRETTY_FUNCTION__))
# 240 "data/160.cpp"
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
    vector<int> lcp_between_ranks;

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
            val = int((lower_bound(uniq.begin(), uniq.end(), val) - uniq.begin()));

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
            pair<int, int> prev = { rank_of_suffix(by_rank[0]), rank_of_suffix(by_rank[0] + len) };
            for (int i = 1; i < SZ; i++) {
                pair<int, int> cur = { rank_of_suffix(by_rank[i]), rank_of_suffix(by_rank[i] + len) };
                new_ranks[by_rank[i]] = new_ranks[by_rank[i - 1]] + (prev != cur);
                prev = cur;
            }
            rank_of.push_back(new_ranks);
        }

        lcp_between_ranks.resize(SZ - 1);
        for (int i = 0, len = 0; i < SZ; i++) {
            if (rank_of_suffix(i) == SZ - 1)
                continue;
            int j = suffix_at_rank(rank_of_suffix(i) + 1);
            while (i + len < SZ && j + len < SZ && input[i + len] == input[j + len])
                len++;
            lcp_between_ranks[rank_of_suffix(i)] = len;
            if (len) --len;
        }
    }

    int rank_of_suffix(int i) const {
        if (i < SZ) {
            return rank_of.back()[i];
        } else switch (FILL) {
            case CYCLIC: return rank_of.back()[i - SZ];
            case NEG_INF: return -1;
            case POS_INF: return SZ;
        }
    }

    int suffix_at_rank(int r) const {
        return by_rank[r];
    }

    struct smaller {
        int operator()(int x, int y) const { return min(x, y); }
    } cmp;

    mutable sparse_table<int, smaller> lcp_between_ranks_rmq;
    int longest_common_prefix(int i, int j) const {
        if (!lcp_between_ranks_rmq.SZ)
            lcp_between_ranks_rmq = sparse_table<int, smaller>(SZ - 1, cmp, [&](int r) { return lcp_between_ranks[r]; });

        
# 361 "data/160.cpp" 3 4
       (static_cast <bool> (
# 361 "data/160.cpp"
       0 <= i && i < SZ && 0 <= j && j < SZ
# 361 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 361 "data/160.cpp"
       "0 <= i && i < SZ && 0 <= j && j < SZ"
# 361 "data/160.cpp" 3 4
       , "data/160.cpp", 361, __extension__ __PRETTY_FUNCTION__))
# 361 "data/160.cpp"
                                                   ;
        if (i == j) return SZ - i;
        int ri = rank_of_suffix(i);
        int rj = rank_of_suffix(j);
        if (ri > rj) swap(ri, rj);
        return lcp_between_ranks_rmq(ri, rj);
    }

    pair<int, int> ranks_with_prefix(int pos, int len) const {
        
# 370 "data/160.cpp" 3 4
       (static_cast <bool> (
# 370 "data/160.cpp"
       0 <= pos && pos + len <= SZ
# 370 "data/160.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 370 "data/160.cpp"
       "0 <= pos && pos + len <= SZ"
# 370 "data/160.cpp" 3 4
       , "data/160.cpp", 370, __extension__ __PRETTY_FUNCTION__))
# 370 "data/160.cpp"
                                          ;
        auto less_than = [&](int other_pos, int arg) { return longest_common_prefix(pos, other_pos) < arg; };
        auto geq = [&](int other_pos, int arg) { return longest_common_prefix(pos, other_pos) >= arg; };
        return make_pair(
            lower_bound(by_rank.begin(), by_rank.begin() + rank_of_suffix(pos), len, less_than) - by_rank.begin(),
            lower_bound(by_rank.begin() + rank_of_suffix(pos), by_rank.end(), len, geq) - by_rank.begin()
        );
    }

    mutable sparse_table<int, smaller> by_rank_rmq;
    int first_occurence_of(int pos, int len) const {
        if (!by_rank_rmq.SZ)
            by_rank_rmq = sparse_table<int, smaller>(SZ, cmp, [&](int r) { return by_rank[r]; });
        pair<int, int> occurences = ranks_with_prefix(pos, len);
        return by_rank_rmq(occurences.first, occurences.second);
    }
};


int main() {
    setIO();

    string second; re(second);

    vi str;
    for (auto& c : second) str.push_back(c - 'a');
    str.push_back(26);
    reverse((second).begin(), (second).end());
    for (auto& c : second) str.push_back(c - 'a');
    reverse((second).begin(), (second).end());

    suffix_array<POS_INF> sa((str).begin(), (str).end());

    vector<pair<int, int>> suffix_choices;

    for (int suff = 0; suff < ((int((second).size()) - 1)/2 + 1); suff++) {
        int pref = sa.first_occurence_of(int((second).size()) + 1, suff);
        suffix_choices.emplace_back(suff, pref);
    }

    int x = -1, y = 0, pal_begin = -1;

    palindromes pal((second).begin(), (second).end());
    for (int cen = 0; cen < (int((second).size())); cen++) {
        int width = pal.longest_centered_at(cen);

        int suff = prev(lower_bound((suffix_choices).begin(), (suffix_choices).end(), make_pair(cen - width/2, cen + width/2 + 1), [&second](pii suff, pii pal) {
            return (pal.second + suff.first <= int((second).size())) && (pal.first >= suff.second + suff.first);
        }))->first;

        if (2 * suff + width > 2 * x + y) {
            x = suff;
            y = width;
            pal_begin = cen - width/2;
        }
    }

    if (x == 0) {
        ps(1);
        ps(pal_begin + 1, y);
    } else {
        ps(3);
        ps(suffix_choices[x].second + 1, x);
        ps(pal_begin + 1, y);
        ps(int((second).size()) - x + 1, x);
    }



    return 0;
}

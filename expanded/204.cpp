template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
max_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);

template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 27 "data/204.cpp" 2
# 39 "data/204.cpp"

# 39 "data/204.cpp"
typedef long long LL;
typedef std::pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
std::string procStatus()
{
    std::ifstream t("/proc/self/status");
    return std::string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}
template<typename T> T read(T &first)
{
    int f = 1;
    char ch = getchar_unlocked();
    for (; !isdigit(ch); ch = getchar_unlocked())
        if (ch == '-')
            f = -1;
    for (first = 0; isdigit(ch); ch = getchar_unlocked())
        first = 10 * first + ch - '0';
    return first *= f;
}
template<typename T> void write(T first)
{
    if (first == 0) {
        putchar_unlocked('0');
        return;
    }
    if (first < 0) {
        putchar_unlocked('-');
        first = -first;
    }
    static char s[20];
    int top = 0;
    for (; first; first /= 10)
        s[++top] = first % 10 + '0';
    while (top)
        putchar_unlocked(s[top--]);
}


const int MAXN = 2e5 + 5;
const int STEP = 17;

int N;
char S[MAXN];
int max[MAXN][STEP], maxp[MAXN][STEP];
int LOG2[MAXN];

inline Pii querymax(int l, int r)
{
    int k = LOG2[r - l + 1];
    int ret = std::max(max[l][k], max[r - (1 << k) + 1][k]);
    return std::make_pair(ret, ret == max[l][k] ? maxp[l][k] : maxp[r - (1 << k) + 1][k]);
}

void input()
{
    scanf("%s", S + 1);
    N = strlen(S + 1);
}

void solve()
{
    static int fail[MAXN];

    fail[N] = N + 1;
    for (int i = N - 1; i > 0; --i) {
        int p = fail[i + 1];
        while (p != N + 1 && S[p - 1] != S[i]) {
            p = fail[p];
        }
        fail[i] = p - (S[p - 1] == S[i]);
    }

    int mid, bnd = 0;

    S[0] = '$';
    for (int i = 1; i <= N; ++i) {
        int t = i < bnd ? std::min(bnd - i, max[(mid << 1) - i][0]) : 0;
        while (S[i - t - 1] == S[i + t + 1])
            ++t;
        max[i][0] = t;
        maxp[i][0] = i;
        if (chkmax(bnd, i + t - 1))
            mid = i;

    }

    for (int i = 2; i <= N; ++i) {
        LOG2[i] = LOG2[i >> 1] + 1;
    }
    for (int k = 1; (1 << k) <= N; ++k) {
        for (int i = 1; i + (1 << k) - 1 <= N; ++i) {
            max[i][k] = std::max(max[i][k - 1], max[i + (1 << (k - 1))][k - 1]);
            if (max[i][k] == max[i][k - 1])
                maxp[i][k] = maxp[i][k - 1];
            else
                maxp[i][k] = maxp[i + (1 << (k - 1))][k - 1];
        }
    }

    int anslen, first[3], len[3];

    Pii t = querymax(1, N);
    anslen = t.first << 1 | 1;
    first[0] = 0;
    first[1] = t.second - t.first; len[1] = t.first << 1 | 1;

    for (int i = 1, p = N + 1; i <= N; ++i) {
        while (p != N + 1 && S[p - 1] != S[i]) {
            p = fail[p];
        }
        if (S[p - 1] == S[i])
            --p;
        else
            continue;
        int ll = i + 1, rr = p - 1;
        if (ll > rr)
            break;


        int l = 0, r = (rr - ll + 1) >> 1;
        while (l + 1 < r) {
            int mi = (l + r) >> 1;
            int lll = ll + mi, rrr = rr - mi;

            if (lll <= rrr && querymax(lll, rrr).first >= mi)
                l = mi;
            else
                r = mi;
        }


        if (chkmax(anslen, (N - p + 1) * 2 + (l << 1 | 1))) {
            int lll = ll + l, rrr = rr - l;
            t = querymax(lll, rrr);
            first[0] = i - (N - p + 1) + 1; len[0] = N - p + 1;
            first[1] = t.second - l; len[1] = l << 1 | 1;
            first[2] = p; len[2] = N - p + 1;
        }
    }

    if (first[0] == 0)
        printf("1\n%d %d\n", first[1], len[1]);
    else
        printf("3\n%d %d\n%d %d\n%d %d\n", first[0], len[0], first[1], len[1], first[2], len[2]);
}

int main()
{

    freopen("tmp.in", "r", 
# 192 "data/204.cpp" 3 4
                          stdin
# 192 "data/204.cpp"
                               );
    freopen("tmp.out", "w", 
# 193 "data/204.cpp" 3 4
                           stdout
# 193 "data/204.cpp"
                                 );


    input();
    solve();

    return 0;
}

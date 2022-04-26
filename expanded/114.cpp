template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 11 "data/114.cpp" 2




# 14 "data/114.cpp"
using namespace std;

const int maxn = 400000;


string s;
vector< pair<int, int> > ans;
char a[maxn], b[maxn];
int pal[maxn], rpos[maxn], lpos[maxn];
int ext[maxn], n;

void make_pal()
{
    int id = 0, L = 0, R = 0;
    for (int i = 1; i <= n; i ++)
    {
        if (R < i) pal[i] = 0;
        else
        {
            int x = id - (i - id);
            pal[i] = min(R - i, pal[x]);
        }
        while (pal[i] + i < n && i - pal[i] > 1)
            if (a[i + pal[i] + 1] == a[i - pal[i] - 1]) pal[i] ++; else break;
        if (i + pal[i] > R) {L = i - pal[i]; R = i + pal[i]; id = i;}
    }
}

void make_ext()
{
    ext[1] = n * 2 + 1;
    int id = 0, R = 0, m = n * 2 + 1;
    for (int i = 2; i <= m; i ++)
    {
        if (R < i) ext[i] = 0;
        else
        {
            int x = i - id + 1;
            ext[i] = min(ext[x], R - i + 1);
        }
        while (i + ext[i] <= m)
            if (b[i + ext[i]] == b[ext[i] + 1]) ext[i] ++; else break;
        if (i + ext[i] - 1 > R) {R = i + ext[i] - 1; id = i;}
    }
}

void make_pos()
{
    for (int i = 0; i <= n; i ++)
        lpos[i] = n + 1;
    for (int i = 1; i <= n; i ++)
        if (i < lpos[ext[i + n + 1]]) lpos[ext[i + n + 1]] = i;
    for (int i = n - 1; i; i --)
        lpos[i] = min(lpos[i], lpos[i + 1]);
    for (int i = 1; i <= n; i ++)
        rpos[i] = min(lpos[i] + i - 1, n + 1);
}

void make_ans()
{
    int max = 0;
    for (int i = 1; i <= n; i ++)
    {
        int L = i - pal[i], R = i + pal[i];
        vector< pair<int, int> > cur;
        cur.push_back(make_pair(L - 1, R - L + 1));
        int lo = 1, hi = n - R, o = -1;
        while (lo <= hi)
        {
            int mid = (lo + hi) >> 1;
            if (rpos[mid] < L) o = mid;
            if (rpos[mid] < L) lo = mid + 1; else hi = mid - 1;
        }
        int len = R - L + 1;
        if (o != -1)
        {
            len += o * 2;
            cur.push_back(make_pair(rpos[o] - o, o));
            cur.push_back(make_pair(n - o, o));
        }
        if (len > max) {max = len; ans = cur;}
    }
}

int cmp(pair<int, int> a, pair<int, int> b)
{
    return a.first < b.first;
}

int main()
{
    cin >> s;
    n = s.size();
    for (int i = 1; i <= n; i ++)
        a[i] = s[i - 1];
    for (int i = 1; i <= n; i ++)
        b[i] = a[n - i + 1];
    b[n + 1] = '&';
    for (int i = n + 2; i <= n * 2 + 1; i ++)
        b[i] = a[i - n - 1];
    make_pal();
    make_ext();
    make_pos();
    make_ans();

    cout << ans.size() << endl;
    sort(ans.begin(), ans.end(), cmp);
    for (int i = 0; i < ans.size(); i ++)
        cout << ans[i].first + 1 << " " << ans[i].second << endl;
    return 0;
}

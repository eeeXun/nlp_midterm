

  static ios_base::Init __ioinit;


}
# 11 "data/137.cpp" 2

# 11 "data/137.cpp"
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PII;

void ASS(bool b) { if (!b) throw 32; }
struct SH
{
    typedef unsigned long long HT;
    enum {
        k = 3731,
    };
    vector<HT> H;
    vector<HT> K;
    void Init(const char* s, int n)
    {
        H.resize(n + 1);
        K.resize(n + 1);
        H[0] = 0;
        K[0] = 1;
        for (int i = 0; i < (int)(n); ++i)
        {
            H[i + 1] = H[i] * k + s[i];
            K[i + 1] = K[i] * k;
        }
    }
    HT Hash(int a, int b)
    {
        return H[b] - H[a] * K[b - a];
    }
};


int n;
char s[1 << 20];
char rs[1 << 20];

SH h, rh;

int plen[1 << 20];

int MaxLen(int a, int b)
{
    a += n;
    b += n;
    int res = plen[a];
    for (; a < b; a >>= 1, b >>= 1)
    {
        if (a & 1)
            res = max(res, plen[a++]);
        if (b & 1)
            res = max(res, plen[--b]);
    }
    return res;
}
void InitMaxLen()
{
    for (int i = n - 1; i > 0; i--)
        plen[i] = max(plen[i * 2], plen[i * 2 + 1]);
}

int main()
{



    gets(s);
    n = strlen(s);
    strcpy(rs, s);
    reverse(rs, rs + n);
    h.Init(s, n);
    rh.Init(rs, n);


    for (int i = 0; i < n; i++)
    {
        int L = 0;
        int R = min(i, n - i - 1) + 1;
        while (L + 1 < R)
        {
            int m = L + (R - L) / 2;
            if (h.Hash(i - m, i + m) == rh.Hash(n - i - m - 1, n - i + m - 1))
                L = m;
            else
                R = m;
        }
        plen[n + i] = L;
    }
    InitMaxLen();
    int best_suf_len, best_left_end, best_mid_len;
    int best_len = 0;
    int left_end = -1;
    for (int suf_len = 0; suf_len * 2 <= n; suf_len++)
    {
        SH::HT sufh = rh.Hash(0, suf_len);
        left_end++;
        while (left_end + suf_len <= n)
        {
            if (h.Hash(left_end - suf_len, left_end) == sufh)
                break;
            else
                left_end++;
        }
        if (left_end + suf_len >= n)
            break;
        if (h.Hash(left_end - suf_len, left_end) != sufh)
            break;

        int L = 0;
        int R = (n - left_end - suf_len + 1) / 2;
        while (L + 1 < R)
        {
            int m = L + (R - L) / 2;
            int max_len = MaxLen(left_end + m, n - suf_len - m);
            if (max_len >= m)
                L = m;
            else
                R = m;
        }
        int all_len = suf_len * 2 + L * 2 + 1;
        if (all_len > best_len)
        {
            best_len = all_len;
            best_left_end = left_end;
            best_mid_len = L;
            best_suf_len = suf_len;
        }
    }
    vector<PII> res;

    if (best_suf_len > 0)
    {
        res.push_back(PII(best_left_end - best_suf_len, best_suf_len));
        res.push_back(PII(n - best_suf_len, best_suf_len));
    }
    if (best_mid_len >= 0)
    {
        for (int i = best_left_end + best_mid_len; i < n - best_suf_len - best_mid_len; i++)
        {
            if (plen[n + i] >= best_mid_len)
            {
                res.push_back(PII(i - best_mid_len, best_mid_len * 2 + 1));
                break;
            }
        }
    }


    sort(res.begin(), res.end());

    int sum = 0;
    for (int i = 0; i < (int)(res.size()); ++i)
    {
        sum += res[i].second;
        ASS(res[i].second > 0);
    }
    ASS(sum <= n);
    ASS(best_len == sum);

    printf("%d\n", res.size());
    for (int i = 0; i < (int)(res.size()); ++i)
    {
        printf("%d %d\n", res[i].first + 1, res[i].second);
    }
    return 0;
}

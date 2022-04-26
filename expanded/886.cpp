    template<typename _Key, typename _Tp, typename _Cmp = std::less<_Key>>
      using multimap
 = std::multimap<_Key, _Tp, _Cmp,
   polymorphic_allocator<pair<const _Key, _Tp>>>;
  }

}
# 10 "data/886.cpp" 2



# 12 "data/886.cpp"
using namespace std;
template <class T> void show(T a, int n) { for (int i = 0; i < n; ++i) cout << a[i] << ' '; cout << endl; }
template <class T> void show(T a, int r, int l) { for (int i = 0; i < r; ++i) show(a[i], l); cout << endl; }





typedef long long LL;

const int N = 210000;
const int M = 5000;
const int oo = 10000 * 10000 * 10;
const int LOGN = 20;

int n;
char s[N];

int best = -1;
int mpos, suffix_len = 0;
int MLEN;
int lp[N];


void cal_lp(int n, char s[], int lp[])
{
    int i, j, k;
    int a = 0;
    lp[0] = 0;
    for(i = 1; i < n;++i)
    {
        int len = 0;
        if( a + lp[a] - i > 0 )
            len = (lp[2 * a - i] < a + lp[a] - i?lp[2 * a - i]:a + lp[a] - i);
        while(i - len - 1 >= 0 && i + len + 1 < n && s[i - len - 1] == s[i + len + 1])
            ++len;
        lp[i] = len;
        if( i + lp[i] > a + lp[a] )
            a = i;
    }
}

int p[N][LOGN];
int lg[N];
void rmq_init()
{
    int i, j, k;
    lg[0] = -1;
    for(i = 1; i <= n;++i)
        lg[i] = ( i & (i - 1) ) ? lg[i - 1]: lg[i - 1] + 1;
    for(i = 0; i < n;++i)
        p[i][0] = i;
    for(j = 1; (1<<j) <= n;++j)
    {
        for(i = 0; i + (1<<j) - 1 < n;++i)
        {
            if( lp[p[i][j - 1]] > lp[ p[i + (1 << j - 1)][j - 1] ] )
                p[i][j] = p[i][j - 1];
            else
                p[i][j] = p[i + (1 << j - 1)][j - 1];
        }
    }
}

int query(int lf, int hi)
{
    if( lf > hi )
        puts("error");
    int ans;
    int i, j, k;
    j = lg[hi - lf + 1];
    if( lp[ p[lf][j] ] > lp[ p[hi - (1<<j) + 1][j] ] )
        ans = p[lf][j];
    else
        ans = p[hi - (1<<j) + 1][j];

    return ans;
}
int next[N + N];
void prefix_fuction(char *s)
{
    int i, j, k;
    int n = strlen(s);
    next[0] = 0;
    k = 0;
    for(i = 1; i < n;++i)
    {
        while( k > 0 && s[k] != s[i] )
            k = next[k - 1];
        if( s[k] == s[i] )
            ++k;
        next[i] = k;
    }
}

char ts[N + N];
int rpos[N];

int max_pal(int lf, int ri)
{
    if( lf > ri )
        puts("error");
    int la, ra, ma;
    la = 0, ra = (ri - lf) / 2;
    int d;
    while(la < ra)
    {
        ma = (la + ra + 1) / 2;
        d = query(lf + ma, ri - ma);
        if( lp[d] >= ma )
            la = ma;
        else
            ra = ma - 1;
    }

    d = query(lf + la, ri - la);
    return d;
}

int main()
{


    int i, j, cas = 0;
    int k, d;
    scanf("%s", s);
    n = strlen(s);

    cal_lp(n, s, lp);




    rmq_init();
    int tn = 0;
    for(i = n - 1; i >= 0;--i)
        ts[tn++] = s[i];
    ts[tn++] = -1;
    for(i = 0; i < n;++i)
        ts[tn++] = s[i];
    prefix_fuction(ts);
    for(i = 1; i <= n;++i)
        rpos[i] = oo;

    for(i = n + 1; i < n + n + 1;++i)
    {
        rpos[ next[i] ] = (rpos[ next[i] ] < i - n - 1?rpos[ next[i] ]:i - n - 1);
    }






    mpos = max_pal(0, n - 1);


    best = lp[mpos] * 2 + 1;


    for(i = 1; i <= (n - 1) / 2;++i)
    {
        int lf = rpos[i] + 1;
        int ri = n - i - 1;
        if( lf > ri )
            continue;
        d = max_pal(lf, ri);
        int mlen = lp[d];
        mlen = (mlen < (ri - d < d - lf?ri - d:d - lf)?mlen:(ri - d < d - lf?ri - d:d - lf));


        if( 1 + mlen * 2 + i * 2 > best )
        {
            best = 1 + mlen * 2 + i * 2;
            suffix_len = i;
            mpos = d;
            MLEN = mlen;
        }
    }

    if( suffix_len == 0 )
    {
        printf("1\n");
        printf("%d %d\n", mpos - lp[mpos] + 1, 1 + lp[mpos] * 2);
    }
    else
    {
        printf("3\n");
        printf("%d %d\n", rpos[suffix_len] - suffix_len + 2, suffix_len);
        printf("%d %d\n", mpos - MLEN + 1, 1 + MLEN * 2);
        printf("%d %d\n", n - suffix_len + 1, suffix_len);

    }



    return 0;
}

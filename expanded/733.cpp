    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/733.cpp" 2


# 3 "data/733.cpp"
using namespace std;
# 12 "data/733.cpp"
typedef pair<unsigned long long,unsigned long long> PR;

string str, pre;
unsigned long long n, bits[200010], m;
unsigned long long has[2][200010], mul[2][200010], bag[2][200010];
unsigned long long M[] = {1000000007, 141650939};
unsigned long long bm(unsigned long long n, unsigned long long p, unsigned long long m)
{
    if(p == 0) return 1;
    if(p == 1 || n == 1) return n % m;

    unsigned long long ret = bm(n, p/2, m);
    ret = (ret * ret) % m;
    if(p % 2) ret = (ret * n) % m;
    return ret%m;
}

unsigned long long modinv( unsigned long long n, unsigned long long p )
{
    return bm( n, p-2, p );
}

void dude(int ck)
{
    mul[ck][0] = 1;
    bag[ck][0] = modinv(mul[ck][0], M[ck]);
    for(int i=1;i<=n-1;i++)
    {
        mul[ck][i] = mul[ck][i - 1] * 31;
        mul[ck][i] %= M[ck];
        if(i == 1) bag[ck][i] = modinv(mul[ck][i], M[ck]);
        else bag[ck][i] = (bag[ck][i-1] * bag[ck][1]) % M[ck];
    }
}

void info()
{
    for(int ck=0;ck<=1;ck++)
    {
        dude(ck);
        unsigned long long c = 0;
        for(int j=0;j<=n-1;j++)
        {
            c += (unsigned long long)bits[j] * mul[ck][j];
            c %= M[ck];
            has[ck][j] = c;
        }
    }
}

PR ran(unsigned long long l,unsigned long long r)
{
    unsigned long long ret = has[0][r] + M[0];
    if(l) ret -= has[0][l - 1]; ret %= M[0];
    ret *= bag[0][l]; ret %= M[0];

    unsigned long long po = has[1][r] + M[1];
    if(l) po -= has[1][l - 1]; po %= M[1];
    po *= bag[1][l]; po %= M[1];

    return make_pair(ret, po);
}

PR hashVal(string str)
{
    PR ret;
    int n = str.size();

    for(int ck=0;ck<=1;ck++)
    {
        unsigned long long c = 0;
        for(int j=0;j<=n-1;j++)
        {
            unsigned long long v = str[j] - 'a'; v++;
            c += (unsigned long long)v * mul[ck][j];
            c %= M[ck];
        }
        if(!ck) ret.first = c;
        else ret.second = c;
    }
    return ret;
}


PR reverseRan(int l,int r)
{
    return ran(n - r - 1, n - l - 1);
}

int isPalin(int l,int r)
{
    if(ran(l, r) == reverseRan(l, r)) return 1;
    return 0;
}

int centerPoint(int p1,int p2)
{
    int st = 0, en = min(p1, (int)m - (p2 + 1)), mid;

    while(st <= en)
    {
        mid = (st + en)>>1;
        if(isPalin(p1 - mid, p2 + mid)) st = mid + 1;
        else en = mid - 1;
    }

    if(p1 == p2) return 2*st - 1;
    else return 2*st;
}

int cnt[200010], fc[200010], val[200010];
string text;
int lps[200010];

void make_lps(string pattern)
{
    int n = pattern.size();

    lps[0] = lps[1] = 0;
    for(int i=2;i<=n;i++)
    {
        int p = lps[i-1];

        while(true)
        {
            if(pattern[i - 1] == pattern[p])
            {
                lps[i] = p + 1;
                break;
            }

            if(p == 0) break;
            else p = lps[p];
        }
    }

}

int main()
{
    ios::sync_with_stdio(false);

    int l, r, x;


    cin >> str;
    text = str;
    pre = str; reverse(pre.begin(), pre.end());
    str += pre;

    n = str.size(); m = n / 2;

    for(int i=0;i<=n-1;i++)
    {
        unsigned long long x = str[i] - 'a'; x++;
        bits[i] = x;
    }
    info();

    int prin = 0, pos;
    for(int i=0;i<=m-1;i++)
    {
        x = centerPoint(i, i);
        int st = (i - x/2);
        cnt[st] = max(cnt[st], x);
    }

    int v = 0;
    for(int i=0;i<=m-1;i++)
    {
        v = max(v, cnt[i]);
        cnt[i] = v;
        v -= 2;
    }

    string pat = string(text.rbegin(), text.rend()) + "#" + text;

    make_lps( pat );

    memset(fc, -1, sizeof(fc));
    int sz = text.size();

    for(int i=0;i<=text.size()-1;i++)
    {
        int p = sz + i + 1;

        if(lps[p + 1])
            if(fc[ lps[p + 1] ] == -1) fc[ lps[p + 1] ] = i;
    }

    for(int i=1;i<=text.size()-1;i++)
        if(fc[i] != -1) val[ fc[i] ] = i;

    prin = 0;
    int c = 0, k = 0;
    l = 0; m = 0;

    for(int i=0;i<=text.size()-1;i++)
    {

        int x = cnt[i], y = i + x;
        if(x)
        {
            int v = x + min(sz - y, c)*2;
            if(prin < v)
            {
                l = min(sz - y, c);
                prin = v;
                m = i + 1;
            }
        }

        c = max(c, val[i]);
    }
    if(l == 0)cout << 1 << endl << m << ' ' << prin << endl;
    else cout << 3 << endl
        << fc[l] - l + 2 << ' ' << l << endl
        << m << ' ' << prin - l*2 << endl
        << sz - l + 1 << ' ' << l << endl;

    return 0;
}

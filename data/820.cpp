#if 1
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <stack>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <functional>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <cstdio>
using namespace std;

typedef long long LL;



typedef pair<int, int> pii;
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define iss istringstream
#define oss ostringstream
#define dbg(x) cerr << #x << " = " << x << endl;

const LL p = 31;

const int maxn = 500000;
LL ppow[maxn];
char s[maxn];
char t[maxn];

int prefix[maxn];

void calcPrefix(char *p)
{
    int n = strlen(p);
    int k = prefix[0] = -1;
    for(int q = 1; q < n; ++q)
    {
        while(k >= 0 && p[k + 1] != p[q])
            k = prefix[k];
        if(p[k + 1] == p[q])
            k++;
        prefix[q] = k;
    }
}
LL hs[maxn], ht[maxn];
void calcHash(LL *h, char *s, int n)
{
    h[0] = 0;
    for(int i = 0; i < n; ++i)
        h[i + 1] = h[i] * p + (s[i] - 'a' + 1);
}

bool compare(LL *hs, LL *ht, int i, int j, int len)
{
    LL h1 = hs[i] - hs[i - len] * ppow[len];
    LL h2 = ht[j] - ht[j - len] * ppow[len];
    return h1 == h2;
}
LL palin[maxn];

int f[maxn], fn;
int wh[maxn];
void finit(int n)
{
    memset(f, -1, sizeof f);
    memset(wh, 0, sizeof wh);
    fn = n;
}
void fmodify(int r, int v)
{
    for(int i = r; i < fn; i |= i + 1)
    {
        if(f[i] < v)
            f[i] = v,
            wh[i] = r;
    }
}
pii fmax(int r)
{
    int res = -1;
    int pos = 0;
    for(int i = r; i >= 0; i &= i + 1, --i)
        if(res < f[i])
            res = f[i],
            pos = wh[i];
        
    return mp(res, pos);
}
int main()
{
    ppow[0] = 1;
    for(int i = 1; i < maxn; ++i)
        ppow[i] = ppow[i - 1] * p;
    
    gets(s);
    int n = strlen(s);
    if(n == 1)
    {
        cout << 1 << endl;
        cout << 1 << " " << 1 << endl;
        return 0;
    }
    for(int i = 0; i < n; ++i)
        t[i] = s[n - 1 - i];
    t[n] = 0;

    calcHash(hs, s, n);
    calcHash(ht, t, n);

    for(int i = 0; i < n; ++i)
    {
        int j = n - i - 1;
        int l = 0, r = min((n + 1) / 2, min(i + 1, j + 1)) + 1;
        while(l + 1 < r)
        {
            int m = (l + r) / 2;
            if(compare(hs, ht, i + 1, j + 1, m))
                l = m;
            else
                r = m;
        }
        palin[i] = l;
    }


    t[n] = '$';
    int ct = n + 1;
    for(int i = 0; i < n; ++i)
        t[ct++] = s[i];
    t[ct] = 0;
    calcPrefix(t);
    finit(n);
    for(int i = n + 1; i < ct; ++i)
        fmodify(i - (n + 1), prefix[i]);

    int mlen = 0;
    int p1, l1, p2, l2, p3, l3;
    p1 = l1 = p2 = l2 = p3 = l3 = 0;
    for(int i = 0; i < n; ++i)
    {
        int r = palin[i];
        int le = i - r;
        int ri = i + r;
        pii res = fmax(le);
        int w = res.X + 1;
        le = res.Y;
        w = min(min(w, n - ri), le + 1);
        if(2 * w + 2 * r - 1 > mlen)
        {
            mlen = 2 * w + 2 * r - 1;
            p1 = le - w + 1;
            l1 = w;
            p2 = i - r + 1;
            l2 = 2 * r - 1;
            p3 = n - 1 - w + 1;
            l3 = w;
        }
    }

    int cnt = 0;
    if(l1) cnt++;
    if(l2) cnt++;
    if(l3) cnt++;
    assert(cnt == 1 || cnt == 3);
    cout << cnt << endl;
    if(l1)
        cout << p1 + 1 << " " << l1 << endl;
    if(l2)
        cout << p2 + 1 << " " << l2 << endl;
    if(l3)
        cout << p3 + 1 << " " << l3 << endl;




    return 0;
}
#endif
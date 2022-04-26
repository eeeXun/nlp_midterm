#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
#define rep(x, n) for (int x = 1; x <= n; ++x)
#define zrp(x, n) for (int x = n; x; --x)
#define FOR(x, l, r) for (int x = l; x <= r; ++x)
#define foredge(i, x) for (int i = start[x]; i; i = e[i].l)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(a) ((a) > 0 ? (a) : (-(a)))
typedef long long int64;
const int maxN = 100005;
int n, now, r[maxN], f[maxN], next[maxN];
char s[maxN], c[maxN];
priority_queue<int> QL;
priority_queue<int, vector<int>, greater<int> > QR;
struct Tmid
{
    int x;
    bool operator<(const Tmid &o)const
    {
        return r[x] < r[o.x];
    }
};
priority_queue<Tmid> QM;

void init()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    rep(i, n) c[n - i + 1] = s[i];
    
    //kmp
    int j = 0;
    FOR(i, 2, n)
    {
        while (j && c[j + 1] != c[i])
            j = next[j];
        if (c[j + 1] == c[i]) ++j;
        next[i] = j;
    }
    j = 0;
    rep(i, n)
    {
        while (j && c[j + 1] != s[i])
            j = next[j];
        if (c[j + 1] == s[i]) ++j;
        f[i] = j;
    }
    
    //manacher
    s[0] = -1; s[n + 1] = -2;
    int k = 0;
    rep(i, n)
    {
        if (k + r[k] >= i)
            r[i] = min(k + r[k] - i, r[2 * k - i]);
        else r[i] = 0;
        while (s[i - r[i] - 1] == s[i + r[i] + 1])
            ++r[i];
        if (i + r[i] > k)
            k = i;
    }
}

int getBest(int pl, int pr)
{
    int x, s = 0;
    while (QM.size())
    {
        x = QM.top().x;
        if (x - r[x] <= pl || x + r[x] >= pr)
        {
            QM.pop();
            if (x - r[x] <= pl) QL.push(x);
            if (x + r[x] >= pr) QR.push(x);
        }
        else break;
    }
    if (QM.size() && r[x] * 2 + 1 > s)
        s = r[x] * 2 + 1, now = x;
    
    while (QL.size())
    {
        x = QL.top();
        if (x + r[x] >= pr || x <= pl) QL.pop();
            else break;
    }
    if (QL.size() && (x - pl) * 2 - 1 > s)
        s = (x - pl) * 2 - 1, now = x;
    
    while (QR.size())
    {
        x = QR.top();
        if (x - r[x] <= pl || x >= pr) QR.pop();
            else break;
    }
    if (QR.size() && (pr - x) * 2 - 1 > s)
        s = (pr - x) * 2 - 1, now = x;
    
    return s;
}

void work()
{
    int ans = 0, al, ar, am;
    int pl = 1, tmp;
    rep(i, n) QM.push((Tmid){i});
    zrp(pr, n)
    {
        while (pl <= n && f[pl] != (n - pr + 1))
            ++pl;
        if (pl >= pr) break;
        tmp = getBest(pl, pr);
        if (tmp == 0) break;
        if ((n - pr + 1) * 2 + tmp > ans)
        {
            ans = (n - pr + 1) * 2 + tmp;
            al = pl; ar = pr; am = now;
        }
    }
    
    int x = 1;
    rep(i, n) if (r[i] > r[x]) x = i;
    
    if (r[x] * 2 + 1 > ans)
    {
        printf("%d\n", 1);
        printf("%d %d\n", x - r[x], r[x] * 2 + 1);
    }
    else
    {
        printf("%d\n", 3);
        printf("%d %d\n", al - n + ar, (n - ar + 1));
        r[am] = min(r[am], min(am - al - 1, ar - am - 1));
        printf("%d %d\n", am - r[am], r[am] * 2 + 1);
        printf("%d %d\n", ar, (n - ar + 1));
    }
}

int main()
{
    init();
    work();
    return 0;
}

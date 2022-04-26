

}
# 65 "/usr/include/c++/11.2.0/queue" 2 3
# 8 "data/140.cpp" 2

# 8 "data/140.cpp"
using namespace std;







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
    for (int i = 1; i <= n; ++i) c[n - i + 1] = s[i];


    int j = 0;
    for (int i = 2; i <= n; ++i)
    {
        while (j && c[j + 1] != c[i])
            j = next[j];
        if (c[j + 1] == c[i]) ++j;
        next[i] = j;
    }
    j = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (j && c[j + 1] != s[i])
            j = next[j];
        if (c[j + 1] == s[i]) ++j;
        f[i] = j;
    }


    s[0] = -1; s[n + 1] = -2;
    int k = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (k + r[k] >= i)
            r[i] = ((k + r[k] - i) < (r[2 * k - i]) ? (k + r[k] - i) : (r[2 * k - i]));
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
    for (int i = 1; i <= n; ++i) QM.push((Tmid){i});
    for (int pr = n; pr; --pr)
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
    for (int i = 1; i <= n; ++i) if (r[i] > r[x]) x = i;

    if (r[x] * 2 + 1 > ans)
    {
        printf("%d\n", 1);
        printf("%d %d\n", x - r[x], r[x] * 2 + 1);
    }
    else
    {
        printf("%d\n", 3);
        printf("%d %d\n", al - n + ar, (n - ar + 1));
        r[am] = ((r[am]) < (((am - al - 1) < (ar - am - 1) ? (am - al - 1) : (ar - am - 1))) ? (r[am]) : (((am - al - 1) < (ar - am - 1) ? (am - al - 1) : (ar - am - 1))));
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

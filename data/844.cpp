#include<bits/stdc++.h>

#define sp putchar(' ')
#define ln putchar('\n')
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

typedef long long ll;
typedef std::pair<int, int> pii;

template<typename T>inline bool chkmin(T &a, T b){return b < a ? a = b, true : false;}
template<typename T>inline bool chkmax(T &a, T b){return b > a ? a = b, true : false;}

template<class T> inline T read(T &x)
{
    int sign = 1;
    char c = getchar();
    for(; !isdigit(c); c = getchar())
        if(c == '-')
            sign = -1;
    for(x = 0; isdigit(c); c = getchar())
        x = x * 10 + c - '0';
    return x *= sign;
}
template<class T> inline void write(T x)
{
    if(x == 0) {putchar('0'); return;}
    if(x < 0) {putchar('-'); x = -x;}
    static char s[20];
    int top = 0;
    for(; x; x /= 10)
        s[++ top] = x % 10 + '0';
    while(top)
        putchar(s[top --]);
}

const int maxN = 1e6 + 100;

char s[maxN], rs[maxN];
int fail[maxN], p[maxN], pos[maxN], Log2[maxN], f[maxN][20];
int len;

int querymax(int l, int r)
{
    if(l > r) return -978;
    int len = Log2[r - l + 1];
    return std::max(f[l][len], f[r - (1 << len) + 1][len]);
}

int get(int L, int R)
{
    int l = 0, r = (R - L + 1) / 2 + 1, mid;
    while(l + 1 != r)
        mid = (l + r) >> 1, querymax(L + mid, R - mid) >= mid ? l = mid : r = mid;
    return l * 2 + 1;
}

int getequal(int l, int r, int val)
{
    for(int i = l; i <= r; ++i)
        if(p[i] == val)
            return i;
    return -978;
}

void Print(int be, int le)
{
    for(int i = be; i < be + le; ++i)
        putchar(s[i]);
}

int main()
{
    if(fopen("tmp.in", "r")) {
        freopen("tmp.in", "r", stdin);
        freopen("tmp.out", "w", stdout);
    }

    scanf("%s", s + 1);
    int len = strlen(s + 1);
    memcpy(rs + 1, s + 1, sizeof(*s) * len);
    std::reverse(rs + 1, rs + len + 1);

    //Manacher
    s[0] = '#';
    int mx = 0, id = 0;
    for(int i = 1; i <= len; ++i) {
        if(mx > i)
            p[i] = std::min(mx - i, p[id + id - i]);
        else
            p[i] = 0;
        for(; s[i + p[i] + 1] == s[i - p[i] - 1]; ++ p[i]);
        if(chkmax(mx, p[i] + i)) id = i;
    }

    //Prepare for RMQ
    for(int i = 2; i <= len; ++i) Log2[i] = Log2[i >> 1] + 1;
    for(int i = 1; i <= len; ++i) f[i][0] = p[i];
    for(int i = 1; (1 << i) <= len; ++i)
        for(int j = 1; j + (1 << i) - 1 <= len; ++j)
            f[j][i] = std::max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);

    //Prepare for KMP(between origin and reverse)
    fail[1] = fail[2] = 1;
    for(int i = 2; i <= len; ++i) {
        int j = fail[i];
        while(j != 1 && rs[j] != rs[i]) j = fail[j];
        fail[i + 1] = j + (rs[j] == rs[i]);
    }

    memset(pos + 1, 0x3f, sizeof(*pos) * len);
    for(int i = 1; i <= len; ++i) {
        static int j = 1;
        while(j != 1 && s[i] != rs[j]) j = fail[j];
        j += s[i] == rs[j];
        if(j > 1)
            chkmin(pos[len - (j - 1) + 1], i);
    }

    //Main
    int ans = 0;
    for(int i = len + 1; i >= 1; --i)
        if(pos[i] < i - 1) {
            int tmp = get(pos[i] + 1, i - 1) + (len - i + 1) * 2;
            chkmax(ans, tmp);
        }

    for(int i = len + 1; i >= 1; --i)
        if(pos[i] < i - 1) {
            int tmp = get(pos[i] + 1, i - 1) + (len - i + 1) * 2;
            if(ans == tmp) {
                if(i == len + 1) {
                    puts("1");
                    tmp /= 2;
                    write(getequal(1 + tmp, len - tmp, tmp) - tmp), sp, write(tmp * 2 + 1), ln;
                } else {
                    puts("3");
                    write(pos[i] - (len - i + 1) + 1), sp, write(len - i + 1), ln;
                    tmp = get(pos[i] + 1, i - 1) / 2;
                    write(getequal(pos[i] + tmp + 1, i - tmp - 1, tmp) - tmp), sp, write(tmp * 2 + 1), ln;
                    write(i), sp, write(len - i + 1), ln;
                }
                return 0;
            }
        }


    return 0;
}

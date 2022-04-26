// Copyright (C) 2016 __debug.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string>

#define x first
#define y second
#define MP std::make_pair
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

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
template<typename T> T read(T &x)
{
    int f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (x = 0; isdigit(ch); ch = getchar())
        x = 10 * x + ch - '0';
    return x *= f;
}
template<typename T> void write(T x)
{
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[20];
    int top = 0;
    for (; x; x /= 10)
        s[++top] = x % 10 + '0';
    while (top)
        putchar(s[top--]);
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
    return MP(ret, ret == max[l][k] ? maxp[l][k] : maxp[r - (1 << k) + 1][k]);
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
        // printf("max(%d) = %d\n", i, max[i][0]);
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

    int anslen, x[3], len[3];

    Pii t = querymax(1, N);
    anslen = t.x << 1 | 1;
    x[0] = 0;
    x[1] = t.y - t.x; len[1] = t.x << 1 | 1;

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
        // printf("when i = %d, p = %d\n", i, p);

        int l = 0, r = (rr - ll + 1) >> 1;
        while (l + 1 < r) {
            int mi = (l + r) >> 1;
            int lll = ll + mi, rrr = rr - mi;
            // printf("when mi = %d, lll = %d, rrr = %d, query = %d\n", mi, lll, rrr, querymax(lll, rrr).x);
            if (lll <= rrr && querymax(lll, rrr).x >= mi)
                l = mi;
            else
                r = mi;
        }
        // printf("curlen = %d\n", (N - p + 1) * 2 + l);

        if (chkmax(anslen, (N - p + 1) * 2 + (l << 1 | 1))) {
            int lll = ll + l, rrr = rr - l;
            t = querymax(lll, rrr);
            x[0] = i - (N - p + 1) + 1; len[0] = N - p + 1;
            x[1] = t.y - l;             len[1] = l << 1 | 1;
            x[2] = p;                   len[2] = N - p + 1;
        }
    }

    if (x[0] == 0)
        printf("1\n%d %d\n", x[1], len[1]);
    else
        printf("3\n%d %d\n%d %d\n%d %d\n", x[0], len[0], x[1], len[1], x[2], len[2]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("tmp.in", "r", stdin);
    freopen("tmp.out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}

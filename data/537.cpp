#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define sqr(x) ((x) * (x))
#define two(x) (1 << (x))
#define ord(x, y, z) ((x) <= (y) && (y) <= (z))
#define X first
#define Y second

typedef long long LL;
typedef pair<int, int> pair2;

const int N = 110000;
const double eps = 1e-9;
const int oo = 1000000000;

int n, next[N], f[N], a[N], far[N];
char str[N], nst[N];

void init() {
    scanf("%s", str);
    n = strlen(str);
    for (int i = 0; i < n; ++i) {
        nst[i] = str[n - 1 - i];
    }
    nst[n] = 0;
}

void kmp() {
    for (int i = 0; i < n; ++i) {
        next[i] = -1;
        for (int j = i - 1; j != -1; j = next[j]) if (nst[i] == nst[next[j] + 1]) {
            next[i] = next[j] + 1;
            break;
        }
    }
    int x = -1;
    memset(f, 0, sizeof(f));
    memset(a, 0, sizeof(a));
    for (int i = 0; i < n; ++i) {
        while (x != -1 && str[i] != nst[x + 1]) {
            x = next[x];
        }
        if (str[i] == nst[x + 1]) {
            ++x;
        }
        f[i + 1] = x + 1;
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = f[i] > f[a[i - 1]]? i: a[i - 1];
    }
}

void get_palin() {
    far[1] = 1;
    int fi = 1, ft = 1;
    for (int i = 2; i <= n; ++i) {
        far[i] = 1;
        if (ft >= i) {
            far[i] = min(far[2 * fi - i], ft - i + 1);
        }
        while (i - (far[i] + 1) + 1 >= 1 && i + (far[i] + 1) - 1 <= n && str[i + far[i] - 1] == str[i - far[i] - 1]) {
            far[i] += 1;
        }
        if (i + far[i] - 1 > ft) {
            ft = i + far[i] - 1;
            fi = i;
        }
    }
}

void solve() {
    int ans0 = 1, ans1 = 0, s0 = 1, s1 = -1;
    for (int i = 1; i <= n; ++i) {
        int li = a[i - far[i]]; 
        int le = min(n - (i + far[i] - 1), f[li]); 
        if (far[i] * 2 - 1 + le * 2 > ans0 + ans1 * 2) {
            ans0 = far[i] * 2 - 1;
            ans1 = le;
            s0 = i - far[i] + 1;
            s1 = li - ans1 + 1;
        }
    }
    printf("%d\n", ans1 > 0? 3: 1);
    if (ans1 != 0) {
        printf("%d %d\n", s1, ans1);
    }
    printf("%d %d\n", s0, ans0); 
    if (ans1 != 0) {
        printf("%d %d\n", n - ans1 + 1, ans1);
    }
}

int main() {
    init();
    kmp();
    get_palin();
    //for (int i = 1; i <= n; ++i) cout << far[i] << ' ';cout << endl;
    solve();
    return 0;
}

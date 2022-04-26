




# 8 "data/419.cpp"
using namespace std;

template <class T>
inline void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    if (f) x = -x;
}

const int N = 500005;
char s[N];
int pr[N], n;
struct Match { int l, r, len; } mt[N];
struct Answer { int l, r, p, su, val; } ans;

namespace Manacher {
    char t[N]; int r[N], len;
    inline void init(char* s) {
        for (int i = 1; i <= n; i++)
            t[++len] = '#', t[++len] = s[i]; t[++len] = '#';
    }
    inline void realmain() {
        int mx = 0, p = 0;
        for (int i = 1; i <= len; i++) {
            if (mx > i) r[i] = ((r[2 * p - i]) < (mx - i) ? (r[2 * p - i]) : (mx - i)); else r[i] = 1;
            while (r[i] < i && i + r[i] - 1 <= len && t[i - r[i]] == t[i + r[i]]) ++r[i];
            if (i + r[i] - 1 > mx) mx = i + r[i] - 1, p = i;
        }
        for (int i = 2; i <= len; i += 2) pr[i / 2] = r[i] / 2;
    }
}
namespace KMP {
    char t[N]; int nxt[N];
    inline void init(char* s) {
        for (int i = 1; i <= n; i++) t[i] = s[n - i + 1];
        nxt[0] = -1;
        for (int i = 1, j = -1; i <= n; nxt[i++] = ++j)
            while (t[j + 1] != t[i] && ~j) j = nxt[j];
    }
    inline void realmain(char* s) {
        for (int i = 1, j = 0; i <= n; i++) {
            while (t[j + 1] != s[i] && ~j) j = nxt[j];
            mt[i].len = ++j, mt[i].r = i, mt[i].l = i - j + 1;
        }
        for (int i = 1; i <= n; i++)
            if (mt[i - 1].len > mt[i].len) mt[i] = mt[i - 1];
    }
}
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    KMP::init(s), KMP::realmain(s);
    Manacher::init(s), Manacher::realmain();
    for (int i = 1; i <= n; i++) {
        int pos = i - pr[i], suf = min(mt[pos].len, n - i - pr[i] + 1);
        int res = 2 * (pr[i] + suf) - 1;
        if (res > ans.val)
            ans = { mt[pos].l, mt[pos].r, i, suf, res }
    ;
    }
    int l1 = ans.l, r1 = ans.r;
    int l2 = ans.p - pr[ans.p] + 1, r2 = ans.p + pr[ans.p] - 1;
    int l3 = n - ans.su + 1, r3 = n, tot = 3;
    r1 = min(r1, l2 - 1), l3 = max(l3, r2 + 1);
    if (r1 < l1 || !l1 || !r1) tot--;
    if (l3 > r3 || l3 > n || r3 > n) tot--;
    cout << tot << endl;
    if (l1 <= r1 && l1 && r1) cout << l1 << " " << r1 - l1 + 1 << endl;
    cout << l2 << " " << r2 - l2 + 1 << endl;
    if (l3 <= r3 && l3 <= n && r3 <= n) cout << l3 << " " << r3 - l3 + 1 << endl;
    return 0;
}

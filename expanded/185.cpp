# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/185.cpp" 2

# 5 "data/185.cpp"
using namespace std;

const int maxn = 100005;
char sa[maxn], sb[maxn];
int pal[maxn], next[maxn], pre[maxn];

int main () {
    int n, i, j, t;
    scanf ("%s", sa + 1), n = strlen(sa + 1);
    for (i = 2, t = 1, pal[1] = 1; i <= n; ++i) {
        j = t * 2 - i;
        pal[i] = min(pal[j], j - t + pal[t]);
        for (; i > pal[i] && sa[i - pal[i]] == sa[i + pal[i]]; ++pal[i]);
        if (i + pal[i] > t + pal[t]) t = i;
    }
    for (i = 1; i <= n; ++i)
        sb[i] = sa[n + 1 - i];
    for (i = 2, j = 0, next[0] = -1; i <= n; ++i) {
        for (; ~j && sb[i] != sb[j + 1]; j = next[j]);
        next[i] = ++j;
    }
    for (i = 1, j = 0; i <= n; ++i) {
        for (; ~j && sa[i] != sb[j + 1]; j = next[j]);
        pre[i] = ++j;
    }
    for (i = 1; i <= n; ++i)
        pre[i] = max(pre[i - 1], pre[i]);
    int ans = 0;
    for (i = n; i; --i)
        ans = max(ans, pal[i] + min(pre[i - pal[i]], n + 1 - i - pal[i]));
    for (i = 1; i <= n; ++i)
        if (pal[i] == ans)
            return printf("1\n%d %d\n", i - pal[i] + 1, pal[i] * 2 - 1), 0;
        else if (pal[i] + min (pre[i - pal[i]], n + 1 - i - pal[i]) == ans) {
            printf("3\n");
            for (j = 1; j <= n && pre[j] != pre[i - pal[i]]; ++j);
            printf("%d %d\n", j - pre[j] + 1, pre[j]);
            printf("%d %d\n", i - pal[i] + 1, pal[i] * 2 - 1);
            printf("%d %d\n", n - pre[j] + 1, pre[j]);
            return 0;
        }
    printf("%d\n", ans * 2 - 1);
    return 0;
}

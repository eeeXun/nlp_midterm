# 4 "data/173.cpp" 2


# 5 "data/173.cpp"
using namespace std;

const int MAXN = 111111;

char a[MAXN], b[MAXN];
int id[MAXN], p[MAXN], q[MAXN], r[MAXN];

int main() {
    scanf("%s", a + 1);
    int n = strlen(a + 1);
    a[0] = '$';
    for (int i = 1; i <= n; ++i)
        b[i] = a[n - i + 1];
    for (int i = 2, j = 0; i <= n; ++i) {
        for (; j && b[j + 1] != b[i]; j = p[j]);
        p[i] = j += b[j + 1] == b[i];
    }
    for (int i = 1, j = 0; i <= n; ++i) {
        for (; j && b[j + 1] != a[i]; j = p[j]);
        q[i] = j += b[j + 1] == a[i];
        id[i] = q[i] > q[id[i - 1]] ? i : id[i - 1];
    }
    int u = 0, mx = 0, ans = 0, bg, len, mid;
    for (int i = 1; i <= n; ++i) {
        r[i] = mx > i ? min(r[2 * u - i], mx - i) : 1;
        for (; a[i - r[i]] == a[i + r[i]]; ++r[i]);
        if (i + r[i] > mx)
            mx = i + r[u = i];
        int tlen = min(n - i - r[i] + 1, q[id[i - r[i]]]), tmp = 2 * r[i] - 1 + 2 * tlen;
        if (tmp > ans)
            ans = tmp, bg = id[i - r[i]] - q[id[i - r[i]]] + 1, len = tlen, mid = i;
    }
    if (len)
        printf("3\n%d %d\n%d %d\n%d %d\n", bg, len, mid - r[mid] + 1, 2 * r[mid] - 1, n - len + 1, len);
    else
        printf("1\n%d %d\n", mid - r[mid] + 1, 2 * r[mid] - 1);
    return 0;
}

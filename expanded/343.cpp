}
# 5 "data/343.cpp" 2

# 5 "data/343.cpp"
using namespace std;

char a[100005] , b[100005];
int n , j , id , maxid , f[100005] , g[100005] , en[100005] , t , l , fm , fl , len , p1[100005] , p[100005] , ans;

int main()
{
    scanf("%s" , a);
    n = strlen(a);
    for (int i = n; i; --i)
        a[i] = a[i - 1];
    for (int i = 1; i <= n; ++i)
        b[i] = a[n + 1 - i];
    p1[1] = j = 0;
    for (int i = 2; i <= n; ++i) {
        while (j > 0 && b[j + 1] != b[i])
            j = p1[j];
        if (b[j + 1] == b[i]) ++j;
        p1[i] = j;
    }
    for (int i = 1; i <= n; ++i) {
        if (maxid > i) p[i] = min(p[2 * id - i] , maxid - i); else p[i] = 1;
        while (i - p[i] > 0 && i + p[i] <= n && a[i + p[i]] == a[i - p[i]]) ++p[i];
        if (p[i] + i > maxid) {
            maxid = p[i] + i;
            id = i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        j = f[i - 1];
        while (j && a[i] != b[j + 1])
            j = p1[j];
        if (a[i] == b[j + 1]) ++j;
        f[i] = j;
    }
    for (int i = 1; i <= n; ++i) {
        g[i] = g[i - 1] , en[i] = en[i - 1];
        if (f[i] > g[i]) {
            g[i] = f[i] , en[i] = i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        l = i - p[i];
        t = min(g[l] , n - i - p[i] + 1);
        if (p[i] * 2 - 1 + t * 2 > ans) {
            ans = p[i] * 2 - 1 + t * 2;
            fm = i , fl = en[l] , len = t;
        }
    }
    if (len) printf("3\n%d %d\n%d %d\n%d %d\n" , fl - len + 1 , len , fm - p[fm] + 1 , p[fm] * 2 - 1 , n - len + 1 , len); else printf("1\n%d %d\n" , fm - p[fm] + 1 , p[fm] * 2 - 1);
}

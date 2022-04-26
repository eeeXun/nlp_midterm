
#pragma GCC visibility pop
# 1928 "/usr/include/c++/11.2.0/cmath" 2 3


}
# 14 "data/358.cpp" 2
# 1 "/usr/include/c++/11.2.0/ctime" 1 3
# 39 "/usr/include/c++/11.2.0/ctime" 3
       
# 40 "/usr/include/c++/11.2.0/ctime" 3
# 15 "data/358.cpp" 2



# 17 "data/358.cpp"
const int NUM = 100010;
const double eps = 1e-10, pi = acos(-1.0);
using namespace std;
typedef pair <int, int> P;
typedef long long LL;
typedef unsigned long long uLL;
char s[NUM];
int next[NUM], p[NUM], f[NUM], g[NUM], ans, n;

int main()
{




    int i, j, k, m, q;
    scanf("%s", s + 1);
    s[0] = '$';
    n = strlen(s);
    next[i = n - 1] = j = n;
    while(i > 0)
    {
        while(j < n && s[i] != s[j]) j = next[j];
        if(s[--i] == s[--j]) next[i] = next[j];
        else next[i] = j;
    }
    for(i = 1, j = n - 1; i < n; i++, j--)
    {
        while(j < n && s[i] != s[j]) j = next[j];
        f[i] = n - j;
        if(f[i] > f[i - 1]) g[i] = i - f[i] + 1;
        else f[i] = f[i - 1], g[i] = g[i - 1];
    }
    for(i = 1, j = 0; i < n; i++)
    {
        p[i] = j > i ? min(p[(k<<1) - i], j - i) : 1;
        while(s[i + p[i]] == s[i - p[i]]) ++p[i];
        if(p[i] + i > j) j = p[i] + (k = i);
    }
    for(i = 1; i < n; i++)
    {
        q = min(f[i - p[i]], n - i - p[i]) + p[i];
        if(q > ans) ans = q, m = i;
    }
    i = min(f[m - p[m]], n - m - p[m]);
    if(i)
        printf("3\n%d %d\n%d %d\n%d %d\n", g[m - p[m]], i, m - p[m] + 1, 2*p[m] - 1, n - i, i);
    else
        printf("1\n%d %d\n", m - p[m] + 1, 2*p[m] - 1);
    return 0;
}

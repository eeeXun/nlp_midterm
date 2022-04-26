    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 11 "data/56.cpp" 2


# 12 "data/56.cpp"
using namespace std;





typedef long long ll;
typedef pair < int, int > ii;

const int inf = 1e9 + 333;
const ll linf = 1e18 + 333;

const int N = 1e5 + 5;
const int P = 29;
const int mod = 1e9 + 7;

int n, fo[N];
ll power[N], ___hash[N], rhash[N];
char s[N];

int get(int x, int y) {
    return (___hash[y] + mod - ___hash[x - 1] * power[y - x + 1] % mod) % mod;
}

int rget(int x, int y) {
    return (rhash[x] + mod - rhash[y + 1] * power[y - x + 1] % mod) % mod;
}

int main () {

    scanf("%s", s + 1);

    n = strlen(s + 1);

    power[0] = 1;

    for(int i = 1; i <= n; i++) {
        power[i] = power[i - 1] * P % mod;
        ___hash[i] = (___hash[i - 1] * P + s[i] - 'a' + 1) % mod;
    }

    for(int i = n; i >= 1; i--)
        rhash[i] = (rhash[i + 1] * P + s[i] - 'a' + 1) % mod;

    fo[0] = 1;

    for(int i = 1; i <= n; i++) {
        fo[i] = fo[i - 1];
        while(fo[i] != -1 and fo[i] + i - 1 < n - i + 1 and get(n - i + 1, n) != rget(fo[i], fo[i] + i - 1))
            fo[i]++;
        if(fo[i] + i - 1 >= n - i + 1)
            fo[i] = -1;

    }

    int ans = 0, ans1, ans2, ans3, ansl;

    for(int i = 1; i <= n; i++) {
        int l = 1, r = min(i, n - i + 1);
        while(l + 1 < r) {
            int m = l + r >> 1;
            if(get(i - m + 1, i) == rget(i, i + m - 1))
                l = m;
            else
                r = m - 1;
        }
        if(get(i - r + 1, i) == rget(i, i + r - 1))
            l = r;
        int len = l + l - 1, b = i - l + 1, e = i + l - 1;
        l = 0, r = min(b - 1, n - e);
        while(l + 1 < r) {
            int m = l + r >> 1;
            if(fo[m] != -1 and fo[m] + m - 1 < b)
                l = m;
            else
                r = m - 1;
        }
        if(fo[r] != -1 and fo[r] + r - 1 < b)
            l = r;

        if(len + l + l > ans) {
            ans = len + l + l;
            ans1 = fo[l];
            ans2 = b;
            ans3 = n - l + 1;
            ansl = l;
        }
    }

    if(ans3 == n + 1) {
        puts("1");
        printf("%d %d\n", ans2, ans);
    }
    else {
        puts("3");
        printf("%d %d\n", ans1, ansl);
        printf("%d %d\n", ans2, ans - ansl - ansl);
        printf("%d %d\n", ans3, ansl);
    }

    return 0;

}

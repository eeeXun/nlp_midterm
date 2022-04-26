# 6 "data/284.cpp"
using namespace std;

long long mod = 1000000007;
long long x = 234524543;

char s[100040];
long long powx[100040];
long long lhash[100040];
long long rhash[100040];

int n;
map <long long, int> index;
int start[4], l[4];

long long get_lhash(int a, int b)
{
    long long h = lhash[b + 1] - lhash[a] * powx[b - a + 1];
    h %= mod;
    h += mod;
    h %= mod;
    return h;
}

long long get_rhash(int a, int b)
{
    long long h = rhash[n - a] - rhash[n - b - 1] * powx[b - a + 1];
    h %= mod;
    h += mod;
    h %= mod;
    return h;
}

bool is_palindrome(int a, int b)
{
    return get_lhash(a, b) == get_rhash(a, b);
}

pair <int, int> long_palindrome(int a, int b)
{
    pair <int, int> best;
    int low = 1;
    int high = (b - a + 1 + 1) / 2;
    while (high >= low)
    {
        int mid = (low + high) / 2;
        int len = 2 * mid - 1;
        bool flag = false;
        for (int k = a; k <= b - len + 1; k++)
        {
            if (is_palindrome(k, k + len - 1))
            {
                flag = true;
                best.first = k;
                best.second = len;
                break;
            }
        }
        if (flag)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return best;
}

pair <int, int> best_sub()
{
    pair <int, int> best;
    int low = 0;
    int high = (n - 1) / 2;
    while (high >= low)
    {
        int mid = (low + high) / 2;
        long long goal_hash = get_lhash(n - mid, n - 1);
        bool flag = false;
        for (int i = 0; i < n - mid - mid; i++)
        {
            if (get_rhash(i, i + mid - 1) == goal_hash)
            {
                flag = true;
                best.first = i;
                best.second = mid;
                break;
            }
        }
        if (flag)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return best;
}

int main()
{
    scanf("%s", s);
    n = strlen(s);
    lhash[0] = 0;
    powx[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        powx[i] = powx[i - 1] * x;
        powx[i] %= mod;
    }
    for (int i = 0; i < n; i++)
    {
        lhash[i + 1] = lhash[i] * x + (long long) s[i];
        lhash[i + 1] %= mod;
    }
    rhash[0] = 0;
    for (int i = 0; i < n; i++)
    {
        rhash[i + 1] = rhash[i] * x + (long long) s[n - i - 1];
        rhash[i + 1] %= mod;

    }
    pair <int, int> p1 = long_palindrome(0, n - 1);
    pair <int, int> p2 = best_sub();
    pair <int, int> p3 = long_palindrome(p2.first + p2.second, n - p2.second - 1);
    int j = 0;
    int bestlen = 0;
    bool prev = false;
    for (int i = 0; i < n; i++)
    {
        prev = false;
        while (j < n - j + i - 2 && get_lhash(i, j) == get_rhash(n - j + i - 1, n - 1))
        {
            bestlen = j - i + 1;
            prev = true;
            j++;
        }
        if (prev)
        {
            j--;
            pair <int, int> p = long_palindrome(j + 1, n - j + i - 2);

            if (p.second + 2 * bestlen > p2.second * 2 + p3.second)
            {
                p2.first = i;
                p2.second = bestlen;
                p3 = p;
            }
        }
        j += 2;
    }
    if (p1.second >= p2.second * 2 + p3.second)
    {
        printf("1\n");
        printf("%d %d\n", p1.first + 1, p1.second);
    }
    else
    {
        printf("3\n");
        printf("%d %d\n", p2.first + 1, p2.second);
        printf("%d %d\n", p3.first + 1, p3.second);
        printf("%d %d\n", n + 1 - p2.second, p2.second);
    }
    fflush(
# 171 "data/284.cpp" 3 4
          stdin
# 171 "data/284.cpp"
               );
    getchar();
}

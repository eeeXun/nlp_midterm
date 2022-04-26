    template<typename _Key, typename _Tp, typename _Cmp = std::less<_Key>>
      using multimap
 = std::multimap<_Key, _Tp, _Cmp,
   polymorphic_allocator<pair<const _Key, _Tp>>>;
  }

}
# 12 "data/628.cpp" 2



# 14 "data/628.cpp"
using namespace std;

string a,b;
char s[100005];
int dp[100005];
int prefix[200005];
int L[100005];
int lmax[100005];
int l = 0, r = -1;

void calc()
{
    for (int i = 0; i < a.length(); i++)
    {
        int k = (i > r) ? 0 : min(dp[l + r - i], r - i + 1);
        while ((i - k >= 0) && (i + k < a.length()) && (a[i - k] == a[i + k])) k++;
        dp[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }
}

void calcPrefix()
{
    prefix[0] = 0;
    for (int i = 1; i < b.size(); i++)
    {
        int j = prefix[i - 1];
        while (j && (b[i] != b[j]))
            j = prefix[j - 1];
        if (b[i] == b[j])
            j++;
        prefix[i] = j;
    }
}

int main(void)
{
    scanf("%s", &s);
    a = (string)s;
    calc();
    b = a;
    reverse(b.begin(), b.end());
    b += "#";
    b += a;
    calcPrefix();
    memset(L, -1, sizeof(L));
    for (int i = a.length() + 1; i < b.length(); i++)
    {
        if (L[prefix[i]] == -1)
            L[prefix[i]] = i - 1 - a.length();
    }
    int curLen = 1;
    int cur = 0;
    for (int i = 0; i < a.length(); i++)
    {
        if (L[curLen] == i)
        {
            cur = curLen;
            curLen++;
        }
        lmax[i] = cur;
    }
    int total = 0;
    int pr_st = -1;
    int mid_mid = -1;
    int pr_len = 0;
    for (int i = 0; i < a.length(); i++)
    {
        int tmp = dp[i] * 2 - 1;
        if (i - dp[i] >= 0)
        if (i + dp[i] - 1 + lmax[i-dp[i]] < a.length())
            tmp += lmax[i - dp[i]] * 2;
        if (tmp > total)
        {
            mid_mid = i;
            pr_len = 0;
            if (i - dp[i] >= 0)
            if (lmax[i - dp[i]] != 0)
            {
                pr_st = L[lmax[i - dp[i]]] - lmax[i - dp[i]] + 1;
                pr_len = lmax[i - dp[i]];
            }
            total = tmp;
        }
    }
    if (pr_len)
    {
        printf("3\n");
        printf("%d %d\n", pr_st + 1, pr_len);
        printf("%d %d\n", mid_mid - dp[mid_mid] + 1 + 1, 2 * dp[mid_mid] - 1);
        printf("%d %d\n", a.length() - pr_len + 1, pr_len);
    }
    else
    {
        printf("1\n");
        printf("%d %d\n", mid_mid - dp[mid_mid] + 1 + 1, 2 * dp[mid_mid] - 1);

    }
    return 0;
}

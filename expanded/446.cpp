}
# 4 "data/446.cpp" 2

# 4 "data/446.cpp"
const int N = 100010;
int r[N], next[N], max[N], match[N], prev[N];
char s[N];
int min(int a, int b)
{
    return(a < b ? a : b);
}

int main()
{
    int n, mx, id, i, now, temp;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    r[1] = 1;
    id = 1;
    mx = 2;
    for (i = 2; i <= n; i++)
    {
        if (i >= mx) r[i] = 1;
        else r[i] = min(r[id * 2 - i], mx - i);
        while (i - r[i] > 0 && i + r[i] <= n
        && s[i - r[i]] == s[i + r[i]])
        r[i]++;
        if (i + r[i] > mx)
        {
            id = i;
            mx = i + r[i];
        }
    }
    next[n] = n + 1;
    for (i = n - 1; i >= 1; i--)
    {
        now = next[i + 1];
        while (now != n + 1 && s[now - 1] != s[i])
        now = next[now];
        if (s[now - 1] == s[i])
        next[i] = now - 1;
        else next[i] = n + 1;
    }
    memset(prev, -1, sizeof(prev));
    match[0] = n + 1;
    max[0] = 0;
    for (i = 1; i <= n; i++)
    {
        now = match[i - 1];
        while (now != n + 1 && s[now - 1] != s[i])
        now = next[now];
        if (s[now - 1] == s[i])
        match[i] = now - 1;
        else match[i] = n + 1;
        max[i] = n + 1 - match[i];
        if (prev[max[i]] == -1)
        prev[max[i]] = i + 1 - max[i];
        if (max[i] < max[i - 1])
        max[i] = max[i - 1];
    }
    mx = 0;
    id = 0;
    for (i = 1; i <= n; i++)
    {
        temp = r[i] * 2 - 1 + 2 * min(max[i - r[i]], n + 1 - (i + r[i]));
        if (temp > mx)
        {
            mx = temp;
            id = i;
        }
    }
    temp = min(max[id - r[id]], n + 1 - (id + r[id]));
    if (temp == 0)
    {
        printf("1\n");
        printf("%d %d", id - r[id] + 1, r[id] * 2 - 1);
    }
    else
    {
        printf("3\n");
        printf("%d %d\n", prev[temp], temp);
        printf("%d %d\n", id - r[id] + 1, r[id] * 2 - 1);
        printf("%d %d", n + 1 - temp, temp);
    }
    return(0);
}


}
# 6 "data/20.cpp" 2

# 6 "data/20.cpp"
const double eps(1e-8);
typedef long long lint;



char s[100010];
int R[100010];
char rev[100010];
int next[100010];
int match[100010];
int dp[100010];
int tail[100010];

void Manacher(char *s, int *R, int n)
{
    int mx = 0, p = 0;
    R[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        if(mx > i) R[i] = min(R[2*p - i], mx - i);
        else R[i] = 1;
        while(s[i - R[i]] == s[i + R[i]])
            R[i]++;
        if(i + R[i] > mx)
            mx = i + R[i], p = i;
    }
    return;
}

void KMP(char *s, char *rev, int n)
{
    memset(next, 0, sizeof(next));
    for(int i = 1; i < n; i++)
    {
        int j = i;
        while(j > 0)
        {
            j = next[j];
            if(rev[i] == rev[j])
            {
                next[i + 1] = j + 1;
                break;
            }
        }
    }
    memset(match, 0, sizeof(match));
    for(int i = 1, j = 0; i < n + 1; i++)
        if(s[i] == rev[j])
            j++, match[i] = j;
        else
            while(j > 0)
            {
                j = next[j];
                if(s[i] == rev[j])
                {
                    j++;
                    match[i] = j;
                    break;
                }
            }
    return;

}

vector <pair<int, int> > pos;

int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    s[0] = '@', s[n + 1] = '$';
    Manacher(s, R, n + 1);
    for(int i = 0; i < n; i++)
        rev[i] = s[n - i];
    rev[n] = '\0';
    KMP(s, rev, n);
    int maxl = 0;
    dp[1] = match[1];
    tail[1] = 1;
    for(int i = 1; i <= n; i++)
    {
        if(dp[i - 1] < match[i])
            dp[i] = match[i], tail[i] = i;
        else dp[i] = dp[i - 1], tail[i] = tail[i - 1];
    }
    for(int i = 1; i <= n; i++)
    {
        int middle = 2*R[i] - 1;
        int pre_suf = min(dp[i - R[i]], n - (i + R[i] - 1));
        if(middle + 2*pre_suf > maxl)
        {
            pos.clear();
            maxl = middle + 2*pre_suf;
            if(pre_suf > 0)
                pos.push_back(make_pair(tail[i - R[i]] - pre_suf + 1, pre_suf));
            pos.push_back(make_pair(i - R[i] + 1, 2*R[i] - 1));
            if(pre_suf > 0)
                pos.push_back(make_pair(n - pre_suf + 1, pre_suf));
        }
    }
    printf("%d\n", (int)pos.size());
    for(unsigned int i = 0; i < pos.size(); i++)
        printf("%d %d\n", pos[i].first, pos[i].second);
    return 0;
}

int mana[100010], L, next[200010], match[100010], r[100010];
int min(int x, int y)
{
    return x<y?x:y;
}
void getmana()
{
    mana[0] = 0;
    int id = 0, right = 0;
    for(int i = 1; i < L-1; ++i)
    {
        if(right > i)
        mana[i] = min(mana[2*id - i], right - i);
        else
        mana[i] = 0;
        while(s[i+mana[i]+1] == s[i-mana[i]-1] && (i+mana[i]+1) < L && (i-mana[i]-1) >= 0)
        mana[i]++;
        if(mana[i]+i > right)
        {
            id = i;
            right = mana[i]+i;
        }
    }
}
void getnext(char *temp)
{
    memset(next, 0, sizeof(next));
    next[0] = -1;
    int i = 0, j = -1;
    while(temp[i])
    {
        if(j == -1 || temp[i] == temp[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        j = next[j];
    }
}

int main()
{
    int i, j, k, l;
    while(gets(s) != 
# 50 "data/240.cpp" 3 4
                    __null
# 50 "data/240.cpp"
                        )
    {
        L = strlen(s);
        getmana();
        for(i = L-1; i >= 0; --i)
        s1[L-1-i] = s[i];
        s1[L] = '#';
        s1[L+1] = '\0';
        strcat(s1,s);
        getnext(s1);
        for(i = L+1; i <= 2*L+1; ++i)
        match[i-L-1] = next[i];
        memset(r, -1, sizeof(r));
        for(i = 1; i <= L; ++i)
        {
            if(match[i] > match[i-1])
            r[match[i]-1] = i-1;
            else
            match[i] = match[i-1];
        }
        for(i = 1; i < L; ++i)
        {
            if(r[i] == -1)
            r[i] = r[i-1];

        }

        int ans[3][2] = {0}, max = 0;
        bool ok = true;
        for(i = 1; i < L-1; ++i)
        {
            j = i+mana[i]+1;
            if(j >= L || i-mana[i] <= 0)
            j = L;
            else
            {
                if(r[L-j-1] == -1)
                j = L;
                else
                {
                    if(r[L-j-1] >= i-mana[i])
                    j = L - match[i-mana[i]];
                    else
                    j = L - match[r[L-j-1]+1];
                }
            }
            if(j < L)
            {
                if(2*(L-j) + mana[i]*2 + 1 > max)
                {
                    max = 2*(L-j) + mana[i]*2 + 1;
                    ans[0][0] = r[L-j-1] - L + j + 1;
                    ans[0][1] = L-j;
                    ans[1][0] = i-mana[i];
                    ans[1][1] = 2*mana[i]+1;
                    ans[2][0] = j;
                    ans[2][1] = L-j;
                    ok = false;

                }
            }
            else
            {
                if(2*mana[i]+1 > max)
                {
                    max = 2*mana[i]+1;
                    ok = true;
                    ans[1][0] = i-mana[i];
                    ans[1][1] = 2*mana[i]+1;
                }
            }
        }
        if(ok)
        {
            if(ans[1][1] == 0)
            ans[1][1] = 1;
            printf("1\n%d %d\n", ans[1][0]+1, ans[1][1]);
        }
        else
        {
            printf("3\n");
            printf("%d %d\n", ans[0][0]+1, ans[0][1]);
            printf("%d %d\n", ans[1][0]+1, ans[1][1]);
            printf("%d %d\n", ans[2][0]+1, ans[2][1]);
        }
    }
    return 0;
}

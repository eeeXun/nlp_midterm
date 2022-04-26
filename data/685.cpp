#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
char S[MAXN];
char RevS[MAXN];
int Slen;
char MS[2 * MAXN];
int MSlen;
int Palindrome[2 * MAXN];
int SMatch[MAXN];
int SMatchAid[MAXN];
int SMatchMaxPos[MAXN];
int ans;
int ansarrlen;
int ansarr[3][2];

void ManacherInit(char *from, char *to, int len)
{
    to[0] = '@';

    for(int i = 0; i < len; i ++)
        to[2 * i + 1] = '#', to[2 * i + 2] = from[i];

    to[2 * len + 1] = '#';
    to[2 * len + 2] = '$';
    to[2 * len + 3] = '\0';

    return;
}

void Manacher(char *st, int *palindrom, int len)
{
    int mx = 0, ans = 0, po = 0;

    for(int i = 1; i <= len; i ++)
    {
        if(mx > i)
            palindrom[i] = min(mx - i, palindrom[2 * po - i]);
        else
            palindrom[i] = 1;

        while(st[i - palindrom[i]] == st[i + palindrom[i]])
            palindrom[i] ++;

        if(palindrom[i] + i > mx)
        {
            mx = palindrom[i] + i;
            po = i;
        }
    }

    return;
}

void ReverseString(char *dst, char *src, int len)
{
    for(int i = 0; i < len; i ++)
        dst[len - 1 - i] = src[i];
    dst[len] = '\0';

    return;
}

void KMP(char *A, char *B, int len, int *match, int *aid)
{
    int i = 0, j = -1;
    aid[0] = -1;
    while(i < len)
    {
        if(j == -1 || B[i] == B[j])
        {
            i ++;
            j ++;
            aid[i] = j;
        }
        else
            j = aid[j];
    }

    i = j = 0;
    while(i < len && j < len)
    {
        if(j == -1 || A[i] == B[j])
            i ++, j ++, match[i - 1] = j;
        else
            j = aid[j];
    }

    return;
}

void CalcMaxMatchPos()
{
    SMatchMaxPos[0] = 0;
    for(int i = 1; i < Slen; i ++)
    if(SMatch[i] > SMatch[SMatchMaxPos[i - 1]])
        SMatchMaxPos[i] = i;
    else
        SMatchMaxPos[i] = SMatchMaxPos[i - 1];

    return;
}

void IteratePalindrome()
{
    int l, r, palinlen;
    int matchlen, nowlen;

    ans = 0;
    for(int i = 0; i < Slen; i ++)
    {
        palinlen = (Palindrome[2 * i + 2] - 1) / 2;
        l = i - palinlen;
        r = i + palinlen;
        if(l > 0)
            matchlen = min(SMatch[SMatchMaxPos[l - 1]], Slen - 1 - r);
        else
            matchlen = 0;
        nowlen = palinlen * 2 + 1 + matchlen * 2;

        if(nowlen > ans)
        {
            ans = nowlen;
            if(matchlen == 0)
            {
                ansarrlen = 1;
                ansarr[0][0] = l + 1;
                ansarr[0][1] = 2 * palinlen + 1;
            }
            else
            {
                ansarrlen = 3;
                ansarr[0][0] = SMatchMaxPos[l - 1] - SMatch[SMatchMaxPos[l - 1]] + 1 + 1;
                ansarr[0][1] = matchlen;
                ansarr[1][0] = l + 1;
                ansarr[1][1] = 2 * palinlen + 1;
                ansarr[2][0] = Slen - matchlen + 1;
                ansarr[2][1] = matchlen;
            }
        }
    }

    return;
}

int main()
{

    // freopen("D:\\1.in", "r", stdin);
    // freopen("D:\\1.out", "w", stdout);

    scanf("%s", S);
    Slen = strlen(S);
    MSlen = Slen * 2 + 1;
    ManacherInit(S, MS, Slen);
    Manacher(MS, Palindrome, MSlen);
    ReverseString(RevS, S, Slen);
    KMP(S, RevS, Slen, SMatch, SMatchAid);
    CalcMaxMatchPos();
    IteratePalindrome();

    printf("%d\n", ansarrlen);
    for(int i = 0; i < ansarrlen; i ++)
        printf("%d %d\n", ansarr[i][0], ansarr[i][1]);

	return 0;
}

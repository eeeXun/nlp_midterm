}
# 4 "data/172.cpp" 2

# 4 "data/172.cpp"
using namespace std;

void manacher(int *R, char *s, int n)
{
    R[0] = 1;
    for(int i = 1, p = 0, mx = 0; i < n; i++)
    {
        if(i < mx)
            R[i] = min(R[2*p - i], mx - i);
        else
            R[i] = 1;
        while(s[i + R[i]] == s[i - R[i]])
            R[i]++;
        if(i + R[i] > mx)
            mx = i + R[i], p = i;
    }
}
int next[(100010)], a[(100010)], p[(100010)];
void kmp(char *pattern, int n, char *text, int m)
{

    for(int i = 1, j; i < n; i++)
    {
        j = i;
        while(j > 0)
        {
            j = next[j];
            if(pattern[i] == pattern[j])
            {
                next[i + 1] = j + 1;
                break;
            }
        }
    }

    for(int i = 0, j = 0; i < m; i++)
    {
        if(text[i] == pattern[j])
        {
            j++;
            a[i] = j;
            p[i] = i - j + 1;
        }
        else
        {
            while(j > 0)
            {
                j = next[j];
                if(text[i] == pattern[j])
                {
                    j++;
                    a[i] = j;
                    p[i] = i - j + 1;
                    break;
                }
            }
        }
    }
}
int R[(100010)];
char s[(100010)], si[(100010)];
int main()
{
    s[0] = '$';
    scanf("%s", s + 1);
    int n = strlen(s), m = 0;
    manacher(R, s, n);
    for(int i = n - 1; i > 0; i--)
        si[m++] = s[i];
    si[m++] = '\0';
    kmp(si, m, s, n);

    for(int i = 1; i < n; i++)
    {
        if(a[i] < a[i-1])
        {
            p[i] = p[i-1];
            a[i] = a[i-1];
        }
    }
    int o = 0, k, pre_s, pt, pl, mt, ml, st, sl;
    for(int i = 1, j, d; i < n; i++)
    {
        d = min(a[i - R[i]], n - i - R[i]);
        j = 2 * (R[i] + d) - 1;
        if(j > o)
        {
            o = j;
            k = d ? 3 : 1;
            pt = p[i - R[i]], pl = d;
            mt = i - R[i] + 1, ml = 2*R[i] - 1;
            st = n - d, sl = d;
        }
    }
    if(k == 1)
        printf("%d\n%d %d\n", k, mt, ml);
    else
        printf("%d\n%d %d\n%d %d\n%d %d\n", k, pt, pl, mt, ml, st, sl);
    return 0;
}

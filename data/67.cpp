#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//---aaaaaaaaaaaxaaaaaaayaaaaaaaaaaaa//

const int maxn = 200001;

int n;
char st[maxn];
int A[maxn],B[maxn];
int pre[maxn],mpr[maxn],mre[maxn],ret[maxn],next[maxn];
int ans[10],res;

void updata(int x,int l1,int y,int l2)
{
    if (2*l1+l2 > res)
    {
        res = 2*l1+l2;
        ans[0] = x-l1+1,ans[1] = l1;
        ans[2] = y,ans[3] = l2;
        ans[4] = n-l1+1,ans[5] = l1;
    }
}

int main()
{
    int i,j,x,y;

    scanf("%s",st);
    n = strlen(st);
    for (i = 1; i <= n; ++i) A[i] = st[i-1]-'a'+1;
    for (i = 1; i <= n; ++i) B[i] = A[n-i+1];

    next[1] = 0;
    for (i = 2,j = 0; i <= n; ++i)
    {
        for (; j && B[j+1] != B[i]; j = next[j]) ;
        j += B[j+1] == B[i];
        next[i] = j;
    }

    for (i = 1,j = 0; i <= n; ++i)
    {
        for (; j && B[j+1] != A[i]; j = next[j]) ;
        j += B[j+1] == A[i];
        pre[i] = j;
    }

    for (i = 1; i <= n; ++i) 
        if (mpr[i-1] > pre[i]) mpr[i] = mpr[i-1],mre[i] = mre[i-1];
        else mpr[i] = pre[i],mre[i] = i;

    for (i = 1,x = y = 0; i <= n; ++i)
    {
        if (i < y) ret[i] = min(ret[2*x-i],y-i);
        else ret[i] = 1;
        for (; i-ret[i] >= 1 && i+ret[i] <= n && A[i-ret[i]] == A[i+ret[i]]; ++ret[i]) ;
        if (i+ret[i] > y)
        {
            x = i;
            y = i+ret[i];
        }
    }

    for (i = 1; i <= n; ++i)
        updata(mre[i-ret[i]],min(n-(i+ret[i])+1,mpr[i-ret[i]]),i-ret[i]+1,2*ret[i]-1);

    if (ans[1])
    {
        printf("3\n");
        printf("%d %d\n",ans[0],ans[1]);
        printf("%d %d\n",ans[2],ans[3]);
        printf("%d %d\n",ans[4],ans[5]);
    }
    else 
    {
        printf("1\n");
        printf("%d %d\n",ans[2],ans[3]);
    }

    return 0;
}

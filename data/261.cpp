#pragma comment(linker, "/STACK:102400000,102400000")
#include<cstdio>
#include<ctype.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<string.h>
#include<string>
#include<sstream>
#include<bitset>
using namespace std;
#define ll __int64
#define ull unsigned long long
#define eps 1e-8
#define NMAX 1000000000
#define MOD 51123987
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define PI acos(-1)
#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.end())
template<class T>
inline void scan_d(T &ret)
{
    char c;
    int flag = 0;
    ret=0;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c == '-')
    {
        flag = 1;
        c = getchar();
    }
    while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
    if(flag) ret = -ret;
}
template<class T> inline T Max(T a, T b){ return a > b ? a : b; }
template<class T> inline T Min(T a, T b){ return a < b ? a : b; }

const int X = 141;
const int maxn = 200000+10;
ull h[maxn],x[maxn];
char s[maxn],s2[maxn];
int n;
void init()
{
    h[2*n+1] = 0;
    for(int i = 2*n; i >= 1; i--) h[i] = h[i+1]*X+(ull)(s[i]-'a');
    x[0] = 1;
    for(int i = 1; i <= 2*n; i++) x[i] = x[i-1]*(ull)X;
//    cout<<"kao:"<<x[0]*X<<" "<<n<<endl;
}
int g[maxn],w[maxn];
int fag[maxn];
inline bool judge(int l, int r, int len)
{
    ull t1 = h[l]-h[l+len]*x[len];
    ull t2 = h[r]-h[r+len]*x[len];
//    cout<<t1<<" "<<t2<<endl;
    if(t1 == t2) return true;
    return false;
}
int main()
{
#ifdef GLQ
    freopen("input.txt","r",stdin);
//    freopen("o.txt","w",stdout);
#endif
    scanf("%s",s+1);
    n = strlen(s+1);
    for(int i = n+1; i <= 2*n; i++)
        s[i] = s[2*n-i+1];
//    s[2*n+1] = '\0';
//    cout<<s+1<<endl;
    init();
    memset(g,0,sizeof(g));
    int l = 2*n,r = n;
    while(l > 2*n-r+1)
    {
        if(judge(r,l,n-r+1))
        {
            g[2*n-l+1] = n-r+1;
            r--;
            l--;
        }
        else l--;
    }
    fag[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        if(g[i] > g[i-1])
        {
            fag[i] = i;
        }
        else
        {
            g[i] = g[i-1];
            fag[i] = fag[i-1];
        }
    }
    s2[0] = '$'; s2[n+1] = '#';
    for(int i = 1; i <= n; i++)
        s2[i] = s[i];
    int p0,p = 0;
    for(int i = 1; i <= n; i++)
    {
        if(p > i)
        {
            if(w[2*p0-i] < p-i+1) w[i] = w[2*p0-i];
            else
            {
                int j;
                for(j = p-i; s2[i+j] == s2[i-j]; j++);
                w[i] = j;
                p0 = i;
                p = i+j-1;
            }
        }
        else
        {
            int j;
            for(j = 1; s2[i+j] == s2[i-j]; j++);
            w[i] = j;
            p0 = i;
            p = i+j-1;
        }
    }
    int ans = 0,re[3][2];
    for(int i = 1; i <= n; i++)
    {
        if(ans < 2*w[i]-1+2*Min(g[i-w[i]],n-(i+w[i])+1))
        {
            re[1][0] = i-w[i]+1;
            re[1][1] = 2*w[i]-1;
            if(g[i-w[i]] > n-(i+w[i])+1)
            {
                re[0][0] = fag[i-w[i]]-n+i+w[i];
                re[0][1] = re[2][1] = n-(i+w[i])+1;
                re[2][0] = i+w[i];
            }
            else
            {
                re[0][0] = fag[i-w[i]]-g[i-w[i]]+1;
                re[0][1] = re[2][1] = g[i-w[i]];
                re[2][0] = n-g[i-w[i]]+1;
            }
            ans = 2*w[i]-1+2*Min(g[i-w[i]],n-(i+w[i])+1);
        }
    }
    int nct = 3;
    if(re[0][0]+re[0][1] == re[1][0] && re[0][0]+re[0][1]+re[1][1] == re[2][0])
    {
        re[0][1] += re[1][1]+re[2][1];
        nct = 1;
    }
    if(re[0][1] == 0 && re[2][1] == 0)
    {
        re[0][0] = re[1][0];
        re[0][1] = re[1][1];
        nct = 1;
    }
    printf("%d\n",nct);
    for(int i = 0; i < nct; i++)
        printf("%d %d\n",re[i][0],re[i][1]);
//    printf("%d\n",ans);
    return 0;
}

		    	  	  			      		 	 	 	 	
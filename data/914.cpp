#include<bits/stdc++.h>
using namespace std;
template <class T> bool chkmin(T& a,T b) { return a>b ? a=b,true:false; }
template <class T> bool chkmax(T& a,T b) { return a<b ? a=b,true:false; }
const int maxn=1000000+10;
int n;
char S[maxn];
namespace Code{
    char rev[maxn];
    int fail[maxn];
    int len[maxn];
    inline void init()
    {
        for (int i=1;i<=n;i++)
            rev[i]=S[n-i+1];
        int i=1,j=0;
        while (i<=n)
            if (!j||rev[i]==rev[j])
                fail[++i]=++j;
            else
                j=fail[j];
    }
    inline void KMP()
    {
        int i=1,j=1;
        while (i<=n)
        {
            if (!j||S[i]==rev[j])
                len[i++]=j++;
            else
                j=fail[j];
            if (j==n+1)
                j=fail[j];
        }
    }
}
namespace Geass{
    const int maxm=maxn<<1;
    char ch[maxm];
    int len;
    int h[maxm];
    inline void extend(int i)
    {
        while (1<i-h[i]&&h[i]+i<len&&ch[i-h[i]-1]==ch[i+h[i]+1]) h[i]++;
    }
    inline void init()
    {
        ch[len=1]='$';
        for (int i=1;i<=n;i++)
        {
            ch[i<<1]=S[i];
            ch[i<<1|1]='$';
        }
        len=n<<1|1;
    }
    inline void Manacher()
    {
        for (int i=1,ub=0,id;i<=len;i++)
        {
            if (i>=ub)
                extend(i);
            else
            {
                int j=id*2-i;
                if (h[j]+i<ub)
                    h[i]=h[j];
                else
                    h[i]=ub-i,extend(i);
            }
            if (h[i]+i>ub) ub=h[id=i]+i;
        }
        for (int i=1;i<=n;i++) h[i]=h[i<<1];
    }
}
namespace Mikasa{
#define bit(x) (1<<(x))
    int lg[maxn];
    int d[maxn][22];
    inline void init()
    {
        for (int i=2;i<=n;i++)
            lg[i]=lg[i>>1]+1;
        for (int i=1;i<=n;i++)
            d[i][0]=Geass::h[i];
        for (int j=1;j<=lg[n];j++)
            for (int i=1;i+bit(j)-1<=n;i++)
                d[i][j]=max(d[i][j-1],d[i+bit(j-1)][j-1]);
    }
    inline int Query(int l,int r)
    {
        if (l>r) return 0;
        int k=lg[r-l+1];
        return max(d[l][k],d[r-bit(k)+1][k]);
    }
}
namespace Asuna{
    int ans;
    int pos1,pos2;
    int len1,len2;
    inline int binary_search(int L,int R)
    {
        if (L>R) return 0;
        int l=0,r=R-L+1;
        while (l+1<r)
        {
            int mid=(l+r)>>1;
            if (Mikasa::Query(L+mid,R-mid)>>1>=mid)
                l=mid;
            else
                r=mid;
        }
        return l;
    }
    inline void solve()
    {
        ans=binary_search(1,n)<<1|1;
        for (int i=1,res;i<=n;i++)
            if (Code::len[i]&&i<n-Code::len[i])
                if (chkmax(ans,(res=binary_search(i+1,n-Code::len[i])<<1|1)+(Code::len[i]<<1)))
                {
                    pos1=i-Code::len[i]+1,pos2=n-Code::len[i]+1;
                    len1=Code::len[i],len2=res;
                }
        if (pos1)
        {
            puts("3");
            printf("%d %d\n",pos1,len1);
            for (int i=pos1+len1+len2/2;i<=n-len1;i++)
                if (Geass::h[i]==len2)
                {
                    printf("%d %d\n",i-len2/2,len2);
                    return (void)(printf("%d %d\n",pos2,len1));
                }
        }
        puts("1");
        for (int i=1;i<=n;i++)
            if (Geass::h[i]==ans)
                return (void)(printf("%d %d\n",i-ans/2,ans));
    }
}
int main()
{
    if (fopen("30E.in","r")!=NULL)
    {
        freopen("30E.in","r",stdin);
        freopen("30E.out","w",stdout);
    }
    scanf("%s",S+1);
    n=strlen(S+1);
    Code::init(),Code::KMP();
    Geass::init(),Geass::Manacher();
    Mikasa::init(),Asuna::solve();
    return 0;
}

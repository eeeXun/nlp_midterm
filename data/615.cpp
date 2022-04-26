#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp make_pair
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int N=1e5+10,bas[]={29,31};
const int mod[]={998244353,19260817};
int n;
int f[N],g[N];
int t[2],pw[2][N],hsl[2][N],hsr[2][N];
pii ans[5];
char s[N];

void iniths()
{
    for(int k=0;k<2;++k)
    {
        pw[k][0]=1;
        for(int i=1;i<=n;++i) pw[k][i]=(ll)pw[k][i-1]*bas[k]%mod[k];
    }       
    for(int k=0;k<2;++k)
    {
        for(int i=1;i<=n;++i) hsl[k][i]=((ll)hsl[k][i-1]*bas[k]+(s[i]-'a'+1))%mod[k];
        for(int i=n;i;--i) hsr[k][i]=((ll)hsr[k][i+1]*bas[k]+(s[i]-'a'+1))%mod[k];
    }
}
pii gethsl(int l,int r)
{
    for(int k=0;k<2;++k) 
        t[k]=(hsl[k][r]-(ll)hsl[k][l-1]*pw[k][r-l+1]%mod[k]+mod[k])%mod[k];
    return mkp(t[0],t[1]);
}
pii gethsr(int l,int r)
{
    for(int k=0;k<2;++k) 
        t[k]=(hsr[k][l]-(ll)hsr[k][r+1]*pw[k][r-l+1]%mod[k]+mod[k])%mod[k];
    return mkp(t[0],t[1]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("CF30E.in","r",stdin);
    freopen("CF30E.out","w",stdout);
#endif
    scanf("%s",s+1);n=strlen(s+1);iniths();
    for(int i=1;i<=n;++i)
    {
        int l=1,r=min(i,n-i+1);f[i]=1;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(gethsl(i-mid+1,i)==gethsr(i,i+mid-1)) f[i]=mid,l=mid+1;
            else r=mid-1;
        }
    }
    //for(int i=1;i<=n;++i) printf("%d ",f[i]); puts("");
    for(int i=1;i<=n;++i)
    {
        int mxl=0,l=1,r=n-i+1;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(gethsl(i,i+mid-1)==gethsr(n-mid+1,n)) mxl=mid,l=mid+1;
            else r=mid-1;
        }
        if(mxl) for(int j=mxl;j && !g[j];--j) g[j]=i;
    }
    int anslen=0;
    for(int k=0;k<3;++k) ans[k]=mkp(-1,-1); 
    for(int i=1;i<=n;++i)
    {
        if(f[i]*2-1>anslen) 
        {
            anslen=f[i]*2-1;
            ans[0]=ans[2]=mkp(-1,-1);ans[1]=mkp(i-f[i]+1,i+f[i]-1);
        }
        int l=1,r=min(i,n-i+1),mxl=0;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(n-mid+1>i+f[i]-1 && g[mid] && g[mid]+mid-1<i-f[i]+1) mxl=mid,l=mid+1;
            else r=mid-1;
        }
        if(mxl)
        {
            if(mxl*2+f[i]*2-1>anslen)
            {
                anslen=mxl*2+f[i]*2-1;
                ans[0]=mkp(g[mxl],g[mxl]+mxl-1);ans[1]=mkp(i-f[i]+1,i+f[i]-1);ans[2]=mkp(n-mxl+1,n);
            }
        }
    }
    if(!~ans[0].fi) printf("1\n%d %d",ans[1].fi,ans[1].se-ans[1].fi+1);
    else
    {
        puts("3");
        for(int k=0;k<3;++k) printf("%d %d\n",ans[k].fi,ans[k].se-ans[k].fi+1);
    }
    return 0;
}
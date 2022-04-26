#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;++i)
using namespace std;
const int mn=101000,ml=20;
int n,m,ans,a[3][2];
int f[mn],pre[mn],h[mn][ml],log[mn],bi[ml];
char s1[mn],s2[mn];
bool cmp(int i,int j){return f[i]<f[j];}
void kmp()
{
    int i,j;
    memcpy(s2+1,s1+1,n);
    reverse(s2+1,s2+n+1);
    pre[1]=0,j=0;
    fo(i,2,n)
    {
        for(;j&&s2[i]!=s2[j+1];j=pre[j]);
        if(s2[i]==s2[j+1])++j;
        pre[i]=j;
    }

}
void rmq()
{
    int i,j;
    fo(i,1,n)h[i][0]=i;
    log[1]=0;
    fo(i,2,n)log[i]=log[i>>1]+1;
    fo(i,0,log[n])bi[i]=1<<i;
    fo(j,1,log[n])
        fo(i,1,n-bi[j]+1)
            h[i][j]=max(h[i][j-1],h[i+bi[j-1]][j-1],cmp);
}
int query(int l,int r)
{
    int k=log[r-l+1];
    return max(h[l][k],h[r-bi[k]+1][k],cmp);
}
int main()
{
    scanf("%s",s1+1);
    n=strlen(s1+1);
    int i,j=0,k=0,l,t;
    l=1;
    fo(i,1,n)
    {
        t=0;
        if(i<=j)t=min(j-i,f[k+k-i]);
        while(i-t-1>=1&&i+t+1<=n&&s1[i-t-1]==s1[i+t+1])++t;
        if(i+t>j)j=i+t,k=i;
        f[i]=t;
        if(f[i]>f[l])l=i;
    }
    kmp();
    rmq();
    int la=0,lo,hi,mid,d;
    j=0;
    fo(i,1,n)
    {
        for(;j&&s1[i]!=s2[j+1];j=pre[j]);
        if(s1[i]==s2[j+1])++j;
        if(j<=la)continue;
        if(i>=n-j)break;
        la=j;
        lo=0,hi=(n-i-j-1)/2;
        while(lo<hi)
        {
            mid=(lo+hi+1)/2;
            d=query(i+mid+1,n-j-mid);
            if(f[d]>=mid)lo=mid;else hi=mid-1;
        }
        if(j+j+lo+lo+1>ans)
        {
            ans=j+j+lo+lo+1;
            d=query(i+lo+1,n-j-lo);
            a[0][0]=i-j+1,a[0][1]=i;
            a[1][0]=d-lo,a[1][1]=d+lo;
            a[2][0]=n-j+1,a[2][1]=n;
        }
    }
    if(f[l]*2+1>ans)
    {
        printf("1\n%d %d\n",l-f[l],f[l]*2+1);
        return 0;
    }
    printf("%d\n",3);
    fo(i,0,2)printf("%d %d\n",a[i][0],a[i][1]-a[i][0]+1);
    return 0;
}
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cmath>
#define maxn 100020
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;
char s[maxn],t[maxn];
int nex[maxn];
int n,m;
int f[maxn],k,i;
int mx[maxn],wz[maxn];
struct yqh
{
    int len1,len2,len3;
    int x1,x2,x3;
    void print()
    {
        int x=0;
        if(len1)++x;
        if(len2)++x;
        if(len3)++x;
        printf("%d\n",x);
        if(len1)printf("%d %d\n",x1,len1);
        if(len2)printf("%d %d\n",x2,len2);
        if(len3)printf("%d %d\n",x3,len3);
    }
}ans,aug;
void kmp()
{
    rep(i,n)t[i]=s[n-i];
    nex[0]=-1;
    rep(i,n)
    {
        int x=nex[i-1];
        while(x>=0&&t[x+1]!=t[i])x=nex[x];
        nex[i]=x+1;
    }
    int now=0;
    rep(i,n)
    {
        while(now>=0&&s[i-1]!=t[now+1])now=nex[now];
        ++now;
        mx[i]=now;
        if(now)wz[i]=i-now+1;
        if(mx[i]<mx[i-1])
        {
            mx[i]=mx[i-1];
            wz[i]=wz[i-1];
        }
    }
    for(int i=n;i>0;--i)s[i]=s[i-1];
    s[n+1]='#';
    s[0]='%';
}
bool cmp(yqh a,yqh b)
{
    return a.len1+a.len2+a.len3<b.len1+b.len2+b.len3;
}
void solve()
{
    int k=0,v=0;
    rep(i,n)
    {
        if(i<=v)f[i]=min(f[2*k-i],v-i);else f[i]=0;
        while(s[i-f[i]]==s[i+f[i]])++f[i];
        if(f[i]+i>v)
        {
            v=f[i]+i;
            k=i;
        }
        int x1=i-f[i]+1,y1=2*i-x1;
        int x=min(mx[x1-1],n-y1);
        aug.len1=aug.len3=x;
        aug.len2=2*f[i]-1;
        aug.x1=wz[x1-1];
        aug.x2=x1;
        aug.x3=n-x+1;
    //  aug.print();
        if(cmp(ans,aug))ans=aug;
    //  printf("%d\n",f[i]);
    }
}
int main()
{
    scanf("%s",s);
    n=strlen(s);
    kmp();
    solve();
    ans.print();
    return 0;
}

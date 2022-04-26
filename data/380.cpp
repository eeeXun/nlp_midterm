#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=100100;
int n,m;
char s[N];
int a[N],p[N],b[N],c[N];
void Gans(const int i)
{
    int A=i-a[i],x=min(b[i-a[i]-1],n-i-a[i])*2;
    if ( x==0 )
        printf("1\n%d %d\n",A,a[i]*2+1);
    else printf("3\n%d %d\n%d %d\n%d %d\n",c[A-1]-b[A-1]+1,b[A-1],A,a[i]*2+1,n-b[A-1]+1,b[A-1]);
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);s[n+1]='?';
    for(int i=1,j=0,k=1;i<=n;++i)
    {
        a[i]=(i<=j?min(j-i,a[k*2-i]):0);
        while ( s[i-a[i]-1]==s[i+a[i]+1] ) ++a[i];
        if ( i+a[i]>j ) j=i+a[i],k=i;
    }
    p[n]=n+1;
    for(int i=n-1;i>0;--i)
    {
        int k=p[i+1];
        while ( k<=n && s[i]!=s[k-1] ) k=p[k];
        p[i]=k-(s[k-1]==s[i]);
    }
    for(int i=1,now=n+1;i<=n;++i)
    {
        while( now<=n && s[now-1]!=s[i] ) now=p[now];
        now-=(s[now-1]==s[i]);
        b[i]=n-now+1;
        if ( b[i-1]>b[i] ) b[i]=b[i-1],c[i]=c[i-1];
            else c[i]=i;
    }
    int ans=0,k=0;
    for(int i=1,x;i<=n;++i)
    {
        x=2*a[i]+1+min(b[i-a[i]-1],n-i-a[i])*2;
        if ( x>ans ) ans=x,k=i;
    }
    Gans(k);
    return 0;
}
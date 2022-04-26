#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
int i,j,k,l,n,m,s,an;
const int N=110000;
char a[N],b[N];
int pre[N],g[N],f[N],v[N],h[N];
void kmp()
{
    pre[1]=0;
    for (int i=2;i<=n;i++)
    {
        int j=pre[i-1];
        while ((j!=0)&&(j<=n)&&(b[j+1]!=b[i])) j=pre[j]; 
        if (b[j+1]==b[i]) j++;
        pre[i]=j;
    }
    int j=0;
    for (int i=1;i<=n;i++)
    {
        while ((j!=0)&&(j<n)&&(a[i]!=b[j+1])) j=pre[j];
        if (a[i]==b[j+1]) j++;
        g[i-j+1]=j;
    }
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    int mm=0;
    a[0]='A';
    a[n+1]='B';
    for (int i=1;i<=n;i++)
    {
        if (i<mm) f[i]=min(mm-i,f[2*k-i]);
        else f[i]=1;
        while (a[i-f[i]]==a[i+f[i]]) f[i]++;
        if (i+f[i]>mm) k=i,mm=f[i]+i;
    }
    for (int i=1;i<=n;i++)
    b[i]=a[n-i+1];
    kmp();
    for (int i=1;i<=n;i++)
    {
        if (g[i]>g[h[i-1]]) h[i]=i;
        else h[i]=h[i-1];
    }
    k=0;
    for (int i=1;i<=n;i++)
    {
        int p=i-f[i];
        v[i]=(min(min(g[h[p]],i-f[i]+1-h[p]),n-(f[i]+i-1)));
        v[i]=max(v[i],0);
        if (2*v[i]+2*f[i]-1>an)
        an=2*v[i]+2*f[i]-1,k=i;
    }
    int p=k-f[k];
    if ((g[h[p]]==0)||(h[p]>=k-f[k]+1)||(k+f[k]-1==n))
    {
        printf("1\n%d %d\n",k-f[k]+1,f[k]*2-1);
    }
    else 
    {
        printf("3\n");
        int p=k-f[k];
        printf("%d %d\n",h[p],v[k]);
        printf("%d %d\n",k-f[k]+1,f[k]*2-1);
        printf("%d %d\n",n-v[k]+1,v[k]);
    }
    return 0;
}


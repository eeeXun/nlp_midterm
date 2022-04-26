#include <iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define all(x) x.begin(),x.end()
#define ll long long
#define inf 1000000007
#define N 100010
char s[N];
int f[N],next[N],g[N],h[N];
int main()
{
   // freopen("in.txt","r",stdin);
    int i,j,n,m,k;
    while(~scanf("%s",s+1))
    {
        n=strlen(s+1);
        next[n]=j=n+1;
        for(i=n-1;i>=1;i--)
        {
            while(j<=n&&s[j-1]!=s[i])j=next[j];
            if(s[j-1]==s[i])j--;next[i]=j;
        }
        g[0]=j=n+1;
        for(i=1;i<=n;i++)
        {
            while(j<=n&&s[j-1]!=s[i])j=next[j];
            if(s[j-1]==s[i])j--;
            if(j<g[i-1])g[i]=j,h[i]=i;
            else g[i]=g[i-1],h[i]=h[i-1];
        }
        k=0;f[0]=0;
        int ans=0,x=0,y,z,l,L;
        for(i=1;i<=n;i++)
        {
            if(i<k+f[k]&&i+f[k+k-i]<k+f[k])f[i]=f[k+k-i];
            else
            {
                f[i]=i<k+f[k]?k+f[k]-i:0;
                while(i-f[i]&&i+f[i]<=n&&s[i-f[i]]==s[i+f[i]])f[i]++;
                if(i+f[i]>k+f[k])k=i;
            }
            if(ans<2*f[i]-1)ans=2*f[i]-1,y=i,L=0;
            int w=g[i-f[i]],now=h[i-f[i]];
            if(w<i+f[i])now-=i+f[i]-w,w=i+f[i];
            l=n-w+1;
            if(ans<2*(f[i]+l)-1)ans=2*(f[i]+l)-1,x=now-l+1,y=i,z=w,L=l;
        }
        if(L)
        {
            printf("3\n%d %d\n%d %d\n%d %d\n",x,L,y-f[y]+1,2*f[y]-1,z,L);
        }
        else printf("1\n%d %d\n",y-f[y]+1,2*f[y]-1);
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 100005
using namespace std;

char S[maxn],a[maxn];
int N,f[maxn],g[maxn],h[maxn],r[maxn];

int main()
{
	scanf("%s",S+1),N=strlen(S+1),S[0]=1;
	for (int i=1; i<=N; i++) a[i]=S[N-i+1];
	for (int i=1,p=0,q=0; i<=N; i++)
	{
		r[i]=q>i?min(r[2*p-i],q-i):1;
		for (;S[i+r[i]]==S[i-r[i]]; r[i]++);
		if (i+r[i]>q) p=i,q=i+r[i];
	}
	for (int i=2,j; i<=N; i++)
	{
		for (j=f[i-1]; j&&a[j+1]!=a[i]; j=f[j]);
		f[i]=j+(a[j+1]==a[i]);
	}
	for (int i=1,j=0; i<=N; i++)
	{
		for (;j&&a[j+1]!=S[i]; j=f[j]);
		if (a[j+1]==S[i]) j++;
		g[i]=j,h[i]=g[h[i-1]]>j?h[i-1]:i;
	}
	int ans=0,a1,a2,a3,l1,l2;
	for (int i=1; i<=N; i++)
	{
		int x=min(g[h[i-r[i]]],N-i-r[i]+1);
		if (r[i]*2+x*2-1>ans) ans=r[i]*2+x*2-1,a1=h[i-r[i]]-x+1,l1=x,a2=i-r[i]+1,l2=2*r[i]-1,a3=N-x+1;
	}
	printf("%d\n",2*!!l1+!!l2);
	if (l1) printf("%d %d\n",a1,l1);
	if (l2) printf("%d %d\n",a2,l2);
	if (l1) printf("%d %d\n",a3,l1);
}
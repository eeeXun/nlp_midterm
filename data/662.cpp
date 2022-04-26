#include <cstring>
#include <cstdio>
using namespace std;

const int maxn=200010;
int n;
char a[maxn], b[maxn];
int len[maxn], next[maxn], maxl[maxn], rad[maxn];

int main()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	for (int i=1; i<=n; i++) b[i]=a[n-i+1];
	
	next[1]=0;
	for (int i=2, p=0; i<=n; i++)
	{
		while (p&&b[p+1]!=b[i]) p=next[p];
		if (b[p+1]==b[i]) p++; next[i]=p;
	}
	
	for (int i=1, p=0; i<=n; i++)
	{
		while (p&&b[p+1]!=a[i]) p=next[p];
		if (b[p+1]==a[i]) p++; len[i]=p;
		maxl[i]=maxl[i-1]; if (len[i]>len[maxl[i]]) maxl[i]=i;
	}
	
	for (int i=1, p=1; i<=n; i++)
	{
		int j=p+p-i, x=rad[j]; 
		if (p-rad[p]>j-rad[j]) x=j-(p-rad[p]);
		//if (x<0) x=0;
		while (i+x+1<=n && i-x-1>0 && a[i+x+1]==a[i-x-1]) x++;
		rad[i]=x; if (i+rad[i]>p+rad[p]) p=i;
	}
	
	int anslen=0, ansx, ansy,ansl;
	for (int i=1; i<=n; i++)
	{
		int y=i, x=maxl[y-rad[y]-1], l=len[x];
		if (n-(y+rad[y])<l) l=n-(y+rad[y]);
		
		if (l*2+1+rad[y]*2>anslen) 
			anslen=l*2+1+rad[y]*2, ansx=x, ansy=y, ansl=l;
	}
	if (ansl==0) printf("1\n%d %d\n",ansy-rad[ansy], rad[ansy]*2+1);
	else
	{
		printf("3\n");
		printf("%d %d\n", ansx-ansl+1, ansl);
		printf("%d %d\n", ansy-rad[ansy], rad[ansy]*2+1);
		printf("%d %d\n", n-ansl+1, ansl);
	}
	//for (;;);
	return 0;
}

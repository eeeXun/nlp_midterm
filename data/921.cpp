#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,pos,ans;
int d[maxn],nxt[maxn],f[maxn],g[maxn];
char s[maxn],t[maxn];
bool flag;
int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	s[n+1]='#';
	for(int i=1,p=0,r=0;i<=n;i++)
	{
		d[i]=(r>=i)?min(d[(p<<1)-i],r-i+1):1;
		while(s[i-d[i]]==s[i+d[i]])d[i]++;
		if(i+d[i]-1>r)r=i+d[i]-1,p=i;
	}
	for(int i=1;i<=n;i++)t[i]=s[n-i+1];
	cerr<<t+1<<endl;
	nxt[0]=nxt[1]=0;
	for(int i=2,j=0;i<=n;i++)
	{
		while(j&&t[j+1]!=t[i])j=nxt[j];
		if(t[j+1]==t[i])j++;
		nxt[i]=j;
	}
	for(int i=1,j=0;i<=n;i++)
	{
		while(j&&t[j+1]!=s[i])j=nxt[j];
		if(t[j+1]==s[i])j++;
		f[i]=j;
		if(f[i]==n)j=nxt[j];
		if(f[i])g[i]=i-f[i]+1;
	}
	for(int i=1;i<=n;i++)if(f[i-1]>f[i])f[i]=f[i-1],g[i]=g[i-1];
	for(int i=1;i<=n;i++)if(2*d[i]-1>ans)ans=2*d[i]-1,pos=i-d[i]+1;
	for(int i=1;i<=n;i++)
	{
		int tmp=i-d[i];
		if(2*min(f[tmp],n-(i+d[i]-1))+2*d[i]-1>ans)flag=1,ans=2*min(f[tmp],n-(i+d[i]-1))+2*d[i]-1,pos=i;
	}
	if(!flag)printf("1\n%d %d",pos,ans);
	else printf("3\n%d %d\n%d %d\n%d %d",g[pos-d[pos]],f[pos-d[pos]],pos-d[pos]+1,2*d[pos]-1,n-f[pos-d[pos]]+1,f[pos-d[pos]]);
	return 0;
}
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rep(i,l,r) for (int i=(l); i<=(r); i++)
typedef long long ll;
using namespace std;

const int N=100010;
char s[N],ss[N];
int n,ans,pos,mx,id,nxt[N],r[N],f[N],g[N];

int main(){
	scanf("%s",s+1); n=strlen(s+1); s[n+1]='#';
	rep(i,1,n){
		r[i]=(mx>i) ? min(r[2*id-i],mx-i) : 1;
		while (s[i+r[i]]==s[i-r[i]]) r[i]++;
		if (r[i]+i>mx) mx=r[i]+i,id=i;
	}
	rep(i,1,n) ss[i]=s[n+1-i];
	nxt[0]=nxt[1]=0;
	for (int i=2,j=0; i<=n; i++){
		while (j && ss[j+1]!=ss[i]) j=nxt[j];
		if (ss[j+1]==ss[i]) nxt[i]=++j;
	}
	for (int i=1,j=0; i<=n; i++){
		while (j && ss[j+1]!=s[i]) j=nxt[j];
		if (ss[j+1]==s[i]) f[i]=++j;
		if (f[i]==n) j=nxt[j];
		if (f[i]) g[i]=i-f[i]+1;
	}
	rep(i,1,n) if (f[i-1]>f[i]) f[i]=f[i-1],g[i]=g[i-1];
	bool flag=0;
	rep(i,1,n) if (2*r[i]-1>ans) ans=2*r[i]-1,pos=i-r[i]+1;
	rep(i,1,n){
		int t=i-r[i];
		if (2*min(f[t],n-(i+r[i]-1))+2*r[i]-1>ans) flag=1,ans=2*min(f[t],n-(i+r[i]-1))+2*r[i]-1,pos=i;
	}
	if (!flag) printf("1\n%d %d\n",pos,ans);
		else printf("3\n%d %d\n%d %d\n%d %d\n",g[pos-r[pos]],f[pos-r[pos]],pos-r[pos]+1,2*r[pos]-1,n-f[pos-r[pos]]+1,f[pos-r[pos]]);
	return 0;
}
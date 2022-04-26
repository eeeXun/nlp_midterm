#include<cstdio>
#include<cstring>
#define N 100005
int n,j,k,x,y,z,L,w,now,ans,next[N],f[N],g[N],h[N];
char s[N];
int main()
{
	scanf("%s",s+1),n=strlen(s+1),next[n]=j=n+1;
	for (int i=n-1;i;i--){
		while (j<=n && s[j-1]!=s[i]) j=next[j];
		if (s[j-1]==s[i]) j--; next[i]=j;
		}
	g[0]=j=n+1;
	for (int i=1;i<=n;i++){
		while (j<=n && s[j-1]!=s[i]) j=next[j]; if (s[j-1]==s[i]) j--;
		if (j<g[i-1]) g[i]=j,h[i]=i; else g[i]=g[i-1],h[i]=h[i-1];
		}
	for (int i=1;i<=n;i++){
		if (i<k+f[k] && i+f[k+k-i]<k+f[k]) f[i]=f[k+k-i];
		else {
			f[i]=i<k+f[k]?k+f[k]-i:0;
			while (i-f[i] && i+f[i]<=n && s[i-f[i]]==s[i+f[i]]) f[i]++;
			if (i+f[i]>k+f[k]) k=i;
			}
		if (f[i]>ans) ans=f[i]*2-1,y=i,L=0;
		w=g[i-f[i]],now=h[i-f[i]]; if (w<i+f[i]) now-=i+f[i]-w,w=i+f[i];
		if ((f[i]+n-w)*2+1>ans) ans=(f[i]+n-w)*2+1,L=n-w+1,x=now-L+1,y=i,z=w;
		}
	if (L) printf("3\n%d %d\n%d %d\n%d %d\n",x,L,y-f[y]+1,2*f[y]-1,z,L);
	else printf("1\n%d %d\n",y-f[y]+1,2*f[y]-1);
	return 0;
}

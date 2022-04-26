#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
const int N=101000;
char s[N];
int n,K,ans,p,r[N],f[N],g[N],w[N];
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for (int i=1,j=0,k;i<=n;i+=k,j=max(1,j-k)) {
		while(i>j&&i+j<=n&&s[i-j]==s[i+j])++j;r[i]=j;
		for (k=1;k<r[i]&&r[i]-k!=r[i-k];k++) r[i+k]=min(r[i-k],r[i]-k);
	}
	g[n+1]=K=n+2;
	for (int i=n;i;i--) {
		while (K<=n+1&&s[K-1]!=s[i]) K=g[K];
		g[i]=--K;
	}
	K=n+1;
	rep(i,1,n+1) {
		while (K<=n+1&&s[K-1]!=s[i]) K=g[K];
		f[i]=--K;
	}
	rep(i,1,n+1) {
		f[i]=n+1-f[i];
		if (f[i]<f[i-1]) f[i]=f[i-1],w[i]=w[i-1];
		else w[i]=i-f[i]+1;
	}
	ans=0;
	rep(i,1,n+1) {
		K=2*r[i]-1+min(n-i-r[i]+1,f[i-r[i]])*2;
		if (K>ans) ans=K,p=i;
	}
	K=min(n-p-r[p]+1,f[p-r[p]]);
	if (K) printf("3\n%d %d\n%d %d\n%d %d",w[p-r[p]],K,p+1-r[p],2*r[p]-1,n-K+1,K);
		else printf("1\n%d %d\n",p+1-r[p],2*r[p]-1);
}

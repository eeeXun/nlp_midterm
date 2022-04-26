#include <bits/stdc++.h>
using namespace std;
int n;
char tmp[100005];
char s[200005];
int d[200005];

void Manacher() {
	for(int i=1;i<=n;i++) {
		d[i]=1;
	}
	int p=0,maxr=0;
	for(int i=2;i<=n;i++) {
		if(i<=maxr) {
			d[i]=min(d[p+maxr-i],maxr-i+1);
		}
		while(i+d[i]<=n && i-d[i]>=1 && s[i+d[i]]==s[i-d[i]]) {
			d[i]++;
		}
		if(i+d[i]-1>maxr) {
			p=i-d[i]+1;
			maxr=i+d[i]-1;
		}
	}
}

int fail[200005];

void getFail() {
	int j=0;
	for(int i=2;i<=2*n+1;i++) {
		while(j!=0 && s[i]!=s[j+1]) {
			j=fail[j];
		}
		if(s[i]==s[j+1]) {
			j++;
		}
		fail[i]=j;
	}
}

int mlen,mpos,plen,ppos,slen,spos;
int len;

int f[200005];
int g[200005];

int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	Manacher();
	s[n+1]='#';
	for(int i=1;i<=n;i++) {
		s[i+n+1]=s[i];
	}
	reverse(s+1,s+n+1);
	getFail();
	for(int i=1;i<=n;i++) {
		f[i]=f[i-1];
		g[i]=g[i-1];
		if(fail[n+i+1]>f[i]) {
			f[i]=fail[n+i+1];
			g[i]=i;
		}
		int lenP=min(f[i-d[i]],n-i-d[i]+1);
		if((lenP<<1)+(d[i]<<1)-1>len) {
			len=(lenP<<1)+(d[i]<<1)-1;
			mpos=i-d[i]+1;
			mlen=(d[i]<<1)-1;
			if(lenP>0) {
				plen=lenP;
				slen=lenP;
				ppos=g[i-d[i]]-lenP+1;
				spos=n-lenP+1;
			}else {
				plen=0;
				slen=0;
			}
		}
	}
	printf("%d\n",(plen>0)?3:1);
	if(plen) {
		printf("%d %d\n",ppos,plen);
	}
	printf("%d %d\n",mpos,mlen);
	if(slen) {
		printf("%d %d\n",spos,slen);
	}
	return 0;
}
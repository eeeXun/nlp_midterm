#include<bits/stdc++.h>
using namespace std;
#define RI register int
const int N=100005;
char S[N],revS[N],kS[N<<1];
int n,len,ans,ans_id,p[N<<1],ne[N],mx[N],mx_id[N];

inline void manacher() {
	kS[++len]='#';for(RI i=1;i<=n;++i) kS[++len]=S[i],kS[++len]='#';
	int bj=0;
	for(RI i=1;i<=len;++i) {
		if(bj+p[bj]>=i) p[i]=min(p[bj*2-i],bj+p[bj]-i);
		else p[i]=0;
		while(i+p[i]+1<=len&&i-p[i]-1>=1&&kS[i+p[i]+1]==kS[i-p[i]-1]) ++p[i];
		if(i+p[i]>bj+p[bj]) bj=i;
	}
}
inline void KMP() {
	for(RI i=1;i<=n;++i) revS[i]=S[n-i+1];
	for(RI i=2;i<=n;++i) {
		int j=ne[i-1];
		while(1) {
			if(revS[j+1]==revS[i]) {ne[i]=j+1;break;}
			if(!j) break;j=ne[j];
		}
	}
	for(RI i=1;i<=n;++i) {
		int j=mx[i-1];
		while(1) {
			if(revS[j+1]==S[i]) {mx[i]=j+1;break;}
			if(!j) break;j=ne[j];
		}
	}
	for(RI i=1;i<=n;++i) {
		mx_id[i]=i;
		if(mx[i-1]>mx[i]) mx_id[i]=mx_id[i-1],mx[i]=mx[i-1];
	}
}

int main()
{
	scanf("%s",S+1),n=strlen(S+1);
	manacher(),KMP();
	for(RI i=1;i<=len;++i) {
		if(kS[i]=='#') continue;
		int tmp=p[i]+2*min(mx[(i-p[i]-1)/2],n-(i+p[i]-1)/2);
		if(tmp>ans) ans=tmp,ans_id=i;
	}
	int x=min(mx[(ans_id-p[ans_id]-1)/2],(ans_id+p[ans_id]-1)/2);
	int ans_js=(x!=0)*2+(p[ans_id]!=0);
	printf("%d\n",ans_js);
	if(x) printf("%d %d\n",mx_id[(ans_id-p[ans_id]-1)/2]-x+1,x);
	if(p[ans_id]) printf("%d %d\n",(ans_id-p[ans_id]+1)/2,p[ans_id]);
	if(x) printf("%d %d\n",n-x+1,x);
	return 0;
}
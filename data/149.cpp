#include<bits/stdc++.h>
#define N 100001
#define next Next
using namespace std;
#define G if(++ip==ie)if(fread(ip=ibuf,1,L,stdin))
const int L=1<<19;
char ibuf[L],*ie=ibuf+L,*ip=ie-1;
inline char nc(void){G;return *ip;}
#define getchar nc
inline int read(char*str){
	int n=0;char opt;
	while((opt=getchar())<'a'||opt>'z');
	while(opt>='a'&&opt<='z')str[n++]=opt,opt=getchar();
	str[n]='\0';return n;
}
char s[N],sr[N];
int n,ans,next[N],f[N],g[N],maxl[N],flag;
signed main(void){
	int i,j,tmp,mx=0,pos=0;read(s+1);n=strlen(s+1);s[n+1]='*';
	for(i=1;i<=n;++i){
		maxl[i]=(mx>i)?min(mx-i,maxl[(pos<<1)-i]):1;
		while(s[i+maxl[i]]==s[i-maxl[i]])++maxl[i];
		if(i+maxl[i]>mx)mx=i+maxl[i],pos=i;
		sr[i]=s[n-i+1]; 
	}
	for(j=0,i=2;i<=n;++i){while(j&&sr[j+1]^sr[i])j=next[j];if(sr[j+1]==sr[i])next[i]=++j;}
	for(j=0,i=1;i<=n;++i){while(j&&sr[j+1]^s[i])j=next[j];if(sr[j+1]==s[i])f[i]=++j;if(f[i]==n)j=next[j];if(f[i])g[i]=i-f[i]+1;}
	for(i=1;i<=n;++i)if(f[i-1]>f[i])f[i]=f[i-1],g[i]=g[i-1];
	for(i=1;i<=n;++i)if(ans<maxl[i]*2-1)ans=maxl[i]*2-1,pos=i-maxl[i]+1;
	for(i=1;i<=n;++i){
		tmp=i-maxl[i];
		if(2*min(f[tmp],n-(i+maxl[i]-1))+2*maxl[i]-1>ans)flag=1,ans=2*min(f[tmp],n-(i+maxl[i]-1))+2*maxl[i]-1,pos=i;
	}(!flag)?printf("1\n%d %d\n",pos,ans):printf("3\n%d %d\n%d %d\n%d %d\n",g[pos-maxl[pos]],f[pos-maxl[pos]],pos-maxl[pos]+1,2*maxl[pos]-1,n-f[pos-maxl[pos]]+1,f[pos-maxl[pos]]);
	return 0;
}//QwQ,It is Just a test
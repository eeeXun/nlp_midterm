#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;

const int maxn=100010;
int n,mx,pos,now,ans,k;
char s[maxn];
int r[maxn];
int p[maxn];
int a[maxn],b[maxn];
void print(int i){
	int L=i-r[i]+1,x=min(b[i-r[i]],n-i-r[i]+1);
	if(x==0)printf("1\n%d %d\n",L,2*r[i]-1);
	else{
		printf("3\n");
		printf("%d %d\n",a[L-1]-b[L-1]+1,b[L-1]);
		printf("%d %d\n",L,2*r[i]-1);
		printf("%d %d\n",n-b[L-1]+1,b[L-1]);
	}
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	mx=pos=0;s[0]='$';
	for(int i=1;i<=n;++i){
		r[i]=(mx>i?min(r[2*pos-i],mx-i):1);
		while(s[i+r[i]]==s[i-r[i]])r[i]++;
		if(i+r[i]>mx)mx=i+r[i],pos=i;
	}p[n]=n+1;
	for(int i=n-1;i>=1;--i){
		int k=p[i+1];
		while(k<=n&&s[i]!=s[k-1])k=p[k];
		p[i]=k-(s[i]==s[k-1]);
	}now=n+1;
	for(int i=1;i<=n;++i){
		while(now<=n&&s[now-1]!=s[i])now=p[now];
		now-=(s[now-1]==s[i]);
		b[i]=n-now+1;
		if(b[i]<b[i-1])b[i]=b[i-1],a[i]=a[i-1];
		else a[i]=i;
	}ans=0;k=0;
	for(int i=1;i<=n;++i){
		int tmp=2*r[i]-1+min(b[i-r[i]],n-i-r[i]+1)*2;
		if(tmp>ans)ans=tmp,k=i;
	}print(k);
	return 0;
}

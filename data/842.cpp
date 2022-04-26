#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int NR=1e5+5;
const int MR=1e5+5;
const int INF=0x3f3f3f3f;
const int MOD=1e9+7;
const double eps=1e-8;
inline int read()
{
	int x=0;
	int bei=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')bei=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*bei;
}
char s[NR];
int d[NR];
char a[NR<<1];
int bord[NR<<1];
int id[NR],maxbo[NR];
int getnxt(int x,char c)
{
	if(a[x+1]==c)
		return x+1;
	return x?getnxt(bord[x],c):0;
}
int main()
{
	scanf("%s",s+1);
	int len=strlen(s+1);
	int n=(len<<1)+1;
	for(int i=1;i<=len;++i)
		a[i]=s[len+1-i];
	for(int i=len+2;i<=n;++i)
		a[i]=s[i-len-1];
	a[len+1]='#';
	/*
	for(int i=1;i<=n;++i)
		putchar(a[i]);
	puts("");
	*/
	int p=0,maxr=0;
	for(int i=1;i<=len;++i)
	{
		if(i<=maxr)
			d[i]=min(d[maxr+p-i],maxr-i+1);
		while(i+d[i]<=len&&i-d[i]>=1&&s[i+d[i]]==s[i-d[i]])
			++d[i];
		if(i+d[i]-1>maxr)
			maxr=i+d[i]-1,p=i-d[i]+1;
	}
	/*
	for(int i=1;i<=len;++i)
		printf("%d ",d[i]);
	puts("");
	*/
	for(int i=2;i<=n;++i)
		bord[i]=getnxt(bord[i-1],a[i]);
	/*
	for(int i=1;i<=n;++i)
		printf("%d ",bord[i]);
	puts("");
	*/
	for(int i=1;i<=len;++i)
	{
		if(bord[i+len+1]>maxbo[i-1])
			maxbo[i]=bord[i+len+1],id[i]=i-bord[i+len+1]+1;
		else
			maxbo[i]=maxbo[i-1],id[i]=id[i-1];
	}
	int ans=1,ansid=0,tmp=0;
	for(int i=2;i<=len;++i)
	{
		int l=i-d[i]+1,r=i+d[i]-1;
		int nwbo=min(maxbo[l-1],len-r);
		int nwid=id[l-1];
		if(2*nwbo+2*d[i]-1>2*tmp+2*d[ans]-1)
		{
			ans=i;
			tmp=nwbo;
			ansid=nwid;
		}
	}
	if(!tmp)
		printf("1\n%d %d",ans-d[ans]+1,2*d[ans]-1);
	else
		printf("3\n%d %d\n%d %d\n%d %d",ansid,tmp,ans-d[ans]+1,2*d[ans]-1,len-tmp+1,tmp);
	return 0;
}
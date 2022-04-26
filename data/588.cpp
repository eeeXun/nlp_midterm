# include <stdio.h>
# include <iostream>
# include <string.h>
# include <string>
# include <algorithm>
# include <math.h>
# include <queue>
# include <deque>
# include <climits>
# include <stack>
using namespace std;
char s[120005],a[220005];
int p[120005];
int bo[220005];
int maxbo[120005],id[120005];
int maxr,pos;
int getnext(int i,char now)
{
	if(a[i+1]==now)
		return i+1;
	if(i)
		return getnext(bo[i],now);
	return 0;
}
int main()
{
	scanf("%s",&s[1]);
	int len=strlen(s+1);
	a[0]=' ';
	for(int i=1;i<=len;i++)
		a[i]=s[len-i+1];
	for(int i=len+1;i<=2*len;i++)
		a[i]=s[i-len];
	int n=len*2;
	for(int i=1;i<=len;i++)
	{
		if(i<maxr)
			p[i]=min(p[pos*2-i],maxr-i+1);
		else
			p[i]=1;
		while(s[i+p[i]]==s[i-p[i]] && i+p[i]<=len && i-p[i]>=1)
			p[i]++;
		if(i+p[i]-1>maxr)
		{
			maxr=i+p[i]-1;
			pos=i;
		}
	}
	for(int i=2;i<=n;i++)
		bo[i]=getnext(bo[i-1],a[i]);
	for(int i=1;i<=len;i++)
	{
		if(bo[i+len]>i)
			bo[i+len]=i;
		if(bo[i+len]>maxbo[i-1])
		{
			id[i]=i-bo[i+len]+1;
			maxbo[i]=bo[i+len];
		}
		else
		{
			id[i]=id[i-1];
			maxbo[i]=maxbo[i-1];
		}
	}
	int ans=1,tmp=0,ansid=0;
	for(int i=2;i<=len;i++)
	{
		int now=i-p[i]+1;
		int maxlen=len-(i+p[i]-1);
		int nowbo=min(maxbo[now-1],maxlen);
		int nowid=id[now-1];
		if(p[i]*2-1+nowbo*2>p[ans]*2-1+tmp*2)
		{
			ans=i;
			tmp=nowbo;
			ansid=nowid;
		}
	}
	if(tmp==0)
		printf("1\n%d %d",ans-p[ans]+1,p[ans]*2-1);
	else
		printf("3\n%d %d\n%d %d\n%d %d",ansid,tmp,ans-p[ans]+1,p[ans]*2-1,len-tmp+1,tmp);
	return 0;
}


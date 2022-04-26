#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N=1e5+5;

char s[N]; //原始数组
char tmp[N]; //翻转之后的数组
int pi[N],d[N]; //记录Border和马拉车
int l[N],start[N];

int n;

int findNext(int k,char c)
{
	if(tmp[k+1]==c)
		return k+1;

	if(k==0)
		return 0;

	return findNext(pi[k],c);
}

void KMP()
{
	pi[0]=pi[1]=0;
	for(int i=2;i<=n;i++)
		pi[i]=findNext(pi[i-1],tmp[i]);
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    s[n+1]='#';

    //马拉车一下，找到最大的回文串
	int maxr=0,p=0;
	for(int i=1;i<=n;i++)
		d[i]=1;

	for(int i=2;i<=n;i++)
	{
		if(i<=maxr)
			d[i]=min(d[maxr+p-i],maxr-i+1);

		while(i+d[i]<=n && i-d[i]>=1 && s[i+d[i]]==s[i-d[i]])
			d[i]++;

		if(i+d[i]-1>maxr)
		{
			maxr=i+d[i]-1;
			p=i-d[i]+1;
		}
	}

	//构造反向
    for(int i=1;i<=n;i++)
    	tmp[i]=s[n+1-i];
    KMP();

    int cur=0;
    for (int i=1;i<=n;i++)
    {
    	cur=findNext(cur,s[i]);
    	l[i]=cur;

        if(cur==n)
        	cur=pi[cur];

        if(l[i]>0) //有长度，记录开头位置，便于输出
        	start[i]=i-l[i]+1;
    }

    //把第i变成前i
    for(int i=1;i<=n;i++)
    	if(l[i-1]>l[i])
    	{
    		l[i]=l[i-1];
    		start[i]=start[i-1];
    	}

    bool flag=false;
    int ans=0,pos=0; //记录极大回文串长度，以及左端点
    for(int i=1;i<=n;i++)
    	if(2*d[i]-1>ans)
    	{
    		ans=2*d[i]-1;
    		pos=i-d[i]+1;
    	}

    for(int i=1;i<=n;i++)
    {
        int tmp=i-d[i]; //KMP的最大结尾位置

        //可以凑成3个部分
        if(2*min(l[tmp],n-(i+d[i]-1))+2*d[i]-1>ans)
        {
        	flag=true;
        	ans=2*min(l[tmp],n-(i+d[i]-1))+2*d[i]-1;
        	pos=i;
        }
    }

    if(!flag)
    {
    	printf("1\n");
    	printf("%d %d\n",pos,ans); //左端点和长度
    }
    else
    {
    	printf("3\n");
    	printf("%d %d\n", start[pos-d[pos]],l[pos-d[pos]]); //从start开始，长度为l
    	printf("%d %d\n",pos-d[pos]+1,2*d[pos]-1); //中间的回文
    	printf("%d %d\n",n-l[pos-d[pos]]+1,l[pos-d[pos]]); //最后的，长度也为l，一直到n
    }

    return 0;
}
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N_=100000+50;
typedef unsigned long long ll;
void print(int x)
{
	cout<<x<<endl;
}
inline int maxx(int x,int y)
{
	return (x>y)?x:y;
}
void Manacher(int len,char s[],int pd[])
{
	int max=0,maxi=0;
	for (int i=1;i<=len;i++)
	{
		if (i>max || pd[2*maxi-i]+i-1==max)
		{
			int j=maxx(0,max-i);
			while (j+1<i && s[i+j+1]==s[i-j-1])
				j++;
			pd[i]=j+1;
			maxi=i;
			max=i+j;
		}
		else
			if (pd[2*maxi-i]+i-1<max)
				pd[i]=pd[2*maxi-i];
			else
				pd[i]=max-i+1;
	}
}

ll rHash(int len,ll pp[],ll rhash[],int r,int l)
{
	return (rhash[l]-rhash[r+1])*pp[l-1];
}
ll Hash(int len,ll pp[],ll hash[],int l,int r)
{
	return (hash[r]-hash[l-1])*pp[len-r];
}
void Get_fi_gi(int len,char s[],int f[],int g[])
{
	const int p=101;
	ll pp[N_],hash[N_],rhash[N_];
	pp[0]=1;hash[0]=0;rhash[len+1]=0;
	for (int i=1;i<=len;i++)
	{
		pp[i]=pp[i-1]*p;
		hash[i]=hash[i-1]+(s[i]-96)*pp[i];
	}
	for (int i=len;i>=1;i--)
		rhash[i]=rhash[i+1]+(s[i]-96)*pp[len-i+1];
	int now=1;
	for (int i=0;i<=len;i++)
		f[i]=0;
	for (int i=1;i<=len;i++)
	{
		while (Hash(len,pp,hash,now,now+i-1)!=rHash(len,pp,rhash,len,len-i+1))
			if (now+i-1<len-i+1)
				now++;
			else
				break;
		if ((now+i-1<len-i+1))
		{
			f[i+now-1]=i;
			g[i+now-1]=now;
		}
		else
			break;
	}
	for (int i=1;i<=len;i++)
		if (f[i]<f[i-1])
		{
			f[i]=f[i-1];
			g[i]=g[i-1];
		}
}

struct Ans
{
	int ans,st[3],ln[3];
	Ans(int len,int f[],int g[],int pd[])
	{
		ans=0;f[0]=0;
		for (int i=1;i<=len;i++)
		{

			int cl=min(f[i-pd[i]],len-i-pd[i]+1),now=pd[i]*2-1+cl*2;
			if (now>ans)
			{
				ans=now;
				if (cl)
				{
					ln[2]=ln[0]=cl;
					st[0]=g[i-pd[i]];
					st[2]=len-ln[2]+1;
				}
				else
					st[2]=st[0]=0;
				st[1]=i-pd[i]+1;
				ln[1]=pd[i]*2-1;
			}
		}
	}
	void output()
	{
		printf("%d\n",(st[0])?3:1);
		for (int i=0;i<=2;i++)
			if (st[i])
				printf("%d %d\n",st[i],ln[i]);
	}
};

int main()
{
	//freopen("in","r",stdin);
	char s[N_];
	int pd[N_],f[N_],g[N_];
	scanf("%s",s+1);
	int len=strlen(s+1);
	Manacher(len,s,pd);
	Get_fi_gi(len,s,f,g);
	Ans ans(len,f,g,pd);
	ans.output();
}

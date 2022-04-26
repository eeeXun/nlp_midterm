#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int ma[200000],ne[200000],a[200000],b[200000];
char s[200000];
int l,i,k,ans,xx;
void huiwen()
{
	int now,nn;now=0;nn=0;
	for(int i=1;i<=l;i++)
	{
		ma[i]=(i>=now)?0:min(now-i,ma[2*nn-i]);
		while (s[i-ma[i]-1]==s[i+ma[i]+1]) ma[i]++;
		if (i+ma[i]>now) now=i+ma[i],nn=i;
		//	cout<<i<<' '<<ma[i]<<endl;
	}
}
void kmp()
{
	int k,i;
	ne[l+1]=l+2;
	k=l+2;
	for (i=l;i>=1;i--)
	{
		for(;k<=l+1&&s[i]!=s[k-1];) k=ne[k];
		ne[i]=--k;
	}
	k=l+1;
	for(i=1;i<=l;i++)
	{
		for(;k<=l+1&&s[i]!=s[k-1];) k=ne[k];
		a[i]=--k;	
//		cout<<i<<' '<<a[i]<<endl;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%s",s+1);
	s[0]='$';
	l=strlen(s+1);
	huiwen();
	kmp();
	for(i=1;i<=l;i++)
	{
		a[i]=l+1-a[i];
		if (a[i]<a[i-1])
		a[i]=a[i-1],b[i]=b[i-1];
		else b[i]=i-a[i]+1;		
	}
	int sum;	
	for(i=1;i<=l;i++)
	{
		sum=ma[i]*2+1+min(a[i-ma[i]-1],l-i-ma[i])*2;
		if (ans<sum) ans=sum,k=i;
	}
	xx=min(a[k-ma[k]-1],l-k-ma[k]);
	//cout<<ma[k]<<endl;
	if (xx)
	{
		printf("3\n");
		printf("%d %d\n%d %d\n%d %d\n",b[k-ma[k]-1],xx,k-ma[k],ma[k]*2+1,l-xx+1,xx);
	}
	else
	{
		printf("1\n");
		printf("%d %d",k-ma[k],ma[k]*2+1);
	}
}
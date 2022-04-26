#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<map>
#define mod 51123987
using namespace std;
typedef long long ll;
char a[200005];
char b[200005];
string tmp;
int anss,ansmid,haopre,haosuf,haomid,lpre,lsuf,lmid;
int n; 
int d[200005],kmp[200005],maxx[200005],maxhao[200005];
void manacher()
{
	int p=0,maxr=0;
	for(int i=1;i<=n;i++) d[i]=1;
	for(int i=1;i<=n;i++)
	{
		if(i<=maxr) d[i]=min(maxr-i+1,d[p+maxr-i]);
		while(i-d[i]>=1&&i+d[i]<=n&&a[i+d[i]]==a[i-d[i]]) d[i]++;
		if(i+d[i]-1>maxr)
		{
			maxr=i+d[i]-1;
			p=i-d[i]+1;
		}
	}
}
void Kmp()
{
	for(int i=2;i<=2*n+1;i++)
	{
		int j=kmp[i-1];
		while(j!=0&&b[j+1]!=b[i]) j=kmp[j];
		kmp[i]=(b[j+1]==b[i]?j+1:0); 
	}
}
int main()
{
	//freopen("test.txt","r",stdin);
	//freopen("test1.out","w",stdout);
	cin>>tmp;
	n=tmp.size();
	for(int i=1;i<=n;i++) a[i]=tmp[i-1];
	manacher();
	for(int i=1;i<=n;i++) b[i]=a[n-i+1];
	b[n+1]='#';
	for(int i=n+2;i<=2*n+1;i++) b[i]=a[i-n-1];
	Kmp();
	for(int i=n+2;i<=2*n+1;i++)
	{
        if(kmp[i]>n/2) {maxx[i-n-1]=maxx[i-n-2];continue;}
        int j=kmp[i];
		maxx[i-n-1]=max(maxx[i-n-2],j);
		if(maxx[i-n-2]>j) 
		{
			maxhao[i-n-1]=maxhao[i-n-2];
		}
		else
		{
			maxhao[i-n-1]=i-n-1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int tmp=min(maxx[i-d[i]],min(n-(i+d[i]-1),n/2));
		if(d[i]*2-1+2*tmp>anss*2+ansmid)
		{
			anss=tmp;
			ansmid=d[i]*2-1;
			haomid=i-d[i]+1;
			lmid=2*d[i]-1;
			haopre=maxhao[i-d[i]]-tmp+1;
			lpre=anss;
			haosuf=n-lpre+1;
		}
	}
	if(anss==0)
	{
		printf("1\n");
		printf("%d %d\n",haomid,lmid);
	}
	else
	{
		printf("3\n");
		printf("%d %d\n",haopre,lpre);
		printf("%d %d\n",haomid,lmid);
		printf("%d %d\n",haosuf,lpre);
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <cfloat>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
#pragma comment(linker, "/STACK:16777216")
#define pb push_back
#define L(s) (int)(s).size()
#define rp(i,n) for(int (i)=0;(i)<(n);++(i))
#define VI vector<int>
#define inf 1000000000
#define ll long long
#define C(a) memset((a),0,sizeof((a)))
#define all(s) (s).begin(),s.end()
#define pi 3.1415926535897932384626433832795
#define pdd pair<long double,long double>
#define mp make_pair
//#define x first
//#define y second
char s[111111];
char t[222222];
int d[111111];
int sf[222222];
int mx[111111];
int mps[111111];
int n;
void pals()
{
	int l=0,r=-1;
	rp(i,n)
	{
		int maxs=((i>r)?(0):min(d[l+r-i],r-i))+1;
		while(i+maxs<n&&i-maxs>=0&&s[i-maxs]==s[i+maxs])
			++maxs;
		d[i]=--maxs;
		if (i+maxs>r)
			l=i-maxs,r=i+maxs;
	}
}
void kmp()
{
	int m=0;
	for(int i=n-1;i>=0;--i)
		t[m++]=s[i];
	t[m++]='!';
	rp(i,n)
		t[m++]=s[i];
	sf[0]=-1;
	for(int i=1;i<m;++i)
	{
		int j=sf[i-1];
		while(j!=-1&&t[j+1]!=t[i])
			j=sf[j];
		if (t[j+1]==t[i])
			sf[i]=j+1;
		else
			sf[i]=-1;
	}
}
int main()
{
	gets(s);
	n=(int)strlen(s);
	pals();
	kmp();
	mx[0]=sf[n+1]+1;
	mps[0]=0;
	for(int i=1;i<n;++i)
		if	(mx[i-1]>sf[n+1+i]+1)
		{
			mx[i]=mx[i-1];
			mps[i]=mps[i-1];
		}
		else
		{
			mx[i]=sf[n+1+i]+1;
			mps[i]=i;
		}
	int ans=0;
	int pos1=0,pos2=0,pos3=0,len1=0,len2=0;
	rp(i,n)
		if (d[i]==i&&ans<2*d[i]+1)
		{
			ans=2*d[i]+1;
			pos1=pos3=-1;
			pos2=i+1-d[i];
			len1=0;
			len2=ans;
		}
		else
			if (d[i]+i==n-1&&ans<2*d[i]+1)
			{
				ans=2*d[i]+1;
				pos1=pos3=-1;
				pos2=i+1-d[i];
				len1=0;
				len2=ans;
			}
			else
				if (ans<2*d[i]+1+2*min(mx[i-d[i]-1],n-1-(i+d[i])))
				{
					ans=2*d[i]+1+2*min(mx[i-d[i]-1],n-1-(i+d[i]));
					len1=min(mx[i-d[i]-1],n-1-(i+d[i]));
					pos1=mps[i-d[i]-1]+1-len1+1;
					len2=2*d[i]+1;
					pos2=i+1-d[i];
					pos3=n+1-len1;
				}
	if (len1==0)
	{
		cout<<1<<endl;
		cout<<pos2<<" "<<len2<<endl;
	}
	else
	{
		cout<<3<<endl;
		cout<<pos1<<" "<<len1<<endl;
		cout<<pos2<<" "<<len2<<endl;
		cout<<pos3<<" "<<len1<<endl;
	}
}
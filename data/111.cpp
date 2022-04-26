//its not how good you are...its how good you want to be
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define inf 100000000
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define all(v) v.begin(),v.end()
#define S second
#define F first
#define boost1 ios::sync_with_stdio(false);
#define boost2 cin.tie(0);
#define mem(a,val) memset(a,val,sizeof a)

ll power[1000001],pre[1000001],suff[1000001],base=127,dp[1000001];
ll getpre(ll l,ll r)
{
	return pre[r]-pre[l-1]*power[r-l+1];
}	
ll getsuff(ll l,ll r)
{
	return suff[l]-suff[r+1]*power[r-l+1];
}
int main()
{
	boost1;boost2;
	string s;
	ll i,j,k,l,lo,mid,hi,x1,x2,x3,l1,l2,l3,x,y,ans=0;
	cin>>s;
	l=s.length();
	pre[0]=s[0]-'a';
	for(i=1;i<l;i++)
	pre[i]=pre[i-1]*base+s[i]-'a';
	suff[l-1]=s[l-1]-'a';
	for(i=l-2;i>=0;i--)
	suff[i]=suff[i+1]*base+s[i]-'a';
	power[0]=1;
	for(i=1;i<=l;i++)
	power[i]=base*power[i-1];
	for(i=0;i<=l;i++)
	dp[i]=inf;
	for(i=0;i<l;i++)
	{
		lo=0;
		hi=(l-i)/2;
		while(lo<hi)
		{
			mid=(lo+hi+1)/2;
			if(getpre(i,i+mid-1)==getsuff(l-mid,l-1))
			lo=mid;
			else
			hi=mid-1;
		}
		dp[lo]=min(dp[lo],i);
	}
	for(i=l;i>=0;i--)
	{
		dp[i-1]=min(dp[i-1],dp[i]);
		dp[i]+=i-1;
	}
	for(i=0;i<l;i++)
	{
		lo=0;
		hi=min(i,l-i-1);
		while(lo<hi)
		{
			mid=(lo+hi+1)/2;
			if(getpre(i-mid,i)==getsuff(i,i+mid))
			lo=mid;
			else
			hi=mid-1;
		}
		x=lo;
		lo=0;
		hi=l-x-1-i;
		while(lo<hi)
		{
			mid=(lo+hi+1)/2;
			if(dp[mid]+x<i)
			lo=mid;
			else
			hi=mid-1;
		}
		if(2*x+1+2*lo>ans)
		{
			ans=2*x+1+2*lo;
			x1=dp[lo]-lo+1;
			x2=i-x;
			x3=l-lo;
			l1=lo;
			l3=lo;
			l2=2*x+1;
		}
	}
	if(l1)
	{
		cout<<"3"<<endl;
		cout<<x1+1<<" "<<l1<<endl;
		cout<<x2+1<<" "<<l2<<endl;
		cout<<x3+1<<" "<<l3<<endl;
	}
	else
	{
		cout<<"1"<<endl;
		cout<<x2+1<<" "<<l2<<endl;
	}
	return 0;
}

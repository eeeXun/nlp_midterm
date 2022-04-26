#include<bits/stdc++.h>
#define N 100005
#define p1 19260817
#define p2 19491001
#define ull unsigned long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
char s[N];
int n,maxn[N],ans,num;
ull LtoR1[N],LtoR2[N],RtoL1[N],RtoL2[N],mul1[N],mul2[N],pos[N];
pii ans1,ans2,ans3;
void init(ull LtoR[],ull RtoL[],ull mul[],ull p)
{
	mul[0]=1;
	for(int i=1;i<n;++i)mul[i]=mul[i-1]*p;
	LtoR[0]=mul[n-1]*s[0];
	for(int i=1;i<n;++i)LtoR[i]=mul[n-i-1]*s[i]+LtoR[i-1];
	RtoL[n-1]=mul[n-1]*s[n-1];
	for(int i=n-2;i>=0;--i)RtoL[i]=mul[i]*s[i]+RtoL[i+1];
}
bool check(int i,int mid,ull LtoR[],ull RtoL[],ull mul[])
{
	ull hs1=(LtoR[i+mid-1]-LtoR[i]),hs2=(RtoL[i-mid+1]-RtoL[i]);
	hs1*=mul[i];
	hs2*=mul[n-i-1];
	return hs1==hs2;
}
void find_longest_odd_length_palindrome()
{
	pos[0]=0;
	for(int i=1;i<n;++i)
	if(maxn[i]>maxn[i-1])pos[i]=i;
	else maxn[i]=maxn[i-1],pos[i]=pos[i-1];
	for(int i=0;i<n;++i)
	{
		int l=1,r=min(i+1,n-i)+1;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(check(i,mid,LtoR1,RtoL1,mul1)&&check(i,mid,LtoR2,RtoL2,mul2))l=mid;
			else r=mid;
		}
		if(i+l-1==n||i-l+1==0)
		{
			if(l+l-1>ans)
			{
				ans=l+l;
				num=1;
				ans1=mp(i-l+1,l+l-1);
			}
			continue;
		}
		int t;
		if(maxn[i-l]>=n-(i+l))t=n-(i+l);
		else t=maxn[i-l];
		if(t+t+l+l-1>=ans)
		{
			ans=t+t+l+l-1;
			if(!t)
			{
				num=1;
				ans1=mp(i-l+1,l+l-1);
				continue;
			}
			num=3;
			ans1=mp(pos[i-l]-maxn[i-l]+1,t);
			ans2=mp(i-l+1,l+l-1);
			ans3=mp(n-t,t);
		}
	}
}
bool check2(int i,int mid,ull mul[],ull LtoR[],ull RtoL[])
{
	return (LtoR[i+mid-1]-(i>0?LtoR[i-1]:0))*mul[i]==RtoL[n-mid];
}
void init_every_index_suffix()
{
	int j=0;
	for(int i=0;i<n;++i)
	{
		int l=0,r=n-i;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(check2(i,mid,mul1,LtoR1,RtoL1)&&check2(i,mid,mul2,LtoR2,RtoL2))l=mid;
			else r=mid;
		}
		while(j<i+l)maxn[j]=j-i+1,++j;
	}
}
int main()
{
	scanf("%s",s);
	n=strlen(s);
	init(LtoR1,RtoL1,mul1,p1);
	init(LtoR2,RtoL2,mul2,p2);
	init_every_index_suffix();
	find_longest_odd_length_palindrome();
	if(num==1)printf("1\n%d %d",ans1.fi+1,ans1.se);
	else printf("3\n%d %d\n%d %d\n%d %d\n",ans1.fi+1,ans1.se,ans2.fi+1,ans2.se,ans3.fi+1,ans3.se);
	return 0;
}
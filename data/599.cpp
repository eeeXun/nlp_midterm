#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstdlib>
#include<map>
#include<vector>
#include<ctime>
#include<stack>
#include<cctype>
#include<set>
#define mp make_pair
#define pa pair<int,int>
#define INF 0x3f3f3f3f
#define inf 0x3f
#define fi first
#define se second
#define pb push_back
#define ll long long
#define ull unsigned long long

using namespace std;

inline ll read()
{
	long long f=1,sum=0;
	char c=getchar();
	while (!isdigit(c)){if (c=='-') f=-1;c=getchar();}
	while (isdigit(c)){sum=sum*10+c-'0';c=getchar();}
	return sum*f;
}
const int MAXN=100010;
char s[MAXN];
int p[MAXN],n;
void manacher()
{
	int mx=0,id=0;
	for (int i=1;i<=n;i++)
	{
		if (i<mx)
			p[i]=min(mx-i,p[2*id-i]);
		else
			p[i]=1;
		while (s[i+p[i]]==s[i-p[i]]) p[i]++;
		if (i+p[i]>mx)
			mx=i+p[i],id=i;
	}	
}
int f[MAXN*4];
void build(int root,int left,int right)
{
	if (left==right)
	{
		f[root]=left;
		return ;
	}
	int mid=(left+right)>>1;
	build(2*root,left,mid);
	build(2*root+1,mid+1,right);
	f[root]=(p[f[2*root]]>=p[f[2*root+1]])?f[2*root]:f[2*root+1];
}
int query(int root,int left,int right,int qleft,int qright)
{
	if (qleft<=left && right<=qright)
		return f[root];
	int mid=(left+right)>>1;
	if (qright<=mid)
		return query(2*root,left,mid,qleft,qright);
	else if (qleft>mid)
		return query(2*root+1,mid+1,right,qleft,qright);
	else
	{
		int ans1,ans2;
		ans1=query(2*root,left,mid,qleft,mid);
		ans2=query(2*root+1,mid+1,right,mid+1,qright);
		return (p[ans1]>=p[ans2])?ans1:ans2;
	}
}
#define P 2333
ull po[MAXN],hsh[MAXN];
vector <pa> ans;
ull get_hsh(int l,int len)
{
	return hsh[l+len-1]-hsh[l-1]*po[len];
}
#define P1 233
#define Mod 1000000007
ll PO[MAXN],HSH[MAXN];
ll get_HSH(int l,int len)
{
	return (HSH[l+len-1]-HSH[l-1]*PO[len]%Mod+Mod)%Mod;
}
int main()
{
		
	scanf("%s",s+1);
	n=strlen(s+1);
	s[n+1]='$'; 
	po[0]=1;
	for (int i=1;i<=n;i++)
		po[i]=po[i-1]*P;
	PO[0]=1;
	for (int i=1;i<=n;i++)
		PO[i]=PO[i-1]*P1,PO[i]%=Mod;
	manacher();
	build(1,1,n);
	for (int i=1;i<=n;i++)
		hsh[i]=hsh[i-1]*P+s[i]-'a'+1;
	for (int i=1;i<=n;i++)
		HSH[i]=HSH[i-1]*P1%Mod+s[i]-'a'+1,HSH[i]%=Mod;
	int pos=query(1,1,n,1,n);
	int anslen=p[pos]*2-1; 
	ans.push_back(mp(pos-p[pos]+1,anslen));
	int l1=1;
	ull hsh2=0;
	ll HSH2=0;
	for (int i=n;(n-i+1)*2<n;i--)
	{
		int l2=i,r2=n,len=r2-l2+1;
		hsh2=hsh2*P+s[i]-'a'+1;
		HSH2=(HSH2*P1%Mod+s[i]-'a'+1)%Mod;
		while ((get_hsh(l1,len)!=hsh2 || get_HSH(l1,len)!=HSH2) && l1<=n) l1++;
		int ed=l1+len-1;
		if (ed>=i) break;  
		int l=1,r=(i-ed)/2,mid,anss=0,npos;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (i-mid>=ed+mid && p[(pos=query(1,1,n,ed+mid,i-mid))]>=mid)
				anss=mid,l=mid+1,npos=pos;
			else
				r=mid-1;
		}
//		if(s[1]=='r'&&s[2]=='q'&&s[3]=='c'&&s[4]=='w'&&i==71171)
//			printf("%d %d %d\n",l1,i,anss);
		if (anslen<len*2+anss*2-1)
		{
			ans.clear();
			ans.push_back(mp(l1,len));
			ans.push_back(mp(npos-anss+1,anss*2-1));
			ans.push_back(mp(i,len));
			anslen=len*2+anss*2-1;
		}
	}
	printf("%d\n",(int)ans.size());
	for (int i=0;i<(int)ans.size();i++)
		printf("%d %d\n",ans[i].fi,ans[i].se);
	return 0;
}

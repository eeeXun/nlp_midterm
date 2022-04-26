#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<climits>
#define BAS 37
#define uint unsigned long long int
#define N 200010
#define INF (INT_MAX/10-10)
using namespace std;
int ans,n;char s[N],t[N];
uint hv[N],mi[N];
int r[N],z[N],f[N];
int l[10],rr[10],k;
inline uint calc(int s,int t)
{
	return hv[t]-hv[s-1]*mi[t-s+1];
}
inline int get_z(int x)
{
	int L=1,R=2*n-x+1,mid=(L+R)>>1;
	if(t[x]^t[1]) return 0;
	while(L<=R)
	{
		if(calc(x,x+mid-1)==calc(1,mid))
			L=mid+1;
		else R=mid-1;mid=(L+R)>>1;
	}
	return R;
}
inline int get_r(int x)
{
	int L=1,R=min(x-n-1,2*n-x),mid=(L+R)>>1;
	if(x==1||x==n||t[x-1]!=t[x+1]) return 0;
	while(L<=R)
	{
		if(calc(x-mid,x-1)==calc(2*n-x-mid+1,2*n-x)) L=mid+1;
		else R=mid-1;mid=(L+R)>>1;
	}
	return R;
}
int main()
{
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=mi[0]=1;i<=n;i++) mi[i]=mi[i-1]*BAS;
	for(int i=1;i<=n;i++) t[i]=s[i];
	for(int i=1;i<=n/2;i++) swap(t[i],t[n-i+1]);
	for(int i=1,x=n;i<=n;i++) t[++x]=s[i];
	for(int i=1;i<=2*n;i++) hv[i]=(hv[i-1]+t[i]-'a'+1)*BAS;
	for(int i=n+1;i<=2*n;i++) r[i-n]=get_r(i);
	for(int i=1;i<=2*n;i++) z[i]=get_z(i);
	for(int i=1;i<=n;i++) f[i]=INF;
	for(int i=n+1;i<=2*n;i++) f[z[i]]=min(f[z[i]],i-n);
	for(int i=n-1;i>=1;i--) f[i]=min(f[i],f[i+1]);
//	for(int i=1;i<=n;i++) cout<<i<<" "<<r[i]<<" "<<f[i]<<endl;
	for(int i=1;i<=n;i++)
	{
		int x=2*r[i]+1,L=0,R=min(n-i-r[i],i-r[i]-1),mid=(L+R)>>1;
		if(x>ans) ans=x,k=1,l[1]=i-r[i],rr[1]=i+r[i];
		while(L<=R)
		{
			if(f[mid]+mid-1<i-r[i]) L=mid+1;
			else R=mid-1;mid=(L+R)>>1;
		}
		if(x+2*R>ans) ans=x+2*R,k=3,l[2]=i-r[i],rr[2]=i+r[i],l[1]=f[R],rr[1]=f[R]+R-1,l[3]=n-R+1,rr[3]=n;
	}
	printf("%d\n",k);
	for(int i=1;i<=k;i++) printf("%d %d\n",l[i],rr[i]-l[i]+1);
	return 0;
}
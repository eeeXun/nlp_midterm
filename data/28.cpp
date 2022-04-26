#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int MAXN=100010;
const int M=1<<17;
const int inf=0x0f0f0f0f;
char S[MAXN],R[MAXN];
typedef long long ll;
ll SEED=1000000007;
ll HS[MAXN],HR[MAXN],PS[MAXN];
inline ll geth(ll *H,int l,int len)
{
	return H[l+len-1]-H[l-1]*PS[len];
}
int N;
int maxplen[MAXN];//sfx[i]最长的一个前缀，其逆序是原串的后缀（不重叠）
int T[M+M];//对每个pfx[i]计算长度最大的一个后缀，其逆序是原串的后缀
inline void setl(int l,int r,int x)
{
	for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1)
	{
		if(~l&1&&x<T[l+1])T[l+1]=x;
		if(r&1&&x<T[r-1])T[r-1]=x;
	}
}
int ql(int x)
{
	int ret=x+1;
	for(x+=M;x;x>>=1)if(T[x]<ret)ret=T[x];
	return ret;
}
int maxslen[MAXN],maxsleni[MAXN];
int mmaxslen[MAXN],mmaxsleni[MAXN];
int ans;
int l1,ll1,l2,ll2;
int main()
{
	scanf("%s",S+1);
	N=strlen(S+1);
	PS[0]=1;
	for(int i=1;i<=N;i++)R[N-i+1]=S[i]-='a';
	for(int i=1;i<=N;i++)PS[i]=PS[i-1]*SEED,HS[i]=HS[i-1]*SEED+S[i],HR[i]=HR[i-1]*SEED+R[i];
	for(int i=1;i<=N;i++)
	{
		int l=0,r=((N-i+1)>>1)+1;
		while(l+1!=r)
		{
			int mid=(l+r)>>1;
			if(geth(HS,i,mid)==HR[mid])l=mid;
			else r=mid;
		}
		maxplen[i]=l;
	}
	for(int i=1;i<=N+M;i++)T[i]=inf;
	for(int i=1;i<=N;i++)setl(i,i+maxplen[i]-1,i);
	for(int i=1;i<=N;i++)maxsleni[i]=ql(i),maxslen[i]=i-maxsleni[i]+1;
	for(int i=1;i<=N;i++)if(maxslen[i]>mmaxslen[i-1])mmaxslen[i]=maxslen[i],mmaxsleni[i]=maxsleni[i];
	else mmaxslen[i]=mmaxslen[i-1],mmaxsleni[i]=mmaxsleni[i-1];
	for(int i=1;i<=N;i++)//计算以i为中心的最长回文串
	{
		int l=1,r=min(i,N-i+1)+1;
		while(l+1!=r)
		{
			int mid=(l+r)>>1;
			if(geth(HS,i,mid)==geth(HR,N-i+1,mid))l=mid;
			else r=mid;
		}
		int tans=l+l-1,ml=tans;
		r=i+l,l=i-l;
		int ll;
		if(N-mmaxslen[l]+1<r)tans+=(ll=N-r+1)*2;
		else tans+=(ll=mmaxslen[l])*2;
		if(tans>ans)ans=tans,l1=mmaxsleni[l],ll1=ll,l2=l+1,ll2=ml;
	}
	if(ll1)printf("3\n%d %d\n%d %d\n%d %d\n",l1,ll1,l2,ll2,N-ll1+1,ll1);
	else printf("1\n%d %d\n",l2,ll2);
	return 0;
}

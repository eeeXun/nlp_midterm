#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef pair<int,int> pr;
pr Interval[100010];
int p[100010],Next[100010],ans[100010],len,vis[100010],ST[100010][19];
char str[100030],rev[100030];
void manacher()
{
	int Max=0,id=0;
	for (int i=1;i<=len;i++)
	{
		if (i<=Max) p[i]=min(Max-i+1,p[2*id-i]);
		while (i-p[i]>=1&&i+p[i]<=len&&str[i-p[i]]==str[i+p[i]]) p[i]++;
		if (i+p[i]-1>Max) Max=i+p[i]-1,id=i;
	}
}
void KMP()
{
	int k=0;
	Next[1]=0;
	for (int i=2;i<=len;i++)
	{
		while (k&&rev[k+1]!=rev[i]) k=Next[k];
		if (rev[k+1]==rev[i]) k++;
		Next[i]=k;
	}
}
void init()
{
	int k=0;
	for (int i=1;i<=len;i++)
	{
		while (k&&rev[k+1]!=str[i]) k=Next[k];
		if (rev[k+1]==str[i]) k++;
		//rev[1,k] matches str[i-k+1,i] -> str[i-k+1,i] matches str[n-k+1,n]
		//last: [i+1,n-k]
		if (i+1>len-k) return;
		if (!vis[k])
		{
			vis[k]=i;
			Interval[k]=pr(i+1,len-k);
		}
	}
}
int query(int L,int R)
{
	if (L>R) return -1;
	int lg=floor(log10((double)R-L+1)/log10((double)2));
	return max(ST[L][lg],ST[R-(1<<lg)+1][lg]);
}
int Binary_Search(int L,int R)
{
	int l=1,r=len;
	while (l<r)
	{
		int mid=(l+r+1)>>1;
		if (query(L+mid-1,R-mid+1)>=mid) l=mid;
		else r=mid-1;
	}
	return l;
}
int main()
{
	scanf("%s",str+1);
	len=strlen(str+1);
	for (int i=1;i<=len;i++) rev[i]=str[len-i+1];
	manacher();
	KMP();
	init();
	for (int i=len;i>=1;i--)
	{
		ST[i][0]=p[i];
		for (int j=1;j<=17;j++)
		{
			if (i+(1<<j)>len) break;
			ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
		}
	}
	vis[0]=1;Interval[0]=pr(1,len);
	int Maxi=0;
	for (int i=0;vis[i];i++)
	{
		ans[i]=2*Binary_Search(Interval[i].first,Interval[i].second)-1;
		//if you choose suffix [n-i+1,n], the maximum length of B is ans[i]. The lengtn of the passwd you get is i+ans[i]+i
		if (2*i+ans[i]>Maxi*2+ans[Maxi]) Maxi=i;
	}
	if (Maxi==0)//A=C='' is the best.
	{
		printf("1\n");
		for (int i=1;i<=len;i++)//Check the middle point of B
			if (p[i]*2-1==Maxi*2+ans[Maxi])
			{
				printf("%d %d\n",i-p[i]+1,p[i]*2-1);
				return 0;
			}
	}
	else
	{
		printf("3\n");
		printf("%d %d\n",Interval[Maxi].first-Maxi,Maxi);
		for (int i=Interval[Maxi].first;i<=Interval[Maxi].second;i++)
			if (min(p[i],min(i-Interval[Maxi].first,Interval[Maxi].second-i)+1)*2-1+2*Maxi==Maxi*2+ans[Maxi])
			{
				printf("%d %d\n",i-(ans[Maxi]>>1),ans[Maxi]);
				break;
			}
		printf("%d %d\n",len-Maxi+1,Maxi);
	}
	return 0;
}
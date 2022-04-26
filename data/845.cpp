#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200010;
int n,q,p[maxn],cur,mid,l,r,fail[maxn],a[maxn],b[maxn],ans,nww;
char s[maxn],t[maxn],rev[maxn];
int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	t[0]='@';for(int i=1;i<=n;i++)t[i]=s[i],b[i]=n+1;t[n+1]='#';
	q=n+1;mid=r=1;
	for(int i=1;i<=q;i++)
	{
		if(i<=r)p[i]=min(p[mid+mid-i],r-i+1);
		while(t[i-p[i]]==t[i+p[i]])p[i]++;
		if(i+p[i]-1>=r)r=i+p[i]-1,mid=i;
	}
	for(int i=1;i<=n;i++)rev[i]=s[n-i+1];
	for(int i=2,j=0;i<=n;i++)
	{
		while(j&&rev[i]!=rev[j+1])j=fail[j];
		if(rev[i]==rev[j+1])j++;
		fail[i]=j;
	}
	for(int i=1,j=0;i<=n;i++)
	{
		while(j&&s[i]!=rev[j+1])j=fail[j];
		if(s[i]==rev[j+1])j++;
		a[i]=j;if(b[j]==n+1)b[j]=i;
	}
	for(int i=1;i<=n;i++)
	{
		l=0;r=n+1;
		while(l+1<r)
		{
			int mid=(l+r)>>1;
			if(i-p[i]+1>b[mid]&&i+p[i]-1<n-mid+1)l=mid;
			else r=mid;
		}
		ans=max(ans,2*p[i]-1+2*l);
	}
	for(int i=1;i<=n;i++)
	{
		l=0;r=n+1;
		while(l+1<r)
		{
			int mid=(l+r)>>1;
			if(i-p[i]+1>b[mid]&&i+p[i]-1<n-mid+1)l=mid;
			else r=mid;
		}
		if(ans==2*p[i]-1+2*l)
		{
			if(l==0)printf("1\n%d %d\n",i-p[i]+1,2*p[i]-1);
			else printf("3\n%d %d\n%d %d\n%d %d\n",b[l]-l+1,l,i-p[i]+1,2*p[i]-1,n-l+1,l);
			return 0;
		}
	}
	return 0;
}
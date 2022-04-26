#include<cstdio>
#include<cstring>
#include<iostream>
#define ull unsigned long long
using namespace std;
const int N=100010;
const int bas=211;
ull ha[N],fha[N],mi[N];
int n,z[2*N],cnt,pos[2*N];
struct huiwen{
	int l,r;
}q[N];
char s[2*N];
int ans,pans[4],lans[4];
ull gha(int l,int r)
{
	return ha[r]-ha[l-1]*mi[r-l+1];
}
ull fgha(int l,int r)
{
	return fha[l]-fha[r+1]*mi[r-l+1];
}
void getpos(int i)
{
	int r=min(i,n-i-1),l=0,ans=0;
	while (l<=r)
	{
		int mid=l+r>>1;
		if (gha(i-mid,i)==fgha(i,i+mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	q[i].l=i-ans,q[i].r=i+ans;
}
void findhw()
{
	for (int i=0;i<n;i++)
		getpos(i);
}
void zalo()
{
	int l=0,r=0;
	for (int i=1;i<=2*n;i++)
	{
		if (i<=n)pos[i]=1e9;
		if (i>r)
		{
			int t=i,bg=0;
			while (s[t]==s[bg]) t++,bg++;
			z[i]=bg;
			l=i,r=t-1;
		}
		else
		{
			if (i+z[i-l]-1<r) z[i]=z[i-l];
			else
			{
				int t=r+1,bg=r-i+1;
				while (s[t]==s[bg]) t++,bg++;
				z[i]=bg;
				l=i,r=t-1;
			}
		}
		if (i>n) pos[z[i]]=min(pos[z[i]],i+z[i]-1-n);
	}
	for (int i=n-1;i>=1;i--) pos[i]=min(pos[i],pos[i+1]-1);
	//for (int i=1;i<=n;i++) cout<<i<<" "<<pos[i]<<endl;
}
int main()
{
	scanf("%s",s);
	n=strlen(s);
	ha[0]=s[0];
	mi[0]=1;
	for (int i=1;i<=n;i++) mi[i]=mi[i-1]*bas;
	for (int i=1;i<n;i++) ha[i]=ha[i-1]*bas+s[i]; 
	for (int i=n-1;i;i--) fha[i]=fha[i+1]*bas+s[i];
	findhw();
	//if (q[n/2].l==0) {printf("%d\n%d %d\n",1,1,n);return 0;}
	s[n]='$';
	for (int i=0;i<n;i++)
		s[i+n+1]=s[i];
	for (int i=0,j=n-1;i<j;i++,j--) swap(s[i],s[j]);
	zalo();
	for (int i=0;i<n;i++)
	{
		int l=q[i].r+1,r=n-1,as=-1;
		while (l<=r)
		{
			int mid=l+r>>1;
			if (pos[n-mid]<=q[i].l) as=mid,r=mid-1;
			else l=mid+1;
		}
		//cout<<q[i].l<<" "<<q[i].r<<" "<<as<<" "<<ans<<endl;
		if (as==-1) {if (q[i].r-q[i].l+1>ans) ans=q[i].r-q[i].l+1,cnt=1,pans[1]=q[i].l,lans[1]=ans;}
		else
		{
			if (q[i].r-q[i].l+1+2*(n-as)>ans)
			{
				ans=q[i].r-q[i].l+1+2*(n-as);
				pans[1]=pos[n-as]-n+as,lans[1]=n-as;
				pans[2]=q[i].l,lans[2]=q[i].r-q[i].l+1;
				pans[3]=as,lans[3]=n-as;
				cnt=3;
			}
		}
	}
	printf("%d\n",cnt);
	for (int i=1;i<=cnt;i++) printf("%d %d\n",pans[i]+1,lans[i]);
}

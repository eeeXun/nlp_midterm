#include<bits/stdc++.h>
#define maxn 1000000
using namespace std;
struct chuan {int l,len;};
char s[maxn],t[maxn],now[maxn];
int len,next[maxn],p[maxn],v[maxn],ans,mx[maxn],wz[maxn];
chuan pre,mid,suf;
void build(int now, int l, int r)
{
	if (l==r)
	{
		wz[now]=l; mx[now]=v[l];
		return;
	}
	int mid=(l+r)/2;
	build(now*2,l,mid); build(now*2+1,mid+1,r);
	if (mx[now*2]>mx[now*2+1])
	{
		mx[now]=mx[now*2]; wz[now]=wz[now*2];
	}
	else
	{
		mx[now]=mx[now*2+1]; wz[now]=wz[now*2+1];
	}
}
int findmx(int now, int l, int r, int left, int right)
{
	if (l==left && r==right) return mx[now];
	int mid=(l+r)/2,ans=0;
	if (left<=mid) ans=findmx(now*2,l,mid,left,min(right,mid));
	if (right>=mid+1) ans=max(ans,findmx(now*2+1,mid+1,r,max(left,mid+1),right));
	return ans;
}
int findwz(int now, int l, int r, int left, int right)
{
	if (l==left && r==right) return wz[now];
	int mid=(l+r)/2,t1=0,t2=0;
	if (left<=mid) t1=findwz(now*2,l,mid,left,min(right,mid));
	if (right>=mid+1) t2=findwz(now*2+1,mid+1,r,max(left,mid+1),right);
	if (t1==0) return t2; else if (t2==0) return t1;
	if (v[t1]>v[t2]) return t1; else return t2;
}
int main()
{
	char c=getchar();
	while (c!='\n')
	{
		len++; s[len]=c;
		c=getchar();
	}
	int n=len;
	t[1]='$'; t[2]='#';
	for (int i=1;i<=len;i++)
	t[2*i+1]=s[i],t[2*i+2]='#';
	t[2*len+3]='?';
	len=len*2+3;
	int mx=2,id=2;
	for (int i=3;i<=len-1;i++)
	{
		if (i<=mx) p[i]=min(p[2*id-i],mx-i+1);
		while (t[i+p[i]]==t[i-p[i]]) p[i]++;
		if (i%2) 
		{
			v[i/2]=p[i]-1;
			if (p[i]-1>ans)
			{
				ans=p[i]-1; mid=(chuan){i/2-ans/2,ans};
			}
		}
		if (i+p[i]-1>mx)
		{
			mx=i+p[i]-1; id=i;
		}
	}
	build(1,1,n);
	pre=suf=(chuan){0,0}; len=0;
	int j=0,p1=0,p2;
	for (int i=n;i>=1;i--)
	{
		now[++len]=s[i];
		if (len>1)
		{
			while (j && now[j+1]!=now[len]) j=next[j];
			if (now[j+1]==now[len]) j++; 
			next[len]=j; 
		}
		p2=len-1;
		p1++;
		while (p1<i)
		{
			while (p2 && now[p2+1]!=s[p1]) p2=next[p2];
			if (now[p2+1]==s[p1]) p2++;
			if (p2==len) break;
			p1++;
		}
		if (p1>=i) break;
		int zuo=p1+1,you=i-1,lef=0,righ=you-zuo+1,sum=0;
		while (lef<=righ)
		{
			int mid=(lef+righ)/2,cd=2*mid+1;
			if (cd>=you-zuo+1)
			{
				righ=mid-1; continue;
			}
			if (findmx(1,1,n,zuo+mid,you-mid)>=cd) 
			{
				sum=cd; lef=mid+1;
			}
			else righ=mid-1;
		}
		if (sum!=0 && sum+len*2>ans)
		{
			ans=sum+len*2;
			pre=(chuan){zuo-len,len};
			suf=(chuan){i,len};
			int wz=findwz(1,1,n,zuo+sum/2,you-sum/2);
			mid=(chuan){wz-sum/2,sum};
		}
	}
	if (pre.l==0)
	{
		printf("1\n%d %d\n",mid.l,mid.len);
	}
	else
	{
		printf("3\n%d %d\n",pre.l,pre.len);
		printf("%d %d\n%d %d\n",mid.l,mid.len,suf.l,suf.len);
	}
	return 0;
}
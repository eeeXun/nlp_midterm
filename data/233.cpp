#include<bits/stdc++.h>
using namespace std;
int n,lc,lb,l,maxr,ans1,ans2,ans,len,Al,Ar,Bl,Br,Cl,Cr,al,ar,bl,br,cl,cr,d[200005],nxt[200005],maxn[200005],maxn1[200005];
char a[200005],b[200005],c[200005];
//c manacher    b kmp
int get(int x,char y)
{
	if(b[x+1]==y) return x+1;
	if(x) return get(nxt[x],y);
	return 0;
}
int main()
{
	int i,j;
	scanf("%s",a+1);
	n=strlen(a+1);
	c[1]='#';
	for(i=1;i<=n;i++) c[i*2]=a[i],c[i*2+1]='#';
	for(i=1;i<=n;i++)
	{
		b[i]=a[n-i+1];
		b[i+n]=a[i];
	}
	lb=2*n;lc=2*n+1;
	for(i=1;i<=lc;i++)
	{
		if(i<=maxr) d[i]=min(d[l+maxr-i],maxr-i+1);
		while(i-d[i]>0 && i+d[i]<=lc && c[i-d[i]]==c[i+d[i]]) d[i]++;
		if(i+d[i]-1>maxr)
		{
			l=i-d[i]+1;
			maxr=i+d[i]-1;
		}
	}
	for(i=2;i<=lb;i++)
	{
		nxt[i]=get(nxt[i-1],b[i]);
		if(i-nxt[i]+1>n)
		{
			if(nxt[i]>=maxn[i-1])
			{
				maxn[i]=nxt[i];
				maxn1[i]=i;
			}
			else
			{
				maxn[i]=maxn[i-1];
				maxn1[i]=maxn1[i-1];
			}
		}
	}
	for(i=n+1;i<=lb;i++)
	{
		bl=i-d[(i-n)*2]/2+1;
		br=i+d[(i-n)*2]/2-1;
		if(br-bl+1>ans)
		{
			ans=br-bl+1;
			Al=bl;Ar=bl-1;
			Bl=bl;Br=br;
			Cl=br+1;Cr=br;
		}
		if(maxn[bl-1]==0 && br-bl+1>ans)
		{
			ans=br-bl+1;
			Al=bl;Ar=bl-1;
			Bl=bl;Br=br;
			Cl=br+1;Cr=br;
		}
		ar=maxn1[bl-1];
		al=ar-maxn[bl-1]+1;
		cr=lb;
		cl=cr-maxn[bl-1]+1;
		if(al<=n || ar<=n || cl<=br) continue;
		len=ar-al+br-bl+cr-cl+3;
		if(len>ans)
		{
			ans=len;
			Al=al;Ar=ar;Bl=bl;Br=br;Cl=cl;Cr=cr;
		}
	}
	if(Ar+1==Bl && Br+1==Cl) printf("1\n%d %d",Al-n,Cr-Al+1);
	else printf("3\n%d %d\n%d %d\n%d %d",Al-n,Ar-Al+1,Bl-n,Br-Bl+1,Cl-n,Cr-Cl+1);
	return 0;
}
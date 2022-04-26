#include<bits/stdc++.h>
using namespace std;
string s;
int z[202020],cc[202020],wr[202020],ed[202020],cn[202020];
void get_z(string SS)
{
	int l=0,r=0,n=SS.size();
	for(int i=1;i<n;i++)
	{
		if(i>r)
		{
			l=i;
			r=i;
			while(r<n && SS[r-l]==SS[r])
			{
				r++;
			}
			z[i]=r-l;
			r--;
		}
		else
		{
			int k=i-l;
			if(z[k]<r-i+1)
			{
				z[i]=z[k];
			}
			else
			{
				l=i;
				while(r<n && SS[r-l]==SS[r])
				{
					r++;
				}
				z[i]=r-l;
				r--;
			}
		}
	}
}
void hwc()
{
	int n=s.size(),l=0,r=-1;
	for(int i=0;i<n;i++)
	{
		int kkk;
		if(i>r)
		{
			kkk=1;
		}
		else
		{
			kkk=min(cc[l+r-i]+1,r-i+1);
		}
		while(i+kkk<n && i-kkk>=0 && s[i+kkk]==s[i-kkk])
		{
			kkk++;
		}
		kkk--;
		cc[i]=kkk;
		if(i+kkk>r)
		{
			l=i-kkk;
			r=i+kkk;
		}
	}
}
int main()
{
	cin>>s;
	hwc();
	string SS=s;
	reverse(SS.begin(),SS.end());
	SS+='#';
	SS+=s;
	get_z(SS);
	int n=s.size();
	for(int i=0;i<n;i++)
	{
		cc[i]++;
	}
	for(int i=0;i<n+10;i++)
	{
		wr[i]=n;
	}
	wr[0]=0;
	for(int i=n+1;i<=n+n;i++)
	{
		if(z[i]==0)
		{
			continue;
		}
		wr[z[i]]=min(wr[z[i]],i-n-1);
	}
	for(int i=n+1;i>=0;i--)
	{
		wr[i]=min(wr[i],wr[i+1]);
		ed[i]=wr[i]+i;
	}
	for(int i=0;i<=n;i++)
	{
		int a=ed[i],b=ed[i+1];
		for(int j=a;j<b;j++)
		{
			cn[j]=i;
		}
	}
	int mx=0,ans=-1;
	for(int i=0;i<n;i++)
	{
		int ll=i-cc[i]+1,rr=n-i-cc[i],kk=cc[i]*2-1+2*min(cn[ll],rr);
		if(kk>mx)
		{
			mx=kk;
			ans=i;
		}
	}
	int zhongjian=cc[ans]*2-1,liangbian=(mx-zhongjian)/2,ll=wr[liangbian]+1,rr=n-liangbian+1;
	if(zhongjian<mx)
	{
		cout<<3<<endl;
		cout<<ll<<' '<<liangbian<<endl<<ans-cc[ans]+2<<' '<<zhongjian<<endl<<rr<<' '<<liangbian<<endl;
	}
	else
	{
		cout<<1<<endl;
		cout<<ans-cc[ans]+2<<' '<<zhongjian<<endl;
	}
	return 0;
}
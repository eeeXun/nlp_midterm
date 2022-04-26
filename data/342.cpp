#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define CHECK(x) cout << (#x) << " is " << (x) << endl;
#define MOD 1000000007
#define MAX 200005
int base =2*(rand()%100005+68745)+1;
struct Hash
{
	vector<int> v;
	vector<int> pw;
	Hash(string s)
	{
		v.push_back(0);
		pw.push_back(1);
		for(auto &cv:s)
		{
			v.push_back((1LL*v.back()*base+cv)%MOD);
			pw.push_back(1LL*pw.back()*base%MOD);
		}
	}
	int get_hash(int l,int r)
	{
		return ((v[r+1]-1LL*v[l]*pw[r-l+1]%MOD)+MOD)%MOD;
	}
};
int pal[MAX];
int pref[MAX];
int last[MAX];
int lg[(1<<20)+1];
int dp[22][MAX];
int query(int l,int r)
{
	int len=(r-l+1);
	if(len<=0)
		return 0;
	return max(dp[lg[len]][l],dp[lg[len]][r-(1<<lg[len])+1]);
}
void solve()
{
	string s;
	cin>>s;
	int n=s.size();
	Hash sh(s);
	reverse(s.begin(), s.end());
	Hash sp(s);
	for(int i=0;i<n;i++)
	{
		int mx=(i+1)/2;
		int len=0;
		for(int j=20;j>=0;j--)
		{
			int k=len+(1<<j);
			if(k<=mx&&sp.get_hash(0,k-1)==sh.get_hash(n-i-1,n-i-1+k-1))
				len=k;
		
		}
		pref[i]=len;
		len=1;
		mx=min(i+1,n-i);
		for(int j=20;j>=0;j--)
		{
			int k=(len)+(1<<j);
			if(k<=mx&&sp.get_hash(i,i+k-1)==sh.get_hash(n-i-1,n-i-1+k-1))
				len=k;
		}
		pal[i-len+1]=max(2*len-1,pal[i-len+1]);
	}
	int idx=0;
	for(int i=0;i<n;i++)
	{
		if(i)
			pal[i]=max(pal[i-1]-2,pal[i]);
		dp[0][i]=pal[i];
		if(pal[i]>pal[idx])
			idx=i;
	}

	for(int j=1;j<=20;j++)
	{
		for(int i=n-1;i>=0;i--)
		{
			dp[j][i]=dp[j-1][i];
			if(i+(1<<(j-1))<n)
				dp[j][i]=max(dp[j][i],dp[j-1][i+(1<<(j-1))]);
		}
		lg[1<<j]=j;
	}
	lg[1]=0;
	for(int i=2;i<=n;i++)
		if(!lg[i])
			lg[i]=lg[i-1];
	for(int i=0;i<n;i++)
	{
		last[pref[i]]=i;
	}

	for(int i=n;i>=0;i--)
	{
		last[i]=max(last[i+1],last[i]);
	}
	int ans=0;
	int a,b,c,len1,len2;
	for(int i=0;i<n;i++)
	{
		if(last[i+1]-i-1<=i)
			continue;
		int r=last[i+1]-i;
		r--;
		int cur=2*(i+1);
		int clen2=0;
		for(int j=20;j>=0;j--)
		{
			int k=clen2+(1<<j);
			if(r-k+1>i&&query(i+1,r-(2*k-1)+1)>=(2*k-1))
			{
				clen2=k;
			}
		}
		clen2=2*clen2-1;
		cur+=clen2;
		if(cur>ans)
		{
			ans=cur;
			a=i;
			b=last[i+1]-i;
			len1=i+1;
			b+=len1-1;
			len2=clen2;
			c=r-len2+1;

			for(int j=20;j>=0;j--)
			{
				int k=c-(1<<j);
				if(k>=i+1&&query(i+1,k)==len2)
				{
						c=k;
				}
			}
			c+=len2-1;
		}

	}
	if(pal[idx]>ans)
	{
		cout<<1<<endl;
		ans=pal[idx];
		idx=n-idx;
		cout<<idx-ans+1<<' '<<ans<<endl;
	}
	else if(len2)
	{
		cout<<3<<endl;
		a=n-a;
		b=n-b;
		c=n-c;
		cout<<b<<' '<<len1<<endl;
		cout<<c<<' '<<len2<<endl;
		cout<<a<<' '<<len1<<endl;
	}
	else
	{
		a=n-a;
		b=n-b;
		cout<<2<<endl;
		cout<<b<<' '<<len1<<endl;
		cout<<a<<' '<<len1<<endl;
	}


}
int32_t main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	int t=1;
	// cin>>t;
	while(t--)
	{
		solve();
	}
    return 0;
}
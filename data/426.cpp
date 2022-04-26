//problem:
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fst first
#define scd second

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

inline int read(){
	int f=1,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline ll readll(){
	ll f=1,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN=2e5+5;
char s[MAXN];
struct SA{
	int n,m,c[MAXN],x[MAXN],y[MAXN],sa[MAXN],rk[MAXN],ht[MAXN],lg[MAXN],st[MAXN][20];
	void init_sa(){
		m=114514;
		for(int i=1;i<=n;++i)c[x[i]=s[i]]++;
		for(int i=1;i<=m;++i)c[i]+=c[i-1];
		for(int i=n;i>=1;--i)sa[c[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1){
			int num=0;
			for(int i=n-k+1;i<=n;++i)y[++num]=i;
			for(int i=1;i<=n;++i)if(sa[i]>k)y[++num]=sa[i]-k;
			for(int i=1;i<=m;++i)c[i]=0;
			for(int i=1;i<=n;++i)c[x[i]]++;
			for(int i=1;i<=m;++i)c[i]+=c[i-1];
			for(int i=n;i>=1;--i)sa[c[x[y[i]]]--]=y[i],y[i]=0;
			for(int i=1;i<=n;++i)swap(x[i],y[i]);
			x[sa[1]]=num=1;
			for(int i=2;i<=n;++i){
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
			}
			if(num==n)break;
			m=num;
		}
		for(int i=1;i<=n;++i)rk[sa[i]]=i;
		for(int i=1;i<=n;++i)assert(rk[i]==x[i]);
		int k=0;
		for(int i=1;i<=n;++i){
			if(rk[i]==1)continue;
			if(k)--k;
			int j=sa[rk[i]-1];
			while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])++k;
			ht[rk[i]]=k;
		}
		lg[0]=-1;
		for(int i=1;i<=n;++i)lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;++i)st[i][0]=ht[i];
		for(int j=1;j<20;++j){
			for(int i=1;i+(1<<(j-1))<=n;++i){
				st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
			}
		}
	}
	int rmq(int x,int y){
		assert(x!=y);
		if(x>y)swap(x,y);
		++x;
		int k=lg[y-x+1];
		return min(st[x][k],st[y-(1<<k)+1][k]);
	}
	int get_lcp(int x,int y){
		assert(x!=y);
		return rmq(rk[x],rk[y]);
	}
	SA(){}
}sa;
int n;
inline int revpos(int i){assert(1<=i&&i<=n);return n+2+n-i;}
int solve1(){
	int ans=1;
	for(int i=1;i<=n;++i)ans=max(ans,sa.get_lcp(i,revpos(i)));
	return ans*2-1;
}
void get_ans1(int ans){
	cout<<1<<endl;
	ans=(ans+1)/2;
	for(int i=1;i<=n;++i)if(sa.get_lcp(i,revpos(i))==ans){
		cout<<i-ans+1<<" "<<ans*2-1<<endl;
		return;
	}
	assert(0);
}

int rt[MAXN];
struct FrogTree{
	int sum[MAXN*30],ls[MAXN*30],rs[MAXN*30],cnt;
	void modify(int &x,int y,int l,int r,int pos){
		x=++cnt;
		ls[x]=ls[y],rs[x]=rs[y],sum[x]=sum[y]+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(pos<=mid)modify(ls[x],ls[y],l,mid,pos);
		else modify(rs[x],rs[y],mid+1,r,pos);
	}
	int query(int x,int y,int l,int r,int ql,int qr){
		if(!x)return 0;
		if(ql<=l&&qr>=r)return sum[x]-sum[y];
		int mid=(l+r)>>1,res=0;
		if(ql<=mid)res+=query(ls[x],ls[y],l,mid,ql,qr);
		if(qr>mid)res+=query(rs[x],rs[y],mid+1,r,ql,qr);
		return res;
	}
	FrogTree(){}
}T;//主席树
int res[MAXN];
int solve3(){
	int ans=0;
	for(int i=1;i<=n;++i)T.modify(rt[i],rt[i-1],1,sa.n,sa.rk[i]);
	for(int i=1;i<=n;++i){
		int len=sa.get_lcp(i,revpos(i));
		//cout<<i<<" "<<len<<endl;
		assert(len>=1&&len<=i&&i+len-1<=n);
		if(len==i||i+len-1==n)continue;
		int a=1,b=i-len,c=n+2,d=revpos(i+len);
		int L=0,R=min(b-a+1,d-c+1);
		while(L<R){
			int Mid=(L+R+1)>>1;
			int lrange,rrange;
			int l=1,r=sa.rk[c];
			while(l<r){
				int mid=(l+r)>>1;
				if(sa.rmq(mid,sa.rk[c])>=Mid)r=mid;
				else l=mid+1;
			}
			lrange=l;
			l=sa.rk[c],r=sa.n;
			while(l<r){
				int mid=(l+r+1)>>1;
				if(sa.rmq(mid,sa.rk[c])>=Mid)l=mid;
				else r=mid-1;
			}
			rrange=l;
			if(T.query(rt[b-Mid+1],rt[a-1],1,sa.n,lrange,rrange))L=Mid;
			else R=Mid-1;
		}
		if(L)ans=max(ans,L*2+len*2-1),res[i]=L;
	}
	return ans;
}
void get_ans3(int ans){
	cout<<3<<endl;
	for(int i=1;i<=n;++i){
		int len=sa.get_lcp(i,revpos(i));
		if(res[i]&&res[i]*2+len*2-1==ans){
			int a=1,b=i-len,c=n+2;
			for(int j=a;j<=b;++j)if(sa.get_lcp(j,c)>=res[i]){
				cout<<j<<" "<<res[i]<<endl;
				cout<<i-len+1<<" "<<len*2-1<<endl;
				cout<<n-res[i]+1<<" "<<res[i]<<endl;
				return;
			}
			assert(0);
		}
	}
	assert(0);
}
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	s[n+1]='#';
	for(int i=n+2;i<=n*2+1;++i)s[i]=s[n-(i-(n+1))+1];
	sa.n=n*2+1;
	sa.init_sa();
	//for(int i=1;i<=sa.n;++i)cout<<s[i];cout<<endl;
	//int x,y;while(cin>>x>>y)cout<<s[x]<<" "<<s[y]<<" "<<sa.get_lcp(x,y)<<endl;
	int x=solve1(),y=solve3();
	if(x>y)get_ans1(x);
	else get_ans3(y);
	return 0;
}
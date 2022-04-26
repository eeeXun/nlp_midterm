#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
#define rep(i,n) for (int i=0;i<(n);++i)
#define REP(i,n) for (int i=1;i<=(n);++i)
#define all(x) x.begin(),x.end()
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define RI(x) scanf("%d",&x)
#define RII(x,y) scanf("%d%d",&x,&y)
int n,N;
char s[200005];
int fail[200005];
int far[100005];// the farthest pos that can be matched
inline void KMP(){
	int j=0;
	fail[1]=0;
	// process length: N
	for (int i=2;i<=N;++i){
		while(j&&s[1+j]!=s[i]) j=fail[j];
		if (s[1+j]==s[i]) ++j;
		fail[i]=j;
		if (i>n+1) far[j]=max(far[j],N-i+1); 
	}
	for (int i=n-1;i>=1;--i) far[i]=max(far[i],far[i+1]);
}
const int INF=1e8;
const int MAXN=100005;
class segT{// sustainable
private:
	int dat[51*MAXN],lc[51*MAXN],rc[51*MAXN],rt[MAXN],cntNode,cntVer;
	inline int copy(int org){
		++cntNode;
		dat[cntNode]=dat[org];
		lc[cntNode]=lc[org];rc[cntNode]=rc[org];
		return cntNode;
	}
	inline int update(int old,int val,int a,int b,int l,int r){
		if (a<=l&&r<=b){
			int now=copy(old);dat[now]=max(dat[now],val);return now;
		}
		else if (r<a||b<l) return old;
		else{
			int m=l+r>>1;
			int ret=copy(old);
			lc[ret]=update(lc[old],val,a,b,l,m);
			rc[ret]=update(rc[old],val,a,b,m+1,r);
			//dat[ret]=max(dat[lc[ret]],dat[rc[ret]]);
			return ret;
		}
	}
	inline int query(int v,int p,int l,int r){
		if (!v) return -INF;
		else if (l==r) return dat[v];
		else{
			int m=l+r>>1;
			if (p<=m) return max(query(lc[v],p,l,m),dat[v]);
			else return max(query(rc[v],p,m+1,r),dat[v]);
		}
	}
public:
	inline segT(){
		cntNode=0;cntVer=0;dat[0]=-INF;lc[0]=rc[0]=rt[0]=0;
	}
	inline void update(int a,int b,int val){
		++cntVer;
		rt[cntVer]=update(rt[cntVer-1],val,a,b,1,n);
	}
	inline int query(int ver,int pos){
		return query(rt[ver],pos,1,n);
	}
}constL,constR,lineL,lineR;
int ans=0,where;
int palin[100005];// how many chars to expand
inline void Manacher(){
	int l=0,r=0;
	for (int i=1;i<=n;++i){
		int k=(i<r? min(palin[l+r-i],r-i+1):1);
		while(i-k>0&&i+k<=n&&s[i+k]==s[i-k]) ++k;
		palin[i]=--k;
		if (i+k>r) l=i-k,r=i+k;
		if ((k<<1|1) >ans) ans=k<<1|1,where=0;
	}
	// segT building
	for (int i=1;i<=n;++i){
		constL.update(1,i-palin[i],palin[i]<<1|1);lineL.update(i-palin[i],i,i<<1|1);
	}
	for (int i=n;i>=1;--i){
		constR.update(i+palin[i],n,palin[i]<<1|1);lineR.update(i,i+palin[i],1-(i<<1));
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>s+1;
	n=strlen(s+1);N=n+n+1;
	reverse(s+1,s+n+1);
	s[n+1]='#';
	for (int i=1;i<=n;++i) s[n+1+i]=s[n-i+1];// concatenate a reversed string at the end
	KMP();
	Manacher();

	for (int len=1;len*2<n;++len){
		// [1+len,far-1]
		int lb=1+len,rb=far[len]-1;// rb:decreasing
		if (lb>rb) break;//bad
		int mid=lb+rb>>1;
		int cur=
		max(max(constL.query(mid,lb),lineL.query(mid,lb)-lb*2),
		max(constR.query(n-mid,rb),lineR.query(n-mid,rb)+rb*2));
		//cerr<<len<<' '<<lb<<' '<<rb<<' '<<mid<<' '<<cur<<endl;
		cur+=len*2;
		if (cur>ans) ans=cur,where=len;
	}
	if (where==0){
		printf("1\n");
		for (int i=1;i<=n;++i) if ((palin[i]<<1|1)==ans){
			printf("%d %d\n",n+1-(i+palin[i]),ans);return 0;
		}
	}
	else{
		printf("3\n");
		int lb=1+where,rb=far[where]-1;
		printf("%d %d\n",n+1-(rb+where),where);
		//cerr<<ans<<' '<<where<<endl;
		int k=(ans-where*2)>>1;
		for (int i=lb+k;i<=rb-k;++i) if (palin[i]>=k){
			printf("%d %d\n",n+1-(i+k),k<<1|1);break;
		}
		printf("%d %d\n",n+1-(where),where);
	}
	return 0;
}
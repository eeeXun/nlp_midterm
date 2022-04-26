#include<bits/stdc++.h> 
using namespace std;
namespace Sakurajima_Mai{
	//#pragma GCC optimize(2)
    //#pragma G++ optimize(2)
	#define ms(a) memset(a,0,sizeof(a))
	#define reg register
	#define repi(i,a,b) for(reg int i=a,bbb=b;i<=bbb;++i)//attention reg int or reg ll ?
	#define repd(i,a,b) for(reg int i=a,bbb=b;i>=bbb;--i)
	#define reps(s) for(reg int i=head[s],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
	#define ce(i,r) i==r?'\n':' '
	#define pb push_back 
	#define all(x) x.begin(),x.end()
	#define gmn(a,b) a=min(a,b)
	#define gmx(a,b) a=max(a,b)
	#define fi first
	#define se second   					  
	typedef long long ll;
	typedef unsigned long long ull;
	typedef double db;
	const int infi=2e9;
	const ll infl=4e18;
	inline ll ceil_div(ll a,ll b){ return (a+b-1)/b; }
	//std::mt19937 rnd(time(0));//std::mt19937_64 rnd(time(0));
}
using namespace Sakurajima_Mai;
namespace Fast_Read{
	inline int qi(){
	    int f=0,fu=1; char c=getchar();
	    while(c<'0'||c>'9'){ if(c=='-')fu=-1; c=getchar(); }
	    while(c>='0'&&c<='9'){ f=(f<<3)+(f<<1)+c-48; c=getchar(); }
	    return f*fu;
	}
	inline ll ql(){
		ll f=0;int fu=1; char c=getchar();
	    while(c<'0'||c>'9'){ if(c=='-')fu=-1; c=getchar(); }
	    while(c>='0'&&c<='9'){ f=(f<<3)+(f<<1)+c-48; c=getchar(); }
	    return f*fu;
	}
	inline db qd(){
	    char c=getchar();int flag=1;double ans=0;
	    while((!(c>='0'&&c<='9'))&&c!='-') c=getchar();
	    if(c=='-') flag=-1,c=getchar();
	    while(c>='0'&&c<='9') ans=ans*10+(c^48),c=getchar();
	    if(c=='.'){c=getchar();for(register int Bit=10;c>='0'&&c<='9';Bit=(Bit<<3)+(Bit<<1)) ans+=(double)(c^48)*1.0/Bit,c=getchar();}
	    return ans*flag;
	}
}
namespace Read{
	#define si(a) scanf("%d",&a)
	#define sl(a) scanf("%lld",&a)
	#define sd(a) scanf("%lf",&a)
	#define ss(a) scanf("%s",a)
	#define rai(x,a,b) repi(i,a,b) x[i]=qi()
	#define ral(x,a,b) repi(i,a,b) x[i]=ql()
}
namespace Out{
	#define pi(x) printf("%d",x)
	#define pl(x) printf("%lld",x)
	#define ps(x) printf("%s",x)
	#define pc(x) printf("%c",x)
}
namespace DeBug{
	#define pr(x) cout<<#x<<": "<<x<<endl
	#define pra(x,a,b) cout<<#x<<": "<<endl; \
			repi(i,a,b) cout<<x[i]<<" ";	 \
			puts("");   
	#define FR(a) freopen(a,"r",stdin)
	#define FO(a) freopen(a,"w",stdout)
}
using namespace Fast_Read;
using namespace Read;
using namespace Out;
using namespace DeBug;
const int MAX_N=2e5+5;
const int MAX_S=2e5+5;
const int MAX_M=2e5+5;
char s[MAX_N],t[MAX_N<<1];
int dia[MAX_N<<1],lp;
int Manacher(char *s)
{
	int pos=0,i=0;
	t[pos]='%',lp=strlen(s+1);
	while(i<lp)	t[++pos]='#',t[++pos]=s[++i];
	t[++pos]='#';	
	int rm=0,id=0,ans=0;	
	lp=pos;
	repi(i,2,lp){
		dia[i]=i<rm?min(rm-i,dia[2*id-i]):1;
		while(t[i-dia[i]]==t[i+dia[i]])	dia[i]++;
		if(dia[i]+i-1>rm) id=i,rm=dia[i]+i-1;
	}
	repi(i,1,lp) --dia[i],ans=max(ans,dia[i]); 
	return ans;	 
}
int match[MAX_N];
int dp[MAX_N],st[MAX_N];
struct KMP{
	char s[MAX_S],mode[MAX_M];//ss(s+1)
	int ls,lm,nxt[MAX_M];//nxt?? ???????????????(?????,?L??nxt???L-1)
	void build_next()
	{
		lm=strlen(mode+1);
		nxt[1]=0;
		for(int i=2,j=0;i<=lm;i++){
			while(j&&mode[i]!=mode[j+1]) j=nxt[j];
			nxt[i]=(mode[j+1]==mode[i]?++j:j);
		}
	}
	void find()
	{
		ls=strlen(s+1);
		for(int i=1,j=0;i<=ls;i++){
			while(j&&s[i]!=mode[j+1]) j=nxt[j];
			if(s[i]==mode[j+1]) j++;
			match[i]=j;
			if(j==lm){ j=nxt[j]; }//???j=nxt[j] ??? j=0
		}
	}
}kmp;
typedef pair<int,int> P;
vector<P> rec;
int main()
{
	ss(s+1); int len=strlen(s+1);
	Manacher(s);
	reverse(s+1,s+1+len);
	repi(i,1,len+1) kmp.mode[i]=s[i];
	kmp.build_next();
	reverse(s+1,s+1+len);
	repi(i,1,len+1) kmp.s[i]=s[i];
	kmp.find();
	repi(i,1,len){
		if(match[i]>dp[i-1]) dp[i]=match[i],st[i]=i-match[i]+1;
		else dp[i]=dp[i-1],st[i]=st[i-1];
	}
	int ans=0;
	vector<P> rec;
	repi(i,1,len){
		int middle=dia[2*i],lb=i-middle/2-1,rb=i+middle/2+1;
		int ps=min(dp[lb],len-rb+1);
		if(2*ps+middle>ans){
			ans=2*ps+middle; rec.clear();
			if(ps) rec.pb(P(st[lb],ps));
			rec.pb(P(lb+1,middle));
			if(ps) rec.pb(P(len-ps+1,ps));
		}
	}
	pi(rec.size()),puts("");
	for(auto x:rec) pi(x.fi),pc(' '),pi(x.se),puts("");
	return 0;
}
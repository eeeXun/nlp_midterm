#include "bits/stdc++.h"
#define MAXN 100009
#define INF 1000000007
#define mp(x,y) make_pair(x,y)
#define all(v) v.begin(),v.end()
#define pb(x) push_back(x)
#define wr cout<<"----------------"<<endl;
#define ppb() pop_back()
#define tr(ii,c) for(typeof((c).begin()) ii=(c).begin();ii!=(c).end();ii++)
#define ff first
#define ss second
#define left snup
#define right born

using namespace std;

typedef long long ll;
typedef pair<ll,ll> PII;
template<class T>bool umin(T& a,T b){if(a>b){a=b;return 1;}return 0;}
template<class T>bool umax(T& a,T b){if(a<b){a=b;return 1;}return 0;}
//freopen("file.in","r",stdin);
//freopen("file.out","w",stdout);
char s[MAXN];
ll pre[MAXN],suf[MAXN],pwa[MAXN],n;
ll pr[MAXN],su[MAXN],pwb[MAXN];
ll lpos[MAXN];
const ll T=1123414153;
ll mod(ll x){
	while(x<0)
		x+=INF;
	return (x%INF);
}
ll md(ll x){
	while(x<0)
		x+=T;
	return (x%T);
}
ll L(ll l,ll r){
	return mod(pre[r]-mod(pre[l-1]*pwa[r-l+1]));
}
ll R(ll l,ll r){
	return mod(suf[l]-mod(suf[r+1]*pwa[r-l+1]));
}
ll L1(ll l,ll r){
	return md(pr[r]-md(pr[l-1]*pwb[r-l+1]));
}
ll R1(ll l,ll r){
	return md(su[l]-md(su[r+1]*pwb[r-l+1]));
}
ll go(ll x){
	ll st=1,en=min(x,n-x+1);
	while(st+1<en){
		ll mid=(st+en)>>1;
		if(L(x-mid+1,x)==R(x,mid+x-1) and L1(x-mid+1,x)==R1(x,mid+x-1))
			st=mid;
		else
			en=mid;
	}
	for(ll i=en;i>=st;i--)
		if(L(x-i+1,x)==R(x,x+i-1) and L1(x-i+1,x)==R1(x,x+i-1))
			return i;	
	return -1;		
}
ll LOG[MAXN];
PII M[MAXN][20];
PII q(ll l,ll r){
	if(r<l)
		return mp(-1,-1);
	ll k=LOG[r-l+1];
	return max(M[l][k],M[r-(1<<k)+1][k]);
}
ll cost(ll l,ll r){
	ll st=0,en=(r-l+1)/2;
	while(st+1<en){
		ll mid=(st+en)>>1;
		if(q(l+mid,r-mid).ff>=mid)
			st=mid;
		else
			en=mid;
	}
	for(ll i=en;i>=st;i--)
		if(q(l+i,r-i).ff>=i)
			return i*2+1;
	return -1;		
}
int main(){
	pwa[0]=pwb[0]=1;
	ll ans=0;
	for(ll i=1;i<MAXN;i++)
		pwa[i]=mod(pwa[i-1]*27);
	for(ll i=1;i<MAXN;i++)
		pwb[i]=md(pwb[i-1]*53);	
	scanf("%s",s+1);
	n=strlen(s+1);
	for(ll i=1;i<=n;i++)
		pre[i]=mod((pre[i-1]*27)+(s[i]-'a'+1));
	for(ll i=n;i>=1;i--)
		suf[i]=mod((suf[i+1]*27)+(s[i]-'a'+1));	
	for(ll i=1;i<=n;i++)
		pr[i]=md((pr[i-1]*53)+(s[i]-'a'+1));
	for(ll i=n;i>=1;i--)
		su[i]=md((su[i+1]*53)+(s[i]-'a'+1));		
	for(ll i=1;i<=n;i++){
		M[i][0]=mp(go(i)-1,i);
		LOG[i]=log2(i);
	}
	for(ll j=1;j<=18;j++)
		for(ll i=1;i<=n;i++)
			M[i][j]=max(M[i][j-1],(i+(1<<(j-1))<=n?M[i+(1<<(j-1))][j-1]:mp(0LL,0LL)));
	umax(ans,cost(1,n));
	ll i1=-1,i2=-1,i3=-1;
	ll i4=-1,i5=ans,i6=-1;
	i2=q(1+(ans-1)/2,n-(ans-1)/2).ss;
	i2-=(ans-1)/2;
	lpos[0]=1;
	for(ll i=n;i>=1;i--){
		ll len=n-i+1;lpos[len]=lpos[len-1];
		while(lpos[len]+len-1<i-1){
			if(L(lpos[len],lpos[len]+len-1)==R(i,n) and L1(lpos[len],lpos[len]+len-1)==R1(i,n))
				break;
			lpos[len]++;
		}
		if(lpos[len]+len>=i-1 or L(lpos[len],lpos[len]+len-1)!=R(i,n) or L1(lpos[len],lpos[len]+len-1)!=R1(i,n))
			break;		
		ll yapma=cost(lpos[len]+len,i-1);	
		if(umax(ans,yapma+len*2)){
			i1=lpos[len];i4=len;
			i2=q(lpos[len]+len+(yapma-1)/2,i-1-(yapma-1)/2).ss;i5=yapma;
			i2-=(yapma-1)/2;
			i3=i;i6=len;
		}
	}		
	if(~i1)
		printf("3\n%lld %lld\n%lld %lld\n%lld %lld\n",i1,i4,i2,i5,i3,i6);
	else
		printf("1\n%lld %lld\n",i2,i5);
	return 0;
}
/*
 backerimircodeforcescab
 */

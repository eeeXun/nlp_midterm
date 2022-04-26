#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pr;
const double pi=acos(-1);
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,n,a) for(int i=n;i>=a;i--)
#define Rep(i,u) for(int i=head[u];i;i=Next[i])
#define clr(a) memset(a,0,sizeof(a))
#define pb push_back
#define mp make_pair
#define fi first
#define sc second
#define pq priority_queue
#define pqb priority_queue <int, vector<int>, less<int> >
#define pqs priority_queue <int, vector<int>, greater<int> >
#define vec vector
ld eps=1e-9;
ll pp=1000000007;
ll mo(ll a,ll pp){if(a>=0 && a<pp)return a;a%=pp;if(a<0)a+=pp;return a;}
ll powmod(ll a,ll b,ll pp){ll ans=1;for(;b;b>>=1,a=mo(a*a,pp))if(b&1)ans=mo(ans*a,pp);return ans;}
void fre() { freopen("bzoj_1006.in", "r", stdin); freopen("bzoj_1006.out", "w", stdout); }
//void add(int x,int y,int z){ v[++e]=y; next[e]=head[x]; head[x]=e; cost[e]=z; }
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};
ll read(){ ll ans=0; char last=' ',ch=getchar();
while(ch<'0' || ch>'9')last=ch,ch=getchar();
while(ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
if(last=='-')ans=-ans; return ans; }
const int N=1e05+5;
int Mx[N][25],Mw[N][25],p[N],Next[N],W[N],ans=-1,ansn,ansl,ansm;
char str[N],str_[N];
int query(int a,int b){
	int l=log2(b-a+1);
	return max(Mx[a][l],Mx[b-(1<<l)+1][l]);
}
int queryw(int a,int b){
	int l=log2(b-a+1);
	if (Mx[a][l]>Mx[b-(1<<l)+1][l]) return Mw[a][l];
	else return Mw[b-(1<<l)+1][l];
}
int main(){
	scanf("%s",str+1); int n=strlen(str+1);
	str[0]='@';
	int maxn=0,po=0;
	for (int i=1;i<=n;i++){
		p[i]=(maxn>i)?min(p[po+po-i],maxn-i):0;
		while (str[i-p[i]-1]==str[i+p[i]+1]) p[i]++;
		if (i+p[i]>maxn) maxn=p[i]+i,po=i;
	}
	for (int i=1;i<=n;i++) Mx[i][0]=p[i],Mw[i][0]=i;
	for (int i=1;i<=24;i++)
		for (int j=1;j<=n-(1<<i)+1;j++)
			if (Mx[j][i-1]>Mx[j+(1<<(i-1))][i-1]) Mx[j][i]=Mx[j][i-1],Mw[j][i]=Mw[j][i-1];
			else Mx[j][i]=Mx[j+(1<<(i-1))][i-1],Mw[j][i]=Mw[j+(1<<(i-1))][i-1];
	for (int i=1;i<=n;i++) str_[i]=str[n-i+1];
	int now=0; 
	for (int i=2;i<=n;i++){
		while (now && str_[now+1]!=str_[i]) now=Next[now];
		now+=(str_[now+1]==str_[i]); Next[i]=now;
	}
	now=0;
	for (int i=1;i<=n;i++){
		while (now && (str_[now+1]!=str[i] || now>=n-i)) now=Next[now];
		now+=(str_[now+1]==str[i] && now<n-i); W[i]=now;
	}	
	for (int i=0;i<=n;i++){
		int L=i+1,R=n-W[i],l=0,r=(R-L)/2,m=0;
		if (L>R) continue;
		while (l<r){
			int mid=(l+r+1)>>1;
			if (query(L+mid,R-mid)>=mid) l=mid;
			else r=mid-1;
		}
		if (l+W[i]>ans) ans=l+W[i],ansn=i,ansm=queryw(L+l,R-l),ansl=l;
	}
	if (!W[ansn]){
		puts("1"); printf("%d %d\n",ansm-ansl,ansl+ansl+1);
	} else {
		puts("3"); printf("%d %d\n%d %d\n%d %d\n",ansn-W[ansn]+1,W[ansn],ansm-ansl,ansl+ansl+1,n-W[ansn]+1,W[ansn]);
	}
	return 0;
}
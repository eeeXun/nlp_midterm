/*----------------by syr----------------*/
/*
  -----  -----  -----
  |   |  |---|    _/
  |   |  | \_    /
  -----  |   \  -----

  |---\  \   /  |\  /|
  |   |   \_/   | \/ |
  |   |   / \   |    |
  |---/  /   \  |    |
*/
#include<bits/stdc++.h>

using namespace std;

#define PH push
#define MP make_pair
#define PB push_back
#define fst first
#define snd second
#define FOR(i,x,y) for(int i=(x);i<(y);++i)
#define REP(i,x,y) for(int i=(x);i<=(y);++i)
#define x0 x0123456789
#define y0 y0123456789
#define x1 x1234567890
#define y1 y1234567890
#define x2 x2345678901
#define y2 y2345678901
typedef double db;
typedef long long ll;
typedef long double ldb;
typedef pair<int,int> pii;

const int INF=1e9+7;
const int maxn=2e5+5;
const int logn=22;

namespace SA{
	int len;
	int lcp[maxn],rk[maxn],sa[maxn],tmp[maxn],lg[maxn];
	int st[maxn][logn];
	char s[maxn];
	pii elm[maxn];
	inline bool cmp(const int &i,const int &j){return elm[i]<elm[j];}
	inline void calcSa(){
		REP(i,0,len) sa[i]=i,rk[i]=s[i];
		for(int k=1;k<=len;k<<=1){
			REP(i,0,len) elm[i]=MP(rk[i],(i+k<=len)?(rk[i+k]):(-1));
			sort(sa,sa+len+1,cmp);
			tmp[sa[0]]=0;
			REP(i,1,len) tmp[sa[i]]=tmp[sa[i-1]]+cmp(sa[i-1],sa[i]);
			REP(i,0,len) rk[i]=tmp[i];
		}
		return;
	}
	inline void calcLcp(){
		int h=0;
		lcp[0]=0;
		REP(i,0,len){
			int j=sa[rk[i]-1];
			for(h-=(h)?(1):(0);i+h<len&&j+h<len&&s[i+h]==s[j+h];++h);
			lcp[rk[i]-1]=h;
		}
		return;
	}
	inline void calcRmq(){
		lg[1]=0;
		REP(i,2,len) lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i);
		REP(i,0,len) st[i][0]=lcp[i];
		FOR(j,1,logn){
			REP(i,0,len){
				if(i+(1<<j)>len) st[i][j]=st[i][j-1];
				else st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
			}
		}
		return;
	}
	inline void init(char *s,int len){
		SA::len=len;
		FOR(i,0,len) SA::s[i]=s[i];
		calcSa();
		calcLcp();
		calcRmq();
		return;
	}
	inline int query(int x,int y){
//		printf("query: x=%d y=%d\n",x,y);
		x=rk[x];y=rk[y];
		if(x>y) swap(x,y);
		--y;
//		printf("query: x=%d y=%d\n",x,y);
		return min(st[x][lg[y-x+1]],st[y-(1<<lg[y-x+1])+1][lg[y-x+1]]);
	}
}

int n,ans;
int pos[maxn];
char s[maxn];
vector<pii> vans;

inline void calcPos(){
	int p=SA::rk[0],h;
	h=n;
	FOR(i,0,SA::len) pos[i]=INF;
	for(int i=p-1;i>=0;--i){
		h=min(h,SA::lcp[i]);
//		printf("%d %d\n",SA::sa[i],h);
		if(SA::sa[i]>n) pos[h]=min(pos[h],SA::sa[i]-n-1);
	}
	h=SA::lcp[p];
	REP(i,p+1,SA::len){
//		printf("%d %d\n",SA::sa[i],h);
		if(SA::sa[i]>n) pos[h]=min(pos[h],SA::sa[i]-n-1);
		h=min(h,SA::lcp[i]);
	}
	return;
}

inline int getPre(int l,int r){
	int lb=0,rb=n;
	while(lb+1<rb){
		int md=(lb+rb)>>1;
		if(md+pos[md]-1<l&&n-md>r) lb=md;
		else rb=md;
	}
	return lb;
}

int main(){
	scanf("%s",s);
	n=strlen(s);
	s[n]='$';
	REP(i,n+1,n<<1) s[i]=s[i-n-1];
	reverse(s,s+n);
	SA::init(s,n<<1|1);
/*	FOR(i,0,SA::len) printf("%c",s[i]);
	puts("");
	REP(i,0,SA::len) printf("%d ",SA::sa[i]);
	puts("");
	REP(i,0,SA::len) printf("%d ",SA::lcp[i]);
	puts("");
*/	calcPos();
	for(int i=n-1;i>=0;--i) pos[i]=min(pos[i],pos[i+1]);
//	REP(i,0,n) printf("%d ",pos[i]);
//	puts("");
	FOR(i,0,n){
		int len=SA::query(i+n+1,n-i-1);
//		printf("%d %d\n",i,len);
		int pre=getPre(i-len+1,i+len-1);
//		printf("pre=%d\n",pre);
		if((pre<<1)+((len<<1)-1)>ans){
			vans.clear();
			ans=(pre<<1)+((len<<1)-1);
			if(!pre){
				vans.PB(MP(i-len+1,(len<<1)-1));
			}else{
				vans.PB(MP(pos[pre],pre));
				vans.PB(MP(i-len+1,(len<<1)-1));
				vans.PB(MP(n-pre,pre));
			}
		}
	}
	printf("%d\n",vans.size());
	FOR(i,0,vans.size()) printf("%d %d\n",vans[i].fst+1,vans[i].snd);
	return 0;
}

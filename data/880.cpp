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
const int logn=25;

class SparseTable{
private:
	int lg[maxn];
	int table[maxn][logn];
public:
	inline void init(int *dat,int len){
		FOR(i,2,maxn) lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i);
		FOR(i,0,len) table[i][0]=dat[i];
		FOR(j,1,logn){
			FOR(i,0,len){
				if(i+(1<<j)>=len) table[i][j]=table[i][j-1];
				else table[i][j]=max(table[i][j-1],table[i+(1<<j-1)][j-1]);
			}
		}
		return;
	}
	inline int query(int l,int r){
		int len=r-l+1;
		return max(table[l][lg[len]],table[r-(1<<lg[len])+1][lg[len]]);
	}
}st;

int n,ans;
int lft[maxn],p[maxn],z[maxn];
pii ansx,ansy,ansz;

inline void manacher(char *s,int len){
	int l=-1,r=-1;
	FOR(i,0,len){
//		printf("i=%d l=%d r=%d\n",i,l,r);
		if(i<=r) p[i]=min(r-i+1,p[l+r-i]);
		for(;i+p[i]<len&&i-p[i]>=0&&s[i+p[i]]==s[i-p[i]];++p[i]);
		if(i+p[i]-1>r) l=i-p[i]+1,r=i+p[i]-1;
	}
	return;
}

inline void zMatch(char *s,int len){
	int l=-1,r=-1;
	z[0]=n;
	REP(i,1,len){
		if(i<=r) z[i]=min(r-i+1,z[i-l]);
		for(;i+z[i]<len&&s[i+z[i]]==s[z[i]];++z[i]);
		if(i+z[i]-1>r) l=i,r=i+z[i]-1;
	}
	return;
}

inline int getPalin(int l,int r){
	int lb=0,rb=n;
	while(lb+1<rb){
		int md=(lb+rb)>>1;
		if(l+md-1>r-md+1){
			rb=md;
			continue;
		}
		if(st.query(l+md-1,r-md+1)>=md) lb=md;
		else rb=md;
	}
//	printf("l=%d r=%d lb=%d\n",l,r,lb);
	return lb;
}

char s[maxn];

int main(){
	scanf("%s",s);
	n=strlen(s);
	manacher(s,n);
//	FOR(i,0,n) printf("%c ",s[i]);
//	puts("");
//	FOR(i,0,n) printf("%d ",p[i]);
//	puts("");
	st.init(p,n);
	s[n]='$';REP(i,n+1,n<<1) s[i]=s[i-n-1];
	reverse(s,s+n);
//	printf("%s\n",s);
	zMatch(s,n<<1|1);
//	FOR(i,0,n<<1|1) printf("%d ",z[i]);
//	puts("");
	REP(i,0,n) lft[i]=INF;
	FOR(i,n+1,n<<1|1) lft[z[i]]=min(lft[z[i]],i-n-1);
	for(int i=n-1;i>=0;--i) lft[i]=min(lft[i],lft[i+1]);
//	FOR(i,0,n) printf("%d ",lft[i]);
//	puts("");
	ansx=ansy=ansz=MP(-1,-1);
	FOR(i,0,n) if(ansy.snd<(p[i]<<1)-1) ansy=MP(i-p[i]+1,(p[i]<<1)-1);
	ans=ansy.snd;
	REP(i,0,n){
		if(lft[i]==INF) continue;
		int l=lft[i]+i,r=n-i-1;
		if(l>r) continue;
		int x=getPalin(l,r);
//		printf("i=%d x=%d\n",i,x);
		if((i<<1)+(x<<1)-1>ans){
			ans=(i<<1)+(x<<1)-1;
			ansx=MP(lft[i],i);
			ansz=MP(n-i,i);
			ansy.snd=(x<<1)-1;
		}
	}
	if(ansx.fst!=-1){
		int l=ansx.fst+ansx.snd+((ansy.snd+1)>>1)-1;
		int r=ansz.fst-((ansy.snd+1)>>1);
		REP(i,l,r) if((p[i]<<1)-1>=ansy.snd) ansy.fst=i-((ansy.snd+1)>>1)+1;
	}
	if(ansx.fst==-1){
		puts("1");
		printf("%d %d\n",ansy.fst+1,ansy.snd);
		return 0;
	}
	puts("3");
	printf("%d %d\n",ansx.fst+1,ansx.snd);
	printf("%d %d\n",ansy.fst+1,ansy.snd);
	printf("%d %d\n",ansz.fst+1,ansz.snd);
	return 0;
}


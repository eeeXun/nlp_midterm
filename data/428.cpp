/* --- author: dxm --- */
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;

#define INF 1e9
#define Inf 1e18
#define rep(i,n) for(int (i)=0;(i)<n;i++)
#define REP(i,n) for(int (i)=1;(i)<=n;i++)
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<long long,long long> pll;

void qread(int &x){
    int neg=1;x=0;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')neg=-1;c=getchar();}
    while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
    x*=neg;
}

const int maxn=200005;
int n,m,ans;
char c[maxn];
int z[maxn],p[maxn],mn[maxn],pos[3],len[3];
pii pre[maxn];
string s;

void zalgo(string s){
    int l=0,r=0;
    REP(i,s.size()-1){
	if(i<r)z[i]=min(r-i,z[i-l]);
	while(i+z[i]<s.size()&&s[z[i]]==s[i+z[i]])z[i]++;
	if(i+z[i]-1>r)l=i,r=i+z[i]-1;
    }
}

void manacher(string s){
    int c=0,r=0;
    rep(i,s.size()){
	if(i<r)p[i]=min(p[2*c-i],r-i);
	while(i-p[i]>=0&&i+p[i]<s.size()&&s[i-p[i]]==s[i+p[i]])p[i]++;
	if(i+p[i]-1>r)c=i,r=i+p[i]-1;
    }
}

int main(){
#ifdef FILE
     freopen("FILE.in","r",stdin);
     freopen("FILE.out","w",stdout);
#endif
     scanf("%s",c);n=strlen(c);s=c;
     string t=s;
     reverse(t.begin(),t.end());
     zalgo(t+"#"+s);
     rep(i,n)mn[i]=i+1;
     rep(i,n)if(z[i+n+1]>=1)mn[i+z[i+n+1]-1]=min(mn[i+z[i+n+1]-1],i);
     for(int i=n-2;i>=0;i--)mn[i]=min(mn[i],mn[i+1]);
     rep(i,n)pre[i]=mp(i-mn[i]+1,i);
     REP(i,n-1)pre[i]=max(pre[i],pre[i-1]);
     manacher(s);
     rep(i,n){
	 int l=i-p[i]+1,r=i+p[i]-1;
	 if(r-l+1>ans){
	     ans=r-l+1;
	     m=1;
	     pos[0]=l;len[0]=r-l+1;
	 }
	 if(!l)continue;
	 pii cur=pre[l-1];
	 cur.fst=min(cur.fst,n-1-(r+1)+1);
	 if(cur.fst*2+r-l+1>ans){
	     ans=cur.fst*2+r-l+1;
	     m=3;
	     pos[0]=cur.snd-cur.fst+1;len[0]=cur.fst;
	     pos[1]=l;len[1]=r-l+1;
	     pos[2]=n-1-cur.fst+1;len[2]=cur.fst;
	 }
     }
     printf("%d\n",m);
     rep(i,m)printf("%d %d\n",pos[i]+1,len[i]);
#ifdef TIME
     printf("Running Time = %d ms\n",int(clock()*1000.0/CLOCKS_PER_SEC));
#endif
     return 0;
}

/*
Input:
-----------------
Output:
*/

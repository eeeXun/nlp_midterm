#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<queue>
#include<deque>
#include<set>
#include<algorithm>
#include<ctime>
#include<map>
#ifdef unix
#define PL "%lld"
#else
#define PL "%I64d"
#endif
#define PB push_back
#define MP make_pair
#define INF 0x5fffffff
#define rep(i,x,y) for(i=x;i<=y;i++)
#define reps(i,x,y) for(i=x;i>=y;i--)
#define sqr(x) ((x)*(x))
#define Imin(x,y) ((x)<(y)?(x):(y))
#define Imax(x,y) ((x)>(y)?(x):(y))
#define Iabs(x) ((x)>0?(x):(-(x)))
#define N 110000
using namespace std;
typedef long long LL;
typedef double DB;
typedef vector<int> VI;
string s;
int R[N];
int ex[N],next[N];
int Max[N];
void init(){
	int i,j,k;
	cin>>s;	
	R[0]=1;int p=0,mx=0;
	for(i=1;i<s.size();i++){
		if(i<=mx)R[i]=min(R[2*p-i],mx-i+1);
		else R[i]=1;
		while(i-R[i]>=0&&i+R[i]<s.size()&&s[i-R[i]]==s[i+R[i]])R[i]++;
		if(i+R[i]-1>=mx)p=i,mx=i+R[i]-1;
	}
	
	string t=s;
	for(i=0;i<t.size()/2;i++)swap(t[i],t[t.size()-i-1]);
	for(i=1;i<t.size();i++){
		j=next[i];
		while(j&&t[j]!=t[i])j=next[j];
		if(t[j]==t[i])next[i+1]=j+1;
		else next[i+1]=0;
	}
	for(i=0;i<s.size();i++){
		j=ex[i];
		while(j&&t[j]!=s[i])j=next[j];
		if(t[j]==s[i])ex[i+1]=j+1;
		else ex[i+1]=0;
	}
}
void solve(){
	int i,j,k;
	int ret=0;
	int p1,l1,p2,l2;
	for(i=0;i<s.size();i++){
		if(i)Max[i-1]=max(Max[i-2],ex[i]);
		int tmp=Max[i-R[i]];
		if(i+R[i]-1+tmp>s.size()-1){
			tmp=s.size()-i-R[i];
		}
		if(2*R[i]-1+tmp*2>ret){
			ret=2*R[i]-1+tmp*2;
			l1=tmp;p2=i-R[i]+1;l2=2*R[i]-1;
		}
	}
	if(!l1)printf("1\n%d %d\n",p2+1,l2);
	else {
		puts("3");
		for(i=1;i<s.size();i++)
			if(ex[i]==l1)break;
		printf("%d %d\n",i-l1+1,l1);
		printf("%d %d\n",p2+1,l2);
		printf("%d %d\n",s.size()-l1+1,l1);
	}
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	#endif
	init();
	solve();
	return 0;
}

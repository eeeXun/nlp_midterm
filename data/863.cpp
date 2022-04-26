//#gragma GCC optimize(2)
#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const double pi=acos(-1.0);
const double eps=1e-10;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
int n,tn;
char s[maxn],ns[maxn<<1],rs[maxn];
int R[maxn<<1],nxt[maxn],d[maxn],dmx[maxn];
vector<pii>output;
void getNext(){
	nxt[1]=0;
	for(int i=2,j=0;i<=n;i++){
		while(j&&rs[j+1]!=rs[i])j=nxt[j];
		if(rs[j+1]==rs[i])++j;
		nxt[i]=j;
	}
}
void kmp(){
	getNext();
	for(int i=1,j=0;i<=n;i++){
		while(j&&rs[j+1]!=s[i])j=nxt[j];
		if(rs[j+1]==s[i])++j;
		d[i]=j;
		if(d[i]>d[dmx[i-1]]){
			dmx[i]=i;
		}
		else{
			dmx[i]=dmx[i-1];
		}
	}
}
void manacher(){
	ns[0]='$';
	ns[1]='#';
	for(int i=1;i<=n;i++){
		ns[2*i]=s[i];
		ns[2*i+1]='#';
	}
	tn=2*n+1;
	ns[tn+1]='\0';
	int mx=0,p=0;
	for(int i=1;i<=tn;i++){
		if(mx>i)R[i]=min(mx-i,R[2*p-i]);
		else R[i]=1;
		while(ns[i-R[i]]==ns[i+R[i]])++R[i];
		if(i+R[i]>mx){
			mx=i+R[i];
			p=i;
		}	
	}
}
int main(void){
//	freopen("in.txt","r",stdin);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=n;i>=1;i--){
		rs[n-i+1]=s[i];
	}
	kmp();
	manacher();
//	printf("%s\n",s+1);
//	printf("%s\n",rs+1);
//	for(int i=1;i<=n;i++)printf("%d ",d[i]);
//	puts("");
//	for(int i=1;i<=n;i++)printf("%d ",dmx[i]);
//	puts(""); 
//	printf("%s\n",ns+1);
	int ans=0;
	for(int i=1;i<=tn;i++){
		if(ns[i]=='#')continue;
		int tmp=R[i]-1,l=i/2-tmp/2,r=i/2+tmp/2;
//		printf("%d %d %d %d\n",i,tmp,l,r);
		int tans=tmp+2*min(d[dmx[l-1]],n-r);
//		printf("*%d\n",tans);
		if(tans>ans){
			output.clear();
			if(min(d[dmx[l-1]],n-r)){
				output.pb(mp(dmx[l-1]-d[dmx[l-1]]+1,min(d[dmx[l-1]],n-r)));
				output.pb(mp(l,tmp));
				output.pb(mp(n-min(d[dmx[l-1]],n-r)+1,min(d[dmx[l-1]],n-r)));
			}
			else{
				output.pb(mp(l,tmp));
			}
			ans=tans;
		}
	}
	printf("%d\n",output.size());
	for(int i=0;i<output.size();i++){
		printf("%d %d\n",output[i].fi,output[i].se);
	}
	return 0;
}

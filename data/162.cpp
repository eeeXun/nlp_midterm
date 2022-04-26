#include<bits/stdc++.h>
using namespace std;

template<typename T>
inline void Read(T &n){
	char ch; bool flag=false;
	while(!isdigit(ch=getchar()))if(ch=='-')flag=true;
	for(n=ch^48;isdigit(ch=getchar());n=(n<<1)+(n<<3)+(ch^48));
	if(flag) n=-n;
}

const int MAXN = 100005;
const int MOD = 998244353;
const int base = 1107;

inline int ksm(int base, int k=MOD-2){
	int res=1;
	while(k){
		if(k&1)
			res = 1ll*res*base%MOD;
		base = 1ll*base*base%MOD;
		k >>= 1;
	}
	return res;
}

char a[MAXN];
int n;

int Pow[MAXN], invPow[MAXN];
int hs1[MAXN], hs2[MAXN];

inline int get(int l, int r, int opt){ if(l>r) return 0;
	if(opt==1) return (hs1[r]-1ll*hs1[l-1]*Pow[r-l+1]%MOD+MOD)%MOD;
	return 1ll*(hs2[r]-hs2[l-1]+MOD)%MOD*invPow[l-1]%MOD;
}

int mnpre[MAXN];

int loc[3], len[3], mxlen;

int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%s",a+1);
	n = strlen(a+1);
	Pow[0] = invPow[0] = 1;
	Pow[1] = base, invPow[1] = ksm(base);
	for(register int i=2; i<=n; i++) Pow[i] = 1ll*Pow[i-1]*Pow[1]%MOD, invPow[i] = 1ll*invPow[i-1]*invPow[1]%MOD;
	for(register int i=1; i<=n; i++) 
		hs1[i] = (1ll*hs1[i-1]*base%MOD+a[i]-'a')%MOD,
		hs2[i] = (hs2[i-1]+1ll*Pow[i-1]*(a[i]-'a')%MOD)%MOD;
	
	memset(mnpre,63,sizeof mnpre);
	int it = 1;
	for(register int i=1; i<=n; i++){
		int head=0, tail=(n-i+1)/2+1, mid;
		while(head<tail){
			mid = head+tail >> 1;
			if(get(i,i+mid-1,1) == get(n-mid+1,n,2)) head = mid+1;
			else tail = mid;
		}
		while(it<=head-1 and it<=n/2) mnpre[it++] = i;
	}
	
	for(register int i=0; i<3; i++) loc[i] = len[i] = -1; mxlen = 0;
	for(register int i=1; i<=n; i++){
		int head=1, tail=min(i,n-i+1)+1, mid;
		while(head<tail){
			mid = head+tail >> 1;
			if(get(i-mid+1,i,1) == get(i,i+mid-1,2)) head = mid+1;
			else tail = mid;
		}
		int dis = head-1, l = i-dis+1, r = i+dis-1;
		if(2*dis-1 > mxlen)
			mxlen = 2*dis-1,
			loc[0] = len[0] = -1,
			loc[1] = l, len[1] = 2*dis-1,
			loc[2] = len[2] = -1;
		
		head=0, tail=min(l-1,n-r)+1;
		while(head<tail){
			mid = head+tail >> 1;
			if(mnpre[mid]+mid-1 < l) head = mid+1;
			else tail = mid;
		}
		int mxsuf = head-1;
		if(mxsuf+2*dis-1+mxsuf > mxlen)
			mxlen = mxsuf+2*dis-1+mxsuf,
			loc[0] = mnpre[mxsuf], len[0] = mxsuf,
			loc[1] = l, len[1] = 2*dis-1,
			loc[2] = n-mxsuf+1, len[2] = mxsuf;
	}
	
	if(loc[0]==-1){
		puts("1");
		printf("%d %d\n",loc[1],len[1]);
	}
	else{
		puts("3");
		for(register int i=0; i<3; i++) printf("%d %d\n",loc[i],len[i]);
	}
	
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e8 + 1;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//---
const int N=100005;
char s[N];
int f[N*2];
int p[N],Ans[N],pos[N];
int n;
void manacher(char* str){
    static char s[N*2];
    rep(i,0,n+1) s[i*2]=str[i], s[i*2+1]='#';
    s[0]='!'; s[2*n+2]='?';
    int a=0,p=0;   
    rep(i,1,2*n+2){
        int h=0;
        if(i<=a+p)h=min(f[2*a-i],a+p-i);
        while(s[i+h+1]==s[i-h-1])h++;
        f[i]=h;
        if(i+h>a+p)a=i,p=h;
    }
}
void prefix(char s[], int * pre) {
	pre[0] = 0;
	for(int i = 1, k = 0;s[i];++ i) {
		while(k > 0 && s[k] != s[i]) k = pre[k-1];
		if(s[k] == s[i]) ++ k;
		pre[i] = k;
	}
}
void KMP(char *x) {
	for(int i = 0,j=0;x[i];++ i) {
			while(j > 0 && x[n-j-1] != x[i]) j = p[j - 1];
			if(x[n-j-1] == x[i]) ++ j;
			Ans[i+1]=j;
	}
}
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	manacher(s);
	rep(i,1,n+1)f[i*2]=f[i*2]/2+1;
	strrev(s+1);
	prefix(s+1,p);
	strrev(s+1);
	KMP(s+1);
	rep(i,0,n+1)pos[i]=i;
	rep(i,1,n+1)if(Ans[pos[i]]<Ans[pos[i-1]])pos[i]=pos[i-1];
	pii s1,s2,s3;
	rep(i,1,n+1) {
		pii _s1,_s2,_s3;
		int ml=f[i<<1];
		_s1=mp(i-ml+1,ml*2-1);
		int Pos=pos[i-ml];
		int ans=Ans[Pos];ans=min(ans,n-(i+ml-1));
		_s2=mp(Pos-ans+1,ans);
		_s3=mp(n-ans+1,ans);
		if(_s1.se+_s2.se+_s3.se>s1.se+s2.se+s3.se)s1=_s1,s2=_s2,s3=_s3;
	}
	int k=s2.se?3:1;printf("%d\n",k);
	if(k==1)printf("%d %d\n",s1.fi,s1.se);
	if(k==3)printf("%d %d\n%d %d\n%d %d\n",s2.fi,s2.se,s1.fi,s1.se,s3.fi,s3.se);
	return 0;
}
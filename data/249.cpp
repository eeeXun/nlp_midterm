/* --- author: dxm --- */
#include<bits/stdc++.h>
using namespace std;

#define INF 1e9
#define Inf 1e18
#define rep(i,n) for(int (i)=0;(i)<n;i++)
#define REP(i,n) for(int (i)=1;(i)<=n;i++)
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
typedef long long ll;
inline void Fail(){printf("0");exit(0);}
inline void debug(int x){cerr<<"debug: "<<x<<"\n";}
inline void debug(int n,int x[]){cerr<<"debug "<<"\n";rep(i,n)cerr<<x[i]<<" ";cerr<<"\n";}
inline void debug(string x){cerr<<"debug: "<<x<<"\n";}

const int maxn=100005;
const int H=20160516;
const int mod1=1e9+7;
const int mod2=19260817;
int n,ans;
char c[maxn];
string s;
int z[maxn*2],f[maxn*2];
int a[3],len[3];

class Hash{
public:
	int h1,h2;
	Hash(){}
	Hash(int _h1,int _h2){h1=_h1;h2=_h2;}
	Hash operator + (const Hash &other)const{
		Hash res(h1+other.h1,h2+other.h2);
		if(res.h1>=mod1)res.h1-=mod1;
		if(res.h2>=mod2)res.h2-=mod2;
		return res;
	}
	Hash operator - (const Hash &other)const{
		Hash res(h1-other.h1,h2-other.h2);
		if(res.h1<0)res.h1+=mod1;
		if(res.h2<0)res.h2+=mod2;
		return res;
	}
	Hash operator * (const Hash &other)const{
		return Hash(1LL*h1*other.h1%mod1,1LL*h2*other.h2%mod2);
	} 
	bool operator == (const Hash &other)const{
		return h1==other.h1&&h2==other.h2;
	}
}pre[maxn],suf[maxn],pw[maxn];

bool palin(int l,int r){
	if(l<0||r>=n)return false;
	int m=(l+r)>>1;
	Hash cur1=pre[r]-(m==0?Hash(0,0):pre[m-1])*pw[r-m+1];
	Hash cur2=suf[l]-suf[m+1]*pw[m-l+1];
	return cur1==cur2;
}

void Z_algorithm(string S){
	int l=0,r=0;
	REP(i,S.size()-1){
		if(r<=i){
			rep(j,S.size())
			if(S[j]==S[j+i])z[i]++;
			else break;
			if(z[i])l=i,r=i+z[i]-1;
		} 
		else{
			if(i>l&&i<r&&z[i-l]<r-i)z[i]=z[i-l];
			else{
				z[i]=r-i;
				for(int j=r-i;j<S.size();j++)
				if(S[j]==S[j+i])z[i]++;
				else break;
				if(z[i])l=i,r=i+z[i]-1;
			}
		}
	}
}

int main(){
	scanf("%s",c);s=c;
	n=s.size();
	string t=s;reverse(t.begin(),t.end());
	rep(i,n+1)f[i]=INF;
	Z_algorithm(t+"*"+s);
	rep(i,n)if(f[z[i+n+1]]==INF)f[z[i+n+1]]=i;
	for(int i=n-1;i>=0;i--)f[i]=min(f[i],f[i+1]);
//	rep(i,n+1)cout<<f[i]<<endl;
	pw[0]=Hash(1,1);
	REP(i,n)pw[i]=pw[i-1]*Hash(H,H);
	pre[0]=Hash(s[0],s[0]);
	REP(i,n-1)pre[i]=pre[i-1]*Hash(H,H)+Hash(s[i],s[i]);
	suf[n-1]=Hash(s[n-1],s[n-1]);
	for(int i=n-2;i>=0;i--)suf[i]=suf[i+1]*Hash(H,H)+Hash(s[i],s[i]);
	rep(i,n){
		int l=0,r=n;
		while(r-l>1){
			int mid=(l+r)>>1;
			if(palin(i-mid,i+mid))l=mid;
			else r=mid;
		}
		int L=i-l,R=i+l,Len=l;
		l=0;r=n;
		while(r-l>1){
			int mid=(l+r)>>1;
			if(f[mid]!=INF&&f[mid]+mid-1<L&&n-mid>R)l=mid;
			else r=mid;
		}
		if(2*Len+1+2*l>ans){
			ans=2*Len+1+2*l;
			a[0]=f[l];a[1]=L;a[2]=n-l;
			len[0]=l;len[1]=2*Len+1;len[2]=l; 
		}
	}
	if(len[0]==0){
		printf("1\n%d %d\n",a[1]+1,len[1]);
	}
	else{
		printf("3\n");
		rep(i,3)printf("%d %d\n",a[i]+1,len[i]);
	}
	return 0;
}

/*
Input:
-----------------
Output:
*/
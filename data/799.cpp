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
int z[maxn*2],f[maxn*2],r[maxn*2],pos[maxn];
int a[3],len[3];

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

void Manacher(string S){
	string s="";
	int R=0,cen=0;
	rep(i,S.size()){
		s+='$';
		s+=S[i];
	}
	s+='$';
	rep(i,s.size()){
		if(i<R)r[i]=min(r[cen*2-i],R-i);
		while(i-r[i]-1>=0&&i+r[i]+1<s.size()&&s[i-r[i]-1]==s[i+r[i]+1])r[i]++;
		if(i+r[i]>R){
			R=i+r[i];
			cen=i;
		}
	}
}

int main(){
	scanf("%s",c);s=c;
	n=s.size();
	string t=s;reverse(t.begin(),t.end());
	Z_algorithm(t+"*"+s);
	rep(i,n){
		int len=z[i+n+1];
		if(len>f[i+len-1])f[i+len-1]=len,pos[i+len-1]=i;
	}
	for(int i=n-2;i>=0;i--)if(f[i+1]-1>f[i])f[i]=f[i+1]-1,pos[i]=pos[i+1];
	REP(i,n-1)if(f[i-1]>f[i])f[i]=f[i-1],pos[i]=pos[i-1];
//	rep(i,n)cout<<f[i]<<" "<<pos[i]<<endl;
	Manacher(s);
	rep(i,n){
		int Len=r[2*i+1]/2,L=i-Len,R=i+Len;
		int l=min(((!L)?0:f[L-1]),n-R-1);
		if(2*Len+1+2*l>ans){
			ans=2*Len+1+2*l;
			a[0]=(!L)?0:pos[L-1];a[1]=L;a[2]=n-l;
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

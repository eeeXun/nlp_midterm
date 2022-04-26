#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define ll long long
#define ull unsigned ll
#define MAX_N 400005
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define Pii pair<int,int>
#define int ll
using namespace std;

char s[MAX_N];
int p[MAX_N];
int n;

void manacher(){
	int mx=0,id=0;
	for(int i=1;i<n;i++){
		p[i]=(mx>i)?min(mx-i,p[2*id-i]):1;
		while(s[i-p[i]]==s[i+p[i]]) p[i]++;
		if(i+p[i]>mx){
			mx=i+p[i];
			id=i;
		}
	}
}

int dp[MAX_N];

void kmp(){
	dp[1]=0;
	for(int i=2;i<2*n-1;i++){
		int j=dp[i-1];
		while(j&&s[j+1]!=s[i]) j=dp[j];
		if(s[j+1]==s[i]) j++;
		dp[i]=j;
	}
}
string s2;
signed main(){
	char c;
	s[n++]='$';
	while(cin>>c){
		s[n++]='#';
		s[n++]=c;
		s2.push_back(c);
	}
	s[n++]='#';
//	cout<<n<<' '<<s<<endl;
	manacher();
//	for(int i=0;i<n;i++){
//		cout<<p[i]<<' ';
//	}cout<<endl;
	for(int i=1;i<n;i++){
		s[n+i-1]=s[i];
	}
	reverse(s+1,s+n);
//	cout<<s<<endl;
	kmp();
//	for(int i=0;i<2*n-1;i++){
//		cout<<dp[i]<<' ';
//	}cout<<endl;
	for(int i=n+1;i<2*n;i++){
		dp[i]=max(dp[i],dp[i-1]);
		dp[i-n]=0;
	}
//	for(int i=0;i<2*n-1;i++){
//		cout<<dp[i]<<' ';
//	}cout<<endl;
	int Max=0,mid=0,len=0;
	for(int i=n;i<2*n-1;i++){
		if(s[i]!='#'){
			int t=p[i-n+1]-1+min(dp[i-p[i-n+1]]/2*2,2*n-1-i-p[i-n+1]);
			if(t>Max){
				Max=t;
				mid=i-n+1;
				len=min(dp[i-p[i-n+1]]/2*2,2*n-1-i-p[i-n+1]);
			}
//			cout<<t<<' '<<i-n+1<<' '<<dp[i-p[i-n+1]]/2*2<<' '<<2*n-1-i-p[i-n+1]<<endl;
		}
	}
//	cout<<Max<<' '<<mid<<' '<<len<<endl;
	string s1;
	if(len)cout<<3<<endl;
	else cout<<1<<endl;
	if(len){
		for(int i=2*n-2;i>=2*n-1-len;i--){
			if(s[i]!='#') s1.push_back(s[i]);
		}
		cout<<s2.find(s1)+1<<' '<<len/2<<endl;
	}
	cout<<mid/2-p[mid]/2+1<<' '<<p[mid]-1<<endl;
	if(len){
		cout<<(n-len)/2<<' '<<len/2<<endl;
	}
    return 0;
}
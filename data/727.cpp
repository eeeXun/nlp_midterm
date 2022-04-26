#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <numeric>
#include <queue>
#include <iostream>
#include <string>
#include <cstring>
#include <utility>
#define sz(a) ((int)(a).size())
#define pb push_back
#define mk make_pair
#define fi first
#define se second
#define Rep(i,j,k) for (int i=(j); i<=(k); i++)
#define Repd(i,j,k) for (int i=(j); i>=(k); i--)
#define ALL(c) (c).begin(),(c).end()
#define TR(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define SUM(a) accumulate(all(a),string())
#define online1
#define RAND ((rand()<<15)+rand())
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> II;
typedef long long LL;
#define N 110000

char s[N];
int n;
int r[N], f[N], g[N];
int hash[N], rhash[N], p=1000000007, pp[N];

void palindrome(){
	int i=1, k=0;
	while(i<=n){
		while(i-k>0 && i+k<=n && s[i-k]==s[i+k])
			k++;
		r[i]=k;
		int j=1;
		while(j<k && k-j!=r[i-j])
			r[i+j]=min(k-j,r[i-j]), j++;
		i=i+j;
		k=k-j;
	}
}

int Hash(int l, int r){
	return (hash[r]-hash[l-1])*pp[n-r];
}

int rHash(int l, int r){
	return (rhash[l]-rhash[r+1])*pp[l-1];
}

int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	//p=10;
	pp[0]=1;
	Rep(i,1,n) pp[i]=pp[i-1]*p, hash[i]=hash[i-1]+pp[i]*(s[i]-'a'+1);
	Repd(i,n,1) rhash[i]=rhash[i+1]+pp[n-i+1]*(s[i]-'a'+1);
	
	palindrome();
	
	int now=1;
	Rep(i,1,n){
		while(now+i-1<n-i+1){
			if (Hash(now,now+i-1)==rHash(n-i+1,n))
				break;
			now++;
		}
		if (now+i-1<n-i+1)
			if (f[now+i-1]<i){
				f[now+i-1]=i;
				g[now+i-1]=now+i-1;
			}
	}
	Rep(i,1,n)
		if (f[i-1]>f[i]) f[i]=f[i-1], g[i]=g[i-1];
	
	int ans=0;
	string means;
	Rep(i,1,n){
		int now=r[i]*2-1+2*min(n-(i+r[i]-1), f[i-r[i]]);
		if (now>ans){
			ans=now;
			stringstream o;
			int k=min(n-(i+r[i]-1), f[i-r[i]]);
			if (k==0) o<<1<<endl<<i-r[i]+1<<" "<<2*r[i]-1<<endl;
				else{
					o<<3<<endl;
					o<<g[i-r[i]]-k+1<<" "<<k<<endl;
					o<<i-r[i]+1<<" "<<2*r[i]-1<<endl;
					o<<n-k+1<<" "<<k<<endl;
				}
			means=o.str();
		}
	}
	cout<<means;
	
    return 0;
}

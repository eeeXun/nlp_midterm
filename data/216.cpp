#include <iostream>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

long long mod=1000000007;
long long p=163;

int maxPal(const string &pal, int k){
	int left=k-1,right=k+1;
	int count=0;
	while(left>=0 && right<=pal.length()-1 && pal[left]==pal[right]){
		count++;
		left--;
		right++;
	}
	return count;
}

long long calcHash(const vector<long long> &h,const vector<long long> &pow,int l,int r){
	if (r==pow.size()-1)
		return h[l];
	else{
		// cout<<h[l]<<" "<<h[r+1]<<" "<<pow[r-l+1]<<endl;
		return ((h[l]-h[r+1]*pow[r-l+1])%mod+mod)%mod;
	}
}

int main(){
	string input;
	cin>>input;
	int n=input.length();
	vector<int> maxL(n,0);
	vector<long long> hash(n,0);
	vector<long long> hashR(n,0);
	vector<long long> pow(n,0);
	for(int x=0; x<n; x++){
		if (x==0){
			hash[n-1]=input[n-1];
			hashR[n-1]=input[0];
			pow[x]=1;
		}else{
			pow[x]=(pow[x-1]*p)%mod;
			hash[n-1-x]=(input[n-1-x]+hash[n-x]*p)%mod;
			hashR[n-1-x]=(input[x]+hashR[n-x]*p)%mod;
		}
	}
	for (int x=0; x<n; x++){
		//cout<<hash[x]<<" "<<pow[x]<<endl;
	}
	// cout<<calcHash(hashR,pow,0,0)<<endl;
	// cout<<calcHash(hash,pow,10,10)<<" "<<calcHash(hashR,pow,0,0)<<endl;
	for (int x=0; x<n; x++){
		int low=0;
		int high=min(x,n-1-x);
		int mid=(low+high)/2;
		while (low<high){
			if (calcHash(hash,pow,x-mid,x+mid)==calcHash(hashR,pow,n-1-x-mid,n-1-x+mid)){
				low=mid+1;
			}
			else{
				high=mid;
			}
			mid=(low+high)/2;
		}
		if (calcHash(hash,pow,x-mid,x+mid)!=calcHash(hashR,pow,n-1-x-mid,n-1-x+mid)){
			mid--;
		}
		maxL[x]=mid;
	}
	vector<int> firstPre(n,n);
	vector<int> firstPreR(n,n);
	int i=0;
	int maxPre;
	for (int x=0; x<n; x++){
		while (true){
			if (i+x>=n)
				break;
			if (calcHash(hashR,pow,0,x) == calcHash(hash,pow,i,i+x)){
				firstPre[x]=i;
				firstPreR[x]=i+x;
				break;
			}
			i++;
		}
		if (i+x>=n){
			maxPre=x;
			break;
		}
	}
	// cout<<"first pre"<<endl;
	for(int x=0; x<n; x++){
		// cout<<firstPre[x]<<endl;
	}
	// cout<<"first pre"<<endl;
	int curBest=0;
	int pl=0;
	int pi=0;
	int mi=0;
	for (int x=0; x<n; x++){
		int searchIndex=x-maxL[x]-1;
		int append=0;
		int preInd=0;
		if (searchIndex>=firstPreR[0] && n-1-x-maxL[x]-1>=0){
			int low=0;
			int high=min(maxPre,n-1-x-maxL[x]-1);
			int mid=(low+high)/2;
			while(low<high){
				if(searchIndex<firstPreR[mid]){
					high=mid-1;
				}
				else{
					low=mid+1;
				}
				mid=(low+high)/2;
			}
			if (searchIndex<firstPreR[mid])
				mid--;
			append=mid+1;
			preInd=firstPreR[mid]-mid;
		}
		int nextLength=2*append+1+2*maxL[x];
		if (nextLength>curBest){
			curBest=nextLength;
			pl=append;
			pi=preInd;
			mi=x;
		}
	}
	// cout<<"new"<<endl;
	// cout<<curBest<<" "<<pl<<" "<<pi<<" "<<mi<<" "<<maxL[mi]<<endl;
	if (pl==0){
		cout<<1<<endl;
		cout<<mi-maxL[mi]+1<<" "<<2*maxL[mi]+1<<endl;
	}
	else{
		cout<<3<<endl;
		cout<<pi+1<<" "<<pl<<endl;
		cout<<mi-maxL[mi]+1<<" "<<2*maxL[mi]+1<<endl;
		cout<<n-pl+1<<" "<<pl<<endl;
	}
	// cout<<"new"<<endl;

	// int bestPreIndex=-1;
	// int bestPreL=0;
	// int bestMidIndex=-1;
	// int bestMidL=0;
	// int ans=0;
	// for(int x=0; x<n-bestPreL; x++){
	// 	int currentAns=0;
	// 	int left=x;
	// 	int right=n-1;
	// 	while(input[left]==input[right] && right-left>1){
	// 		left++;
	// 		right--;
	// 		currentAns+=2;
	// 	}
	// 	int bestMid=0;
	// 	int bestMidStart=0;
	// 	for (int y=left; y<=right; y++){
	// 		int curMid=1+2*min(maxL[y],min(right-y,y-left));
	// 		if (curMid>bestMid){
	// 			bestMid=curMid;
	// 			bestMidStart=y-(curMid-1)/2;
	// 		}
	// 	}
	// 	currentAns+=bestMid;
	// 	if (currentAns>ans){
	// 		ans=currentAns;
	// 		bestPreIndex=x;
	// 		bestPreL=left-x;
	// 		bestMidL=bestMid;
	// 		bestMidIndex=bestMidStart;
	// 	}
	// }
	// // cout<<ans<<endl;
	// if (bestPreL==0){
	// 	cout<<1<<endl;
	// 	cout<<bestMidIndex+1<<" "<<bestMidL<<endl;
	// }
	// else{
	// 	cout<<3<<endl;
	// 	cout<<bestPreIndex+1<<" "<<bestPreL<<endl;
	// 	cout<<bestMidIndex+1<<" "<<bestMidL<<endl;
	// 	cout<<n-bestPreL+1<<" "<<bestPreL<<endl;
	// }
}
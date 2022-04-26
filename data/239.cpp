#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string s;
    cin >> s;
    int n = s.length();
    
    // manacher's algorithm
    vector<int> P(n,0);
    int C = 0; // current center
    int R = 0; // current right bound
    
    for(int i = 1; i < n-1; i++) {
	int mirror = 2*C - i;
	
	if(R > i){
	    P[i] = min(R-i, P[mirror]);
	}else{
	    P[i] = 0;
	}
	
	while((i+1+P[i] < n) && (i-1-P[i]>=0) && (s[i+1+P[i]]==s[i-1-P[i]])){
	    P[i]++;
	}
	
	if(i + P[i] > R){
	    C = i;
	    R = i + P[i];
	}
    }
    
//      for(int i=0;i<n;i++){
// 	cout << s[i] << " " << P[i] << endl;
//      }
//     

    // kmp
    string rev(s);
    reverse(rev.begin(), rev.end());
    
    vector<int> T(n, 0); //kmp table
    T[0] = -1;
    int pos = 2;
    int cnd = 0;
    
    
    while(pos < n){
	if(rev[pos-1]==rev[cnd]){
	    cnd++;
	    T[pos] = cnd;
	    pos++;
	}else if(cnd>0){
	    cnd = T[cnd];
	}else{
	    T[pos] = 0;
	    pos++;
	}
    }
    
    int m=0;
    int revI=0;
    vector<int> found(n+1, -1);
    found[0] = 0;
    
    while(revI < n && m+revI < n){
	if(rev[revI]==s[m+revI]){
	    if(found[revI+1] == -1){
		found[revI+1] = m;
	    }
	    revI++;
	}else{
	    m = m + revI - T[revI];
	    if(T[revI] > -1){
		revI = T[revI];
	    }else{
		revI = 0;
	    }
	}
    }
    

    
    vector<int> fend(n+1, -1);
    int fendMax = 0;
    for (int i=0;i<=n;i++){
	if(found[i]!=-1){
	    fend[i] = found[i] + i;
	    fendMax = i;
	}
    }
    
    
    int best = 0;
    int bestMidSt = 0;
    int bestMidL = 0;
    int bestLeftSt = 0;
    int bestSideL = 0;
    
    
    for(int i=0;i<n;i++){
	int midStart = i-P[i];
	int midEnd = i+P[i];
	/*
	cout << "---" << i << " " << midStart << " " << midEnd << endl;
	*/
	// binary search for largest l such that fend[l] <= pstart and pend + l < n
	int lLow = 0;
	int lHigh = min(n-midEnd, fendMax+1);
	int lCur = (lLow+lHigh)/2;
	while(lHigh - lLow > 1){
// 	    cout << lHigh << " " << lLow << " " << lCur << endl;
	    if(fend[lCur] <= midStart){
		lLow = lCur;
	    }else{
		lHigh = lCur;
	    }
	    lCur = (lLow + lHigh)/2;
	}
	
	int curBest = 2*P[i]+1 + 2*lCur;
	if(curBest > best){
	    best = curBest;
	    bestMidSt = midStart;
	    bestMidL = 2*P[i]+1;
	    bestLeftSt = found[lCur];
	    bestSideL = lCur;
	}
    }
    
    if(bestSideL==0){
	cout << 1 << endl;
	cout << (bestMidSt + 1) << " " << bestMidL << endl;
    }else{
	cout << 3 << endl;
	cout << (bestLeftSt + 1) << " " << bestSideL << endl;
	cout << (bestMidSt + 1) << " " << bestMidL << endl;
	cout << (n-bestSideL + 1) << " " << bestSideL << endl;
    }
    return 0;
}
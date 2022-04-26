#include<bits/stdc++.h>
using namespace std;

const int m = 1e9+7;
int hs[100005];
int po[100005];

int hfunc( int s , int e){
    if(s)
    return hs[e] - hs[s-1]*po[e-s+1];
    
    return hs[e];
}

int main(){
    
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    
    string s;
    cin>>s;
    
    int n = s.size();
    int len[100005];
    
    memset(len,0,sizeof(len));
    
    int l=0 , r=-1;
    for(int i=0 ; i<s.size(); ++i){
        
        if(i < r)
            len[i] = min(r-i,len[l+r-i]);
        
        while( i-len[i] >= 0 && i+len[i] < n && (s[i-len[i]] == s[i+len[i]]) ){
	       	len[i]++;
	}
        --len[i];
        
        if(i+len[i] > r)
            r = i+len[i] , l = i-len[i];
    }
    
    po[0] = 1;
    hs[0] = s[0];
    
    for(int i=1 ; i<s.size() ; ++i)
        hs[i] = hs[i-1]*m + s[i] , po[i] = po[i-1]*m;
        
    int rs[100005];
    
    rs[0] = s[s.size()-1];
    for(int i=s.size()-2 ; i>=0 ; --i)
        rs[n-i-1] = rs[n-i-2]*m + s[i];
    
    int occ[100004],lar[100005];
    memset(occ,-1,sizeof(occ));
    memset(lar,-1,sizeof(lar));
    
    int idx=0 , k=0;
    while(idx+k < n){
        
        if(hfunc(idx,idx+k) == rs[k]){
            occ[k] = idx;
            lar[k+idx] = k;
            k++;
            continue;
        }
        idx++;
    }
    
    for(int i=1 ; i<n ; ++i)
	    lar[i] = max(lar[i-1],lar[i]);

    int maxl = 0;
    int maxa = 0;
    bool solo = 0;
    int slen = 0;
    
    for(int i=0 ; i<n ; ++i){
        
        int le = len[i]*2 + 1;
        if( i-len[i] > 0 && i+len[i] < n-1 && lar[i-len[i]-1] != -1){
		int m = i-len[i]-1;
		if(lar[m] > n-1-i-len[i]-1)
			k = n-1-i-len[i]-1;
		else k = lar[m];
            //int m = min(i-len[i]-1 , n-1-i-len[i]-1);
            le += (k+1)*2;
            
            if(le > maxl){
                solo = 0;
                idx = i-len[i];
                maxl = le;
                maxa = 2*len[i] + 1;
		slen = k;
            }
        }
        else{
            if(le > maxl){
                solo = 1;
                idx = i-len[i];
                maxl = le;
            }
        }
        
    }
    
    if(solo)
        cout<<1<<'\n'<<idx+1<<" "<<maxl<<'\n';
    else
        cout<<3<<'\n'<<occ[slen]+1<<" "<<slen+1<<"\n"<<idx+1<<" "<<maxa<<"\n"<<n-slen<<" "<<slen+1;
        
    
}

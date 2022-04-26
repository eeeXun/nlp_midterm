#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <set>
#include <bitset>

#define pi acos(-1)
#define inf 0x7fffffff
#define llinf 0x7fffffffffffffffLL
#define eps 0.000001
#define lp(i,n) for(int i=0;i<n;i++)
#define lpb(i,n) for(int i=1;i<=n;i++)
#define fr(i,j,k) for(int i=j;i<k;i++)
#define smap(p,ma) for(p=ma.begin();p!=ma.end();p++)
#define MA(a,b) ((a)>(b)?(a):(b))
#define MI(a,b) ((a)<(b)?(a):(b))
#define PB push_back
#define FIR first
#define SEC second
#define MP make_pair
#define PQ priority_queue
#define MSET multiset
#define NPS string::npos
#define debug
#define DB double
#define MOD 5767169 
#define LL long long int 
#define _max 100005
using namespace std;
int n,k,X,Y,kk,seqlen;
vector<int> ln_palindrome(char *seq){
   seqlen = strlen(seq);
  vector <int> p;
  int i=0,palLen=0,s,e,d;
  while(i < seqlen){
    if(i>palLen && seq[i-palLen-1]==seq[i]){
      palLen+=2; i++; continue;
    }
    p.PB(palLen);

    s = p.size()-2;
    e = s - palLen;
    bool fl = true;
    for(int j=s;j!=e;j--){
      d = j - e - 1;
      if(p[j]==d){
        palLen = d; fl=false; break;
      }
      p.PB(min(d,p[j]));
    }
    if(fl) palLen=1,i+=1;   
  }
  p.PB(palLen);
  s = p.size()-2;
  e = s- (2*seqlen + 1 - p.size());
  for(int i=s;i!=e;i--){
    d = i - e - 1;
    p.PB(min(d,p[i]));
  }
  return p;
} 

vector<int> p;
char s[_max];
int wei[_max],pl[_max],fail[_max];
void kp(){
	
}
void arr(){
	int last=0,len=0;
	
	fail[0]=0;
	for(int i=1,k=0,j;i<seqlen;i++){
		while(k>0&&s[seqlen-1-i]!=s[seqlen-1-k])
		k = fail[k-1];
		if(s[seqlen-1-i]==s[seqlen-1-k]) k++;
		fail[i]=k;
	}
	
	//lp(i,seqlen) cout<<fail[i]<<' ';
	//cout<<endl;
	
	int qq=0;
	lp(i,seqlen){
		while(qq>0 && s[i]!=s[seqlen-1-qq])
				qq = fail[qq-1];
		if(s[i] == s[seqlen-1-qq]){
			qq++; 
		}
	
		/*if(i==0){
			if(s[0] == s[seqlen-1]){
				pos[0]=1; wei[_max]=i;
			}
		} else {
		
			if( s[ seqlen-1-pos[i-1] ] == s[i]){
				pos[i]=pos[i-1]+1; 
			} else if(s[ i ] == s[seqlen-1]){
				pos[i]=1;
			}else{
				pos[i]=0;
			}
		
		}*/
		if(qq>len){
			len = qq; wei[i]=i; last=i; 
		}else {
			wei[i] = last;
		}
		pl[i]=len;
	}
}
int st[3],ed[3];
main(){
	scanf("%s",s);
	p = ln_palindrome(s); //lp(i,p.size())cout<<p[i]<<' ';
	arr(); 
	//lp(i,seqlen) cout<<pos[i]<<' ';
	//return 0;
	int index,left,right,mx=-1,K;
	for(int i=1;i<p.size();i+=2){
		index = (i-1)/2;
		int ll = p[i];
		left = index - p[i]/2 - 1; right = index + p[i]/2 + 1;
		if(left<0 || right>seqlen-1){
			if(ll > mx){
				mx = ll; K=1; st[0]=left+1; ed[0]=ll;
			}
			continue;
		}
		int minl = min(seqlen-right,pl[left]);
		if(2*minl + ll > mx){
			mx = 2*minl + ll;
			if(minl==0){
				K=1; st[0]=left+1; ed[0]=ll;
			}else{
				K=3; //cout<<left<<' '<<minl<<endl;
				st[0]=wei[left]-minl+1; ed[0]=minl;
				st[1]=left+1; ed[1]=ll;
				st[2]=seqlen-minl; ed[2]=minl;
			}
		}
	}
	printf("%d\n",K);
	lp(i,K) printf("%d %d\n",st[i]+1,ed[i]);
	

}


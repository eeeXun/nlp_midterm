#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
const int maxn = 5e5+5;
int nxt[maxn],d[maxn];
int mx[maxn],st[maxn];
string s,ss;
int work( int x, char c){
	if (ss[x+1] == c){
		return x+1;
	}
	if (!x) return 0;
	return work(nxt[x],c);
}
int main(){
	//freopen("a.in","r",stdin);
	ios::sync_with_stdio(false);
	
	cin >> s;

	
	int l,r;
	l = 0, r = -1;
	for (int i = 0; i < s.length(); i++){
		if (i < r) d[i] = min(d[l+r-i],r-i+1);
		while(i+d[i] < s.length() && i+d[i] >= 0 && s[i+d[i]] == s[i-d[i]]) d[i]++;
		if (i+d[i]-1 > r) r = i+d[i]-1, l = i-d[i]+1;
	}
	
	//cout << s << endl;
	ss = s;
	reverse(ss.begin(), ss.end());
	ss = ss+"#"+s;
	ss = " "+ss;
//	cout << ss << endl;
//	return 0;


	for (int i = 2; i < ss.length(); i++){
		
		nxt[i] = work(nxt[i-1],ss[i]);
		//cout << i << " " << nxt[i] << endl;
		if (i > s.length()){
			mx[i-s.length()-2] = nxt[i];
		}
	} 
	
	//return 0;
	
	/*if (pan){
		cout << "no";
		return 0;
	}*/
	
	int slen = s.length();
	for (int i = 0; i < slen; i++){
		mx[i] = min(mx[i],slen-i);
	}
	
	for (int i = 1; i < slen; i++){
		st[i] = i-mx[i]+1;
		if(mx[i] < mx[i-1]){
			st[i] = st[i-1];
			mx[i] = mx[i-1];
		}
	}
	int mxans = 0;
	int beg[3], len[3];
	for (int i = 0; i < slen; i++){
		int lft = 0;
		if(i) lft = min(mx[i-d[i]],slen-i-d[i]);
		
		if(mxans < (d[i]*2-1)+lft*2){
			mxans = (d[i]*2-1)+lft*2;
			beg[0] = st[i-d[i]], len[0] = lft;
			beg[1] = i-d[i]+1,len[1] = d[i]*2-1;
			beg[2] = s.length()-lft,len[2] = lft;
		}
	}

	int ans = 3;
	for (int i = 0; i <= 2; i++) if(!len[i]) ans--;
	
	cout << ans << endl;
	for (int i = 0; i <= 2; i++){
		if (!len[i]) continue;
		cout << beg[i]+1 << " " << len[i] << endl;
	}
	return 0;
}
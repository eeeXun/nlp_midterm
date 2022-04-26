// In The Name Of God
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <bitset>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <unordered_set>
#include <unordered_map>
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define f first
#define s second
#define pb push_back
#define mp make_pair
#define sagyndym_seni ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const ll N = 1e5+5, p1 = 911382323, p2 = 972663749, mod = 1e9+123;

inline int read(){
	char c = getchar();
	bool minus = 0;
	while (c < '0' || '9' < c){
		if(c == '-'){ minus = 1;}
		c = getchar();
		if(c == '-'){ minus = 1;}
	}
	int res = 0;
	while ('0' <= c && c <= '9') {
		res = (res << 3) + (res << 1) + c - '0';
		c = getchar();
	}
	if(minus){ res *= -1;}
	return res;
}

string s, t;
int suffPos[N], n;
vector<int> temp, pal;
int tree[N << 2];

void build1(int v, int vl, int vr){
	if(vl == vr){ tree[v] = temp[vl + n + 1]; return;}
	int vm = (vl + vr) >> 1;
	build1(v*2+1, vl, vm);
	build1(v*2+2, vm+1, vr);
	tree[v] = max(tree[v*2+1], tree[v*2+2]);
}

int down(int v, int vl, int vr, int val){
	if(vl == vr){ return vl;}
	int vm = (vl + vr) >> 1;
	if(tree[v*2+1] >= val){
		return down(v*2+1, vl, vm, val);
	}else
	if(tree[v*2+2] >= val){
		return down(v*2+2, vm+1, vr, val);
	}else{
		return -1;
	}
}

pair<int, int> tree2[N<<2];

void build2(int v, int vl, int vr){
	if(vl == vr){ tree2[v] = {pal[vl], vl}; return;}
	int vm = (vl + vr) >> 1;
	build2(v*2+1, vl, vm);
	build2(v*2+2, vm+1, vr);
	if(tree2[v*2+1].f > tree2[v*2+2].f){
		tree2[v] = tree2[v*2+1];
	}else{
		tree2[v] = tree2[v*2+2];
	}
}
// 0 1 2 3 4 5 |6| 5 4 3 2 1 0

pair<int, int> query(int v, int vl, int vr, int l, int r){
	if(l > vr || r < vl || r < l){ return {-mod, -mod};}
	if(l <= vl && vr <= r){ return tree2[v];}
	int vm = (vl + vr) >> 1;
	pair<int, int> q1 = query(v*2+1, vl, vm, l, r);
	pair<int, int> q2 = query(v*2+2, vm+1, vr, l, r);
	return (q1.f > q2.f ? q1 : q2);
}

void print(int v, int vl, int vr){
	if(vl == vr){ cout<<tree2[v].f<<" "; return;}
	int vm = (vl + vr) >> 1;
	print(v*2+1, vl, vm);
	print(v*2+2, vm+1, vr);
}

int main(){
	cin>>s; t = s;
	if(sz(s) == 1){cout<<"1\n1 1"; return 0;}
	n = sz(s);
	reverse(all(t));
	t = t + '#' + s; reverse(all(s));
	temp.resize(sz(t));
	for(int i = 1; i < sz(t); i++){
		int j = temp[i - 1];
		while(j > 0 && t[i] != t[j]){ j = temp[j - 1];}
		if(t[i] == t[j]){ j++;} temp[i] = j;
	}
	build1(0, 0, n-1); suffPos[0] = n;
	for(int i = 0; i < (n >> 1); i++){
		int res = down(0, 0, n-1, i + 1);
		suffPos[i + 1] = res == -1 ? -1 : n - res - 1;
	}
	pal.resize(n);
	int l = 0, r = -1;
	for(int i = 0; i < n; i++){
		int k = i > r ? 1 : min(pal[l+r-i], r-i+1);
		while(i + k < n && i - k >= 0 && s[i+k] == s[i-k]){ k++;}
		pal[i] = k;
		if(i+k-1 > r){
			l = i-k+1; r = i+k-1;
		}
	}
	build2(0, 0, n-1);
	int mxAns = 0, sfxPos = -1;
	pair<int, int> palPos = {-1, -1};
	for(int i = 0; i < (n >> 1); i++){
		if(suffPos[i] == -1){ continue;}
		int L = i, R = suffPos[i] - 1;
		int Left = 1, Right = n;
		pair<int, int> palindrome = {-1, -1};
		while(Left <= Right){
			int Mid = (Left + Right) >> 1;
			pair<int, int> val = query(0, 0, n-1, L + Mid - 1, R - Mid + 1);
			if(val.f >= Mid){
				palindrome = {Mid, val.s};
				Left = Mid + 1;
			}else{
				Right = Mid - 1;
			}
		}
		if(i * 2 + palindrome.f * 2 - 1 > mxAns){
			mxAns = i * 2 + palindrome.f * 2 - 1;
			sfxPos = i-1; palPos = palindrome;
		}
	}
	if(sfxPos == -1){
		cout<<"1\n";
		int pos = palPos.s + palPos.f - 1;
		int len = palPos.f * 2 - 1;
		cout<<n-pos<<" "<<len;
	}else{
		cout<<"3\n";
		int len1 = sfxPos + 1;
		int pos1 = sfxPos;
		int pos2 = suffPos[sfxPos + 1];
		pos2 = pos2 + len1 - 1;
		cout<<n-pos2<<" "<<len1<<"\n";
		int pos3 = palPos.s + palPos.f - 1;
		int len = palPos.f * 2 - 1;
		cout<<n-pos3<<" "<<len<<"\n";
		cout<<n-pos1<<" "<<len1;
	}
	return 0;
}
/* TIMUS: 292220YC*/



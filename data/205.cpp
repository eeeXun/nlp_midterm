#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cctype>

using namespace std;
typedef long long int64;
const int inf = 0x3f3f3f3f;
typedef double real;
const real eps = 1e-6;
typedef pair<int,int> pip;
#define Eo(x) { cerr << #x << " = " << (x) << endl; }

const int maxn = 1<<20;
char buf[maxn];
int d[maxn];
int z[maxn];
int where[maxn];
int finish[maxn];
int can[maxn];

void go(const string& s){
	int l=0, r=-1;
	int n =s.size();
	for (int i=0; i<n; ++i) {
		int k = (i>r ? 0 : min (d[l+r-i], r-i)) + 1;
		while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])  ++k;
		d[i] = --k;
		if (i+k > r)
			l = i-k,  r = i+k;
	}
}

void calcz(const string& s){
	int i,j=0,r=0,l;
	z[0] = l = s.size();
	for (i = 1; i < l; i++){
		z[i] = max(min(r-i,z[i-j]),0);
		for (;i+z[i]<l && s[z[i]] == s[i+z[i]]; z[i]++);
		if (i+z[i]>r){
			r = i+z[i];
			j = i;
		}
	}
}

int main(){
	gets(buf);
	string s(buf);
	go(s);
	{
	string zz(s);
	reverse(zz.begin(),zz.end());
	zz += '$';
	zz += s;
	calcz(zz);
	}
    for (int i=0; i<s.size()+3; ++i) {
		if (i < s.size())
		d[i]++;
        where[i] = s.size();
    }
	where[0] = 0;
	for (int i = s.size()+1; i < 1+2*s.size(); i++) if (z[i]){
		int j = i-s.size()-1;
		int zv = z[i];
		where[zv] = min(where[zv],j);
	}
	for (int i = s.size()+1; i >= 0; i--){
		where[i] = min(where[i],where[i+1]);
		finish[i] = where[i]+i;
	}
	for (int i = 0; i <= s.size(); i++){
		int from = finish[i];
		int to = finish[i+1];
		for (int j = from; j < to; j++){
			can[j] = i;
		}
	}
	int mx = 0;
	int best = -1;
	for (int i = 0; i < s.size(); i++){
		int l = d[i]*2-1;
		int rig = s.size()-i-d[i];
		int lef = i-d[i]+1;
		int tmp = l+2*min(can[lef],rig);
		if (tmp > mx){
			mx = tmp;
			best = i;
		}
	}
	int dd = d[best]*2-1;
	int centre = dd;
	int zz = (mx-centre)/2;
	int rig = s.size()-zz+1;
	int lef = where[zz]+1;
	if (centre < mx){
		puts("3");
		printf("%d %d\n%d %d\n%d %d\n",lef,zz,best-d[best]+2,centre,rig,zz);
	} else {
		puts("1");
		printf("%d %d\n",best-d[best]+2,centre);
	}

	return 0;
}


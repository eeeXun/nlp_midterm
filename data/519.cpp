#include <bits/stdc++.h>

using namespace std;

#define dbgs(x) cerr << (#x) << " --> " << (x) << ' '
#define dbg(x) cerr << (#x) << " --> " << (x) << endl

#define foreach(i,x) for(type(x)i=x.begin();i!=x.end();i++)
#define FOR(ii,aa,bb) for(int ii=aa;ii<=bb;ii++)
#define ROF(ii,aa,bb) for(int ii=aa;ii>=bb;ii--)

#define type(x) __typeof(x.begin())

#define sag (k + k + 1)
#define sol (k + k)

#define pb push_back
#define mp make_pair

#define nd second
#define st first

#define endl '\n'

typedef pair < int ,int > pii;

typedef long long ll;

const long long linf = 1e18+5;
const int mod = (int) 1e9 + 7;
const int logN = 17;
const int inf = 1e9;
const int N = 2e5 + 5;

int mx, n, m, x, y, hash1[N], hash2[N], P[N], GO[N], k, t;
char str[N];
pii ans[4];

int get1(int x, int y) { return hash1[y] - hash1[x-1] * P[y-x+1]; }
int get2(int x, int y) { return hash2[x] - hash2[y+1] * P[y-x+1]; }

int get(int l, int r) {
	int bas = r+1, son = n;
	while(bas < son) {
		int orta = bas + son >> 1;
		if(GO[orta] >= l) bas = orta + 1;
		else son = orta;
	}
	if(GO[bas] < l) return n-bas+1;
	return 0;
}

void solve(int x) {
	int bas = 1, son = min(x, n-x+1);
	while(bas < son) {
		int orta = bas + son >> 1;
		if(orta == bas) orta++;
		if(get1(x-orta+1, x+orta-1) == get2(x-orta+1,x+orta-1)) bas = orta;
		else son = orta - 1;
	}
	int l = x-bas+1, r = x+bas-1;
	int sz = get(l, r), w = n - sz + 1;
	if(2 * sz + bas * 2 - 1 > mx) {
		mx = 2 * sz + bas * 2 - 1;
		k = (sz != 0) * 2 + 1;
		if(sz) { ans[3] = mp(w, sz); ans[1] = mp(GO[w]-sz+1, sz); ans[2] = mp(l, r-l+1);  }
		else ans[1] = mp(l, r-l+1);
	}
}

int main() {

	scanf("%s", str+1);
	n = strlen(str+1);
	
	P[0] = 1;
	FOR(i, 1, n) P[i] = P[i-1] * 29;
	FOR(i, 1, n) hash1[i] = hash1[i-1] * 29 + str[i] - 'a';
	ROF(i, n, 1) hash2[i] = hash2[i+1] * 29 + str[i] - 'a';

	int j = 1;

	ROF(i, n, 1) {
		while(get1(i, n) != get2(j, j+n-i) && j < n) j++;
		GO[i] = j + n - i;
	}
	
	FOR(i, 1, n)
		solve(i);		
	
	cout << k << endl;
	
	FOR(i, 1, k)
		cout << ans[i].st << ' ' << ans[i].nd << endl;

	return 0;
}

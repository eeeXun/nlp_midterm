#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define dd(a) cout << #a << " = " << a << " "
#define de(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, ans;
int pa[N << 1], ns[N], nt[N], ma[N], pos[N];
vector<pii> res;
char s[N], sr[N];

void Manacher(char *s,int n,int *pa){
	pa[0] = 1;
	for(int i=1,j=0;i<(n<<1)-1;++i){
		int p = i >> 1 , q = i - p , r = ((j + 1)>>1) + pa[j] - 1;
		pa[i] = r < q ? 0 : min(r - q + 1 , pa[(j<<1) - i]);
		while(0 <= p - pa[i] && q + pa[i] < n && s[p - pa[i]] == s[q + pa[i]])
			pa[i]++;
		if(q + pa[i] - 1 > r) j = i;
	}
	rep(i, 0, n) pa[i] = pa[i << 1];
}

void kmp(char *s,int *ns,char *t,int *nt){
	int lens = strlen(s);
	int lent = strlen(t);
	nt[0] = -1;
	for(int i=0,j=-1;i<lens;++i){
		while(j >= 0 && s[i] != t[j + 1]) j = nt[j];
		if(s[i] == t[j + 1]) ++j;
		ns[i] = j;
		if(j + 1 == lent) j = nt[j];
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	n = strlen(s);
	Manacher(s, n, pa);
	rep(i, 0, n) sr[i] = s[n - 1 - i];sr[n] = '\0';
	kmp(sr + 1, nt + 1, sr, nt);
	kmp(s, ns, sr, nt);
	rep(i, 0, n) if(~ns[i]) ++ns[i];
	ma[0] = ns[0];
	pos[0] = 0;
	rep(i, 1, n) {
		ma[i] = ma[i - 1];
		pos[i] = pos[i - 1];
		if(ma[i] < ns[i]) {
			ma[i] = ns[i];
			pos[i] = i;
		}
	}
	rep(i, 0, n) {
		int k = i - pa[i];
		int t = max(0, min(k < 0 ? 0 : ma[k], n - i - pa[i]));
		int c = pa[i] * 2 - 1 + t * 2;
		if(ans < c) {
			ans = c;
			res.clear();
			res.pb(mp(i - pa[i] + 1, pa[i] * 2 - 1));
			if(t) {
				res.pb(mp(n - t, t));
				int o = pos[k] - 2 * ns[pos[k]] + t + 1;
				res.pb(mp(o, t));
			}
		}
	}
	sort(all(res));
	cout << sz(res) << endl;
	for(auto u : res) cout << u.fi + 1 << " " << u.se << endl;
	return 0;
}

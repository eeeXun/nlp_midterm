#include <bits/stdc++.h>

using namespace std;

#define fore(i, s, e) for(int i = s; i < e; i++)
#define SZ(a) ((int)a.size())
#define pb push_back
#define FIN ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define ALL(a) a.begin(), a.end()
#define fst first
#define snd second

#define RB(x) (x<n?r[x]:0)
void csort(vector<int>& sa, vector<int>& r, int k){
	int n=sa.size();
	vector<int> f(max(255,n),0),t(n);
	fore(i,0,n)f[RB(i+k)]++;
	int sum=0;
	fore(i,0,max(255,n))f[i]=(sum+=f[i])-f[i];
	fore(i,0,n)t[f[RB(sa[i]+k)]++]=sa[i];
	sa=t;
}
vector<int> constructSA(string& s){ // O(n logn)
	int n=s.size(),rank;
	vector<int> sa(n),r(n),t(n);
	fore(i,0,n)sa[i]=i,r[i]=s[i];
	for(int k=1;k<n;k*=2){
		csort(sa,r,k);csort(sa,r,0);
		t[sa[0]]=rank=0;
		fore(i,1,n){
			if(r[sa[i]]!=r[sa[i-1]]||RB(sa[i]+k)!=RB(sa[i-1]+k))rank++;
			t[sa[i]]=rank;
		}
		r=t;
		if(r[sa[n-1]]==n-1)break;
	}
	return sa;
}
vector<int> computeLCP(string& s, vector<int>& sa){
	int n=s.size(),L=0;
	vector<int> lcp(n),plcp(n),phi(n);
	phi[sa[0]]=-1;
	fore(i,1,n)phi[sa[i]]=sa[i-1];
	fore(i,0,n){
		if(phi[i]<0){plcp[i]=0;continue;}
		while(s[i+L]==s[phi[i]+L])L++;
		plcp[i]=L;
		L=max(L-1,0);
	}
	fore(i,0,n)lcp[i]=plcp[sa[i]];
	return lcp; // lcp[i]=LCP(sa[i-1],sa[i])
}

const int N = 2e5;
const int K = 20;

struct Sparse {
  vector<vector<int>> st;int n;  // K such that 2^K>n
  int (*oper)(int, int);
  Sparse(int n, int (*f)(int, int)): n(n), oper(f) {
    st.resize(K);
    fore(i, 0, K) st[i].resize(1<<K);
  }
  void st_init(vector<int>& a){
    fore(i,0,n)st[0][i]=a[i];
    fore(k,1,K)fore(i,0,n-(1<<k)+1)
      st[k][i]=oper(st[k-1][i],st[k-1][i+(1<<(k-1))]);
  }
  int st_query(int s, int e){
    int k=31-__builtin_clz(e-s);
    return oper(st[k][s],st[k][e-(1<<k)]);
  }
};

pair<int, int> getBoundaries(int l, int k, int n, Sparse &s) {
  int bl = k, br = k;
  int izq = 0, der = k - 1;
  while(izq <= der) {
    int med = (izq + der) / 2;
    if(s.st_query(med + 1, k + 1) >= l) der = med - 1, bl = med;
    else izq = med + 1;
  }
  izq = k + 1, der = n - 1;
  while(izq <= der) {
    int med = (izq + der) / 2;
    if(s.st_query(k + 1, med + 1) >= l) izq = med + 1, br = med;
    else der = med - 1;
  }
  return {bl, br};
}

int my_max(int a, int b) {
  return max(a, b);
}
int my_min(int a, int b) {
  return min(a, b);
}

int d1[N];

void manacher(string& s){
	int l=0,r=-1,n=s.size();
	fore(i,0,n){
		int k=i>r?1:min(d1[l+r-i],r-i);
		while(i+k<n&&i-k>=0&&s[i+k]==s[i-k])k++;
		d1[i]=k--;
		if(i+k>r)l=i-k,r=i+k;
	}
}

int main() {
  string s; cin >> s;
  string t = string(s.rbegin(), s.rend());
  string R = s + '{' + t + '}';

  vector<int> best(SZ(s), SZ(s));
  auto sa = constructSA(R);
  auto lcp = computeLCP(R, sa);
  
  Sparse ssa(SZ(sa), my_max); ssa.st_init(sa);
  Sparse slpc(SZ(lcp), my_min); slpc.st_init(lcp);

  fore(i, 0, SZ(sa)) {
    if(sa[i] >= SZ(s)) continue;
    int l = SZ(s) - sa[i];
    if(2 * l >= SZ(s)) continue;
    auto p = getBoundaries(l, i, SZ(R), slpc);
    int w = ssa.st_query(p.fst, p.snd + 1);
    if(w > SZ(s)) {
      w = 2 * SZ(s) - w - l + 1;
      best[l] = w;
    }
  }
  manacher(s);
  int res = 0;
  vector<pair<int, int>> rta;
  fore(i, 0, SZ(s)) {
    int l = i - d1[i] + 1, r = d1[i] + i; // [l, r)
    int dist = r - l;
    if(dist > res) {
      res = dist;
      rta = {{l, dist}};
    }
    int izq = 1, der = SZ(s) - r;
    while(izq <= der) {
      int med = (izq + der) / 2;
      if(best[med] + med <= l) {
        if(dist + 2 * med > res) {
          res = dist + 2 * med;
          rta = {{best[med], med}, {l, dist}, {SZ(s) - med, med}};
        }
        izq = med + 1;
      } else der = med - 1;
    }
  }
  cout << SZ(rta) << endl;
  for(auto x : rta) cout << x.fst + 1 << " " << x.snd << endl;

  
  return 0;
}
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/933.cpp" 2


# 3 "data/933.cpp"
using namespace std;
# 14 "data/933.cpp"
void csort(vector<int>& sa, vector<int>& r, int k){
 int n=sa.size();
 vector<int> f(max(255,n),0),t(n);
 for(int i = 0; i < n; i++)f[(i+k<n?r[i+k]:0)]++;
 int sum=0;
 for(int i = 0; i < max(255,n); i++)f[i]=(sum+=f[i])-f[i];
 for(int i = 0; i < n; i++)t[f[(sa[i]+k<n?r[sa[i]+k]:0)]++]=sa[i];
 sa=t;
}
vector<int> constructSA(string& s){
 int n=s.size(),rank;
 vector<int> sa(n),r(n),t(n);
 for(int i = 0; i < n; i++)sa[i]=i,r[i]=s[i];
 for(int k=1;k<n;k*=2){
  csort(sa,r,k);csort(sa,r,0);
  t[sa[0]]=rank=0;
  for(int i = 1; i < n; i++){
   if(r[sa[i]]!=r[sa[i-1]]||(sa[i]+k<n?r[sa[i]+k]:0)!=(sa[i-1]+k<n?r[sa[i-1]+k]:0))rank++;
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
 for(int i = 1; i < n; i++)phi[sa[i]]=sa[i-1];
 for(int i = 0; i < n; i++){
  if(phi[i]<0){plcp[i]=0;continue;}
  while(s[i+L]==s[phi[i]+L])L++;
  plcp[i]=L;
  L=max(L-1,0);
 }
 for(int i = 0; i < n; i++)lcp[i]=plcp[sa[i]];
 return lcp;
}

const int N = 2e5;
const int K = 20;

struct Sparse {
  vector<vector<int>> st;int n;
  int (*oper)(int, int);
  Sparse(int n, int (*f)(int, int)): n(n), oper(f) {
    st.resize(K);
    for(int i = 0; i < K; i++) st[i].resize(1<<K);
  }
  void st_init(vector<int>& a){
    for(int i = 0; i < n; i++)st[0][i]=a[i];
    for(int k = 1; k < K; k++)for(int i = 0; i < n-(1<<k)+1; i++)
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
 for(int i = 0; i < n; i++){
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

  vector<int> best(((int)s.size()), ((int)s.size()));
  auto sa = constructSA(R);
  auto lcp = computeLCP(R, sa);

  Sparse ssa(((int)sa.size()), my_max); ssa.st_init(sa);
  Sparse slpc(((int)lcp.size()), my_min); slpc.st_init(lcp);

  for(int i = 0; i < ((int)sa.size()); i++) {
    if(sa[i] >= ((int)s.size())) continue;
    int l = ((int)s.size()) - sa[i];
    if(2 * l >= ((int)s.size())) continue;
    auto p = getBoundaries(l, i, ((int)R.size()), slpc);
    int w = ssa.st_query(p.first, p.second + 1);
    if(w > ((int)s.size())) {
      w = 2 * ((int)s.size()) - w - l + 1;
      best[l] = w;
    }
  }
  manacher(s);
  int res = 0;
  vector<pair<int, int>> rta;
  for(int i = 0; i < ((int)s.size()); i++) {
    int l = i - d1[i] + 1, r = d1[i] + i;
    int dist = r - l;
    if(dist > res) {
      res = dist;
      rta = {{l, dist}};
    }
    int izq = 1, der = ((int)s.size()) - r;
    while(izq <= der) {
      int med = (izq + der) / 2;
      if(best[med] + med <= l) {
        if(dist + 2 * med > res) {
          res = dist + 2 * med;
          rta = {{best[med], med}, {l, dist}, {((int)s.size()) - med, med}};
        }
        izq = med + 1;
      } else der = med - 1;
    }
  }
  cout << ((int)rta.size()) << endl;
  for(auto x : rta) cout << x.first + 1 << " " << x.second << endl;


  return 0;
}

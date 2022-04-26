# 63 "/usr/include/c++/11.2.0/set" 2 3
# 71 "/usr/include/c++/11.2.0/set" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

  namespace pmr
  {
    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 13 "data/287.cpp" 2




# 16 "data/287.cpp"
using U = unsigned int;
using LL = long long;
using ULL = unsigned long long;
using LD = long double;
using std::cin; using std::cout;
using std::endl; using std::cerr;
using std::bitset; using std::map;
using std::queue; using std::priority_queue;
using std::set; using std::string;
using std::vector;
using std::pair; using std::make_pair;
using pii = std::pair<int, int>;
using pll = std::pair<LL, LL>;




void displayTime() {}
# 53 "data/287.cpp"
class MyTimer {
public: void reset() {} void report() {}
} myTimer;


template<typename T1, typename T2>
inline bool chmin(T1 &a, const T2 &b) { return a > b ? a = b, true : false; }
template<typename T1, typename T2>
inline bool chmax(T1 &a, const T2 &b) { return a < b ? a = b, true : false; }




inline int readint() {
  int a = 0; char c = getchar(), p = 0;
  while(isspace(c)) c = getchar();
  if(c == '-') p = 1, c = getchar();
  while(isdigit(c)) a = a*10 + c - '0', c = getchar();
  return p ? -a : a;
}
inline LL readLL() {
  LL a = 0; char c = getchar(), p = 0;
  while(isspace(c)) c = getchar();
  if(c == '-') p = 1, c = getchar();
  while(isdigit(c)) a = a*10 + c - '0', c = getchar();
  return p ? -a : a;
}

const int maxN = 100000 + 233;
int n, r[maxN];
char buc[maxN * 2];
int buc_z[maxN * 2];
char *s = buc + maxN;
int *z = buc_z + maxN;
int ans;
vector<pii> sol;

void manacher(char *s, int *r) {
  int n = strlen(s);
  int M = 0, R = 0;
  r[0] = 1;
  for(int i = 1; i < n; ++i) {
   int &len = r[i];
    len = i > R ? 1 : std::min(r[2 * M - i], R - i);
    while(i - len >= 0 && i + len < n && s[i + len] == s[i - len]) ++len;
    if(i + len > R) M = i, R = i + len;
  }
}

void algoZ(char *s, int *z) {
  int n = strlen(s);
  int L = 0, R = 0;
  for(int i = 1; i < n; ++i) {
    int &len = z[i];
  len = i > R ? 0 : std::min(z[i - L], R - i);
    while(i + len < n && s[len] == s[i + len]) ++len;
    if(i + len > R) L = i, R = i + len;
  }
}

template<int NODE>
struct SegmentTree {


  int max[NODE];
  void maintain(int o, int L, int R) {
    max[o] = r[max[(o << 1)]] > r[max[(o << 1 | 1)]] ? max[(o << 1)] : max[(o << 1 | 1)];
  }
  void build(int o, int L, int R) {
    if(L == R) {
      max[o] = L;
    } else {
      int M = (L + R) >> 1;
      build((o << 1), L, M);
      build((o << 1 | 1), M + 1, R);
      maintain(o, L, R);
    }
  }
  int ql, qr, qp, qans;
  void modify(int o, int L, int R) {
    if(L == R) {
      max[o] = n;
    } else {
      int M = (L + R) >> 1;
      if(qp <= M) modify((o << 1), L, M);
      else modify((o << 1 | 1), M + 1, R);
      maintain(o, L, R);
    }
  }
  void query(int o, int L, int R) {
    if(ql <= L && R <= qr) {
      if(chmax(qans, r[max[o]])) qp = max[o];
    } else {
      int M = (L + R) >> 1;
      if(ql <= M) query((o << 1), L, M);
      if(qr > M) query((o << 1 | 1), M + 1, R);
    }
  }


};
SegmentTree <maxN * 4> st;

int mode;
struct Candidate {
  int ls, rs, sideLen;
  int L, M, R;
  int pos, len;
  Candidate(int ls, int rs, int sideLen, int L, int M, int R) :
    ls(ls), rs(rs), sideLen(sideLen), L(L), M(M), R(R) { pos = len = -1; }
  void update() {
    if(chmax(ans, sideLen * 2 + len)) sol = {pii(ls, sideLen), pii(pos, len), pii(rs, sideLen)};
  }
  friend bool operator < (const Candidate &A, const Candidate &B) {
    if(mode == 1) return A.L < B.L;
    else if(mode == 2) return A.R < B.R;
    else return 
# 169 "data/287.cpp" 3 4
               (static_cast <bool> (
# 169 "data/287.cpp"
               false
# 169 "data/287.cpp" 3 4
               ) ? void (0) : __assert_fail (
# 169 "data/287.cpp"
               "false"
# 169 "data/287.cpp" 3 4
               , "data/287.cpp", 169, __extension__ __PRETTY_FUNCTION__))
# 169 "data/287.cpp"
                            , false;
  }
};
vector<Candidate> vc;

void initialize() {
  scanf("%s", s);
  n = strlen(s);
  manacher(s, r);
  for(int i = 0; i < n; ++i) s[- i - 1] = s[i];
  algoZ(s - n, z - n);




  ans = 0;
  for(int i = 0; i < n; ++i) if(chmax(ans, r[i] * 2 - 1)) ans = r[i] * 2 - 1, sol = {pii(i - r[i] + 1, r[i] * 2 - 1)};

  for(int i = 0; i < n; ++i) {
    int len = std::min(z[i], (n - i - 1) / 2);
    if(len == 0 || n - i < ans) continue;
    int l = i + len, r = n - len - 1;
    int m = (l + r) / 2;
    vc.push_back(Candidate(i, n - len, len, l, m, r));
  }
}

priority_queue <pii, vector<pii>, std::greater<pii> > little_top;
priority_queue <pii, vector<pii>, std::less<pii> > large_top;

void solve() {

  mode = 1;
  std::sort(vc.begin(), vc.end());
  for(int i = 0; i < n; ++i) little_top.push(pii(i - r[i] + 1, i));
  st.build(1, 0, n - 1);
  for(auto &c : vc) {
   int r = c.R, l = c.L;
    if(r - l < 5) {
      for(int i = l; i < r; ++i) {
        c.len = std::min({::r[i], i - l + 1, r - i + 1});
        c.pos = i - c.len + 1;
        c.len = c.len * 2 - 1;
        c.update();
      }
      break;
    }
    while(!little_top.empty() && little_top.top().first < c.L) {
      st.qp = little_top.top().second;
      st.modify(1, 0, n - 1);
      little_top.pop();
    }
    st.qans = -1; st.qp = -1;
    st.ql = c.L; st.qr = c.M;
    st.query(1, 0, n - 1);
    if(c.L <= st.qp && st.qp <= c.M) {
      c.pos = st.qp - ::r[st.qp] + 1;
      c.len = ::r[st.qp] * 2 - 1;
      c.update();
    }
  }




  mode = 2;
  std::sort(vc.begin(), vc.end());
  for(int i = 0; i < n; ++i) large_top.push(pii(i + r[i] - 1, i));
  st.build(1, 0, n - 1);
  for(auto &c : vc) {
   int r = c.R, l = c.L;
    if(r - l < 5) break;
    while(!large_top.empty() && large_top.top().first > c.R) {
      st.qp = large_top.top().second;
      st.modify(1, 0, n - 1);
      large_top.pop();
    }
    st.qans = -1; st.qp = -1;
    st.ql = c.M + 1; st.qr = c.R;
    st.query(1, 0, n - 1);
    if(c.M + 1 <= st.qp && st.qp <= c.R) {
      c.pos = st.qp - ::r[st.qp] + 1;
      c.len = ::r[st.qp] * 2 - 1;
      c.update();
    }
  }

}

int main() {

  initialize();

  solve();

  cout << sol.size() << endl;
  for(auto p : sol) cout << p.first + 1 << " " << p.second << endl;
  return 0;
}

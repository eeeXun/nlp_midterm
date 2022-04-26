      static auto&
      _S_get_tree(std::set<_Val, _Cmp2, _Alloc>& __set)
      { return __set._M_t; }

      static auto&
      _S_get_tree(std::multiset<_Val, _Cmp2, _Alloc>& __set)
      { return __set._M_t; }
    };



}
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
# 7 "data/435.cpp" 2

# 7 "data/435.cpp"
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
# 40 "data/435.cpp"
const int MAX = 100000;
const int INF = 1000000001;

void manacher(char T[], int n, int R[], bool p) {
 int j = -1;
 for(int i=0;i<n;++i)
 {
  R[i] = min(R[max(0, j-(i-j))], j + R[j] - i);
  R[i] = max(R[i], 0);
  while(i+R[i]+1 < n && i-R[i]-p >= 0 && T[i+R[i]+1] == T[i-R[i]-p])
   ++R[j = i];
 }
}
void prefpref(char T[], int n, int PP[]) {
 PP[0] = 0;
 int j = 0;
 for(int i=1;i<=n-1;++i)
 {
  PP[i] = min(PP[j]+j-i, PP[max(0, i-j)]);
  PP[i] = max(PP[i], 0);
  while(PP[i]+i < n && T[PP[i]] == T[PP[i]+i])
   ++PP[j = i];
 }
}

char A[2*MAX+2];

int palin[MAX];
int pref[2*MAX+1];
int Pmax[MAX];

int n;

int binSearch(int prefLen, int sufLen) {
 int p = 0, q = min(prefLen, sufLen);
 while(p < q)
 {
  int r = (p+q+1)/2;
  if(Pmax[prefLen-r] >= r)
   p = r;
  else
   q = r - 1;
 }
 return p;
}

int main(int argc, char *argv[]) {
 scanf("%s", A);
 n = strlen(A);
 if(n < 3) {
  printf("1\n1 1\n");
  return 0;
 }
 manacher(A, n, palin, true);
 A[n] = '$';
 memcpy(A+n+1, A, n);
 reverse(A, A+n);
 prefpref(A, 2*n+1, pref);
 Pmax[0] = pref[n+1];
 for(int i=1;i<=n-1;++i)
  Pmax[i] = max(Pmax[i-1], pref[n+1+i]);
 reverse(A, A+n);
 int ans;
 int ansLen = 0;
 for(int i=1;i<=n-2;++i)
 {
  int midLen = 2 * palin[i] + 1;
  int prefLen = i - palin[i];
  int sufLen = n - midLen - prefLen;
  int x = binSearch(prefLen, sufLen);
  int passLen = 2*x + midLen;
  if(passLen > ansLen) {
   ans = i;
   ansLen = passLen;
  }
 }
 int midLen = 2 * palin[ans] + 1;
 int prefLen = ans - palin[ans];
 int sufLen = n - midLen - prefLen;
 int x = binSearch(prefLen, sufLen);




 if(x) {
  printf("3\n");
  int i = 0;
  while(pref[n+1+i] < x)
   ++i;
  printf("%d %d\n", i + 1, x);
  printf("%d %d\n", ans - palin[ans] + 1, midLen);
  printf("%d %d\n", n - x + 1, x);
 }
 else {
  printf("1\n");
  printf("%d %d\n", prefLen + 1, midLen);
 }
 return 0;
}

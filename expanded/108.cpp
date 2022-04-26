# 4 "data/108.cpp" 2



# 6 "data/108.cpp"
using std::pair;
using std::min;
using std::max;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const int N = 100010;
const int BASE = 131;
int _w;

int n, ans1, ans2;
char s[N];
ull pf[N], sf[N], pw[N];
pii pos1, pos2[3];

void prelude() {
 for( int i = 1; i <= n; ++i )
  pf[i] = pf[i-1] * BASE + s[i];
 for( int i = n; i >= 1; --i )
  sf[i] = sf[i+1] * BASE + s[i];
 pw[0] = 1;
 for( int i = 1; i <= n; ++i )
  pw[i] = pw[i-1] * BASE;
}

ull pfh( int l, int r ) {
 return pf[r] - pf[l-1] * pw[r-l+1];
}

ull sfh( int l, int r ) {
 return sf[l] - sf[r+1] * pw[r-l+1];
}

int r[N];

namespace RMQ {
 int maxv[N][20], logn[N];
 void init() {
  for( int i = 1; i <= n; ++i )
   maxv[i][0] = i;
  for( int k = 1; (1<<k) <= n; ++k )
   for( int i = 1; i+(1<<k)-1 <= n; ++i ) {
    int p = maxv[i][k-1], q = maxv[i+(1<<(k-1))][k-1];
    maxv[i][k] = r[p] > r[q] ? p : q;
   }
  int k = 0;
  for( int i = 1; i <= n; ++i ) {
   if( (1<<(k+1)) == i ) ++k;
   logn[i] = k;
  }
 }
 int query( int l, int r ) {
  int k = logn[r-l+1];
  int p = maxv[l][k], q = maxv[r+1-(1<<k)][k];
  return ::r[p] > ::r[q] ? p : q;
 }
}

int _solve2( int l, int r ) {
 int low = 1, high = n;
 while( low < high ) {
  int mid = (low + high + 1)/2;
  int p = l+mid-1, q = r-mid+1;
  if( p <= q && ::r[RMQ::query(p, q)] >= mid ) low = mid;
  else high = mid-1;
 }
 return RMQ::query(l+low-1, r-low+1);
}

void solve1() {
 r[1] = 1;
 int right = 1, mid = 1;
 for( int i = 2; i <= n; ++i ) {
  int l = i > right ? 1 : min(right-i+1, r[mid+mid-i]);
  while( i-l >= 1 && i+l <= n && s[i-l] == s[i+l] ) ++l;
  r[i] = l;
  if( i+l-1 >= right ) right = i+l-1, mid = i;
 }
 for( int i = 1; i <= n; ++i )
  if( r[i]+r[i]-1 > ans1 ) {
   ans1 = r[i]+r[i]-1;
   pos1 = pii(i-r[i]+1, r[i]+r[i]-1);
  }
 RMQ::init();
}

int lcp( int i, int j ) {
 int low = 0, high = n-i+1;
 while( low < high ) {
  int mid = (low + high + 1)/2;
  if( pfh(i, i+mid-1) == sfh(j-mid+1, j) )
   low = mid;
  else high = mid-1;
 }
 return low;
}

void solve2() {
 for( int i = 1; i <= n-2; ++i ) {
  int len = lcp(i, n);
  if( !len || i+len-1 >= n-len+1 ) continue;
  int l = i+len, r = n-len;
  int p = _solve2(l, r);
  int rad = min(r-p+1, p-l+1);
  rad = min(rad, ::r[p]);
  if( len+len+rad+rad-1 > ans2 ) {
   ans2 = len+len+rad+rad-1;
   pos2[0] = pii(i, len);
   pos2[1] = pii(p-rad+1, rad+rad-1);
   pos2[2] = pii(n-len+1, len);
  }
 }
}

int main() {
 _w = scanf( "%s", s+1 );
 n = (int)strlen(s+1);
 prelude(), solve1(), solve2();
 if( ans1 > ans2 ) {
  puts("1");
  printf( "%d %d\n", pos1.first, pos1.second );
 } else {
  puts("3");
  for( int i = 0; i < 3; ++i )
   printf( "%d %d\n", pos2[i].first, pos2[i].second );
 }
 return 0;
}

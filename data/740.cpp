#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <climits>
#include <queue>
#include <set>
#include <map>
#include <valarray>
#include <bitset>
#include <stack>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)n;++i)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
#define ALL(c) (c).begin(), (c).end()
typedef long long ll;
typedef pair<int,int> pii;
const int INF = 1<<29;
const double PI = acos(-1);
const double EPS = 1e-8;

const int MAX_N = 100000;
int rad[MAX_N*2];
void manacher(const string &text) {
  int n = text.size();
  int i, j, k;
  for (i = 0, j = 0; i < 2*n; i += k, j = max(j-k, 0)) {
    while (i-j >= 0 && i+j+1 < 2*n && text[(i-j)/2] == text[(i+j+1)/2]) ++j;
    rad[i] = j;
    for (k = 1; i-k >= 0 && rad[i]-k >= 0 && rad[i-k] != rad[i]-k; ++k)
      rad[i+k] = min(rad[i-k], rad[i]-k);
  }
  REP(i,n) rad[i]=rad[i*2];
}

// calc posl[suflen]
typedef unsigned long long ull;
int posl[100000];
int posr[100000];

void calc(const string &s) {
  int n = s.size();
  const ull B = 1e8+7;
  ull suf_hash = 0;
  ull pre_hash = 0;
  
  REP(i,n)posr[i]=posl[i]=INF;
  posl[0] = 0;

  ull t = B;

  for (int i=1; i<=n/2; ++i) {
    suf_hash = suf_hash*B + s[n-i];
    for (int left=posl[i-1]; left+i<n-i; ++left) {
      pre_hash = pre_hash * B + s[left+i-1];
      if (left != posl[i-1]) pre_hash -= s[left-1]*t;
      if (pre_hash == suf_hash) {
        posl[i] = left;
        break;
      }
    }
    if (posl[i] == INF) break;
    t *= B;
    posr[i] = posl[i] + i;
  }
}

bool check(int n, int i, int x) {
  if (i+rad[i]/2 >= n-x) return 0;
  if (posr[x] > i-rad[i]/2) return 0;
  return 1;
}

int main() {
  string s;
  cin >> s;
  manacher(s);
  calc(s);
  int n = s.size();
  int ma = -1;
  pii ans;
  REP(i,n) {
    int tmp = rad[i];
    int low = 0, high = n;
    while(low+1<high) {
      int mid = (low+high)/2;
      if (check(n,i,mid)) low = mid;
      else high = mid;
    }
    tmp += low*2;
    if (tmp > ma) {
      ma = tmp;
      ans = pii(i,low);
    }
  }
  if (ans.second == 0) {
    cout << 1 << endl;
    int i = ans.first;
    cout << i-rad[i]/2+1 << " " << rad[i] << endl;
  } else {
    cout << 3 << endl;
    cout << posl[ans.second]+1 << " " << ans.second << endl;
    int i = ans.first;
    cout << i-rad[i]/2+1 << " " << rad[i] << endl;
    cout << n-ans.second+1 << " " << ans.second << endl;
  }
}

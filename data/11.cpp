// In the name of God

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <complex>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <deque>
#define pf push_front
#define pb push_back
#define x first
#define y second

using namespace std;

typedef long long ll;
typedef double ld;
typedef complex<ld> point;
typedef pair<ll,ll> pii;
typedef pair<pii,int> ppii;

const int maxn = 1000 * 100 + 10;
const ll hn = 29;

string s;
int n;
ll hash[maxn],hash_[maxn],Pow[maxn];
int l[maxn];

class segment
{
public:
  int ind_Max,beg,end;
  segment *l_,*r;

  inline void make(int fi,int se){
    beg = fi;
    end = se;
    if(fi == se){
      l_ = r = NULL;
      ind_Max = fi;
      return;
    }

    int mid = (beg + end) / 2;

    l_ = new segment;
    r = new segment;

    l_ -> make(beg,mid);
    r -> make(mid+1,end);

    int ml,mr;
    ml = l_ -> ind_Max;
    mr = r -> ind_Max;

    if(l[ml] > l[mr])
      ind_Max = ml;
    else
      ind_Max = mr;
  }

  inline int get_Max(int fi,int se){
    if(fi == beg && se == end)
      return ind_Max;
    if(fi > se)
      return -1;

    int mr = -1,ml = -1;
    ml = l_ -> get_Max(max(fi,l_->beg),min(l_->end,se) );
    mr = r -> get_Max(max(fi,r->beg),min(r->end,se) );

    if(ml == -1 && mr == -1)
      return -1;
    else if(ml == -1)
      return mr;
    else if(mr == -1)
      return ml;
    else if(l[mr] > l[ml])
      return mr;
    else
      return ml;
  }

};

inline ll find_hash(int fi,int se)
{
  if(fi > se)
    return 0;
  if(fi == 0)
    return hash[se];
  return Pow[fi] * (hash[se] - hash[fi-1]);
}

inline ll find_hash_(int fi,int se)
{
  if(fi > se)
    return 0;
  if(se == n-1)
    return hash_[fi];
  return Pow[n-se-1] * (hash_[fi] - hash_[se+1]);
}

inline bool ok(int ind,int L)
{
  if(ind-L+1 < 0 || ind+L-1 > n-1)
    return false;

  return (find_hash(ind-L+1,ind) == find_hash_(ind,ind+L-1) );
}

segment *root;

int main()
{
  ios_base::sync_with_stdio(false);

  cin >> s;
  n = s.size();

  Pow[0] = 1;
  for(int i=1;i<maxn;++i)
    Pow[i] = Pow[i-1] * hn;

  hash[0] = (s[0] - 'a') * Pow[maxn-1];
  for(int i=1;i<n;++i)
    hash[i] = hash[i-1] + (s[i] - 'a') * Pow[maxn-i-1];

  hash_[n-1] = (s[n-1] - 'a') * Pow[maxn-1];
  for(int i=n-2;i>=0;--i)
    hash_[i] = hash_[i+1] + (s[i] - 'a') * Pow[maxn-(n-i)];

  for(int i=0;i<n;++i){
    int mi = 0;
    int ma = n+1;
    for(;mi+1<ma;){
      int mid = (mi + ma) / 2;
      if(ok(i,mid) )
	mi = mid;
      else
	ma = mid;
    }
    l[i] = mi;
  }

  root = new segment;
  root -> make(0,n-1);

  int now = 0;
  int ans = -1;
  vector<pii> out;
  for(int i=0;i<=n/2;++i){
    while(now<n){
      if(now+i-1 >= n-i-1){
	sort(out.begin(),out.end() );
	cout << out.size() << endl;
	for(int j=0;j<out.size();++j)
	  cout << out[j].x+1 << " " << out[j].y << endl;
	return 0;
      }
      if(find_hash(now,now+i-1) == find_hash_(n-i,n-1) ){
	int beg = now+i;
	int end = n-i-1;
	int mi = 0;
	int ma = ( (end-beg+1)/2) - ( ( (end-beg+1)%2) == 0) + 1;
	int J = now+i;
	for(;mi+1<ma;){
	  int mid = (mi+ma) / 2;
	  if(beg+mid > end-mid){
	    ma = mid;
	    continue;
	  }
	  int maxi = root -> get_Max(beg+mid,end-mid);
	  if(l[maxi] >= mid+1){
	    mi = mid;
	    J = maxi;
	  }
	  else
	    ma = mid;
	}
	int NOW = i*2+mi*2+1;
	if(NOW > ans){
	  ans = NOW;
	  out.resize(0);
	  if(i > 0){
	    out.pb(pii(n-i,i) );
	    out.pb(pii(now,i) );
	  }
	  out.pb(pii(J-mi,mi*2+1) );
	}
	break;
      }
      else
	now++;
    }
    if(now >= n){
      sort(out.begin(),out.end() );
      cout << out.size() << endl;
      for(int j=0;j<out.size();++j)
	cout << out[j].x+1 << " " << out[j].y << endl;
      return 0;
    }
    if(i == n/2){
      sort(out.begin(),out.end() );
      cout << out.size() << endl;
      for(int j=0;j<out.size();++j)
	cout << out[j].x+1 << " " << out[j].y << endl;
      return 0;
    }
  }

  return 0;
}

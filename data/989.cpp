#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200036
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n;
char S[MAXN];
const int base = 137 , ivb = 131276920;
const int P = 418254373;

int Pow( int x , int a ) {
	int ret = 1;
	while( a ) {
		if( a & 1 ) ret = ret * 1ll * x % P;
		x = x * 1ll * x % P , a >>= 1;
	}
	return ret;
}

char W[MAXN << 1];
int len[MAXN];
void manacher( ) {
	rep( i , 1 , n ) W[i << 1] = S[i] , W[i << 1 | 1] = '#';
	int N = n << 1 | 1;
	W[0] = '(' , W[1] = '#' , W[N + 1] = ')';
	int mx = 0 , ps = 0;
	rep( i , 1 , N ) {
		len[i] = i > mx ? 1 : min( len[( ps << 1 ) - i] , mx - i );
		while( W[i - len[i]] == W[i + len[i]] ) ++ len[i];
		if( i + len[i] > mx ) mx = i + len[i] , ps = i;
	}
}

int w[MAXN];
int has[MAXN];
int bs[MAXN] , ib[MAXN];
int hs[MAXN] , rhs[MAXN] , pr[MAXN];

bool equa( int l , int r , int L , int R ) {
	return ( hs[r] - hs[l - 1] + P ) * 1ll * ib[l - 1] % P == ( rhs[L] - rhs[R + 1] + P ) * 1ll * ib[n - R] % P;
}

void solve() {
	scanf("%s",S + 1);
	n = strlen( S + 1 );
	manacher();
	rep( i , 1 , n ) w[i] = len[i << 1] / 2 - 1;
	bs[0] = ib[0] = 1;
	rep( i , 1 , n ) bs[i] = bs[i - 1] * 1ll * base % P , ib[i] = ib[i - 1] * 1ll * ivb % P;
	int cur = 1;
	rep( i , 1 , n ) hs[i] = ( hs[i - 1] + S[i] * 1ll * bs[i] ) % P;
	per( i , n , 1 ) rhs[i] = ( rhs[i + 1] + S[i] * 1ll * bs[n - i + 1] ) % P;
	per( i , n , 1 ) {
		int l = n - i + 1;
		while( cur <= n && ( cur < l || !equa( i , n , cur - l + 1 , cur ) ) ) ++ cur;
		pr[n - i + 1] = cur;
	}
	int as = 0;
	int p1 , l1 , p2 , l2 , p3;
	rep( i , 1 , n ) {
		int fr = i - w[i] , tr = i + w[i];
		int s = ( upper_bound( pr + 1 , pr + 1 + n , fr - 1 ) - pr - 1 );
		s = max( tr + 1 , n - s + 1 );
		if( ( n - s + 1 ) * 2 + w[i] * 2 + 1 > as ) {
			as = ( n - s + 1 ) * 2 + w[i] * 2 + 1;
			p2 = i - w[i] , l2 = w[i] * 2 + 1;
			if( s == n + 1 ) {
				p1 = p3 = 0;
			} else {
				l1 = n - s + 1;
				p1 = pr[n - s + 1] - l1 + 1 , p3 = s;
			}
		}
	}
	if( !p1 ) {
		puts("1");
		cout << p2 << ' ' << l2 << endl;
	} else {
		puts("3");
		cout << p1 << ' ' << l1 << endl << p2 << ' ' << l2 << endl << p3 << ' ' << l1 << endl;
	}
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}

 	 		 		  		 		 			 	   	 	
#include <bits/stdc++.h>
#define ud unsigned int
#define ll long long
#define ull unsigned long long
#define MAX_INF 0x3f
#define MAX_INF_VAL 0x3f3f3f3f
#define MAX_INF_VAL_LL 0x3f3f3f3f3f3f3f3f
#define pi 3.141592653589
#define eps 1e-8
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
//#define p 2173412051LL
//#define sz 2

template< typename T > void read( T &x ) {
	x = 0;
	char ch = getchar();
	ll f = 1;
	while( !isdigit( ch ) ) {
		if( ch == '-' )
		f *= -1;
		ch = getchar();
	}
	while( isdigit( ch ) ) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x *= f;
}

using namespace std;

const int N = 200010;

char s[ N ], t[ N ];
int d[ N ], fail[ N ];
int v[ N ], fst[ N ];

void manacher( char*, int* );
void make_fail( char*, int* );

int main() {
	int n, m;
	int l, x, mid, xx;
	int ans = 0;
	scanf( "%s", s );
	m = n = strlen( s );
	reverse( s, s + n );
	s[ n++ ] = '#';
	for( int i = 0; i < m; ++i )
		s[ n++ ] = s[ m - 1 - i ];
	manacher( s, d );
	make_fail( s, fail );
	for( int i = m + 1; s[ i ]; ++i ) {
		if( fail[ i ] > v[ i - 1 ] ) {
			v[ i ] = fail[ i ];
			fst[ i ] = i - fail[ i ] + 1;
		} else {
			v[ i ] = v[ i - 1 ];
			fst[ i ] = fst[ i - 1 ];
		}
	}
	for( int i = m + 1; i < n; ++i ) {
		int lft = n - i - d[ i ], fk = min( v[ i - d[ i ] ], lft );
		int tmp = 2 * d[ i ] - 1 + fk * 2;
		if( tmp > ans ) {
			ans = tmp;
			mid = i - d[ i ] + 1 - m;
			xx = 2 * d[ i ] - 1;
			if( fk ) {
				l = fst[ i - 1 ] - m;
				x = fk;
			} else {
				l = -1;
			}
		}
	}
	if( l != -1 ) {
		printf( "3\n" );
		printf( "%d %d\n", l, x );
		printf( "%d %d\n", mid, xx );
		printf( "%d %d\n", m - x + 1, x );
	} else {
		printf( "1\n" );
		printf( "%d %d\n", mid, xx );
	}
	return 0;
}

void manacher( char* s, int* d ) {
	for( int i = 0, l = 0, r = 0; s[ i ]; ++i ) {
		d[ i ] = 1;
		if( i < r )
			d[ i ] = min( d[ l + r - i ], r - i + 1 );
		while( i - d[ i ] >= 0 && s[ i - d[ i ] ] == s[ i + d[ i ] ] )
			++d[ i ];
		if( i + d[ i ] - 1 > r ) {
			r = i + d[ i ] - 1;
			l = i - d[ i ] + 1;
		}
	}
}

void make_fail( char* s, int* fail ) {
	for( int i = 1, j = 0; s[ i ]; ++i ) {
		while( j && s[ i ] != s[ j ] )
			j = fail[ j - 1 ];
		if( s[ i ] == s[ j ] )
			++j;
		fail[ i ] = j;
	}
}
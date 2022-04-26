#include <list>
#include <set>
#include <map>
#include <ctime>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <deque>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iterator>
#include <cassert>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <complex>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
 
#define For(i,n) for( int i=0; i < n; i++)
#define FOR(i,a,b) for( __typeof(b) i=(a); i<=(b); i++)
#define ALL(c)  c.begin() , c.end()
#define LL long long
#define int64 LL
#define Set(t,v) memset((t), (v), sizeof(t))

typedef vector < int > VI;
typedef pair< int , int > PII;
typedef pair < LL , LL > PLL;
#define fr first
#define se second
#define pi M_PI
#define rad(x) (x)*acos(-1)/180.0
#define EPS 1e-6
#define INF 10000*10000
stringstream ss;
#define two(x) ( 1LL<<x )
#define sq(x) ( (x)*(x) )
LL mod = 1000000007LL;

/**************************Code****************************/

int ind[100010], n;
PII mx[100010];
LL hash[100010][20], Hash[100010][20];
LL P[100010];
vector < PII > a;

int *buildFail( string p )
{
	int m = p.size();
	int *fail = new int [m+1];
	int j = fail[0] = -1;
	for( int i = 1 ; i <= m ; i ++ )
	{
		while( j >= 0 && p[j] != p[i-1] )
			j = fail[j];
		fail[i] = ++j;
	}
	return fail;
}
int match( string t , string p , int *fail )
{
	int n = t.size(), m = p.size();
	int count = 0;
	for( int i = 0, k = 0 ; i < n ; i ++ )
	{
		while( k >= 0 && p[k] != t[i] )
			k = fail[k];
		k ++;
		ind[i] = k;
		if( k >= m )
		{
			++count; // match at t [i-m+1. i] 
			k = fail[k];
		}
	}
	return count;
}
int query( int l , int r )
{
	if( l < 0 || r >= n )
		return 0;
	for( int i = 20 ; i >= 0 ; i -- )
		if( two(i) <= (r-l+1) )
		{
			if( hash[l][i] != Hash[r][i] )
				return 0;
			l += two(i), r -= two(i);
		}
	return 1;
}
int cmp( PII a , PII b )
{
	if( a.se == b.se )
		return a.fr < b.fr;
	return a.se < b.se;
}

int main()
{
	P[0] = 1;
	for( int i = 1 ; i < 100010 ; i ++ )
		P[i] = P[i-1] * 127LL;
	string s, t;
	cin >> s;
	t = s;
	s = "$" + s;
	n = s.size();
	reverse( t.begin() , t.end() );
	if( match( s , t , buildFail( t ) ) )
	{
		cout << 1 << endl << 1 << " " << t.size() - !( t.size() % 2 ) << endl;
		return 0;
	}
	for( int i = 1 ; i < n ; i ++ )
		if( ind[i] )
	{
		a.push_back( PII( i-ind[i]+1 , i ) );
	}
	sort( a.begin() , a.end() , cmp );
	int st = 0;
	PII now = mx[0] = PII( 0 , -1 );
	for( int i = 1 ; i < n ; i ++ )
	{
		while( st < a.size() && a[st].se <= i )
		{
			if( now.se - now.fr + 1 < a[st].se - a[st].fr + 1 )
				now = a[st];
			st ++;
		}
		mx[i] = now;
	}
	for( int i = 1 ; i < n ; i ++ )
		hash[i][0] = Hash[i][0] = s[i];
	for( int j = 1 ; two(j) <= n ; j ++ )
		for( int i = 1 ; i < n ; i ++ )
		{
			if( i+two(j) < n )
				hash[i][j] = hash[i][j-1] + hash[i+two(j-1)][j-1] * P[ two(j-1) ];
			if( i-two(j) >= 0 )
				Hash[i][j] = Hash[i][j-1] + Hash[i-two(j-1)][j-1] * P[ two(j-1) ];
		}
	int l1 = -1, l2, l3, r1, r2, r3;
	int mx_len = 0;
	for( int i = 2 ; i < n ; i ++ )
	{
		int l = 0, r = n;
		while( l+1 < r )
		{
			int mid = ( l + r ) / 2;
			if( query( i-mid , i+mid ) )
				l = mid;
			else
				r = mid;
		}
		now = PII( i-l , i+l );
		PII left = mx[ i-l-1 ];
		PII right = PII( n-( left.se - left.fr + 1 ) , n-1 );
		while( left.se > right.fr )
		{
			left.se --;
			right.fr ++;
		}
		while( now.fr <= left.se )
			now.fr ++, now.se --;
		while( now.se >= right.fr )
			now.fr ++, now.se --;
		if( mx_len < left.se - left.fr + 1 + now.se - now.fr + 1 + right.se - right.fr + 1 )
		{
			mx_len = left.se - left.fr + 1 + now.se - now.fr + 1 + right.se - right.fr + 1;
			l1 = left.fr, r1 = left.se - left.fr + 1;
			l2 = now.fr, r2 = now.se - now.fr + 1;
			l3 = right.fr, r3 = right.se - right.fr + 1;
		}
	}
	if( r1 == 0 )
	{
		cout << 1 << endl;
		cout << l2 << " " << r2 << endl;
	}
	else
	{
		cout << 3 << endl;
		cout << l1 << " " << r1 << endl;
		cout << l2 << " " << r2 << endl;
		cout << l3 << " " << r3 << endl;
	}
	return 0;
}

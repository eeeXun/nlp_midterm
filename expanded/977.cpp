
template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
max_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);

template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 24 "data/977.cpp" 2

# 24 "data/977.cpp"
using namespace std;
# 33 "data/977.cpp"
typedef vector < int > VI;
typedef pair< int , int > PII;
typedef pair < long long , long long > PLL;






stringstream ss;


long long mod = 1000000007LL;



int ind[100010], n;
PII mx[100010];
long long hash[100010][20], Hash[100010][20];
long long P[100010];
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
   ++count;
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
  if( ( 1LL<<i ) <= (r-l+1) )
  {
   if( hash[l][i] != Hash[r][i] )
    return 0;
   l += ( 1LL<<i ), r -= ( 1LL<<i );
  }
 return 1;
}
int cmp( PII a , PII b )
{
 if( a.second == b.second )
  return a.first < b.first;
 return a.second < b.second;
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
  while( st < a.size() && a[st].second <= i )
  {
   if( now.second - now.first + 1 < a[st].second - a[st].first + 1 )
    now = a[st];
   st ++;
  }
  mx[i] = now;
 }
 for( int i = 1 ; i < n ; i ++ )
  hash[i][0] = Hash[i][0] = s[i];
 for( int j = 1 ; ( 1LL<<j ) <= n ; j ++ )
  for( int i = 1 ; i < n ; i ++ )
  {
   if( i+( 1LL<<j ) < n )
    hash[i][j] = hash[i][j-1] + hash[i+( 1LL<<j-1 )][j-1] * P[ ( 1LL<<j-1 ) ];
   if( i-( 1LL<<j ) >= 0 )
    Hash[i][j] = Hash[i][j-1] + Hash[i-( 1LL<<j-1 )][j-1] * P[ ( 1LL<<j-1 ) ];
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
  PII right = PII( n-( left.second - left.first + 1 ) , n-1 );
  while( left.second > right.first )
  {
   left.second --;
   right.first ++;
  }
  while( now.first <= left.second )
   now.first ++, now.second --;
  while( now.second >= right.first )
   now.first ++, now.second --;
  if( mx_len < left.second - left.first + 1 + now.second - now.first + 1 + right.second - right.first + 1 )
  {
   mx_len = left.second - left.first + 1 + now.second - now.first + 1 + right.second - right.first + 1;
   l1 = left.first, r1 = left.second - left.first + 1;
   l2 = now.first, r2 = now.second - now.first + 1;
   l3 = right.first, r3 = right.second - right.first + 1;
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

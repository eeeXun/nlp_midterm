# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 9 "data/772.cpp" 2








# 16 "data/772.cpp"
using namespace std;

int N, M, Max, Mid;
int L[ 3 ], R[ 3 ];
int f[ 20 ][ 502012 * 2 + 100 ];
int fail[ 502012 ], match[ 502012 ], first[ 502012 ], lg[ 502012 * 2 ];
int P[ 30 ];
char s[ 502012 ], c[ 502012 * 2 + 100 ];

inline void Manacher()
{
 int MaxR = 0, id;
 for ( int i = 1; i <= M; ++i )
 {
  if ( i == 10000 )
  int bp = 1;
  f[ 0 ][ i ] = 1;
  if ( MaxR > i ) f[ 0 ][ i ] = min( f[ 0 ][ id * 2 - i ], MaxR - i );
  while ( i - f[ 0 ][ i ] > 0&& i + f[ 0 ][ i ] <= M && c[ i - f[ 0 ][ i ] ] == c[ i + f[ 0 ][ i ] ])
  ++f[ 0 ][ i ];
  if ( i + f[ 0 ][ i ] - 1 > MaxR ) MaxR = i + f[ 0 ][ i ] - 1, id = i;
 }
}

int main(){


 gets( s + 1 ); N = strlen( s + 1 );

 for ( int i = 1; i <= N; ++i ) c[ i * 2 ] = s[ i ];

 M = 2 * N + 1;

 Manacher();

 for ( int i = 1; i <= M; ++i )
 {
  --f[ 0 ][ i ];
  if ( i & 1 ) f[0][i] = 0;
 }

 int size = 1, lgsize = 0;
 while ( size <= M )
 {
  lg[ size ] = lgsize;
  P[ lgsize ] = size;
  size <<= 1; ++lgsize;
 }

 for ( int i = 1; i <= M; ++i )
 if ( Max < f[ 0 ][ i ] )
 {
  Max = f[ 0 ][ i ];
  L[ 1 ] = R[ 1 ] = L[ 2 ] = R[ 2 ] = 0;
  if ( i & 1 )
  {
   L[ 0 ] = (i>>1) - (f[0][i]>>1)+1;
   R[ 0 ] = (i>>1) + (f[0][i]>>1);
  }
  else
  {
   L[ 0 ] = (i>>1) - (f[0][i]>>1);
   R[ 0] = (i>>1) + (f[0][i]>>1);
  }
 }

 for ( int i = 3; i <= M; ++i )
 if ( !lg[ i ] ) lg[ i ] = lg[ i - 1 ];

 for ( int i = 1, p = 2; p <= M; p <<= 1, ++i )
 for ( int j = 1; j <= M - p + 1; ++j )
 f[ i ][ j ] = max( f[ i - 1 ][ j ], f[ i - 1 ][ j + (p>>1) ] );


 for ( int i = 1; i <= N; ++i ) c[ i ] = s[ N - i + 1 ];

 int j = 0;
 for ( int i = 2; i <= N; ++i )
 {
  while ( j&& c[ j + 1 ] != c[ i ] ) j = fail[ j ];
  if ( c[ j + 1 ] == c[ i ] ) fail[ i ] = ++j;
  else fail [ i ] = j;
 }

 j = 0;
 for ( int i = 1; i <= N; ++i )
 {
  while ( j&& c[ j + 1 ] != s[ i ] ) j = fail[ j ];
  if ( c[ j + 1 ] == s[ i ] ) match[ i ] = ++j;
  else match[ i ] = j;

  if ( !first[ match[ i ] ] ) first[ match[ i ] ] = i;
 }

 for ( int i = N; i > N/2; --i )
 {
  if ( first[ N - i + 1 ] >= i-1|| !first[ N - i + 1 ] ) break;
  int bg = first[ N - i + 1 ] + 1, ed = i - 1, ans = 0;
  int l = 0, r = (ed - bg + 1)>>1, mid = -1;
  while( l <= r&&(mid != l||mid != r) )
  {
   mid = (l + r)>>1;
   int BG = bg + mid, ED = ed - mid, len;
   BG <<= 1, ED <<= 1, len = ED - BG + 1;
   if ( BG > ED ) { r = mid; continue; }
   int L = max( f[ lg[ len ] ][ BG ], f[ lg[ len ] ][ ED - P[ lg[ len ] ] + 1 ] );
   if ( ((L-1)>>1) < mid ) r = mid;
   else l = mid + 1, ans = mid;
   }
  if ( Max < ((N - i + 1)<<1) + ans * 2 + 1 )
  {
   Max = ((N - i + 1)<<1) + ans * 2 + 1 ;
   R[ 0 ] = first[ N - i + 1 ] ; L[ 0 ] = R[ 0 ] - (N - i);
   L[ 2 ] = i; R[ 2 ] = N;
   Mid = ans * 2 + 1;
  }
 }


 if ( Mid & 1 )
 {
  for ( int i = R[ 0 ] + (Mid>>1) + 1; i <= L[ 2 ] - (Mid>>1) - 1; ++i )
  if ( f[ 0 ][ i * 2 ] >= Mid )
  {
   L[ 1 ] = i - (Mid>>1); R[ 1 ] = i + (Mid>>1);
   break;
  }
 }
 else
 {
  for ( int i = R[ 0 ] + (Mid>>1) + 1; i <= L[ 2 ] - (Mid>>1) - 1; ++i )
  {
   if ( f[ 0 ][ i * 2 - 1 ] == Mid )
   {
    L[ 1 ] = i - (Mid>>1);
    R[ 1 ] = i + (Mid>>1) - 1;
    break;
   }
   if ( f[ 0 ][ i * 2 + 1 ] == Mid )
   {
    L[ 1 ] = i - (Mid>>1) + 1;
    R[ 1 ] = i + (Mid>>1);
    break;
   }
  }
 }


 if( !L[ 2 ] )
 {
  printf( "1\n%d %d\n", L[ 0 ], R[ 0 ] - L[ 0 ] + 1 );
 }
 else if ( L[ 2 ]&&L[ 3 ] )
 {
  printf( "3\n");
  printf( "%d %d\n%d %d\n%d %d\n", L[0], R[0]-L[0]+1, L[1], R[1]-L[1]+1, L[2], R[2]-L[2]+1 );
 }
 else
 {
  printf("2\n");
  printf( "%d %d\n%d %d\n",L[0],R[0]-L[0]+1,L[2],R[2]-L[2]+1);
 }


 return 0;
}

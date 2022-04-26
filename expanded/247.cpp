# 5 "data/247.cpp" 2

# 5 "data/247.cpp"
using namespace std;

const int N = 1e5+100;
char str1[N];
int len1;

char str2[2*N];
int len2;
void initStr2() {
 int j = 0;
 for( int i = len1-1; i >= 0; --i ) {
  str2[j++] = str1[i];
 }
 str2[j++] = '$';
 for( int i = 0; i < len1; ++i ) {
  str2[j++] = str1[i];
 }
 str2[j] = 0;
 len2 = j;
}

int next[2*N];
void initNext() {
 next[0] = -1;
 for( int i = 1; i < len2; ++i ) {
  int j = next[i-1];
  while( j != -1 && str2[j+1] != str2[i] ) {
   j = next[j];
  }
  if( str2[j+1] == str2[i] ) {
   next[i] = j+1;
  } else {
   next[i] = -1;
  }
 }
}

int match[N];
int matchId[N];
void initMatch() {
 int add = len1+1;
 for( int i = 0; i < len1; ++i ) {
  match[i] = next[i+add]+1;
 }

 int i = 0, j = len1-1;
 while( i < j ) {
  swap( match[i], match[j] );
  i += 1;
  j -= 1;
 }
 matchId[len1-1] = len1-1;
 for( int i = len1-2; i >= 0; --i ) {
  if( match[i] < match[matchId[i+1]] ) {
   matchId[i] = matchId[i+1];
  } else {
   matchId[i] = i;
  }
 }
}

char str3[N*2];
int len3;
void initStr3() {
 int j = 0;
 str3[j++] = '*';
 str3[j++] = '$';
 for( int i = 0; i < len1; ++i ) {
  str3[j++] = str1[i];
  str3[j++] = '$';
 }
 str3[j++] = '#';
 str3[j] = 0;
 len3 = j;
}

int Len[2*N];
void manachar() {
 int p, p0;
 Len[0] = 1;
 p = p0 = 0;
 for( int i = 1; i < len3; ++i ) {
  if( i <= p ) {
   Len[i] = min( Len[2*p0-i], p-i+1 );
  } else {
   Len[i] = 1;
  }
  while( str3[i+Len[i]] == str3[i-Len[i]] ) {
   Len[i] += 1;
  }
  if( i+Len[i]-1 > p ) {
   p = i+Len[i]-1;
   p = min( p, len3-1 );
   p0 = i;
  }
 }
}

bool flag;
int ans[10];
int maxs;
void findAns() {
 maxs = -1;
 for( int i = 2; i < len3; i += 2 ) {
  int l = ( i - Len[i] + 1 ) / 2;
  int r = ( i + Len[i] - 1 ) / 2 - 1;
  if( l > r ) {
   continue;
  }
  if( l == 0 || r == len1-1 ) {
   if( maxs <= Len[i]-1 ) {
    maxs = Len[i] - 1;
    flag = 0;
    ans[1] = l;
    ans[2] = r;
   }
  } else {
   int L = min( l, match[matchId[r+1]] );
   if( maxs <= L*2+Len[i]-1 ) {
    if( L == 0 ) {
     maxs = Len[i]-1;
     flag = 0;
     ans[1] = l;
     ans[2] = r;
    } else {
     int a = 0, b = L-1, c = l, d = r, f = matchId[r+1] + match[matchId[r+1]] - 1;
     int e = f - L + 1;
     if( b < c && d < e ) {
      maxs = Len[i]-1 + 2 * L;
      flag = 1;
      ans[1] = a;
      ans[2] = b;
      ans[3] = l, ans[4] = r;
      ans[5] = e;
      ans[6] = f;
     }
    }
   }
  }
 }
}

void showAns() {
 if( flag ) {
  puts( "3" );
  int a = len1;
  printf( "%d %d\n", a-ans[6], ans[6]-ans[5]+1 );
  printf( "%d %d\n", a-ans[4], ans[4]-ans[3]+1 );
  printf( "%d %d\n", a-ans[2], ans[2]-ans[1]+1 );

 } else {
  puts( "1" );
  int a = len1;
  printf( "%d %d\n", a-ans[2], ans[2]-ans[1]+1 );
 }
}

int main() {
 scanf( "%s", str1 );
 len1 = strlen( str1 );
 initStr2();
 initNext();
 initMatch();
 reverse( str1, str1+len1 );
 initStr3();
 manachar();
 findAns();
 showAns();
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100005;

char s[maxn] , rs[maxn];
int next[maxn] , f[maxn] , len[maxn] , ml[maxn] , n;

void init() {
    scanf( "%s" , s );
    n = strlen(s);
    for ( int i = 0; i < n; i++ ) rs[i] = s[n-i-1];
}

void getnext() {
    memset( next , 0 , sizeof(next) );
    int i , j;
    next[0] = j = -1;
    i = 0;
    while( i < n ) {
        if( j == -1 || rs[i] == rs[j] ) {
            ++i;
            ++j;
            next[i] = j;
        } else j = next[j];
    }
}

void prepare() {
    int i = 0 , j = 0;
    while ( i < n ) {
        if ( j == -1 || s[i] == rs[j] ) {;
            ++i;
            ++j;
            f[i-1] = j;
        } else j = next[j];
    }
    for ( int i = 0; i < n; i++ ) {
        if ( i == 0 ) ml[i] = i;
        else {
            if ( f[ml[i-1]] > f[i] ) ml[i] = ml[i-1];
            else ml[i] = i;
        }
    }
}

void getpalin() {
    len[0] = 1;
    int m = 0 , mid = 0;
    for ( int i = 1; i < n; i++ ) {
        len[i] = 1;
        if ( m >= i ) {
            len[i] = min( len[2*mid-i] , m-i+1 );
        }
        while ( i - len[i] >= 0 && i + len[i] < n && s[i+len[i]] == s[i-len[i]] ) {
            len[i]++;
        }
        if ( i + len[i] - 1 > m ) {
            m = i + len[i] - 1;
            mid = i;
        }
    }
}

void work() {
    getnext();
    prepare();
    getpalin();
    int ans = 1 , l = -1 , m = 0;
    for ( int i = 0; i < n; i++ ) {
        int t = i-len[i] >= 0 ? ml[i-len[i]] : n+1;
        if ( len[i] * 2 - 1 + min( f[t] , n - i - len[i] ) * 2 > ans ) {
            ans = len[i] * 2 - 1 + min( f[t] , n - i - len[i] ) * 2;
            if ( n - i - len[i] > 0 && f[t] > 0 ) l = t;
            else l = -1;
            m = i;
        }
    }
    if ( l == -1 ) printf( "1\n%d %d\n" , m-len[m]+2 , ans );
    else {
        printf( "3\n" );
        printf( "%d %d\n" , l-(ans-len[m]*2+1)/2+2 , (ans-len[m]*2+1)/2 );
        printf( "%d %d\n" , m-len[m]+2 , len[m]*2-1 );
        printf( "%d %d\n" , n-(ans-len[m]*2+1)/2+1 , (ans-len[m]*2+1)/2 );
    }
}

int main() {
    init();
    work();
    return 0;
}

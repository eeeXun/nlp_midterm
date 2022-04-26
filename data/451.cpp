#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

const int MAXS = 100005;

char str[MAXS];
char patt[MAXS];

int len;
int radius[MAXS];
int pi[MAXS];
int firstMatch[MAXS];

ll hash[MAXS];
ll revHash[MAXS];
ll powers[MAXS];

void KMP()
{
    pi[0] = -1;
    for ( int curr = 1, pred = -1; curr < len; curr++, pred = pi[curr-1] )
    {
        while ( pred != -1 and patt[curr] != patt[pred+1] ) pred = pi[pred];
        if ( patt[curr] == patt[pred+1] ) pred++;
        pi[curr] = pred;
    }

    for ( int i = 0; i < len; i++ ) firstMatch[i] = len; //No match
    firstMatch[0] = -1;

    for ( int curr = 0, pred = -1; curr < len; curr++ )
    {
        while ( pred != -1 and str[curr] != patt[pred+1] ) pred = pi[pred];
        if ( str[curr] == patt[pred+1] ) pred++;
        firstMatch[pred+1] = min( firstMatch[pred+1], curr );
    }
}

void findPalindromes()
{
    const int BASE = 29;
    hash[0] = str[0] - 'a' + 1;
    revHash[0] = patt[0] - 'a' + 1;
    powers[0] = 1;
    for ( int i = 1; i < len; i++ )
    {
        powers[i] = BASE * powers[i-1];
        hash[i] = hash[i-1] + powers[i] * ( str[i] - 'a' + 1 );
        revHash[i] = revHash[i-1] + powers[i] * ( patt[i] - 'a' + 1 );
    }
    for ( int i = 0; i < len; i++ )
    {
        int ri = len-i-1;
        radius[i] = 0;
        int r = 1;
        int R = min(i, len-i-1);
        while ( R >= r )
        {
            int mid  = (r+R)/2;
            ll h1 = hash[i+mid] - hash[i];
            ll h2 = revHash[ri+mid] - revHash[ri];
            if ( i > ri ) h2 *= powers[i-ri];
            else h1 *= powers[ri-i];
            if ( h1 == h2 )
            {
                radius[i] = mid;
                r = mid+1;
            }
            else
                R = mid-1;
        }
    }
}

int main()
{
    scanf( "%s", str );
    len = strlen(str);
    strcpy( patt, str );
    reverse( patt, patt+len );

    findPalindromes();
    KMP();
    int left = -1, right = len, center = -1, best = -1;

    for ( int i = 0; i < len; i++ )
    {
        int L = i-radius[i]; //left bound of the circle
        int hi = len-1 - i - radius[i];
        int lo = 1;
        int ans = 0;
        while ( hi >= lo )
        {
            int mid = (hi+lo)/2;
            if ( firstMatch[mid] < L )
            {
                ans = mid;
                lo = mid+1;
            }
            else hi = mid-1;
        }
        int curr = 2 * radius[i] + 1 + 2 * ans;
        if ( curr > best )
        {
            best = curr;
            center = i;
            right = len-ans; //First position right
            left = firstMatch[ans];
        }
    }

    if ( right == len )
        printf( "1\n%d %d\n", center-radius[center]+1, 2*radius[center]+1 );
    else
    {
        int sz = len-right;
        printf( "3\n%d %d\n%d %d\n%d %d\n", left-sz+2, sz, center-radius[center]+1, 2*radius[center]+1, right+1, sz );
    }

//for ( int i = 0; i < len; i++ ) printf( "%d %d\n", i, firstMatch[i] );

    return 0;
}
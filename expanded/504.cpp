# 2 "data/504.cpp"
using namespace std;
const long long mod = 1e9 + 7;
string s , t;
int m , pp = 1069 , hsh [400005] , rhsh [400005] , minv [400005] , rminv [400005] , pi [400005] , mx , a [400005] , b [400005];
vector < pair < int , int > > ans;
long long pw ( long long x , long long y )
{
    if ( y == 0 ) return 1;
    long long ans = pw ( x , y / 2 );
    ans = ( ans * ans ) % mod;
    if ( y % 2 ) ans = ( ans * x ) % mod;
    return ans;
}
bool ck ( int i , int x )
{
    int hshi = ( ( ( hsh [ i + x ] - hsh [i] + mod ) % mod ) * minv [ i + 1 ] ) % mod;
    int hshj = ( ( ( rhsh [ i - x ] - rhsh [i] + mod ) % mod ) * rminv [ i - 1 ] ) % mod;
    if ( hshi == hshj ) return 1;
    return 0;
}
int main()
{


    cin >> s;
    for ( int i = s . size () - 1 ; i >= 0 ; i -- )
    {
        if ( t . size () + 1 == ( s . size () + 1 ) / 2 ) break;
        t . push_back ( s [i] );
    }
    m = t . size () + 1;
    t += '#' + s;
    for ( int i = 1 ; i < t . size () ; i ++ )
    {
        int j = pi [ i - 1 ];
        while ( j && t [i] != t [j] ) j = pi [ j - 1 ];
        if ( t [i] == t [j] ) pi [i] = j + 1;
        else pi [i] = j;
    }
    long long ppp = 1;
    for ( int i = 0 ; i < s . size () ; i ++ )
    {
        hsh [i] = ( hsh [ i - 1 ] + ( s [i] - 'a' + 1 ) * ppp ) % mod;
        minv [i] = pw ( ppp , mod - 2 );
        ppp = ( ppp * pp ) % mod;
    }
    ppp = 1;
    for ( int i = s . size () - 1 ; i >= 0 ; i -- )
    {
        rhsh [i] = ( rhsh [ i + 1 ] + ( s [i] - 'a' + 1 ) * ppp ) % mod;
        rminv [i] = pw ( ppp , mod - 2 );
        ppp = ( ppp * pp ) % mod;
    }
    int mx = -1 , id = 0;
    multiset < pair < int , int > > ms;
    ms . insert ( { 0 , -1 } );
    for ( int i = 0 ; i < s . size () ; i ++ )
    {
        int l = 0 , r = s . size () , mid;
        while ( l < r )
        {
            mid = ( l + r ) / 2;
            if ( i + mid > s . size () - 1 || i - mid < 0 )
            {
                r = mid;
                continue;
            }
            if ( ck ( i , mid ) ) l = mid + 1;
            else r = mid;
        }
        l --;
        int mxx = min ( a [ i - l - 1 ] , ( int ) ( s . size () - i - l - 1 ) );
        if ( 2 * l + 1 + 2 * mxx > mx )
        {
            mx = 2 * l + 1 + 2 * mxx;
            int y = b [ i - l - 1 ];
            ans . clear ();
            if ( mxx )
            {
                ans . push_back ( { y - mxx + 2 , mxx } );
                ans . push_back ( { s . size () - mxx + 1 , mxx } );
            }
            ans . push_back ( { i - l + 1 , 2 * l + 1 } );
        }
        ms . insert ( { pi [ i + m ] , i } );
        if ( a [ i - 1 ] < ( * -- ms . end () ) . first ) b [i] = i;
        else b [i] = b [ i - 1 ];
        a [i] = max ( a [ i - 1 ] , ( * -- ms . end () ) . first );
    }
    sort ( ans . begin () , ans . end () );
    cout << ans . size () << endl;
    for ( int i = 0 ; i < ans . size () ; i ++ ) cout << ans [i] . first << ' ' << ans [i] . second << endl;
}

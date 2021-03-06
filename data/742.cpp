// ==========================================================================
//
//                    Bis-millah ir-Rahman ir-Rahim
//
// ==========================================================================
//
//                    S.M.SHAHEEN SHA
//
//                    Dept. of Computer Science and Engineering
//                    Jahangirnagar University , Bangladesh
//
//                    Email : shaheen.cse20@gmail.com
//                    ID    : shaheen_bd
// ==========================================================================

#include <bits/stdc++.h>

using namespace std;

#define LL                          long long
#define ULL                         unsigned long long

#define SS(s)                       scanf("%s",s)

#define I(X )                       scanf("%d",     &(X))
#define II(X, Y)                    scanf("%d%d",   &(X), &(Y))
#define III(X, Y, Z)                scanf("%d%d%d", &(X), &(Y), &(Z))

#define IL(X)                       scanf("%lld", &X)
#define IIL(X,Y )                   scanf("%lld%lld", &X,&Y)
#define IIIL(X,Y,Z)                 scanf("%lld%lld%lld", &X,&Y,&Z)

#define ID(x)                       scanf("%lf",&x)
#define IID(x,y)                    scanf("%lf%lf",&x,&y)
#define IIID(x,y,z)                 scanf("%lf%lf%lf",&x,&y,&z)

#define DI(X)                       int X;        I(X);
#define DII(X, Y)                   int X, Y;     II(X,Y)
#define DIII(X, Y, Z)               int X, Y, Z;  III(X,Y,Z);

#define DIL(X)                      LL X;         IL(X)
#define DIIL(X,Y)                   LL X,Y;       IIL(X,Y)
#define DIIIL(X,Y,Z)                LL X,Y,Z;     IIIL(X,Y,Z)

#define DDI(x)                      double x;     ID(x);
#define DDII(x,y)                   double x,y;   IID(x,y);
#define DDDII(x,y,z)                double x,y,z; IIID(x,y,z);
// output
#define PI(x)                       printf("%d\n",      x)
#define PII(x,y)                    printf("%d %d\n",   x,y)
#define PIII(x,y,z)                 printf("%d %d %d\n",x,y,z)

#define PIL(x)                      printf("%lld\n",          x)
#define PIIL(x,y)                   printf("%lld %lld\n",     x,y)
#define PIIIL(x,y,z)                printf("%lld %lld %lld\n",x,y,z)
// LOOP
#define rep(i,a,b)                  for(int i=a;i<=b;i++)
#define rev(i,a,b)                  for(int i=a;i>=b;i--)
#define repv(i,a)                   for(int i=0;i<(int)a.size();i++)
#define revv(i,a)                   for(int i=((int)a.size())-1;i>=0;i--)
#define FS(x)                       for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define PR(x)                       for(typeof (x.begin()) it = x.begin(); it != x.end (); it++) {  cout << *it << " "; } cout << endl;
#define PV(a)                       for(int i=0;i<(int)a.size();i++) printf("%d%c",a[i],(i+1==(int)a.size() ? '\n': ' '));
// array initialization
#define MEM(a,val)                  memset(a,val,sizeof(a));
#define SET(a)                      memset(a,-1,sizeof a)
#define CLR(a)                      memset(a,0,sizeof a)
// min-max
#define Max(a,b)                    (a>b?a:b)
#define Min(a,b)                    (a<b?a:b)
#define _Max(a,b,c)                 Max(a,Max(b,c))
#define _Min(a,b,c)                 Min(a,Min(b,c))
#define SQR(n)                      ((n)*(n))
#define all(a)                      a.begin(),a.end()
#define PB                          push_back
#define RPB(a,x,y)                  a[x].PB(y),a[y].PB(x)
#define MP                          make_pair
#define NL                          puts("");
#define pline                       cout << "_________________________" << endl;
// Pair
#define X                           first
#define Y                           second
#define XX                          first.first
#define XY                          first.second
#define YX                          second.first
#define YY                          second.second
// binary search
//#define LB(a,x)                     (lower_bound(all(a),x)-a.begin()) // Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
//#define UB(a,x)                     (upper_bound(all(a),x)-a.begin()) // Returns an iterator pointing to the first element in the range [first,last) which compares greater than val.
//#define MAXV(a)                     (*max_element(all(a)))
//#define MINV(a)                     (*min_element(all(a)))
//#define FastMax(x,y)                ((((y-x)>>(32-1))&(x^y))^y)
//#define FastMin(x,y)                ((((y-x)>>(32-1))&(x^y))^x)
//template<typename T> T  In()   {  char ch; T n = 0; bool ng = false; while (1) { ch = getchar(); if (ch == '-') { ng = true; ch = getchar(); break;} if (ch>='0' && ch<='9') break; }    while (1) { n = n*10 + (ch - '0'); ch = getchar(); if (ch<'0' || ch>'9')   break;    }  return (ng?-n:n);  }
//#define SI(X)           X=In<int>()
//#define SII(X,Y)        X=In<int>(),Y=In<int>()
//#define SIII(X,Y,Z)     X=In<int>(),Y=In<int>(),Z=In<int>()
//#define SL(X)           X=In<LL>()
//#define SLL(X,Y)        X=In<LL>(),Y=In<LL>()
//#define SLLL(X,Y,Z)     X=In<LL>(),Y=In<LL>(),Z=In<LL>()
// segment_tree
//#define Rot             int idx,int s,int e
//#define SEG             int mid=(s+e)>>1,l=(idx<<1),r=(l|1)
//#define Lch             l,s,mid
//#define Rch             r,mid+1,e
//#define Isr             s==x && e==y
//#define Isl             s==e

#define T(a)            cerr << #a << ": " << a << endl;
#define TT(a,b)         cerr << #a << ": " << a << " | " << #b << ": " << b << endl;
#define TTT(a,b,c)      cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << endl;
#define TTTT(a,b,c,d)   cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

#define PC              printf("Case %d: ",cas)
#define SES             return 0

#define isin(l,r,x)     ( l<=x && x<=r )
#define isin2(r,c,x,y)  ( isin(1,r,x) && isin(1,c,y) )
// Bitwise-operation
#define countbit(x)     __builtin_popcount(x)
template< class T, class X > inline bool checkbit(T a, X pos) { T t=1;return ((a&(t<<pos))>0);  }
template< class T, class X > inline T      setbit(T a, X pos) { T t=1;return (a|(t<<pos));      }
template< class T, class X > inline T    resetbit(T a, X pos) { T t=1;return (a&(~(t<<pos)));   }
template< class T, class X > inline T   togglebit(T a, X pos) { T t=1;return (a^(t<<pos));      }
#define  ctone(a)   ( ( (~a)==0 )?32: __builtin_ctz( ~a ) ) // trailing one

#define  debug      0
#define  AA         if(debug)
#define  wait       getchar()
#define  eps        (1e-7)
#define  pi         (2.0*acos(0.0)) //#define PI acos(-1.0)
// IO
#define  READ       freopen("C:\\Users\\BackBencher\\Desktop\\input.txt","r",stdin)
#define  WRITE      freopen("C:\\Users\\BackBencher\\Desktop\\output.txt","w",stdout)
#define  _cin       ios_base::sync_with_stdio(0); cin.tie(0);
// mathematics
//template<typename T> T POW(T base,T power)              { T ret=1; while(power)  { if(power & 1) ret=(ret*base); base=(base*base);  power>>=1; }return ret; }
//template<typename T> inline T GCD(T a,T b)              { if(a<0)return GCD(-a,b);  if(b<0)return GCD(a,-b);    return (b==0)?a:GCD(b,a%b);}
//template<typename T> T LCM(T a,T b)                     { if(a<0)return LCM(-a,b);if(b<0)return LCM(a,-b);return a*(b/GCD(a,b));}
//template<typename T> T EUCLIDE(T a,T b,T &x,T &y)       { if(a<0){T d=euclide(-a,b,x,y);x=-x;return d;}   if(b<0){T d=euclide(a,-b,x,y);y=-y;return d;}   if(b==0){x=1;y=0;return a;}else{T d=euclide(b,a%b,x,y);T t=x;x=y;y=t-(a/b)*y;return d;}}
//template<typename T> T ABS(T a)                         { if(a<0)return -a;else return a;}
////LL Bigmod(LL base,LL power,LL _MOD)                     { LL ret=1;while(power){if(power & 1)ret=(ret*base)%_MOD;base=(base*base)%_MOD;power>>=1;}return ret;}
////LL ModInverse(LL number,LL _MOD)                        { return Bigmod(number,_MOD-2LL,_MOD); }
//template <typename T> T BigMod (T b,T p,T m){if (p == 0) return 1;if (p%2 == 0){T s = BigMod(b,p/2,m);return ((s%m)*(s%m))%m;}return ((b%m)*(BigMod(b,p-1,m)%m))%m;}
//template <typename T> T ModInv (T b,T m){return BigMod(b,m-2,m);}
//// geometry
//template<typename T> double DIS(T x1,T y1,T x2, T y2)   { return sqrt( (double)( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ) );}
//template<typename T> T ANGLE(T x1,T y1,T x2, T y2)      { return atan( double(y1-y2) / double(x1-x2));}
//template<typename T> LL isLeft(T a,T b,T c)             { return (c.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.y-a.y); }
//// debug
//void BINARY(int n){  bitset<31>a=n;  cout << a << endl;}
//void P_ARR(int *ar,int a,int b) { if(a>b) swap(a,b); if(a<=b) cout << ar[a];  for(int i=a+1; i<=b; i++) cout << " "<<ar[i];    cout << endl; }
//template<class T> inline void make_unique_vec( vector<T> &vec ){ sort( vec.begin(), vec.end() ); vec.erase( unique( vec.begin(), vec.end() ), vec.end() ); }
//#define  FF      fflush(stdout) // use after printf (for interactive problem)
//#define  FFF     cout << flush  // use after cout (for interactive problem)
// Degree and Radian
//const double PI = 2 * acos(0);
//double DEG(double x) { return (180.0*x)/(PI*1.0);  }
//double RAD(double x) { return (x*(PI*1.0))/(180.0);}
//template<class T> inline void make_unique_arr( T *ar,int &n)   { sort(ar + 1, ar + n + 1); n = unique(ar + 1, ar + n + 1) - ar - 1; }
// for (map<int, int>::iterator it = mp.begin() , int cnt=0; it != mp.end(); it++) {  mp[it->first] = cnt++; }
// int month[]={31,28,31,30,31,30,31,31,30,31,30,31};                                    // month
// ========================================================================================================
// dir[][0] = x value, dir[][1] = y value
// int dir[5][2] = { {0,0},{1,0},{0,1},{-1,0},{0,-1} };                                  // 4 Direction
// int dir[9][2] = { {0,0},{1,0},{0,1},{-1,0},{0,-1},{-1,1},{-1,-1},{1,-1},{1,1}};       // 8 direction
// int dir[9][2] = { {0,0},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };    // Knight Direction
// int dir[8][2] = { {0,0},{2,0},{1,1},{-1,1} ,{-2,0} , {-1,-1} ,{1,-1} };               // Hexagonal Direction
// ========================================================================================================
#define  VI     vector<int>
#define  pii    pair<int,int>
//              0123456789
#define Base1   10000019ULL
#define Base2   10000079ULL
#define Base3   10000103ULL
#define MOD1    1000000007ULL
#define MOD2    1000000009ULL
#define MOD3    1000000021ULL
///             01234567890123456789
#define  MOD    1000000007LL
#define  inf    2000000007
#define  INF    (1LL<<61)
///             01234567890123456789
#define  MX     300007
#define  maxn   MX


int ar[MX];

char ss[MX];


struct Manacher {
    char text[MX*2];
    int     p[MX*2];
    int lcp,lcp_cen;
    int tot;
    vector< pair<int,int> > pal;

    void init() {
        pal.clear();
        lcp=0;
        tot=0;
        memset(p,0,sizeof p);
    }

    void generate(char *s) {
        init();
        int len = 0 , i=0 ;
        text[len++] = '^';
        while(s[i]) text[len++]=  '#' , text[ len++ ] = s[i++] ;
        text[len++]=  '#';
        text[len++]=  '$';
        int c = 0; // center
        int r = 0; // right edge
        for(i=1; i<len-1; i++) {
            int j = (c<<1)-i; // mirror of i
            p[i] = (r>i)?min(r-i,p[j]):0;
            while(text[i+1+p[i]]==text[i-1-p[i]]) p[i]++;
            if(i+p[i]>r) c=i,r=i+p[i];
        }
        for(i=1; i<len-1; i++) {
//            bool flag = 0;
//            rep(j,i-p[i],i+p[i]) if( isalpha( text[j] ) ){  cout << text[j] , flag = 1; }
//            if(flag) cout << endl;
            if(p[i]>lcp) {
                lcp     = p[i];
                lcp_cen = i;
            }



//            if(p[i]>0)
//            {
//                int s = (i-1-p[i])/2;
//                pal.push_back( make_pair( s,s+p[i] ) );
//            }
        }

        for(int i=2;i<len-1;i+=2){
//            cout << text[i];
            ar[i/2] = p[i];
        }
//           cout << "<<<" << endl;
    }

    void BUG(char *s) {
        for(int i=0; i<pal.size(); i++) {
            for(int j=pal[i].X; j<pal[i].Y; j++) {
                cout << s[j];
            }
            cout << endl;
        }
    }

}man;

char ms[MX];

int n;

int mil[MX];

void z_function(int *z,char *s) {
    int len = strlen(s);
    rep(i,0,len) z[i] = 0;
    for (int i = 1, l = 0, r = 0; i < len; ++i) {
        if (i <= r)  z[i] = min (r - i + 1, z[i - l]);
        while ( i + z[i] < len && s[z[i]] == s[i + z[i]] )   ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    z[0] = len;
    int id = 1;
    rep(i,n+1,len-1) {
        mil[id++] = z[i];
    }
}

int  zz[MX];

struct Seg_Point_update_range_Max {

    int tree[2*MX];
    int n;

    void init(int *ar) {
        rev(i,n,1)   tree[i-1+n] = ar[i];
        rev(i,n-1,1) tree[i]     = Max(tree[(i<<1)],tree[(i<<1)|1]);
    }

    void update(int idx,int val) {
        idx--;
        for(tree[idx+=n]=val; idx>1; idx>>=1) {
            tree[idx>>1] = Max(tree[idx],tree[idx^1]);
        }
    }


    int query(int x,int y) {
        int ret = 0;
        x--;
        for(x+=n,y+=n; x<y; x>>=1,y>>=1) {
            if(x&1) ret=Max(ret,tree[x]),x++;
            if(y&1) --y,ret=Max(ret,tree[y]);
        }
        return ret;
    }

} smax;


int main() {
    SS(ss);
    man.init();
    man.generate(ss);
    n=strlen(ss);
    rep(i,1,n) {
        if(ar[i]==n) {
            cout << 1 << endl;
            cout << 1 << " " << n << endl;
            return 0;
        }
    }

    int id=n-1;
    rep(i,0,n-1) {
        ms[i] = ss[id--];
    }
    ms[n] = '#';

    rep(i,0,n-1) {
        ms[n+1+i] = ss[i];
    }

    ms[n+1+n] = 0;

    z_function(zz,ms);

    smax.n = n;
    smax.init(mil);

    int ret = -1;
    int majpos  = -1;
    int sufflen = -1;
    int majlen  = 0;

    rep(i,2,n-1) {
        int low  = i;
        int high = i+(ar[i]/2);
        if(high==n) high--;
        int pos = -1;
        while( low<=high ) {
            int mid = (low+high)>>1;
            int lt = (i-(mid-i));
            if(lt-1 < 1) {
                high = mid-1;
                continue;
            }
            /// yes
            int v = smax.query(1,lt-1);
            if(v>0) pos = mid, low = mid+1;
            else   high = mid-1;
        }
//        T(pos);
        if(pos==-1) continue; // kono suffix e pai nai
        /// max the suffix length
        int lpos = i-(pos-i);
        low = 1;
        high = Min( n-pos , lpos);
        int mxlen = 0;
//        TTT(low,high,lpos);
        while(low<=high) {
            int mid = (low+high)>>1;
            if(lpos-mid<1) {
                high = mid-1;
                continue;
            }
            int mx = smax.query(1,lpos-mid);
            if(mx>=mid) mxlen = mid , low=mid+1;
            else   high =  mid-1;
        }
//        T(mxlen);
        if(mxlen) {
            int tot = (pos-i)*2+1 + mxlen*2;
//            T(tot);
            if(ret<tot) {
                ret = tot;
                majpos = i-(pos-i);
                majlen = (pos-i)*2+1;
                sufflen = mxlen;
            }
        }
//        wait; wait;
    }
    int flag = 0;
    int mxsuff = 0;
    int spos = -1;
    rep(i,1,n) {
        int e=i+(ar[i]/2);
        if(e==n && ar[i]>=ret) {
            if(mxsuff<ar[i]) {
                mxsuff=ar[i];
                spos = i;
            }
        }
    }

    int midmx = 0;

    rep(i,1,n)
    {
        if(ar[i]>=ret)
        {
            ret = ar[i];
            midmx = i;
        }
    }

    if(midmx)
    {
//        cout << "YEAH" << endl;
        cout << 1 << endl;
        cout << (midmx-(ret/2)) << " " << ret << endl;
        return 0;
    }


    if(spos!=-1) {
        cout << 1 << endl;
        cout << (spos-(n-spos)) << " " << mxsuff << endl;
        return 0;
    }
//    TTT(ret,majpos,sufflen);
//
//
//     T(ret);
    cout << 3 << endl;
    rep(i,1,n) {
        if(mil[i]>=sufflen ) {
            cout << i << " " << sufflen << endl;
            break;
        }
    }
    cout << majpos << " " << majlen << endl;
    cout << (n-sufflen+1) << " " << sufflen << endl;


    return 0;
}

	   				 	 		 		        		    	
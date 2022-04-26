/*****************************************************************
 *                   BISMILLAHIR RAHMANIR RAHIM                  *
 *          Raihat Zaman Neloy                                   *
 *          JU-CSE-21                                            *
 *          raihatneloy                                          *
 *****************************************************************/

#include<algorithm>
#include<cstdio>
#include<sstream>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<set>
#include<queue>
#include<stack>
#include<list>
#include<iostream>
#include<fstream>
#include<numeric>
#include<string>
#include<vector>
#include<cstring>
#include<map>
#include<iterator>
#include<deque>
#include<climits>
#include<complex>

#define S scanf
#define P printf

#define  F(i,a,b) for(int i=a;i<b; i++)
#define FF(i,a,b) for(i=a;i<=b;i++)
#define FI(i,a,b) for((typeof(b)) i=a;i<=b;i++)
#define FR(i, a, b,inc) for(  i = (a); i <= (b); i+=inc )
#define RFR(i, a, b,dec) for(  i = (a); i >= (b); i-=dec )
#define FS(x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define PR(x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++) cout << *it << " "; cout << endl;

#define LL long long int
#define ULL unsigned long long int
#define D double

#define Max(a,b)    (a>b?a:b)
#define Min(a,b)    (a<b?a:b)
#define _Max(a,b,c) Max(a,Max(b,c))
#define _Min(a,b,c) Min(a,Min(b,c))
#define SQR(n)      (n*n)
#define PI          2.0*acos(0.0)

#define all(a) a.begin(),a.end()
#define X  first
#define Y  second
#define MP make_pair

#define PCC        cout<<"Case "<<cas++<<": ";
#define PC         printf("Case %d:",cas++);
#define PCN        printf("Case %d:\n",cas++);
#define NL         printf("\n");
#define cp         printf("here\n");

#define open       freopen("input.txt","r",stdin)
#define close      freopen ("output.txt","w",stdout)
#define Case(a)    printf("Case %d:",a)
#define caseh(a)   printf("Case #%d: ",a)
#define S1(a)      scanf("%d",&a)
#define S2(a,b)    scanf("%d%d",&a,&b)
#define S3(a,b,c)  scanf("%d%d%d",&a,&b,&c)
#define SL1(a)     scanf("%lld",&a)
#define SL2(a,b)   scanf("%lld%lld",&a,&b)
#define SL3(a,b,c) scanf("%lld%lld%lld",&a,&b,&c)
#define CHR        getchar()
#define PB(x)      push_back(x)
#define pb         push_back
#define PP         pop_back()
#define PF(x)      push_front(x)
#define PPF(x)     pop_front()
#define PS(x)      push(x)
#define sz()       size()
#define UB         upper_bound
#define LB         lower_bound
#define mxe(a,n)   (*max_element(a,a+n))
#define mne(a,n)   (*min_element(a,a+n))
#define SUM(a,n)   (accumulate(a,a+n,0))
#define countbit(x) __builtin_popcount(x)
#define DBG(n)      P("Done %d\n",n);

// I/O
#define I(X)                       scanf("%d", &(X))
#define II(X, Y)                   scanf("%d%d", &(X), &(Y))
#define III(X, Y, Z)               scanf("%d%d%d", &(X), &(Y), &(Z))
#define DI(X) int (X);             scanf("%d", &X)
#define DII(X, Y) int X, Y;        scanf("%d%d", &X, &Y)
#define DIII(X, Y, Z) int X, Y, Z; scanf("%d%d%d", &X, &Y, &Z)

#define ILL(X)          scanf("%lld", &(X))
#define DILL(X) LL (X); scanf("%lld", &X)

// LOOP
#define repv(i,a) for(int i=0;i<(int)a.size();i++)
#define revv(i,a) for(int i=((int)a.size())-1;i>=0;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define rev(i,a,b) for(int i=a;i>=b;i--)

#define FS(x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)

#define MEM(a,val) memset(a,val,sizeof(a));
#define SET(a)     memset(a,-1,sizeof a)
#define CLR(a)     memset(a,0,sizeof a)


using namespace std;

template <typename T> T BigMod (T b,T p,T m){if (p == 0) return 1;if (p%2 == 0){T s = BigMod(b,p/2,m);return ((s%m)*(s%m))%m;}return ((b%m)*(BigMod(b,p-1,m)%m))%m;}
template <typename T> T ModInv (T b,T m){return BigMod(b,m-2,m);}
template <typename T> T in(){char ch;T n = 0;bool ng = false;while (1){ch = getchar();if (ch == '-'){ng = true;ch = getchar();break;}if (ch>='0' && ch<='9')     break;}while (1){n = n*10 + (ch - '0');ch = getchar();if (ch<'0' || ch>'9')   break;}return (ng?-n:n);}
template <typename T> T POW(T B,T P){ if(P==0) return 1; if(P&1) return B*POW(B,P-1);  else return SQR(POW(B,P/2));}
template <typename T> T Bigmod(T b,T p,T m){ if(p==0) return 1; else if (!(p&1)) return SQR(Bigmod(b,p/2,m)) % m;else return ((b % m) * Bigmod(b,p-1,m)) % m;}
template <typename T> T Dis(T x1,T y1,T x2, T y2){return sqrt( SQR(x1-x2) + SQR(y1-y2) );}
template <typename T> T Angle(T x1,T y1,T x2, T y2){ return atan( double(y1-y2) / double(x1-x2));}
template <typename T> T DIFF(T a,T b) { T d = a-b;if(d<0)return -d;else return d;}
template <typename T> T ABS(T a) {if(a<0)return -a;else return a;}
template <typename T> T gcd(T a,T b){if(a<0)return gcd(-a,b);if(b<0)return gcd(a,-b);return (b==0)?a:gcd(b,a%b);}
template <typename T> T lcm(T a,T b) {if(a<0)return lcm(-a,b);if(b<0)return lcm(a,-b);return a*(b/gcd(a,b));}
template <typename T> T euclide(T a,T b,T &x,T &y) {if(a<0){T d=euclide(-a,b,x,y);x=-x;return d;}   if(b<0){T d=euclide(a,-b,x,y);y=-y;return d;}   if(b==0){x=1;y=0;return a;}else{T d=euclide(b,a%b,x,y);T t=x;x=y;y=t-(a/b)*y;return d;}}
template <typename T> void ia (T a[],int n){for (int i=0; i<n; i++) cin >> a[i];}
template <typename T> void pa (T a[],int n){for (int i=0; i<n-1; i++) cout << a[i] << " ";cout << a[n-1] << endl;}
template <typename T> LL isLeft(T a,T b,T c) { return (a.x-b.x)*(b.y-c.y)-(b.x-c.x)*(a.y-b.y); }

int    Set(int N,int pos){ return N=N | (1<<pos);}
int  Reset(int N,int pos){return N= N & ~(1<<pos);}
bool Check(int N,int pos){return (bool)(N & (1<<pos));}
template< class T, class X > inline T   togglebit(T a, X i) { T t=1;return (a^(t<<i)); }

int toInt(string s)  { int sm; stringstream ss(s); ss>>sm; return sm; }
int toLlint(string s) { long long int sm; stringstream ss(s); ss>>sm; return sm;}
int cdigittoint(char ch){return ch-'0';}
bool isVowel(char ch){ ch=toupper(ch); if(ch=='A'||ch=='U'||ch=='I'||ch=='O'||ch=='E') return true; return false;}
bool isConst(char ch){if (isalpha(ch) && !isVowel(ch)) return true; return false;}

double DEG(double x) { return (180.0*x)/(PI);}
double RAD(double x) { return (x*(double)PI)/(180.0);}

#define VI  vector< int >
#define VII vector< VI >
#define VLL vector< LL >
#define PII pair< int , int >
#define PLL pair< LL , LL >
#define VPI vector< PII >

///         0123456789
#define MX  100007
#define MOD 1000000007
#define INF (1<<30)-1+(1<<30)
#define eps 1e-9

#define base ((1<<l)-1)
#define lft (idx<<1)
#define rgt (lft|1)
#define mid ((l+r)>>1)

/// Hashing Bases & MOD
///           0123456789
#define Base1 10000019ULL
#define Base2 10000079ULL
#define Base3 10000103ULL
#define MOD1  1000000007ULL
#define MOD2  1000000009ULL
#define MOD3  1000000021ULL
#define LOGX  17
#define PUL   pair< ULL, ULL >

int Tree[4*MX],Lazy[4*MX];
int a[MX];
char s[MX];
int rId[MX];
ULL B1[MX],B2[MX];

struct Hash{
    PUL H[MX];
    int digit[MX];
    int L;
    
    Hash(){
        L = 0;
        H[0] = MP(0,0);
    }
    
    void Insert(char x){
        digit[++L] = x-'a'+1;

        H[L].X = H[L-1].X * Base1 + digit[L];
        H[L].Y = H[L-1].Y * Base2 + digit[L];
    }

    pair<ULL,ULL> SubStr(int l,int r){
        int len = r-l+1;

        pair<ULL,ULL> ans;

        ans.X = H[r].X - H[l-1].X * B1[len];
        ans.Y = H[r].Y - H[l-1].Y * B2[len];

        return ans;
    }
};

void Init(){
    B1[0] = B2[0] = 1;
    
    for (int i=1;i<MX;i++){
        B1[i] = B1[i-1] * Base1;
        B2[i] = B2[i-1] * Base2;
    }
}

void Propagate(int idx,int v){
    Tree[idx] = v;
    Lazy[idx] = v;
}

void Build(int idx,int l,int r){
    if (l == r) {
        Tree[idx] = l;
        return;
    }
    
    Build(lft,l,mid);
    Build(rgt,mid+1,r);
    
    if (a[Tree[lft]] >= a[Tree[rgt]])     Tree[idx] = Tree[lft];
    else                                  Tree[idx] = Tree[rgt];
}

void Update(int idx,int l,int r,int s,int e,int v){
    if (l == s && r == e){
        Propagate(idx,v);
        return;
    }
    
    if (Lazy[idx]){
        Propagate(lft,Lazy[idx]);
        Propagate(rgt,Lazy[idx]);
        Lazy[idx] = 0;
    }
    
    if (e <= mid)       Update(lft,l,mid,s,e,v);
    else if (s > mid)   Update(rgt,mid+1,r,s,e,v);
    else                Update(lft,l,mid,s,mid,v), Update(rgt,mid+1,r,mid+1,e,v);
}

void Traverse(int idx,int l,int r){
    if (l == r){
        if (Tree[idx])      a[l] = l - Tree[idx] + 1;
        return;
    }
    
    if (Lazy[idx]){
        Propagate(lft,Lazy[idx]);
        Propagate(rgt,Lazy[idx]);
        Lazy[idx] = 0;
    }
    
    Traverse(lft,l,mid);
    Traverse(rgt,mid+1,r);
}

int Query(int idx,int l,int r,int s,int e){
    if (s > e)          return 0;
    if (l == s && r == e)return Tree[idx];
    
    if (e <= mid)       return Query(lft,l,mid,s,e);
    else if (s > mid)   return Query(rgt,mid+1,r,s,e);
    else{
        int q1 = Query(lft,l,mid,s,mid);
        int q2 = Query(rgt,mid+1,r,mid+1,e);
        
        if (a[q1] >= a[q2])     return q1;
        else                    return q2;
    }
}

Hash h1,h2;

int lcp(int id1,int id2,int L){
    int l = 1,h = L;

    while (l <= h){
        int md = (l+h)>>1;

        if (h1.SubStr(id1,id1+md-1) == h2.SubStr(id2,id2+md-1))     l = md+1;
        else                                                        h = md-1;
    }

    return h;
}

int main(){
    Init();
    
    S("%s",s+1);
    int l = strlen(s+1);
    
    for (int i=1;i<=l;i++)  h1.Insert( s[i] );
    for (int i=l;i;i--)     h2.Insert( s[i] ), rId[i] = l-i+1;
    
    for (int i=l;i;i--){
        int minLen = l-i+1;
        int len = lcp(i,1,minLen);
        
        if (len)    Update(1,1,l,i,i+len-1,i);
    }
    
    Traverse(1,1,l);
    Build(1,1,l);
    
    int mx = 0;
    VPI ans;
    
    for (int i=1;i<=l;i++){
        int id1 = i,id2 = rId[i];
        int minLen = min( l-id1+1,l-id2+1 );
        int pal = lcp( id1,id2,minLen );
        int sufLen = l - (i+pal-1);
        
        int st = 1, ed = i-pal;
        int pos = Query(1,1,l,st,ed);
        sufLen = min( sufLen , a[pos] );
        int len = 2*sufLen + 2*pal - 1;
        
        if (len > mx){
            mx = len;
            ans.clear();
            
            if (sufLen)     ans.PB( MP(pos-sufLen+1,sufLen) );
            
            ans.PB( MP( i-pal+1,2*pal - 1 ) );
            
            if (sufLen)     ans.PB( MP(l-sufLen+1,sufLen) );
        }
    }
    
    cout << ans.size() << endl;
    
    for (int i=0;i<(int)ans.size();i++)  cout << ans[i].X << " " << ans[i].Y << endl;
return 0;
}

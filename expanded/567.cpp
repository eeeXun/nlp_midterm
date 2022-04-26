      return std::signbit(__x) ? __type(3.1415926535897932384626433832795029L)
                        : __type();



    }

  template<typename _Tp>
    constexpr inline typename __gnu_cxx::__promote<_Tp>::__type
    imag(_Tp)
    { return _Tp(); }

  template<typename _Tp>
    inline typename __gnu_cxx::__promote<_Tp>::__type
    norm(_Tp __x)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return __type(__x) * __type(__x);
    }

  template<typename _Tp>
    constexpr inline typename __gnu_cxx::__promote<_Tp>::__type
    real(_Tp __x)
    { return __x; }

  template<typename _Tp, typename _Up>
    inline std::complex<typename __gnu_cxx::__promote_2<_Tp, _Up>::__type>
    pow(const std::complex<_Tp>& __x, const _Up& __y)
    {
      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
      return std::pow(std::complex<__type>(__x), __type(__y));
    }

  template<typename _Tp, typename _Up>
    inline std::complex<typename __gnu_cxx::__promote_2<_Tp, _Up>::__type>
    pow(const _Tp& __x, const std::complex<_Up>& __y)
    {
      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
      return std::pow(__type(__x), std::complex<__type>(__y));
    }

  template<typename _Tp, typename _Up>
    inline std::complex<typename __gnu_cxx::__promote_2<_Tp, _Up>::__type>
    pow(const std::complex<_Tp>& __x, const std::complex<_Up>& __y)
    {
      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
      return std::pow(std::complex<__type>(__x),
        std::complex<__type>(__y));
    }



  template<typename _Tp>
    std::complex<_Tp> proj(const std::complex<_Tp>&);


  template<typename _Tp>
    inline std::complex<_Tp>
    __complex_proj(const std::complex<_Tp>& __z)
    { return __z; }


  inline complex<float>
  __complex_proj(const complex<float>& __z)
  { return __builtin_cprojf(__z.__rep()); }

  inline complex<double>
  __complex_proj(const complex<double>& __z)
  { return __builtin_cproj(__z.__rep()); }

  inline complex<long double>
  __complex_proj(const complex<long double>& __z)
  { return __builtin_cprojl(__z.__rep()); }
# 1958 "/usr/include/c++/11.2.0/complex" 3
  template<typename _Tp>
    inline std::complex<_Tp>
    proj(const std::complex<_Tp>& __z)
    { return __complex_proj(__z); }


  template<typename _Tp>
    inline std::complex<typename __gnu_cxx::__promote<_Tp>::__type>
    proj(_Tp __x)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return std::proj(std::complex<__type>(__x));
    }

  template<typename _Tp>
    inline
 std::complex<typename __gnu_cxx::__promote<_Tp>::__type>
    conj(_Tp __x)
    {
      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
      return std::complex<__type>(__x, -__type());
    }



inline namespace literals {
inline namespace complex_literals {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"


  constexpr std::complex<float>
  operator""if(long double __num)
  { return std::complex<float>{0.0F, static_cast<float>(__num)}; }

  constexpr std::complex<float>
  operator""if(unsigned long long __num)
  { return std::complex<float>{0.0F, static_cast<float>(__num)}; }

  constexpr std::complex<double>
  operator""i(long double __num)
  { return std::complex<double>{0.0, static_cast<double>(__num)}; }

  constexpr std::complex<double>
  operator""i(unsigned long long __num)
  { return std::complex<double>{0.0, static_cast<double>(__num)}; }

  constexpr std::complex<long double>
  operator""il(long double __num)
  { return std::complex<long double>{0.0L, __num}; }

  constexpr std::complex<long double>
  operator""il(unsigned long long __num)
  { return std::complex<long double>{0.0L, static_cast<long double>(__num)}; }

#pragma GCC diagnostic pop
}
}




}
# 29 "data/567.cpp" 2
# 113 "data/567.cpp"

# 113 "data/567.cpp"
using namespace std;

template <typename T> T BigMod (T b,T p,T m){if (p == 0) return 1;if (p%2 == 0){T s = BigMod(b,p/2,m);return ((s%m)*(s%m))%m;}return ((b%m)*(BigMod(b,p-1,m)%m))%m;}
template <typename T> T ModInv (T b,T m){return BigMod(b,m-2,m);}
template <typename T> T in(){char ch;T n = 0;bool ng = false;while (1){ch = getchar();if (ch == '-'){ng = true;ch = getchar();break;}if (ch>='0' && ch<='9') break;}while (1){n = n*10 + (ch - '0');ch = getchar();if (ch<'0' || ch>'9') break;}return (ng?-n:n);}
template <typename T> T POW(T B,T printf){ if(printf==0) return 1; if(printf&1) return B*POW(B,printf-1); else return (POW(B,printf/2)*POW(B,printf/2));}
template <typename T> T Bigmod(T b,T p,T m){ if(p==0) return 1; else if (!(p&1)) return (Bigmod(b,p/2,m)*Bigmod(b,p/2,m)) % m;else return ((b % m) * Bigmod(b,p-1,m)) % m;}
template <typename T> T Dis(T x1,T y1,T x2, T y2){return sqrt( (x1-x2*x1-x2) + (y1-y2*y1-y2) );}
template <typename T> T Angle(T x1,T y1,T x2, T y2){ return atan( double(y1-y2) / double(x1-x2));}
template <typename T> T DIFF(T a,T b) { T d = a-b;if(d<0)return -d;else return d;}
template <typename T> T ABS(T a) {if(a<0)return -a;else return a;}
template <typename T> T gcd(T a,T b){if(a<0)return gcd(-a,b);if(b<0)return gcd(a,-b);return (b==0)?a:gcd(b,a%b);}
template <typename T> T lcm(T a,T b) {if(a<0)return lcm(-a,b);if(b<0)return lcm(a,-b);return a*(b/gcd(a,b));}
template <typename T> T euclide(T a,T b,T &x,T &y) {if(a<0){T d=euclide(-a,b,x,y);x=-x;return d;} if(b<0){T d=euclide(a,-b,x,y);y=-y;return d;} if(b==0){x=1;y=0;return a;}else{T d=euclide(b,a%b,x,y);T t=x;x=y;y=t-(a/b)*y;return d;}}
template <typename T> void ia (T a[],int n){for (int i=0; i<n; i++) cin >> a[i];}
template <typename T> void pa (T a[],int n){for (int i=0; i<n-1; i++) cout << a[i] << " ";cout << a[n-1] << endl;}
template <typename T> long long int isLeft(T a,T b,T c) { return (a.x-b.x)*(b.y-c.y)-(b.x-c.x)*(a.y-b.y); }

int Set(int N,int pos){ return N=N | (1<<pos);}
int Reset(int N,int pos){return N= N & ~(1<<pos);}
bool Check(int N,int pos){return (bool)(N & (1<<pos));}
template< class T, class first > inline T togglebit(T a, first i) { T t=1;return (a^(t<<i)); }

int toInt(string s) { int sm; stringstream ss(s); ss>>sm; return sm; }
int toLlint(string s) { long long int sm; stringstream ss(s); ss>>sm; return sm;}
int cdigittoint(char ch){return ch-'0';}
bool isVowel(char ch){ ch=toupper(ch); if(ch=='A'||ch=='U'||ch=='I'||ch=='O'||ch=='E') return true; return false;}
bool isConst(char ch){if (isalpha(ch) && !isVowel(ch)) return true; return false;}

double DEG(double x) { return (180.0*x)/(2.0*acos(0.0));}
double RAD(double x) { return (x*(double)2.0*acos(0.0))/(180.0);}
# 174 "data/567.cpp"
int Tree[4*100007],Lazy[4*100007];
int a[100007];
char s[100007];
int rId[100007];
unsigned long long int B1[100007],B2[100007];

struct Hash{
    pair< unsigned long long int, unsigned long long int > H[100007];
    int digit[100007];
    int L;

    Hash(){
        L = 0;
        H[0] = make_pair(0,0);
    }

    void Insert(char x){
        digit[++L] = x-'a'+1;

        H[L].first = H[L-1].first * 10000019ULL + digit[L];
        H[L].second = H[L-1].second * 10000079ULL + digit[L];
    }

    pair<unsigned long long int,unsigned long long int> SubStr(int l,int r){
        int len = r-l+1;

        pair<unsigned long long int,unsigned long long int> ans;

        ans.first = H[r].first - H[l-1].first * B1[len];
        ans.second = H[r].second - H[l-1].second * B2[len];

        return ans;
    }
};

void Init(){
    B1[0] = B2[0] = 1;

    for (int i=1;i<100007;i++){
        B1[i] = B1[i-1] * 10000019ULL;
        B2[i] = B2[i-1] * 10000079ULL;
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

    Build((idx<<1),l,((l+r)>>1));
    Build(((idx<<1)|1),((l+r)>>1)+1,r);

    if (a[Tree[(idx<<1)]] >= a[Tree[((idx<<1)|1)]]) Tree[idx] = Tree[(idx<<1)];
    else Tree[idx] = Tree[((idx<<1)|1)];
}

void Update(int idx,int l,int r,int s,int e,int v){
    if (l == s && r == e){
        Propagate(idx,v);
        return;
    }

    if (Lazy[idx]){
        Propagate((idx<<1),Lazy[idx]);
        Propagate(((idx<<1)|1),Lazy[idx]);
        Lazy[idx] = 0;
    }

    if (e <= ((l+r)>>1)) Update((idx<<1),l,((l+r)>>1),s,e,v);
    else if (s > ((l+r)>>1)) Update(((idx<<1)|1),((l+r)>>1)+1,r,s,e,v);
    else Update((idx<<1),l,((l+r)>>1),s,((l+r)>>1),v), Update(((idx<<1)|1),((l+r)>>1)+1,r,((l+r)>>1)+1,e,v);
}

void Traverse(int idx,int l,int r){
    if (l == r){
        if (Tree[idx]) a[l] = l - Tree[idx] + 1;
        return;
    }

    if (Lazy[idx]){
        Propagate((idx<<1),Lazy[idx]);
        Propagate(((idx<<1)|1),Lazy[idx]);
        Lazy[idx] = 0;
    }

    Traverse((idx<<1),l,((l+r)>>1));
    Traverse(((idx<<1)|1),((l+r)>>1)+1,r);
}

int Query(int idx,int l,int r,int s,int e){
    if (s > e) return 0;
    if (l == s && r == e)return Tree[idx];

    if (e <= ((l+r)>>1)) return Query((idx<<1),l,((l+r)>>1),s,e);
    else if (s > ((l+r)>>1)) return Query(((idx<<1)|1),((l+r)>>1)+1,r,s,e);
    else{
        int q1 = Query((idx<<1),l,((l+r)>>1),s,((l+r)>>1));
        int q2 = Query(((idx<<1)|1),((l+r)>>1)+1,r,((l+r)>>1)+1,e);

        if (a[q1] >= a[q2]) return q1;
        else return q2;
    }
}

Hash h1,h2;

int lcp(int id1,int id2,int L){
    int l = 1,h = L;

    while (l <= h){
        int md = (l+h)>>1;

        if (h1.SubStr(id1,id1+md-1) == h2.SubStr(id2,id2+md-1)) l = md+1;
        else h = md-1;
    }

    return h;
}

int main(){
    Init();

    scanf("%s",s+1);
    int l = strlen(s+1);

    for (int i=1;i<=l;i++) h1.Insert( s[i] );
    for (int i=l;i;i--) h2.Insert( s[i] ), rId[i] = l-i+1;

    for (int i=l;i;i--){
        int minLen = l-i+1;
        int len = lcp(i,1,minLen);

        if (len) Update(1,1,l,i,i+len-1,i);
    }

    Traverse(1,1,l);
    Build(1,1,l);

    int mx = 0;
    vector< pair< int , int > > ans;

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

            if (sufLen) ans.push_back(make_pair(pos-sufLen+1,sufLen));

            ans.push_back(make_pair( i-pal+1,2*pal - 1 ));

            if (sufLen) ans.push_back(make_pair(l-sufLen+1,sufLen));
        }
    }

    cout << ans.size() << endl;

    for (int i=0;i<(int)ans.size();i++) cout << ans[i].first << " " << ans[i].second << endl;
return 0;
}

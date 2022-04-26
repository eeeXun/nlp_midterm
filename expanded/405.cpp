extern int strverscmp (const char *__s1, const char *__s2)
     noexcept (true) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strfry (char *__string) noexcept (true) __attribute__ ((__nonnull__ (1)));


extern void *memfrob (void *__s, size_t __n) noexcept (true) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__read_write__, 1, 2)));







extern "C++" char *basename (char *__filename)
     noexcept (true) __asm ("basename") __attribute__ ((__nonnull__ (1)));
extern "C++" const char *basename (const char *__filename)
     noexcept (true) __asm ("basename") __attribute__ ((__nonnull__ (1)));
# 539 "/usr/include/string.h" 3 4
}
# 24 "data/405.cpp" 2






# 29 "data/405.cpp"
using namespace std;
# 75 "data/405.cpp"
#pragma comment(linker,"/STACK:36777216")
#pragma GCC optimize ("O2")




const int inf=~0U>>1;
const int MOD=1000000007;
const long long linf=(long long)1e18;
const double eps=1e-6,PI=4*atan(1);
typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double DB;
typedef long double ld;
typedef pair<int,int> PII;
typedef pair<int,bool> PIB;
typedef pair<int,pair<int,int> > tri;
typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<string> VS;
typedef vector<ll> VL;
typedef vector<double> VD;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef vector<VII> VVII;
typedef vector<int>::iterator vit;
typedef set<int> SI;
typedef set<string> second;
typedef set<ll> SL;
typedef set<double> SD;
typedef set<PII> SII;
typedef set<int>::iterator sit;
typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef map<ll,int> MLI;
typedef map<double,int> MDI;
typedef map<int,bool> MIB;
typedef map<string,bool> MSB;
typedef map<ll,bool> MLB;
typedef map<double,bool> MDB;
typedef map<int,int>::iterator mit;
typedef map<PII,int> MPIII;
typedef map<PII,bool> MPIIB;
typedef istringstream ISS;
typedef ostringstream OSS;
template<class T> string tostr(const T &x){
 OSS out;out<<x;return out.str();
}
struct debugger{
 template<typename T>
 debugger& operator ,(const T &x){
  cerr<<x<<endl;
  return *this;
 }
}dbg;
template<class T> inline void CLR(priority_queue<T,vector<T>,less<T> > &Q){
 while (!Q.empty())Q.pop();
}
template<class T> inline void CLR(priority_queue<T,vector<T>,greater<T> > &Q){
 while (!Q.empty())Q.pop();
}
template<class T> inline void CLR(T &A){A.clear();}
template<class T> inline void SRT(T &A){sort(A.begin(),A.end());}
template <class T> T Min(const T &a,const T &b){return a<b?a:b;}
template <class T> T Max(const T &a,const T &b){return a>b?a:b;}
inline int max_fast(int x,int y){int m=(x-y)>>31;return y&m|x&~m;}
inline int min_fast(int x,int y){int m=(y-x)>>31;return y&m|x&~m;}
template<class T> inline void checkMin(T &a,const T b){if (b<a)a=b;}
template<class T> inline void checkMax(T &a,const T b){if (b>a)a=b;}
template<class T,class C> inline void checkMin(T &a,const T b,C c){if (c(b,a))a=b;}
template<class T,class C> inline void checkMax(T &a,const T b,C c){if (c(a,b))a=b;}
template<class T> inline T Min(const T &a,const T &b,const T &c){return min(min(a,b),c);}
template<class T> inline T Max(const T &a,const T &b,const T &c){return max(max(a,b),c);}
template<class T> inline T Min(const T &a,const T &b,const T &c,const T &d){return min(min(a,b),min(c,d));}
template<class T> inline T Max(const T &a,const T &b,const T &c,const T &d){return max(max(a,b),max(c,d));}
template<class T> inline T sqr(const T &a){return a*a;}
template<class T> inline T cub(const T &a){return a*a*a;}
inline int Ceil(int x,int y){return (x-1)/y+1;}
inline bool _1(int x,int i){return x&1<<i;}
inline bool _1(ll x,int i){return x&1LL<<i;}
inline ll _1(int i){return 1LL<<i;}
template<class T> inline T low_bit(T x){return x&-x;}
template<class T> inline T high_bit(T x){
 T p=low_bit(x); while (p!=x)x-=p,p=low_bit(x); return p;
}
template<class T> inline T cover_bit(T x){
 T p=1; while (p<x)p<<=1;return p;
}
inline int count_bits(int x){
 x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
 x=(x&0x33333333)+((x&0xcccccccc)>>2);
 x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
 x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
 x=(x&0x0000ffff)+((x&0xffff0000)>>16);
 return x;
}
inline int count_bits(ll x){
 x=(x&0x5555555555555555LL)+((x&0xaaaaaaaaaaaaaaaaLL)>>1);
 x=(x&0x3333333333333333LL)+((x&0xccccccccccccccccLL)>>2);
 x=(x&0x0f0f0f0f0f0f0f0fLL)+((x&0xf0f0f0f0f0f0f0f0LL)>>4);
 x=(x&0x00ff00ff00ff00ffLL)+((x&0xff00ff00ff00ff00LL)>>8);
 x=(x&0x0000ffff0000ffffLL)+((x&0xffff0000ffff0000LL)>>16);
 x=(x&0x00000000ffffffffLL)+((x&0xffffffff00000000LL)>>32);
 return x;
}
int reverse_bits(int x){
 x=((x>>1)&0x55555555)|((x<<1)&0xaaaaaaaa);
 x=((x>>2)&0x33333333)|((x<<2)&0xcccccccc);
 x=((x>>4)&0x0f0f0f0f)|((x<<4)&0xf0f0f0f0);
 x=((x>>8)&0x00ff00ff)|((x<<8)&0xff00ff00);
 x=((x>>16)&0x0000ffff)|((x<<16)&0xffff0000);
 return x;
}
ll reverse_bits(ll x){
 x=((x>>1)&0x5555555555555555LL)|((x<<1)&0xaaaaaaaaaaaaaaaaLL);
 x=((x>>2)&0x3333333333333333LL)|((x<<2)&0xccccccccccccccccLL);
 x=((x>>4)&0x0f0f0f0f0f0f0f0fLL)|((x<<4)&0xf0f0f0f0f0f0f0f0LL);
 x=((x>>8)&0x00ff00ff00ff00ffLL)|((x<<8)&0xff00ff00ff00ff00LL);
 x=((x>>16)&0x0000ffff0000ffffLL)|((x<<16)&0xffff0000ffff0000LL);
 x=((x>>32)&0x00000000ffffffffLL)|((x<<32)&0xffffffff00000000LL);
 return x;
}
inline void INC(int &a,int b){a+=b;if (a>=MOD)a-=MOD;}
inline int SUM(int a,int b){a+=b;if (a>=MOD)a-=MOD;return a;}
inline void DEC(int &a,int b){a-=b;if (a<0)a+=MOD;}
inline int DFF(int a,int b){a-=b;if (a<0)a+=MOD;return a;}
inline void MUL(int &a,int b){a=(ll)a*b%MOD;}
inline int SUM(int a,int b,int c){return SUM(SUM(a,b),c);}
inline int SUM(int a,int b,int c,int d){return SUM(SUM(a,b),SUM(c,d));}
inline int pow(int x,int y){
 int res=1;
 for (;y;y>>=1){
  if (y&1)MUL(res,x);MUL(x,x);
 }
 return res;
}
inline ll mul32(ll x,ll y){
 ll res=0;x%=MOD;y%=MOD;
 while (y){if (y&1)res+=x;x=(x<<1)%MOD;y>>=1;}
 return res;
}
template<class T> inline T gcd(T x,T y){return !y?x:gcd(y,x%y);}
template<class T> inline T lcm(T x,T y){return x*(y/gcd(x,y));}
template<class T> inline T exgcd(T a,T b,T &x,T &y){
 if (!b){x=1;y=0;return a;}
 T res=exgcd(b,a%b,y,x);y-=x*(a/b);
 return res;
}
ll extend_gcd(ll a,ll b,ll &x,ll &y){
 if (!b){x=1;y=0;return a;}
 ll tmp=extend_gcd(b,a%b,y,x);y-=x*(a/b);
 return tmp;
}
template<class T> pair<vector<T>,int> factor(T x){
 pair<vector<T>,int> res;
 for (T i=2;i*i<=x;++i)if (x%i==0){
  int cnt=0;while (x%i==0)x/=i,++cnt;res.push(make_pair(i,cnt));
 }
 if (x>1)res.push(make_pair(x,1));
 return res;
}
template<class T> T eularfunction(T x){
 pair<vector<T>,int> tmp=factor(x);
 for (int i=0;i<tmp.size();++i)x=x/tmp[i].first*(tmp[i].first-1);return x;
}
ll exp(ll x,ll y,ll z){
 ll ans=1;
 while (y){
  if (y&1)ans=ans*x%z;
  x=x*x%z;y>>=1;
 }
 return ans;
}
bool witness(ll x,ll n){
 ll tmp=n-1;
 while (!(tmp&1))tmp>>=1;
 ll x0,x1=exp(x,tmp,n);
 while (tmp!=n-1){
  x0=x1;x1=x0*x0%n;
  if (x1==1&&x0!=1&&x0!=n-1)return 1;
  tmp<<=1;
 }
 if (x1!=1)return 1;
  else return 0;
}
bool Judge(ll x){

 if (x==1)return 0;
 for (int i=0;i<4;++i){
  ll tmp=((rand()<<16)+rand())%(x-1)+1;
  if (witness(tmp,x))return 0;
 }
 return 1;
}
ll inv(ll x,ll p,ll P){return exp(x,p-2,P);}
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x;}
inline int rand32(){return (bool(rand()&1)<<30)|(rand()<<15)+rand();}
inline int random32(int l,int r){return rand32()%(r-l+1)+l;}
inline int random(int l,int r){return rand()%(r-l+1)+l;}
template<int _N,int _M>
struct Edge{
 int link[_M],next[_M],son[_N],l;
 void clear(){l=0;memset(son,0,sizeof(son));}
 void addedge(int x,int y){
  link[++l]=y;next[l]=son[x];son[x]=l;
 }
};
template<int _N,int _M>
struct Edge_c{
 int link[_M*2],next[_M*2],cost[_M*2],son[_N],l;
 void clear(){l=0;memset(son,0,sizeof(son));}
 void addedge(int x,int y,int z){
  link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
 }
};
namespace Matrix{
 const ll P=1000000007LL;size_t size;
 template<size_t Size>
 struct matrix{
  ll key[Size][Size];
  void clear(){
   memset(key,0,sizeof(key));
  }
  void print(int n){
   for (int i=0;i<size;++i)
    for (int j=0;j<size;++j)
     printf("%d%c",(int)key[i][j],j+1==size?'\n':' ');
  }
  int det(){
   if (P==1)return 0;
   for (int i=0;i<size;++i)
    for (int j=0;j<size;++j)key[i][j]%=P;
   int ans=1;
   for (int i=0;i<size;++i){
    for (int j=i+1;j<size;++j)while (key[j][i]){
     int t=key[i][i]/key[j][i];
     for (int k=i;k<size;++k)
      key[i][k]=((ll)key[j][k]*-t+key[i][k])%P;
     for (int k=i;k<size;++k)
      {int tmp=key[i][k];key[i][k]=key[j][k];key[j][k]=tmp;}
     ans=-ans;
    }
    if (key[i][i]==0)return 0;
    ans=(ll)ans*key[i][i]%P;
   }
   return ((ll)ans+P)%P;
  }
 };
 template<size_t Size>
 const matrix<Size>& operator +(const matrix<Size> &a,const matrix<Size> &b){
  static matrix<Size> T;T.clear();
  for (int i=0;i<size;++i)
   for (int j=0;j<size;++j)T.key[i][j]=(a.key[i][j]+b.key[i][j])%P;
  return T;
 }
 template<size_t Size>
 const matrix<Size>& operator *(const matrix<Size> &a,const matrix<Size> &b){
  static matrix<Size> T;T.clear();
  for (int k=0;k<size;++k)
   for (int i=0;i<size;++i)
    for (int j=0;j<size;++j)
     T.key[i][j]+=a.key[i][k]*b.key[k][j];
  for (int i=0;i<size;++i)
   for (int j=0;j<size;++j)T.key[i][j]=T.key[i][j]%P;
  return T;
 }
};
using Matrix::matrix;
struct point{
 static const double eps=1e-10;
 double x,y;
 point(double _x=0,double _y=0):x(_x),y(_y){}
 point operator +(const point &b)const{return point(x+b.x,y+b.y);}
 point operator -(const point &b)const{return point(x-b.x,y-b.y);}
 double operator *(const point &b)const{return x*b.x+y*b.y;}
 double operator ^(const point &b)const{return x*b.y-b.x*y;}
 point operator *(double d)const{return point(x*d,y*d);}
 friend point operator *(double d,const point &x){return point(x.x*d,x.y*d);}
 point operator /(double d)const{return point(x/d,y/d);}
 friend point operator /(double d,const point &x){return point(x.x/d,x.y/d);}
 point operator -()const{return point(-x,-y);}
 bool operator ==(const point &b)const{return fabs(x-b.x)<eps&&fabs(y-b.y)<eps;}
 bool operator !=(const point &b)const{return !(*this==b);}
 double len()const{return sqrt(x*x+y*y);}
};
struct point3D{
 double x,y,z;
 point3D(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
 friend point3D operator +(const point3D &x,const point3D &y){return point3D(x.x+y.x,x.y+y.y,x.z+y.z);}
 friend point3D operator -(const point3D &x,const point3D &y){return point3D(x.x-y.x,x.y-y.y,x.z-y.z);}
 double operator *(const point3D &y)const{return x*y.x+y*y.y+z*y.z;}
 friend point3D operator ^(const point3D &x,const point3D &y){return point3D(x.y*y.z-y.y*x.z,x.z*y.x-y.z*x.x,x.x*y.y-y.x*x.y);}
 double len()const{return sqrt(x*x+y*y+z*z);}
};
struct circle{
 double x,y,r;
 circle(double _x=0,double _y=0,double _r=0):x(_x),y(_y),r(_r){}
};
struct line{
 point x,y;
 line(){}
 line(const point &_x,const point &_y):x(_x),y(_y){}
};
struct plane{
 double A,B,C,angle;
 plane(double _A=0,double _B=0,double _C=0,double _angle=0):A(_A),B(_B),C(_C),angle(_angle){}
 void rev(){A=-A;B=-B;C=-C;}
 inline friend bool operator <(const plane &x,const plane &y){return x.angle+eps<y.angle;}
};
inline int sgn(double x){return fabs(x)<eps?0:(x<0?-1:1);}
inline double dist(const point &x,const point &y){return (x-y).len();}
inline double cross(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
inline double dot(double x1,double y1,double x2,double y2){return x1*x2-y1*y2;}
double (*cha)(double,double,double,double)=cross;
inline double area(const point3D &a,const point3D &b,const point3D &c){return ((b-a)^(c-a)).len();}
inline double volume(const point3D &a,const point3D &b,const point3D &c,const point3D &d){return ((b-a)^(c-a))*(d-a);}
inline point rotate(const point &x,double angle){
 return point(x.x*cos(angle)-x.y*sin(angle),x.y*cos(angle)+x.x*sin(angle));
}
inline int on_segment(const point &p,const line &l){
 if (min(l.x.x,l.y.x)-eps<=p.x&&max(l.x.x,l.y.x)+eps>=p.x&&
 min(l.x.y,l.y.y)-eps<=p.y&&max(l.x.y,l.y.y)+eps>=p.y)return 1;
 else return 0;
}
inline int online(const point &p,const line &l){
 return sgn((p-l.x)*(l.y-l.x))==0
  &&sgn((p.x-l.x.x)*(p.x-l.y.x))<1
  &&sgn((p.y-l.x.y)*(p.y-l.y.y))<1;
}
inline double angle(const point &o,const point &p1,const point &p2){
 double sx=p1.x-o.x,sy=p1.y-o.y,ex=p2.x-o.x,ey=p2.y-o.y;
 double fi,cosfi=sx*ex+sy*ey,norm=(sx*sx+ey*ey)*(ex*ex+ey*ey); cosfi/=sqrt(norm);
 if (cosfi>=1.0)return 0; if (cosfi<=-1.0)return -PI; fi=acos(cosfi);
 if (cha(sx,sy,ex,ey)>0)return fi; else return -fi;
}
inline int direction(const point &p1,const point &p2,const point &p3){return sgn((p3-p1)^(p2-p1));}
inline bool cross(const line &a,const line &b){
 const point &p1=a.x,&p2=a.y,&p3=b.x,&p4=b.y;
 int d1=direction(p3,p4,p1),
  d2=direction(p3,p4,p2),
  d3=direction(p1,p2,p3),
  d4=direction(p1,p2,p4);
 if (d1*d2==-1&&d3*d4==-1)return 1;
 else if (d1==0&&on_segment(p1,b))return 1;
 else if (d2==0&&on_segment(p2,b))return 1;
 else if (d3==0&&on_segment(p3,a))return 1;
 else if (d4==0&&on_segment(p4,a))return 1;
 else return 0;
}
inline pair<point,point> cross_circle(const circle &O,const point &x){
 double d1=dist(point(O.x,O.y),x),d2=sqrt(d1*d1-O.r*O.r),angle=asin(O.r/d1);
 point delta=point(O.x,O.y)-x,x1=x+rotate(delta,-angle)*(d2/d1),x2=x+rotate(delta,angle)*(d2/d1);
 return make_pair(x1,x2);
}
inline double new_angle(double angle){
 angle+=2*
# 432 "data/405.cpp" 3 4
         3.14159265358979323846
# 432 "data/405.cpp"
             ;
 return angle-floor(angle/(2.0*
# 433 "data/405.cpp" 3 4
                              3.14159265358979323846
# 433 "data/405.cpp"
                                  ))*2.0*
# 433 "data/405.cpp" 3 4
                                         3.14159265358979323846
# 433 "data/405.cpp"
                                             ;
}
inline double angle(const circle &O,const point &x){
 double angle=asin(x.y-O.y);
 if (x.x-O.x<0)angle=
# 437 "data/405.cpp" 3 4
                    3.14159265358979323846
# 437 "data/405.cpp"
                        -angle;
 return angle;
}
inline point to_point(const circle &O,double angle){
 return point(O.x+O.r*cos(angle),O.y+O.r*sin(angle));
}
inline point3D cross(const plane &x,const plane &y){
 point3D p;p.x=x.B*y.C-x.C*y.B; p.y=x.C*y.A-x.A*y.C; p.z=x.A*y.B-x.B*y.A;
 if (fabs(p.z)>eps)p.x/=p.z,p.y/=p.z,p.z=1;
 return p;
}
inline bool stayout(const point3D &p,const plane &l){
 return l.A*p.x+l.B*p.y+l.C*p.z<-eps?1:0;
}
inline plane make_line(double x1,double y1,double x2,double y2){
 plane l;double z1=1,z2=1;
 l.A=y1*z2-y2*z1;l.B=z1*x2-z2*x1;l.C=x1*y2-x2*y1;l.angle=atan2(y2-y1,x2-x1);
 if (stayout(point3D(x1+y1-y2,y1+x2-x1,1),l))l.rev();return l;
}
struct polygon{
 vector<point> x;
 typedef vector<point>::iterator vit;
 double area(){
  double res=0;
  for (vit i=x.begin(),next;i!=x.end();++i){
   next=i;++next; if (next==x.end())next=x.begin(); res+=(*i)*(*next);
  }
  return fabs(res/2);
 }
 bool inside(const point &p){
  bool in=0;
  for (vit i=x.begin(),next;i!=x.end();++i){
   next=i;++next; if (next==x.end())next=x.begin();
   if (cross(line(*i,*next),line(p,point(0,1e10))))in^=1;
  }
  return in;
 }
};
template<size_t N,size_t M>
struct graph{


 int link[M],cost[M],next[M],son[N],*cap,*opp,*st,l;
 void add(int x,int y,int z=0){
  link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
 }
 void clear(){l=0;memset(son,-1,sizeof(son));}
 void set(int _n){n=_n;clear();}
 graph():n(0),cap(
# 485 "data/405.cpp" 3 4
                 __null
# 485 "data/405.cpp"
                     ),opp(
# 485 "data/405.cpp" 3 4
                           __null
# 485 "data/405.cpp"
                               ){}
 graph(int _n):n(_n),cap(
# 486 "data/405.cpp" 3 4
                        __null
# 486 "data/405.cpp"
                            ),opp(
# 486 "data/405.cpp" 3 4
                                  __null
# 486 "data/405.cpp"
                                      ){clear();}
 void addedge(int x,int y){add(x,y);}
 void addedge2(int x,int y){add(x,y);add(y,x);}
 void addedge(int x,int y,int z){add(x,y,z);}
 void addedge2(int x,int y,int z){add(x,y,z);add(y,x,z);}
 void addedge_f(int x,int y,int z){
  if (!cap)cap=new int[M],opp=new int[M];
  link[++l]=y;next[l]=son[x];son[x]=l;cap[l]=z;opp[l]=l+1;
  link[++l]=x;next[l]=son[y];son[y]=l;cap[l]=0;opp[l]=l-1;
 }
 void addedge_c(int x,int y,int z,int c){
  if (!cap)cap=new int[M],opp=new int[M];if (!st)st=new int[M];
  link[++l]=y;st[l]=x;next[l]=son[x];son[x]=l;cap[l]=z;cost[l]=c;opp[l]=l+1;
  link[++l]=x;st[l]=y;next[l]=son[y];son[y]=l;cap[l]=0;cost[l]=-c;opp[l]=l-1;
 }
 int *inq,*q,*d,*f,*pre,n,S,T;
 void spfa(int S,int *d){
  int h=0,t=1;inq=new int[n+5];q=new int[n+5];
  for (int i=1;i<=n;++i)d[i]=(1<<29);
  for (int i=1;i<=n;++i)inq[i]=0;
  d[S]=0;q[1]=S;inq[S]=1;
  while (h!=t){
   h=h<n?h+1:1;int i=q[h];inq[i]=0;
   for (int p=son[i];p!=-1;p=next[p]){
    int j=link[p];
    if (d[i]+cost[p]<d[j]){
     d[j]=d[i]+cost[p];
     if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
    }
   }
  }
  delete[] inq;delete[] q;
 }
 struct d_node{
  int d,x;
  d_node(int _d,int _x){d=_d;x=_x;}
  bool operator <(const d_node &y)const{return d>y.d;}
 };
 void dijkstra(int S,int *dis){
  priority_queue<d_node> Q;
  bool *visit=new bool[n+5];
  for (int i=1;i<=n;++i)visit[i]=0,dis[i]=(1<<29);
  Q.push(d_node(0,S));
  while (!Q.empty()){
   int d=Q.top().d,x=Q.top().x;visit[x]=1;dis[x]=d;
   for (int p=son[x];p!=-1;p=next[p])
    Q.push(d_node(d+cost[p],link[p]));
   while (visit[Q.top().x]&&!Q.empty())Q.pop();
  }
  delete[] visit;
 }
 int *dfn,*low,*stack,*instack,*num,top,D,now;
 void tarjan_f(int x){
  dfn[x]=low[x]=++D;stack[++top]=x;instack[x]=1;
  for (int p=son[x];p!=-1;p=next[p]){
   int j=link[p];
   if (!dfn[j]) tarjan_f(j),low[x]=min(low[x],low[j]);
   else if (instack[j]) low[x]=min(low[x],dfn[j]);
  }
  if (low[x]==dfn[x]){
   int k;++now;
   do k=stack[top--],instack[k]=0,num[k]=now; while (k!=x);
  }
 }
 void tarjan(int *_num){
  dfn=new int[n+5];low=new int[n+5];stack=new int[n+5];instack=new int[n+5];
  memset(dfn,0,sizeof(int)*(n+5));D=0;top=0;now=0;num=_num;
  for (int i=1;i<=n;++i)if (!dfn[i])tarjan(i);
  delete[] dfn;delete[] low;delete[] stack;delete[] instack;
 }
 int toposort(int *q){
  int *in;in=new int[n+5];
  int h=0,t=0;
  for (int i=1;i<=n;++i)in[i]=0;
  for (int i=1;i<=n;++i)
   for (int p=son[i];p!=-1;p=next[p])++in[link[p]];
  for (int i=1;i<=n;++i)if (!in[i])q[++t]=i;
  while (h<t){
   int i=q[++h];
   for (int p=son[i];p!=-1;p=next[p]){
    int j=link[p]; --in[j];
    if (!in[j])q[++t]=j;
   }
  }
  delete[] in;return t;
 }
 int find(int x){
  if (f[x]==x)return x;
  else return f[x]=find(f[x]);
 }
 struct k_edge{
  int x,y,z,id;
  bool operator <(const k_edge &y)const{return z<y.z;}
 };
 int kruskal(){
  k_edge *e=new k_edge[l+5];f=new int[n+5];
  int m=0,ans=0,num=0;
  for (int i=1;i<=n;++i)
   for (int p=son[i];p!=-1;p=next[p])
    e[++m].x=i,e[m].y=link[p],e[m].z=cost[p],e[m].id=m;
  std::sort(e+1,e+1+m);
  for (int i=1;i<=n;++i)f[i]=i;
  for (int i=1;i<=m;++i){
   int f1=find(e[i].x),f2=find(e[i].y);
   if (f1!=f2)f[f1]=f2,ans+=e[i].z,++num;
  }
  delete[] e;delete[] f;
  if (num==n-1)return ans;else return (1<<29);
 }
 bool build(){
  int x,y,l=1,r=1;
  memset(d,-1,sizeof(int)*(n+5));
  q[1]=S;d[S]=0;
  while (l<=r){
   x=q[l++];
   for (int i=son[x];i!=-1;i=next[i]){
    y=link[i];
    if (cap[i]&&d[y]==-1){
     d[y]=d[x]+1;q[++r]=y;
     if (y==T)return 1;
    }
   }
  }
  return 0;
 }
 int find(int now,int flow){
  int ret,y,w=0;
  if (now==T)return flow;
  for (int i=son[now];i!=-1&&w<flow;i=next[i]){
   y=link[i];
   if (cap[i]&&d[y]==d[now]+1&&(ret=find(y,min(flow-w,cap[i]))))
    cap[i]-=ret,cap[opp[i]]+=ret,w+=ret;
  }
  if (!w)d[now]=-1;
  return w;
 }
 int dinic(int _S,int _T){
  int ans=0;d=new int[n+5];q=new int[n+5];S=_S;T=_T;
  while (build()) while (1){
   int flow=find(S,(1<<29));
   if (!flow)break;
   ans+=flow;
  }
  delete[] d;delete[] q;
  return ans;
 }
 int spfa_c(int s){
  int h=0,t=1,i,j,p;
  for (int i=0;i<=n;++i)d[i]=(1<<29);
  for (int i=0;i<=n;++i)inq[i]=0;
  d[S]=0;q[1]=S;inq[S]=1;
  while (h!=t){
   h=h<n?h+1:1;i=q[h];inq[i]=0;
   for (p=son[i];p!=-1;p=next[p]){
    j=link[p];
    if (d[i]+cost[p]<d[j]&&cap[p]){
     d[j]=d[i]+cost[p];pre[j]=p;
     if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
    }
   }
  }
  return d[T]<(1<<29)?1:0;
 }
 void update(int &maxflow,int &mincost){
  int p,flow=(1<<29);
  for (p=T;p!=S;p=st[p]){
   p=pre[p];if (cap[p]<flow)flow=cap[p];
  }
  maxflow+=flow;
  for (p=T;p!=S;p=st[p]){
   p=pre[p];mincost+=cost[p]*flow;
   cap[p]-=flow;cap[opp[p]]+=flow;
  }
 }
 pair<int,int> costflow(int _S,int _T){
  int maxflow,mincost;S=_S;T=_T;d=new int[n+5];pre=new int[n+5];
  maxflow=mincost=0;while (spfa(S))update(maxflow,mincost);
  delete[] d;delete[] pre;
  return make_pair(maxflow,mincost);
 }


};
template<int S>
struct BitSet{



 typedef unsigned int uint;
 uint a[((S)<1?0:((S)+31)>>5)];int size;
 void clear(){memset(a,0,sizeof(uint)*size);}
 BitSet():size(((S)<1?0:((S)+31)>>5)){clear();}
 BitSet(uint x):size(((S)<1?0:((S)+31)>>5)){clear();a[0]=x;}
 BitSet(const BitSet<S> &x):size(((S)<1?0:((S)+31)>>5)){*this=x;}
 void set(int x,int y){
  if (y<0||y>1){printf("error!\n");return;}
  int X=x>>5,Y=x&31;
  if (y)a[X]|=1<<Y;else a[X]&=~(1<<Y);
 }
 uint find(uint x){uint X=x>>5,Y=x&31;return (a[X]>>Y)&1u;}
 uint operator [](uint x){return find(x);}
 BitSet& operator =(const BitSet &y){
  memcpy(a,y.a,sizeof(uint)*size);



  return *this;
 }
 BitSet<S> operator |(const BitSet<S> &y){
  BitSet<S> res;
  for (int i=0;i<size;++i)res.a[i]=a[i]|y.a[i];
  return res;
 }
 BitSet<S> operator &(const BitSet<S> &y){
  BitSet<S> res;
  for (int i=0;i<size;++i)res.a[i]=a[i]&y.a[i];
  return res;
 }
 BitSet<S> operator ^(const BitSet<S> &y){
  BitSet<S> res;
  for (int i=0;i<size;++i)res.a[i]=a[i]^y.a[i];
  return res;
 }
 BitSet<S> operator ~(){
  return BitSet<S>(*this).flip();





 }
 BitSet<S>& operator =(const char *s){
  memset(a,0,sizeof(uint)*size);
  for (int i=0;i<S;++i){
   if (s[i]!='0'&&s[i]!='1')break;
   int X=i>>5,Y=i&31;
   if (s[i]=='1')a[X]|=1<<Y;
  }
  return *this;
 }
 BitSet<S>& operator =(const int *s){
  memset(a,0,sizeof(uint)*size);
  for (int i=0;i<S;++i){
   if (s[i]!=0&&s[i]!=1)break;
   int X=i>>5,Y=i&31;
   if (s[i]==1)a[X]|=1<<Y;
  }
  return *this;
 }
 BitSet<S> operator <<(uint x){}
 BitSet<S> operator >>(uint x){}
 BitSet<S>& operator |=(const BitSet<S> &y){
  uint *startA=a;const uint *startB=y.a,*endA=a+size;
  while (startA!=endA)*startA++|=*startB++;

  return *this;
 }
 BitSet<S>& operator &=(const BitSet<S> &y){
  uint *startA=a;const uint *startB=y.a,*endA=a+size;
  while (startA!=endA)*startA++&=*startB++;

  return *this;
 }
 BitSet<S>& operator ^=(const BitSet<S> &y){
  uint *startA=a;const uint *startB=y.a,*endA=a+size;
  while (startA!=endA)*startA++^=*startB++;

  return *this;
 }
 operator bool(){return count()>0;}
 BitSet<S>& flip(){
  for (uint *start=a,*end=a+size;start!=end;*start=~*start++);
  return *this;
 }

 void flip(int x){a[x>>5]^=1<<(x&31);}
 uint popcount(uint x)const{
  x=(x&0x55555555)+((x>>1)&0x55555555);
  x=(x&0x33333333)+((x>>2)&0x33333333);
  x=(x&0x0F0F0F0F)+((x>>4)&0x0F0F0F0F);
  x=(x&0x00FF00FF)+((x>>8)&0x00FF00FF);
  x=(x&0x0000FFFF)+((x>>16)&0x0000FFFF);
  return x;
 }
 int count(){
  int res=0;
  if (S&31)a[size-1]&=(1<<(S&31))-1;
  for (int i=0;i<size;++i)res+=popcount(a[i]);
  return res;
 }
 void reset(){
  memset(a,0,sizeof(uint)*size);

 }
 uint to_uint(){
  if (S&31)a[size-1]&=(1<<(S&31))-1;
  return a[0];
 }
 void print(){
  for (int i=0;i<size;++i)
   for (int j=0;j<=31&&(i<<5)+j+1<=S;++j)printf("%d",(a[i]>>j)&1);
  printf("\n");
 }



};
template<class Tkey,class Tvalue>
struct hash{
 Tkey *key; Tvalue *value;
 int *v,*next,len,P,size;
 void build(int Len=9,int p=11)
 {
  P=p;len=0;size=Len;++Len;
  v=new int[p];memset(v,0,sizeof(int)*p);
  value=new Tvalue[Len];memset(value,0,sizeof(Tvalue)*Len);
  next=new int[Len];memset(next,0,sizeof(int)*Len);
  key=new Tkey[Len];memset(key,0,sizeof(Tkey)*Len);
 }
 hash(int Len=0,int p=11){
  if (Len==0)return;build(Len,p);
 }
 void clear(){len=0;memset(v,0,sizeof(int)*P);}
 Tkey gethash(Tkey x){return x%P;}
 void insert(Tkey x,Tvalue y=0){
  Tkey x1=gethash(x);
  key[++len]=x;value[len]=y;
  next[len]=v[x1];v[x1]=len;
 }
 void del(Tkey x){
  Tkey x1=gethash(x);int i=v[x1],pre=0;
  while(i){
   if (key[i]==x){
    if (pre==0)v[x1]=next[i];
     else next[pre]=next[i];
   }
   pre=i;i=next[i];
  }
  }
 int find(Tkey x){
  Tkey x1=gethash(x);int i=v[x1];
  while(i){
   if (key[i]==x)return value[i];
   i=next[i];
  }
  return -1;
 }
 void inc(Tkey x,Tvalue y=1){
  Tkey x1=gethash(x);int i=v[x1];
  while(i){
   if (key[i]==x){value[i]+=y;return;}
   i=next[i];
  }
 }
 int operator [](Tkey x){return find(x);}
};
namespace fastIO{




 bool IOerror=0;
 inline char nc(){
  static char buf[100000],*p1=buf+100000,*pend=buf+100000;
  if (p1==pend){
   p1=buf; pend=buf+fread(buf,1,100000,
# 851 "data/405.cpp" 3 4
                                        stdin
# 851 "data/405.cpp"
                                             );
   if (pend==p1){IOerror=1;return -1;}

  }
  return *p1++;
 }
 inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
 inline void read(int &x){
  bool sign=0; char ch=nc(); x=0;
  for (;blank(ch);ch=nc());
  if (IOerror)return;
  if (ch=='-')sign=1,ch=nc();
  for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
  if (sign)x=-x;
 }
 inline void read(long long &x){
  bool sign=0; char ch=nc(); x=0;
  for (;blank(ch);ch=nc());
  if (IOerror)return;
  if (ch=='-')sign=1,ch=nc();
  for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
  if (sign)x=-x;
 }
 inline void read(double &x){
  bool sign=0; char ch=nc(); x=0;
  for (;blank(ch);ch=nc());
  if (IOerror)return;
  if (ch=='-')sign=1,ch=nc();
  for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
  if (ch=='.'){
   double tmp=1; ch=nc();
   for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
  }
  if (sign)x=-x;
 }
 inline void read(char *s){
  char ch=nc();
  for (;blank(ch);ch=nc());
  if (IOerror)return;
  for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
  *s=0;
 }
 inline void read(char &c){
  for (c=nc();blank(c);c=nc());
  if (IOerror){c=-1;return;}
 }

 inline void read1(int &x){
  char ch;int bo=0;x=0;
  for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
  for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
  if (bo)x=-x;
 }
 inline void read1(long long &x){
  char ch;int bo=0;x=0;
  for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
  for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
  if (bo)x=-x;
 }
 inline void read1(double &x){
  char ch;int bo=0;x=0;
  for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
  for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
  if (ch=='.'){
   double tmp=1;
   for (ch=getchar();ch>='0'&&ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
  }
  if (bo)x=-x;
 }
 inline void read1(char *s){
  char ch=getchar();
  for (;blank(ch);ch=getchar());
  for (;!blank(ch);ch=getchar())*s++=ch;
  *s=0;
 }
 inline void read1(char &c){for (c=getchar();blank(c);c=getchar());}

 inline void read2(int &x){scanf("%d",&x);}
 inline void read2(long long &x){




   scanf("%lld",&x);




 }
 inline void read2(double &x){scanf("%lf",&x);}
 inline void read2(char *s){scanf("%s",s);}
 inline void read2(char &c){scanf(" %c",&c);}
 inline void readln2(char *s){gets(s);}

 struct Ostream_fwrite{
  char *buf,*p1,*pend;
  Ostream_fwrite(){buf=new char[100000];p1=buf;pend=buf+100000;}
  void out(char ch){
   if (p1==pend){
    fwrite(buf,1,100000,
# 950 "data/405.cpp" 3 4
                         stdout
# 950 "data/405.cpp"
                               );p1=buf;
   }
   *p1++=ch;
  }
  void print(int x){
   static char s[15],*s1;s1=s;
   if (!x)*s1++='0';if (x<0)out('-'),x=-x;
   while(x)*s1++=x%10+'0',x/=10;
   while(s1--!=s)out(*s1);
  }
  void println(int x){
   static char s[15],*s1;s1=s;
   if (!x)*s1++='0';if (x<0)out('-'),x=-x;
   while(x)*s1++=x%10+'0',x/=10;
   while(s1--!=s)out(*s1); out('\n');
  }
  void print(long long x){
   static char s[25],*s1;s1=s;
   if (!x)*s1++='0';if (x<0)out('-'),x=-x;
   while(x)*s1++=x%10+'0',x/=10;
   while(s1--!=s)out(*s1);
  }
  void println(long long x){
   static char s[25],*s1;s1=s;
   if (!x)*s1++='0';if (x<0)out('-'),x=-x;
   while(x)*s1++=x%10+'0',x/=10;
   while(s1--!=s)out(*s1); out('\n');
  }
  void print(double x,int y){
   static long long mul[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,
    1000000000,10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
    100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL};
   if (x<-1e-12)out('-'),x=-x;x*=mul[y];
   long long x1=(long long)floor(x); if (x-floor(x)>=0.5)++x1;
   long long x2=x1/mul[y],x3=x1-x2*mul[y]; print(x2);
   if (y>0){out('.'); for (size_t i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i); print(x3);}
  }
  void println(double x,int y){print(x,y);out('\n');}
  void print(char *s){while (*s)out(*s++);}
  void println(char *s){while (*s)out(*s++);out('\n');}
  void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,
# 990 "data/405.cpp" 3 4
                                               stdout
# 990 "data/405.cpp"
                                                     );p1=buf;}}
  ~Ostream_fwrite(){flush();}
 }Ostream;
 inline void print(int x){Ostream.print(x);}
 inline void println(int x){Ostream.println(x);}
 inline void print(char x){Ostream.out(x);}
 inline void println(char x){Ostream.out(x);Ostream.out('\n');}
 inline void print(long long x){Ostream.print(x);}
 inline void println(long long x){Ostream.println(x);}
 inline void print(double x,int y){Ostream.print(x,y);}
 inline void println(double x,int y){Ostream.println(x,y);}
 inline void print(char *s){Ostream.print(s);}
 inline void println(char *s){Ostream.println(s);}
 inline void println(){Ostream.out('\n');}
 inline void flush(){Ostream.flush();}

 char Out[100000],*o=Out;
 inline void print1(int x){
  static char buf[15];
  char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
  while(x)*p1++=x%10+'0',x/=10;
  while(p1--!=buf)*o++=*p1;
 }
 inline void println1(int x){print1(x);*o++='\n';}
 inline void print1(long long x){
  static char buf[25];
  char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
  while(x)*p1++=x%10+'0',x/=10;
  while(p1--!=buf)*o++=*p1;
 }
 inline void println1(long long x){print1(x);*o++='\n';}
 inline void print1(char c){*o++=c;}
 inline void println1(char c){*o++=c;*o++='\n';}
 inline void print1(char *s){while (*s)*o++=*s++;}
 inline void println1(char *s){print1(s);*o++='\n';}
 inline void println1(){*o++='\n';}
 inline void flush1(){if (o!=Out){if (*(o-1)=='\n')*--o=0;puts(Out);}}
 struct puts_write{
  ~puts_write(){flush1();}
 }_puts;
 inline void print2(int x){printf("%d",x);}
 inline void println2(int x){printf("%d\n",x);}
 inline void print2(char x){printf("%c",x);}
 inline void println2(char x){printf("%c\n",x);}
 inline void print2(long long x){




   printf("%lld",x);




 }
 inline void println2(long long x){print2(x);printf("\n");}
 inline void println2(){printf("\n");}



};
using namespace fastIO;

string name="", in=".in", out=".out";

int n, j, k, x, y, z, L, w, now, ans, next[100005], f[100005], g[100005], h[100005];
char s[100005];
int main()
{
    read(s + 1), n = strlen(s + 1), next[n] = j = n + 1;
    for (int i = n - 1; i; i--)
    {
        while (j <= n && s[j - 1] != s[i]) j = next[j];
        if (s[j - 1] == s[i]) j--;
        next[i] = j;
    }
    g[0] = j = n + 1;
    for (int i = 1; i <= n; i++)
    {
        while (j <= n && s[j - 1] != s[i]) j = next[j];
        if (s[j - 1] == s[i]) j--;
        if (j < g[i - 1]) g[i] = j, h[i] = i;
        else g[i] = g[i - 1], h[i] = h[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        if (i < k + f[k] && i + f[k + k - i] < k + f[k]) f[i] = f[k + k - i];
        else
        {
            f[i] = i < k + f[k] ? k + f[k] - i : 0;
            while (i - f[i] && i + f[i] <= n && s[i - f[i]] == s[i + f[i]]) f[i]++;
            if (i + f[i] > k + f[k]) k = i;
        }
        if (f[i] > ans) ans = f[i] * 2 - 1, y = i, L = 0;
        w = g[i - f[i]], now = h[i - f[i]];
        if (w < i + f[i]) now -= i + f[i] - w, w = i + f[i];
        if ((f[i] + n - w) * 2 + 1 > ans) ans = (f[i] + n - w) * 2 + 1, L = n - w + 1, x = now - L + 1, y = i, z = w;
    }
    if (L) printf("3\n%d %d\n%d %d\n%d %d\n", x, L, y - f[y] + 1, 2 * f[y] - 1, z, L);
    else printf("1\n%d %d\n", y - f[y] + 1, 2 * f[y] - 1);
    return 0;
}

    typedef Eq_Fn eq_fn;
    typedef Update_Policy update_policy;

    list_update() { }




    template<typename It>
    list_update(It first, It last)
    { base_type::copy_from_range(first, last); }

    list_update(const list_update& other)
    : base_type((const base_type&)other) { }

    virtual
    ~list_update() { }

    list_update&
    operator=(const list_update& other)
    {
      if (this !=& other)
 {
   list_update tmp(other);
   swap(tmp);
 }
      return *this;
    }

    void
    swap(list_update& other)
    { base_type::swap(other); }
  };




}
# 16 "data/790.cpp" 2


# 17 "data/790.cpp"
using namespace __gnu_pbds;

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
# 49 "data/790.cpp"
typedef long long ll;
typedef vector<int> Vi;

inline void read(int &x) {
 x=0; char c=getchar(); int f=1;
 while (!isdigit(c)) {if (c=='-') f=-1; c=getchar();}
 while (isdigit(c)) {x=x*10+c-'0'; c=getchar();} x*=f;
}
const int N = 203000;
int n,P[N],nxt[N],f[N],qz[N],pos[N];
char s[N],t[N];
inline void manacher() {
 int id=0;
 for (register int i=1; i<=n; i++) {
  if (2*id-i>0) P[i]=(((P[2*id-i])<(id+P[id]-i))?(P[2*id-i]):(id+P[id]-i));
  while (i-P[i]>0&&i+P[i]<=n&&s[i-P[i]]==s[i+P[i]]) ++P[i];
  if (i+P[i]>id+P[id]) id=i;
 }
}
inline void kmp(int n) {
 for (int i=2,j=0; i<=n; i++) {
  while (j&&t[j+1]!=t[i]) j=nxt[j];
  if (t[j+1]==t[i]) j++;
  nxt[i]=j;
 }
}
int len,a[5],b[5],ans;
int main() {
 scanf("%s",s+1); n=strlen(s+1); manacher();
 for (register int i=1; i<=n; i++) t[i]=s[n-i+1]; t[n+1]='#'; int len=n+1;
 for (register int i=1; i<=n; i++) t[++len]=s[i]; kmp(len);
 for (register int i=1; i<=n; i++) f[i]=nxt[i+n+1];
 for (register int i=1; i<=n; i++) {
  qz[i]=(((qz[i-1])>(f[i]))?(qz[i-1]):(f[i]));
  pos[i]=(qz[i]==f[i])?i:pos[i-1];
 }
 for (register int i=1; i<=n; i++) {
  int p=pos[i-P[i]];
  if (n-f[p]+1<=i+P[i]-1) p-=(i+P[i]-1)-(n-f[p]+1)+1;
  if (!f[p]) {
   if ((i+P[i]-1)-(i-P[i]+1)+1>ans) {
    ans=(i+P[i]-1)-(i-P[i]+1)+1;
    len=1; a[1]=i-P[i]+1; b[1]=i+P[i]-1;
   }
  }
  else {
   if (f[p]*2+(i+P[i]-1)-(i-P[i]+1)+1>ans) {
    ans=f[p]*2+(i+P[i]-1)-(i-P[i]+1)+1;
    len=3; a[1]=p-f[p]+1; b[1]=p;
    a[2]=i-P[i]+1; b[2]=i+P[i]-1;
    a[3]=n-f[p]+1; b[3]=n;
   }
  }
 }
 printf("%d\n",len);
 for (register int i=1; i<=len; i++) printf("%d %d\n",a[i],b[i]-a[i]+1);
}

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 10 "data/251.cpp" 2






# 15 "data/251.cpp"
typedef long long ll;
using namespace std;
typedef pair<int,int> Pii;
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
  if (2*id-i>0) P[i]=min(P[2*id-i],id+P[id]-i);
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
  qz[i]=max(qz[i-1],f[i]);
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
 return 0;
}

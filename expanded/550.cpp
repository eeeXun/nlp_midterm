# 1 "/usr/include/c++/11.2.0/ctime" 1 3
# 39 "/usr/include/c++/11.2.0/ctime" 3
       
# 40 "/usr/include/c++/11.2.0/ctime" 3
# 23 "data/550.cpp" 2
# 1 "/usr/include/c++/11.2.0/cassert" 1 3
# 41 "/usr/include/c++/11.2.0/cassert" 3
       
# 42 "/usr/include/c++/11.2.0/cassert" 3


# 1 "/usr/include/assert.h" 1 3 4
# 64 "/usr/include/assert.h" 3 4
extern "C" {


extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     noexcept (true) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     noexcept (true) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     noexcept (true) __attribute__ ((__noreturn__));


}
# 45 "/usr/include/c++/11.2.0/cassert" 2 3
# 24 "data/550.cpp" 2
# 37 "data/550.cpp"

# 37 "data/550.cpp"
using namespace std;

template<typename T>inline bool upmin(T &x,T y) { return y<x?x=y,1:0; }
template<typename T>inline bool upmax(T &x,T y) { return x<y?x=y,1:0; }

typedef long long ll;
typedef unsigned long long ull;
typedef long double lod;
typedef pair<int,int> PR;
typedef vector<int> VI;

const lod eps=1e-11;
const lod pi=acos(-1);
const int oo=1<<30;
const ll loo=1ll<<62;
const int mods=998244353;
const int MAXN=600005;
const int INF=0x3f3f3f3f;

inline int read()
{
 int f=1,x=0; char c=getchar();
 while (c<'0'||c>'9') { if (c=='-') f=-1; c=getchar(); }
 while (c>='0'&&c<='9') { x=(x<<3)+(x<<1)+(c^48); c=getchar(); }
 return x*f;
}
struct Ansnode{ int l,mid,len,c; } Ans;
char s[MAXN],t[MAXN],St[MAXN];
PR mx[MAXN][20];
int Log[MAXN],nxt[MAXN],P[MAXN];
void InitKMP(char *st,int len)
{
 for (int i=2,j=0;i<=len;i++)
 {
  while (j&&st[i]!=st[j+1]) j=nxt[j];
  if (st[i]==st[j+1]) j++;
  nxt[i]=j;

 }
}
void Manacher(char *st,int len)
{
 St[0]='%',St[1]='#';
 for (int i=1;i<=len;i++) St[i<<1]=st[i],St[i<<1|1]='#';


 int Len=len<<1|1,mid=0,right=0;
 for (int i=1;i<=Len;i++)
 {
  P[i]=(right>i?min(P[mid*2-i],right-i):1);
  while (St[i-P[i]]==St[i+P[i]]) P[i]++;

  if (right<i+P[i]) right=i+P[i],mid=i;
 }
 for (int i=1;i<=len;i++)
 {
  if (P[i*2]-1>=Ans.c) Ans=(Ansnode){0,i,0,P[i*2]-1};
  P[i]=P[i*2]>>1;

 }
}
PR max(PR x,PR y){ return x.first>=y.first?x:y; }
void InitST(int n)
{
 Log[1]=0;
 for (int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
 for (int i=1;i<=n;i++) mx[i][0]=make_pair(P[i],i);
 for (int i=1;i<=Log[n];i++)
  for (int j=1;j<=n-(1<<i)+1;j++)
   mx[j][i]=max(mx[j][i-1],mx[j+(1<<(i-1))][i-1]);
}
PR querymx(int l,int r)
{
 if (l>r) return make_pair(-100000,0);
 int t=Log[r-l+1];
 return max(mx[l][t],mx[r-(1<<t)+1][t]);
}
PR getans(int L,int R)
{
 if (L>R) return make_pair(-100000,0);
 int l=1,r=(R-L)/2+1;
 while (l<r)
 {
  int mid=(l+r+1)>>1;
  if (querymx(L+mid-1,R-mid+1).first>=mid) l=mid;
  else r=mid-1;
 }
 return make_pair(l,querymx(L+l-1,R-l+1).second);
}
int main()
{
 scanf("%s",t+1);
 int len=strlen(t+1);
 for (int i=1;i<=len;i++) s[i]=t[len-i+1];

 InitKMP(s,len);
 Manacher(t,len);
 InitST(len);

 int ans=0;
 for (int l=1,i=1,j=0;l<=len;l++)
 {

  for (;i<=len;i++)
  {
   while (j&&t[i]!=s[j+1]) j=nxt[j];
   if (t[i]==s[j+1]) j++;
   if (j==l)
   {
    PR q=getans(i+1,len-l);

    if (q.first+q.first+l+l-1>Ans.c) Ans=(Ansnode){i-l+1,q.second,l,q.first+q.first+l+l-1};
    i++;
    break;
   }
  }
 }
 if (!Ans.len) { puts("1"); printf("%d %d\n",Ans.mid-(Ans.c-1)/2,Ans.c); }
 else
 {
  puts("3");
  int q=Ans.c-Ans.len*2;
  printf("%d %d\n",Ans.l,Ans.len);
  printf("%d %d\n",Ans.mid-(q-1)/2,q);
  printf("%d %d\n",len-Ans.len+1,Ans.len);
 }
 return 0;
}

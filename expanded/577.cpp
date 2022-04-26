# 40 "/usr/include/c++/11.2.0/cctype" 3
# 6 "data/577.cpp" 2

# 6 "data/577.cpp"
using namespace std;

const int MAXN = 1e5+5;
const int base = 3081123;
const int mod = 998244353;

template <typename T>
inline void read(T&x){
 x=0; char temp=getchar(); bool f=false;
 while(!isdigit(temp)){if(temp=='-') f=true; temp=getchar();}
 while(isdigit(temp)){x=(x<<1)+(x<<3)+temp-'0'; temp=getchar();}
 if(f) x=-x;
}
template <typename T>
void print(T x){
 if(x<0) putchar('-'),x=-x;
 if(x>9) print(x/10);
 putchar(x%10+'0');
}


int n;
char s[MAXN];


int h[MAXN],revh[MAXN],mi[MAXN];

inline void Init(){
 mi[0]=1;
 for(register int i=1;i<=n;i++) h[i]=1ll*h[i-1]*base%mod+s[i],mi[i]=1ll*mi[i-1]*base%mod;
 for(register int i=n;i>=1;i--) revh[i]=1ll*revh[i+1]*base%mod+s[i];
}

inline int Hash(int l,int r){return ((1ll*h[r]-1ll*h[l-1]*mi[r-l+1]%mod)%mod+mod)%mod;}
inline int RevHash(int l,int r){return ((1ll*revh[l]-1ll*revh[r+1]*mi[r-l+1]%mod)%mod+mod)%mod;}


int l[MAXN],r[MAXN],back[MAXN],start[MAXN],suf[MAXN],from[MAXN];

inline int BinarySearch1(int l,int r,int tar){
 int res=0;
 while(l<=r){
  int mid=l+r>>1,L=tar-mid,R=tar+mid;
  if(0<L&&R<=n&&Hash(L,R)==RevHash(L,R)) res=mid,l=mid+1;
  else r=mid-1;
 }
 return res;
}

inline int BinarySearch2(int l,int r,int tar){
 int res=0;
 while(l<=r){
  int mid=l+r>>1,R=tar+mid-1;
  if(R<=n&&Hash(tar,R)==RevHash(n-mid+1,n)) res=mid,l=mid+1;
  else r=mid-1;
 }
 return res;
}

inline void Solve(){
 int ans=0,k=0,sta[2],len[2];
 for(register int i=1;i<=n;i++){
  int L=l[i],R=r[i],temp=suf[L-1],s=from[L-1]-temp+1;
  if(temp+R>n) temp-=temp+R-n;
  if(ans<temp*2+(R-L+1)){
   ans=temp*2+(R-L+1),sta[0]=L,len[0]=R-L+1;
   if(temp==0) k=1;
   else k=2,sta[1]=s,len[1]=temp;
  }
 }
 if(k==1){
  print(1),puts("");
  print(sta[0]),putchar(' '),print(len[0]),puts("");
 }
 else{
  print(3),puts("");
  print(sta[1]),putchar(' '),print(len[1]),puts("");
  print(sta[0]),putchar(' '),print(len[0]),puts("");
  print(n-len[1]+1),putchar(' '),print(len[1]),puts("");
 }
}

int main(){
 scanf("%s",s+1),n=strlen(s+1);
 Init();
 for(register int i=1;i<=n;i++){
  int len=BinarySearch1(1,n,i);
  l[i]=i-len,r[i]=i+len;
 }
 for(register int i=1;i<=n;i++) back[i]=BinarySearch2(1,n,i);
 for(register int i=1;i<=n;i++){
  from[i]=i;
  int tail=i+back[i]-1;
  if(suf[tail]<back[i]) suf[tail]=back[i];
 }
 for(register int i=1;i<=n;i++)
   if(suf[i-1]>suf[i]){
    suf[i]=suf[i-1];
    from[i]=from[i-1];
   }
 Solve();
 return 0;
}

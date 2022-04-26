  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/465.cpp" 2

# 2 "data/465.cpp"
using namespace std;
# 15 "data/465.cpp"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e8 + 1;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}

const int N=100005;
char s[N];
int f[N*2];
int p[N],Ans[N],pos[N];
int n;
void manacher(char* str){
    static char s[N*2];
    for(int i=(0); i<(n+1); i++) s[i*2]=str[i], s[i*2+1]='#';
    s[0]='!'; s[2*n+2]='?';
    int a=0,p=0;
    for(int i=(1); i<(2*n+2); i++){
        int h=0;
        if(i<=a+p)h=min(f[2*a-i],a+p-i);
        while(s[i+h+1]==s[i-h-1])h++;
        f[i]=h;
        if(i+h>a+p)a=i,p=h;
    }
}
void prefix(char s[], int * pre) {
 pre[0] = 0;
 for(int i = 1, k = 0;s[i];++ i) {
  while(k > 0 && s[k] != s[i]) k = pre[k-1];
  if(s[k] == s[i]) ++ k;
  pre[i] = k;
 }
}
void KMP(char *x) {
 for(int i = 0,j=0;x[i];++ i) {
   while(j > 0 && x[n-j-1] != x[i]) j = p[j - 1];
   if(x[n-j-1] == x[i]) ++ j;
   Ans[i+1]=j;
 }
}
int main() {
 scanf("%s",s+1);
 n=strlen(s+1);
 manacher(s);
 for(int i=(1); i<(n+1); i++)f[i*2]=f[i*2]/2+1;
 strrev(s+1);
 prefix(s+1,p);
 strrev(s+1);
 KMP(s+1);
 for(int i=(0); i<(n+1); i++)pos[i]=i;
 for(int i=(1); i<(n+1); i++)if(Ans[pos[i]]<Ans[pos[i-1]])pos[i]=pos[i-1];
 pii s1,s2,s3;
 for(int i=(1); i<(n+1); i++) {
  pii _s1,_s2,_s3;
  int ml=f[i<<1];
  _s1=make_pair(i-ml+1,ml*2-1);
  int Pos=pos[i-ml];
  int ans=Ans[Pos];ans=min(ans,n-(i+ml-1));
  _s2=make_pair(Pos-ans+1,ans);
  _s3=make_pair(n-ans+1,ans);
  if(_s1.second+_s2.second+_s3.second>s1.second+s2.second+s3.second)s1=_s1,s2=_s2,s3=_s3;
 }
 int k=s2.second?3:1;printf("%d\n",k);
 if(k==1)printf("%d %d\n",s1.first,s1.second);
 if(k==3)printf("%d %d\n%d %d\n%d %d\n",s2.first,s2.second,s1.first,s1.second,s3.first,s3.second);
 return 0;
}

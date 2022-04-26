      _RealType __sum = _RealType(0);
      _RealType __tmp = _RealType(1);
      for (size_t __k = __m; __k != 0; --__k)
 {
   __sum += _RealType(__urng() - __urng.min()) * __tmp;
   __tmp *= __r;
 }
      __ret = __sum / __tmp;
      if (__builtin_expect(__ret >= _RealType(1), 0))
 {

   __ret = std::nextafter(_RealType(1), _RealType(0));




 }
      return __ret;
    }


}
# 52 "/usr/include/c++/11.2.0/random" 2 3
# 26 "data/687.cpp" 2


# 27 "data/687.cpp"
using namespace std;
typedef long long LL;
typedef array<int,4> A;

const int M=1e5+1;
char in[M];
char rev[M];
int r[M];
int l[M];
int u[M];
int n;
int search(const char *t,const char *p){
 if(p[0]==0){
  return 0;
 }
 vector<int> ind;
 ind.push_back(-1);
 int cur=-1;
 for(int i=1;p[i];i++){
  if(p[i]==p[cur+1]){
   cur++;
   ind.push_back(cur);
  }
  else{
   cur=-1;
   ind.push_back(cur);
  }
 }
 int st=-1;
 for(int i=0;t[i];i++){
  while(t[i]!=p[st+1])
  {
   if(st==-1){
    st=-2;
    break;
   }
   st=ind[st];
  }
  st++;
  l[i]=st;

 }

 return -1;
}
int main() {
 scanf("%s",in);
 n=strlen(in);

 r[0]=0;
 int m=0;
 for(int i=0;i<n;i++){
  int w=0;
  if(i<=m+r[m]){
   int j=2*m-i;
   w=min(m+r[m]-i,r[j]);
  }
  r[i]=w;
  w++;
  while(0<=i-w&&i+w<=2*n&&in[i-w]==in[i+w]){
   r[i]=w;
   w++;
  }
  if(m+r[m]<i+r[i]){
   m=i;
  }

  rev[n-1-i]=in[i];
 }

 search(in,rev);
 if(l[n-1]==n-1){
  puts("1");
  if(n%2==0){
   n--;
  }
  printf("%d %d\n", 1, n);
  return 0;
 }
 u[0]=0;
 int ret=1;
 A ret1={{0,0,0,1}};
 for(int i=1;i<n;i++){
  if(l[i]>l[u[i-1]]){
   u[i]=i;
  }
  else{
   u[i]=u[i-1];
  }
  int j=i-r[i]-1;
  int b=n-1-(i+r[i]);
  int t=2*r[i]+1;
  if(t>ret){
   ret=t;
   ret1={{0,0,i-r[i],2*r[i]+1}};
  }
  if(j>=0){
   int k=u[j];
   if(l[k]+1>b){
    k+=b-(l[k]+1);
   }
   if(k>=0){
    t+=2*(l[k]+1);
    if(t>ret){
     ret=t;
     ret1={{k-l[k],l[k]+1,i-r[i],2*r[i]+1}};
    }
   }
  }
 }

 if(ret1[1]==0){
  puts("1");
  printf("%d %d\n",ret1[2]+1,ret1[3]);
 }
 else{
  puts("3");
  printf("%d %d\n",ret1[0]+1,ret1[1]);
  printf("%d %d\n",ret1[2]+1,ret1[3]);
  printf("%d %d\n",n+1-ret1[1],ret1[1]);
 }

 return 0;
}

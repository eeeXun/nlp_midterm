const int fin=0,maxn=100010,maxk=18;
int n;
char a[maxn],b[maxn];
int c[maxn],d[maxn],p[maxn];
int l2[maxn],f[maxn][maxk];

  void KMP(){
    int i,j;
    for(i=1;i<=n;++i)b[i]=a[n-i+1];
    for(p[1]=j=0,i=2;i<=n;++i){
      while(j&&b[i]!=b[j+1])j=p[j];
      if(b[i]==b[j+1])++j;
      p[i]=j;
    }
    for(j=0,i=1;i<=n;++i){
      while(j&&a[i]!=b[j+1])j=p[j];
      if(a[i]==b[j+1])++j;
      if(j&&!c[j])c[j]=i;
    }
  }

  void Manacher(){
    int i,j;
    for(d[1]=j=1,i=2;i<=n;++i)
      if(j+d[j]>i&&d[2*j-i]<j+d[j]-i)
        d[i]=d[2*j-i];
      else{
        d[i]=max(j+d[j]-i,1);
        while(a[i-d[i]]==a[i+d[i]])++d[i];
        j=i;
      }
  }

    inline int gmax(int x,int y){
      return d[x]>d[y]?x:y;
    }

  void ST_pre(){
    int i,k;
    for(i=0;(1<<i)<=n;++i)l2[1<<i]=i;
    for(i=2;i<=n;++i)if(!l2[i])l2[i]=l2[i-1];
    for(i=1;i<=n;++i)f[i][0]=i;
    for(k=1;k<=l2[n];++k)
      for(i=1;i+(1<<k)-1<=n;++i)
        f[i][k]=gmax(f[i][k-1],f[i+(1<<k-1)][k-1]);
  }
  inline int ST_que(int x,int y){
    int k=l2[y-x+1];
    return gmax(f[x][k],f[y-(1<<k)+1][k]);
  }

  inline int que(int x,int y,int &s){
    int l=1,r=y-x+2>>1,m,t;
    while(l<r){
      if(m=l+r+1>>1,t=ST_que(x+m-1,y-m+1),d[t]>=m)
        l=m,s=t;
      else
        r=m-1;
    }
    if(l==1)s=x;
    return l*2-1;
  }

int main(){
  if(fin){
    freopen("t.in","r",
# 74 "data/39.cpp" 3 4
                      stdin
# 74 "data/39.cpp"
                           );
    freopen("t.out","w",
# 75 "data/39.cpp" 3 4
                       stdout
# 75 "data/39.cpp"
                             );
  }
  int i,s,t,l,ans=0,ans0,ans1,ans2;
  gets(a+1),n=strlen(a+1);
  KMP();
  Manacher();
  ST_pre();
  for(i=0;i==0||c[i]&&c[i]+i<n;++i)
    if(l=que(c[i]+1,n-i,s),t=2*i+l,ans<t)
      ans=t,ans0=i,ans1=s,ans2=l;
  i=ans0,s=ans1,l=ans2;
  if(i)
    printf("3\n%d %d\n%d %d\n%d %d\n",c[i]-i+1,i,s-l/2,l,n-i+1,i);
  else
    printf("1\n%d %d\n",s-l/2,l);
  return 0;
}



# 5 "data/192.cpp"
using namespace std;
const int p=1000000009;
int H[100010],h[100010],ex[100010],e[100010],f[100010][21],g[100010][21];
int l,r,mid,i,j,maxx,ans,n,t1,t2;
char c[100010];

int get1(int l,int r){
  return H[r]-H[l-1]*ex[r-l+1];
}

int get2(int l,int r){
  return h[l]-h[r+1]*ex[r-l+1];
}

int getmax(int l,int r){
  int i;
  for (i=20;i>=0;i--)
    if (r-l+1>=e[i]) break;
  return max(f[l][i],g[r][i]);
}

void init(){
  for (e[0]=1,i=1;i<=20;i++)
    e[i]=e[i-1]*2;

  for (i=1;i<=n;i++){
    l=1;r=min(i-1,n-i);
    mid=(l+r)>>1;
    while (l<=r){
      if ( get1(i-mid,i)==get2(i,i+mid) )
        l=mid+1; else r=mid-1;
      mid=(l+r)>>1;
    }

    f[i][0]=g[i][0]=mid;
  }

  for (j=1;j<=20;j++)
    for (i=1;i<=n;i++){
      if (i+e[j]-1<=n) f[i][j]=max(f[i][j-1],g[i+e[j]-1][j-1]);
      if (i-e[j]+1>0) g[i][j]=max(g[i][j-1],f[i-e[j]+1][j-1]);
    }
}

void work(int lef,int rig){
  l=1;r=(rig-lef)>>1;
  mid=(l+r)>>1;
  while (l<=r){
    if (getmax(lef+mid,rig-mid)>=mid)
      l=mid+1; else r=mid-1;
    mid=(l+r)>>1;
  }
}

void print(){
  int len1=(maxx-t1)/2,len2=t1;
  printf("%d\n",ans);
  if (len1) printf("%d %d\n",t2,len1);
  for (i=t2+len1+len2/2;i<=n-len1-len2/2;i++)
    if (g[i][0]>=len2/2) break;
  printf("%d %d\n",i-len2/2,len2);
  if (len1) printf("%d %d\n",n-len1+1,len1);
}

int main(){



  scanf("%s",c);
  n=strlen(c);
  for (ex[0]=1,i=1;i<=n;i++)
    ex[i]=ex[i-1]*p;
  for (i=0;i<n;i++)
    H[i+1]=H[i]*p+c[i];
  for (i=n-1;i>=0;i--)
    h[i+1]=h[i+2]*p+c[i];
  init();

  j=1;
  for (i=0;n-i*2>0;i++){
    for (;n-j+1-2*i>0;j++)
      if (get1(j,j+i-1)==get2(n-i+1,n)) break;
    if (n-j+1-2*i<1) break;
    work(j+i,n-i);
    if (i*2+2*mid+1>maxx){
      maxx=i*2+2*mid+1;
      if (i==0) ans=1; else ans=3;
      t1=2*mid+1;
      t2=j;
    }
  }

  print();
  return 0;
}

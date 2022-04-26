
}
# 11 "data/384.cpp" 2



# 13 "data/384.cpp"
using namespace std;



const double pi = acos(-1.0);

const double eps = 1e-7;
const int N = 200005;
char str[N];







const int M = N;
int height[M],arr[4][M];
int *sa,*nsa,*Rank,*nrank,bin[M];

void calsa(char str[],int n,int K = 256){
 int i,j,k;
 sa = arr[0];
 nsa = arr[1];
 Rank = arr[2];
 nrank = arr[3];
 for(i = 0;i<K;i++)bin[i] = 0;
 for(i = 0;i<n;i++)bin[str[i]]++;
 for(i = 1;i<K;i++)bin[i] += bin[i-1];
 for(i = 0;i<n;i++)sa[--bin[str[i]]] = i;
 Rank[sa[0]] = 0;
 for(i = 1;i<n;i++){
  Rank[sa[i]] = Rank[sa[i-1]];
  if(str[sa[i]]!=str[sa[i-1]])Rank[sa[i]]++;
 }
 for(k = 1;k<=n;k <<= 1){
  for(i = 0;i<n;i++)bin[Rank[sa[i]]] = i;
  for(i = n-1;i>=0;i--){
   if(sa[i]>=k){
    nsa[bin[Rank[sa[i]-k]]--] = sa[i]-k;
   }
  }
  for(i = n-k;i<n;i++){
   nsa[bin[Rank[i]]] = i;
  }
  nrank[nsa[0]] = 0;
  for(i = 1;i<n;i++){
   nrank[nsa[i]] = nrank[nsa[i-1]];
   if(Rank[nsa[i]]>Rank[nsa[i-1]] || Rank[nsa[i]+k]>Rank[nsa[i-1]+k]){
    nrank[nsa[i]]++;
   }
  }
  swap(sa,nsa);
  swap(Rank,nrank);
 }
}
void calhei(char str[],int n){
 int i,j;
 height[0] = 0;
 for(i = 0,j = 0;i<n;i++){
  if(Rank[i]){
   while(str[sa[Rank[i]-1]+j]==str[i+j])j++;
   height[Rank[i]]=j;
   if(j)j--;
  }
 }
}

int Mx[20][M],G2[M];
void pre_rmq(int d[],int n){
 int i,j,k;
 memset(G2,0,sizeof(G2));
 for(i = 0;(1<<i)<=n;i++){
  G2[1<<i] = i;
 }
 for(i = 1;i<=n;i++){
  if(!G2[i]){
   G2[i] = G2[i-1];
  }
 }
 for(i = 0;i<n;i++){
  Mx[0][i] = d[i];
 }
 for(i = 1;(1<<i)<=n;i++){
  for(j = 0;j<n;j++){
   k = min(j+(1<<(i-1)),n-1);
   Mx[i][j] = min(Mx[i-1][j],Mx[i-1][k]);
  }
 }
}
int rmq(int l,int r){
 int k = G2[r-l+1];
 return min(Mx[k][l],Mx[k][r-(1<<k)+1]);
}
int lpos[N],rpos[N],n,a[N];
int mlen,ans[6];

void solve(){
 int i,j,k;
 mlen = 0;
 for(i = 0;i<n;i++){
  int tmp = rpos[i]-lpos[i]+1;
  if(tmp>mlen){
   mlen = tmp;
   for(j = 0;j<3;j++)ans[j] = lpos[i];
   for(j = 3;j<6;j++)ans[j] = rpos[i];
  }
 }
 for(i = 0;i<n;i++){
  int l = 1,r = n-1;
  while(l<=r){
   int mid = (l+r)>>1;
   int work = 0;
   if(a[mid]!=-1){
    if(a[mid]+mid<=lpos[i] && rpos[i]<=n-1-mid){
     work = 1;
    }
   }
   if(work)l = mid+1;
   else r = mid-1;
  }
  if(r>0){
   int tmp = r*2+rpos[i]-lpos[i]+1;
   if(mlen<tmp){
    mlen = tmp;
    ans[0] = a[r];
    ans[1] = a[r]+r-1;
    ans[2] = lpos[i];
    ans[3] = rpos[i];
    ans[4] = n-r;
    ans[5] = n-1;
   }
  }
 }
    if(ans[1]<ans[2] && ans[3]<ans[4]){
  printf("3\n");
  printf("%d %d\n",ans[0]+1,ans[1]-ans[0]+1);
  printf("%d %d\n",ans[2]+1,ans[3]-ans[2]+1);
  printf("%d %d\n",ans[4]+1,ans[5]-ans[4]+1);
 }else if(ans[1]==ans[2] && ans[3]==ans[4]){
  printf("1\n");
  printf("%d %d\n",ans[0]+1,ans[5]-ans[0]+1);
 }else if(ans[1]<ans[2]){
  printf("2\n");
  printf("%d %d\n",ans[0]+1,ans[1]-ans[0]+1);
  printf("%d %d\n",ans[2]+1,ans[5]-ans[2]+1);
 }else{
  printf("2\n");
  printf("%d %d\n",ans[0]+1,ans[3]-ans[0]+1);
  printf("%d %d\n",ans[4]+1,ans[5]-ans[4]+1);
 }
}

int main(){


 int i,j,k,t,nc = 0;
 while(scanf("%s",str)!=
# 170 "data/384.cpp" 3 4
                       (-1)
# 170 "data/384.cpp"
                          ){
  n = strlen(str);
  str[n] = '*';
  for(i = 0;i<n;i++){
   str[n+1+i] = str[n-1-i];
  }
  str[2*n+1] = '#';
  calsa(str,2*n+2);
  calhei(str,2*n+2);
  pre_rmq(height,2*n+2);
  for(i = 0;i<n;i++){
   k = 2*n-i;
   int t1 = Rank[i],t2 = Rank[k];
   if(t1>t2)swap(t1,t2);
   int t3 = rmq(t1+1,t2);
   lpos[i] = i-t3+1;
   rpos[i] = i+t3-1;
  }
  memset(a,-1,sizeof(a));
  for(i = 0;i<n;i++){
   int t1 = Rank[i],t2 = Rank[n+1];
   if(t1>t2)swap(t1,t2);
   int t3 = rmq(t1+1,t2);
   if(a[t3]==-1)a[t3] = i;
  }
  for(i = n;i>=0;i--){
   if(a[i+1]!=-1 && (a[i]==-1 || a[i]>a[i+1])){
    a[i] = a[i+1];
   }
  }
  solve();
 }
 return 0;
}

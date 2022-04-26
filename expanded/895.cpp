






# 9 "data/895.cpp"
using namespace std;

typedef long long lint;
typedef double db;
typedef pair <int,int> ii;
typedef pair <ii,int> iii;
typedef vector <int> vi;
typedef vector <ii> vii;

const int maxn=1e5+20;

int N,K,pw[maxn],go[maxn],hash1[maxn],hash2[maxn],mx;
ii ans[5];
char ar[maxn];

int get1(int x,int y){ return hash1[x]-hash1[y+1]*pw[y-x+1];}
int get2(int x,int y){ return hash2[y]-hash2[x-1]*pw[y-x+1]; }

void solve(int m){
 int a=min(m,N-m+1),cur=0;

 for(int k=18;k>=0;k--){
  int x=cur+(1<<k);
  if(x>a) continue;

  if(get1(m-x+1,m+x-1) == get2(m-x+1,m+x-1))
   cur+=1<<k;
 }

 int l=m-cur+1 , r=m+cur-1;

 int cur2=N+1;

 for(int k=18;k>=0;k--){
  int x=cur2-(1<<k);

  if(x>r && go[x]<l) cur2-=1<<k;
 }

 int sz=N-cur2+1;

 if(2*sz+2*cur-1 >mx){
  mx=2*sz+2*cur-1;
  K=(sz!=0)*2+1;
  if(K==3) ans[3]=ii(cur2,sz) , ans[1]=ii(go[cur2]-sz+1,sz) , ans[2]=ii(l,r-l+1);
  else ans[1]=ii(l,r-l+1);
 }
}

int main(){
 scanf(" %s",ar+1);
 N=strlen(ar+1);

 pw[0]=1;
 for(int i=1;i<=N;i++) pw[i]=pw[i-1]*29;
 for(int i=N;i>=1;i--) hash1[i]=hash1[i+1]*29+ar[i]-'a'+1;
 for(int i=1;i<=N;i++) hash2[i]=hash2[i-1]*29+ar[i]-'a'+1;

 for(int i=N,j=0;i>=0;i--){
  while(get1(i,N)!=get2(j,j+N-i) && j<=N) j++;
  go[i]=j+N-i;
 }

 for(int i=1;i<=N;i++)
  solve(i);

 cout << K << endl;

 for(int i=1;i<=K;i++)
  cout << ans[i].first << ' ' << ans[i].second << endl;

 return 0;
}

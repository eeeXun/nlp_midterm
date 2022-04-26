

# 4 "data/863.cpp"
using namespace std;






const double pi=acos(-1.0);
const double eps=1e-10;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
int n,tn;
char s[maxn],ns[maxn<<1],rs[maxn];
int R[maxn<<1],nxt[maxn],d[maxn],dmx[maxn];
vector<pair<int,int> >output;
void getNext(){
 nxt[1]=0;
 for(int i=2,j=0;i<=n;i++){
  while(j&&rs[j+1]!=rs[i])j=nxt[j];
  if(rs[j+1]==rs[i])++j;
  nxt[i]=j;
 }
}
void kmp(){
 getNext();
 for(int i=1,j=0;i<=n;i++){
  while(j&&rs[j+1]!=s[i])j=nxt[j];
  if(rs[j+1]==s[i])++j;
  d[i]=j;
  if(d[i]>d[dmx[i-1]]){
   dmx[i]=i;
  }
  else{
   dmx[i]=dmx[i-1];
  }
 }
}
void manacher(){
 ns[0]='$';
 ns[1]='#';
 for(int i=1;i<=n;i++){
  ns[2*i]=s[i];
  ns[2*i+1]='#';
 }
 tn=2*n+1;
 ns[tn+1]='\0';
 int mx=0,p=0;
 for(int i=1;i<=tn;i++){
  if(mx>i)R[i]=min(mx-i,R[2*p-i]);
  else R[i]=1;
  while(ns[i-R[i]]==ns[i+R[i]])++R[i];
  if(i+R[i]>mx){
   mx=i+R[i];
   p=i;
  }
 }
}
int main(void){

 scanf("%s",s+1);
 n=strlen(s+1);
 for(int i=n;i>=1;i--){
  rs[n-i+1]=s[i];
 }
 kmp();
 manacher();







 int ans=0;
 for(int i=1;i<=tn;i++){
  if(ns[i]=='#')continue;
  int tmp=R[i]-1,l=i/2-tmp/2,r=i/2+tmp/2;

  int tans=tmp+2*min(d[dmx[l-1]],n-r);

  if(tans>ans){
   output.clear();
   if(min(d[dmx[l-1]],n-r)){
    output.push_back(make_pair(dmx[l-1]-d[dmx[l-1]]+1,min(d[dmx[l-1]],n-r)));
    output.push_back(make_pair(l,tmp));
    output.push_back(make_pair(n-min(d[dmx[l-1]],n-r)+1,min(d[dmx[l-1]],n-r)));
   }
   else{
    output.push_back(make_pair(l,tmp));
   }
   ans=tans;
  }
 }
 printf("%d\n",output.size());
 for(int i=0;i<output.size();i++){
  printf("%d %d\n",output[i].first,output[i].second);
 }
 return 0;
}

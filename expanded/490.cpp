                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 9 "data/490.cpp" 2

# 9 "data/490.cpp"
using namespace std;
const int MAXN=100000;
const size_t P=10007;

size_t h[MAXN+10];
size_t rh[MAXN+10];
size_t pexp[MAXN+10];
char s[MAXN+10];
int l[MAXN+10];
int pei[MAXN+10];
int n;
void initPalindrome(){
 for(int i=1;i<=n;){
  while(i-l[i]-1>=1 && i+l[i]+1<=n && s[i-l[i]-1]==s[i+l[i]+1])
   l[i]++;
  for(int j=i+1;j<=i+l[i];j++){
   int k=i-(j-i);
   if(k-l[k]>i-l[i] || i+l[i]==n){
    l[j]=l[k];
   }else{
    l[j]=k-(i-l[i]);
    i=j;
    goto NextLoop;
   }
  }
  i+=l[i]+1;
  NextLoop:;
 }
}
void initHash(){
 pexp[0]=1;
 for(int i=1;i<=MAXN;i++){
  pexp[i]=pexp[i-1]*P;
 }
 h[0]=0;
 for(int i=1;i<=n;i++)
  h[i]=h[i-1]*P+s[i]-'a';

 rh[n+1]=0;
 for(int i=n;i>=1;i--)
  rh[i]=rh[i+1]*P+s[i]-'a';
}
size_t fhash(int st,int ed){
 return h[ed]-h[st-1]*pexp[ed-st+1];
}
size_t rhash(int st,int ed){
 return rh[st]-rh[ed+1]*pexp[ed-st+1];
}
bool cmp(int x,int y){
 return x-l[x]<y-l[y];
}
int main(){
 scanf("%s",&s[1]);
 n=strlen(&s[1]);
 initPalindrome();



 initHash();

 set<pair<size_t,int> > suffix;
 for(int i=n+1;i>=1;i--){
  suffix.insert(make_pair(fhash(i,n),n-i+1));

 }

 for(int i=1;i<=n;i++){
  int l=i-1,r=n+1,mid=(l+r)>>1;
  while(l<r){
   if(suffix.find(make_pair(rhash(i,mid),mid-i+1))!=suffix.end())
    l=mid+1;
   else
    r=mid;
   mid=(l+r)>>1;
  }
  pei[i]=mid-i;

 }

 vector<int> seq;
 for(int i=1;i<=n;i++)
  seq.push_back(i);
 sort(seq.begin(),seq.end(),cmp);

 priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
 int last=0;

 int ans=0,ansst,ansmid,anslen;

 int gone=0,gonest=1;
 for(size_t i=0;i<seq.size();i++){
  int now=seq[i];

  for(int j=last+1;j<=now-l[now]-1;j++){
   q.push(make_pair(j,j+pei[j]-1));
  }
  last=now-l[now]-1;

  while(!q.empty() && q.top().second<now-l[now]){
   int cur=q.top().second-q.top().first+1;
   if(gone<cur){
    gone=cur;
    gonest=q.top().first;
   }
   q.pop();
  }

  int cur=gone;
  int curst=gonest;
  if(!q.empty() && now-l[now]-q.top().first>cur){
   cur=now-l[now]-q.top().first;
   curst=q.top().first;
  }
  cur=min(cur,n-(now+l[now]));

  if(ans<cur*2+l[now]*2+1){
   ans=cur*2+l[now]*2+1;
   ansst=curst;
   ansmid=now;
   anslen=cur;
  }
 }

 if(anslen){
  puts("3");
  printf("%d %d\n%d %d\n%d %d\n",ansst,anslen,ansmid-l[ansmid],l[ansmid]*2+1,n-anslen+1,anslen);
 }else{
  puts("1");
  printf("%d %d\n",ansmid-l[ansmid],l[ansmid]*2+1);
 }
 return 0;
}

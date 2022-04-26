}


}
# 43 "/usr/include/c++/11.2.0/tr1/unordered_map" 2 3
# 3 "data/40.cpp" 2
# 11 "data/40.cpp"

# 11 "data/40.cpp"
using namespace std;

char s[400005];
long long p[400005];
long long n;

void manacher(){
 long long mx=0,id=0;
 for(long long i=1;i<n;i++){
  p[i]=(mx>i)?min(mx-i,p[2*id-i]):1;
  while(s[i-p[i]]==s[i+p[i]]) p[i]++;
  if(i+p[i]>mx){
   mx=i+p[i];
   id=i;
  }
 }
}

long long dp[400005];

void kmp(){
 dp[1]=0;
 for(long long i=2;i<2*n-1;i++){
  long long j=dp[i-1];
  while(j&&s[j+1]!=s[i]) j=dp[j];
  if(s[j+1]==s[i]) j++;
  dp[i]=j;
 }
}
string s2;
signed main(){
 char c;
 s[n++]='$';
 while(cin>>c){
  s[n++]='#';
  s[n++]=c;
  s2.push_back(c);
 }
 s[n++]='#';

 manacher();



 for(long long i=1;i<n;i++){
  s[n+i-1]=s[i];
 }
 reverse(s+1,s+n);

 kmp();



 for(long long i=n+1;i<2*n;i++){
  dp[i]=max(dp[i],dp[i-1]);
  dp[i-n]=0;
 }



 long long Max=0,mid=0,len=0;
 for(long long i=n;i<2*n-1;i++){
  if(s[i]!='#'){
   long long t=p[i-n+1]-1+min(dp[i-p[i-n+1]]/2*2,2*n-1-i-p[i-n+1]);
   if(t>Max){
    Max=t;
    mid=i-n+1;
    len=min(dp[i-p[i-n+1]]/2*2,2*n-1-i-p[i-n+1]);
   }

  }
 }

 string s1;
 if(len)cout<<3<<endl;
 else cout<<1<<endl;
 if(len){
  for(long long i=2*n-2;i>=2*n-1-len;i--){
   if(s[i]!='#') s1.push_back(s[i]);
  }
  cout<<s2.find(s1)+1<<' '<<len/2<<endl;
 }
 cout<<mid/2-p[mid]/2+1<<' '<<p[mid]-1<<endl;
 if(len){
  cout<<(n-len)/2<<' '<<len/2<<endl;
 }
    return 0;
}

using namespace std;
const int maxn=1e5+10;
string buf;
string s,t;
int dp[maxn],pre[maxn],rad[maxn];
pair<int,int> premax[maxn];
void failure()
{
 int n=t.length();
 dp[0]=-1;
 for(int i=1;i<=n;i++)
 {
  int j;
  for(j=dp[i-1];j>=0;j=dp[j])
   if(t[j]==t[i-1])break;
  dp[i]=j+1;
 }
}
void kmp()
{
 int n=s.length();
 int j=0;
 for(int i=0;i<n;i++)
 {
  while(j==t.length()||(j>=0&&s[i]!=t[j]))j=dp[j];
  j++;
  pre[i+1]=j;
 }
}
void manacher()
{
 int n=s.length(),L=-1,R=-1;
 for(int i=0;i<n;i++)
 {
  int tmp=0;
  if(i<=R)tmp=min(R-i,rad[L+R-i]);
  while(i-tmp-1>=0&&i+tmp+1<n&&s[i-tmp-1]==s[i+tmp+1])tmp++;
  rad[i]=tmp;
  if(i+tmp>R)
  {
   R=i+tmp;
   L=i-tmp;
  }
 }
}
int main()
{
 cin.sync_with_stdio(false);
 cin.tie(0);
 cout.sync_with_stdio(false);
 cout.tie(0);

 cin>>buf;
 s=t=buf;
 int n=s.length();
 reverse(t.begin(),t.end());
 failure();
 kmp();
 manacher();
 premax[0]=make_pair(0,0);
 for(int i=1;i<=n;i++)
 {
  premax[i]=premax[i-1];
  if(pre[i]>premax[i].second)premax[i]=make_pair(i,pre[i]);
 }
 int ans=0;
 vector<pair<int,int> > ansv;
 for(int i=0;i<n;i++)
 {
  int L=i-rad[i],R=i+1+rad[i];
  int len=min(premax[L].second,n-R);
  int tmp=R-L+2*len;
  if(tmp>ans)
  {
   ans=tmp;
   ansv.clear();
   ansv.push_back(make_pair(premax[L].first-premax[L].second,len));
   ansv.push_back(make_pair(L,R-L));
   ansv.push_back(make_pair(n-len,len));
  }
 }
 cout<<((ansv[0].second==0)?1:3)<<endl;
 for(int i=0;i<3;i++)if(ansv[i].second>0)
  cout<<ansv[i].first+1<<" "<<ansv[i].second<<endl;
 return 0;
}

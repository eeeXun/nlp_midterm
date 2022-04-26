# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/226.cpp" 2




# 8 "data/226.cpp"
using namespace std;
int n,ans;
char s[100100],rev_s[100100];
int next[100100],f[100100],pos[100100];
pair<int,int> intervals[100100];
int log_2[100100],a[100100][17],_ans[100100];
void KMP()
{
 int i,fix=0;
 for(i=2;i<=n;i++)
 {
  while( fix && rev_s[fix+1]!=rev_s[i] )
   fix=next[fix];
  if( rev_s[fix+1]==rev_s[i] )
   ++fix;
  next[i]=fix;
 }
 fix=0;
 for(i=1;i<=n;i++)
 {
  while( fix && rev_s[fix+1]!=s[i] )
   fix=next[fix];
  if( rev_s[fix+1]==s[i] )
   ++fix;
  if( i+fix>=n )
   return ;
  if(!pos[fix])
  {
   pos[fix]=i;
   intervals[fix]=make_pair(i+1,n-fix);
  }
 }
}
void Manacher()
{
 int i,id=1,mx=1;
 s[0]='$';
 for(i=1;i<=n;i++)
 {
  f[i]=min(mx-i+1,f[id+id-i]);
  while(s[i+f[i]]==s[i-f[i]])
   ++f[i];
  if(i+f[i]-1>mx)
   mx=i+f[i]-1,id=i;
 }
}
int Get_Max(int x,int y)
{
 int len=log_2[y-x+1];
 return max(a[x][len],a[y-(1<<len)+1][len]);
}
int Bisection(int x,int y)
{
 int l=1,r=y-x+2>>1;
 while(l+1<r)
 {
  int mid=l+r>>1;
  if( Get_Max(x+mid-1,y-mid+1)>=mid )
   l=mid;
  else
   r=mid;
 }
 return Get_Max(x+r-1,y-r+1)>=r?r:l;
}
int main()
{
 int i,j;
 scanf("%s",s+1);n=strlen(s+1);
 for(i=1;i<=n;i++)
  rev_s[i]=s[n-i+1];
 KMP();
 Manacher();
 pos[0]=1;intervals[0]=make_pair(1,n);
 for(i=2;i<=n;i++)
  log_2[i]=log_2[i>>1]+1;
 for(i=1;i<=n;i++)
  a[i][0]=f[i];
 for(j=1;j<=log_2[n];j++)
  for(i=1;i+(1<<j)-1<=n;i++)
   a[i][j]=max(a[i][j-1],a[i+(1<<j-1)][j-1]);
 for(i=0;pos[i];i++)
 {
  _ans[i]=2*Bisection(intervals[i].first,intervals[i].second)-1;
  if(i*2+_ans[i]>ans*2+_ans[ans])
   ans=i;
 }
 if(ans==0)
 {
  cout<<1<<endl;
  for(i=1;i<=n;i++)
   if(f[i]*2-1==_ans[0])
   {
    cout<<i-f[i]+1<<' '<<_ans[0]<<endl;
    return 0;
   }
 }
 else
 {
  cout<<3<<endl;
  cout<<pos[ans]-ans+1<<' '<<ans<<endl;
  int l=intervals[ans].first,r=intervals[ans].second;
  for(i=l;i<=r;i++)
   if( min(min(i-l,r-i)+1,f[i])*2-1==_ans[ans] )
   {
    cout<<i-(_ans[ans]>>1)<<' '<<_ans[ans]<<endl;
    break;
   }
  cout<<n-ans+1<<' '<<ans<<endl;
 }
 return 0;
}

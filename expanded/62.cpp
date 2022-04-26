



# 7 "data/62.cpp"
using namespace std;
const int N=1e5+5;
int n,len[N],h[N],cnt=1;
struct HASH{
 long long mod,ch;
 long long f[2][N],pw[N];
 void init(){pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*ch%mod;}
 void build(int t,string s){f[t][0]=s[0]-'a'+1;for(int i=1;i<n;i++){f[t][i]=f[t][i-1]*ch%mod+s[i]-'a'+1;f[t][i]%=mod;}}
 inline int gethash(int l,int r,int t){return (f[t][r]-(l==0?0:f[t][l-1]*pw[r-l+1]%mod)+mod)%mod;}
 inline bool same(int l,int r,int t,int L,int R,int T){return gethash(l,r,t)==gethash(L,R,T);}
}H;
string s;int mx;vector<int> ans[2];
int main()
{
 srand(time(0));
 cin>>s;n=s.size();
 H.mod=1e9+7;H.ch=113;
 H.init();string t=s;
 reverse(t.begin(),t.end());
 H.build(0,s);H.build(1,t);
 for(int i=0;i<n;i++)
 {
  int l=1,r=n-i;
  while(l<=r)
  {
   int mid=(l+r)>>1;
   if(H.same(i,i+mid-1,0,0,mid-1,1))
    l=mid+1;
   else
    r=mid-1;
  }l--;
  len[i]=l;
 }
 for(int i=0;i<n;i++){while(cnt<=len[i])h[cnt]=i+cnt-1,cnt++;cnt=max(len[i]+1,cnt);}
 while(cnt<=n)h[cnt++]=-1;
 for(int i=0;i<n;i++)
 {
  int l=1,r=min(n-i,i+1);
  while(l<=r)
  {
   int mid=(l+r)>>1;
   int L=i-mid+1,R=i+mid-1;
   if(H.same(L,R,0,n-R-1,n-L-1,1))
    l=mid+1;
   else
    r=mid-1;
  }l--;
  int L=i-l+1,R=i+l-1,j=l;
  r=n-R-1,l=1;
  while(l<=r)
  {
   int mid=(l+r)>>1;
   if(h[mid]!=-1&&h[mid]<L)
    l=mid+1;
   else
    r=mid-1;
  }l--;
  if(j*2-1+l*2>mx)
  {
   mx=j*2-1+l*2;
   ans[0].clear();ans[1].clear();
   if(l)ans[0].push_back(h[l]-l+1),ans[1].push_back(l);
   ans[0].push_back(L),ans[1].push_back(j*2-1);
   if(l)ans[0].push_back(n-l),ans[1].push_back(l);
  }
 }
 cout<<ans[0].size()<<"\n";
 for(int i=0;i<ans[0].size();i++)cout<<ans[0][i]+1<<" "<<ans[1][i]<<"\n";
 return 0;
}

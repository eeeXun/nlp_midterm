# 3 "data/21.cpp"
using namespace std;





typedef long long ll;
const ll INF=1<<28;
const ll LINF=1ll<<61;
typedef unsigned long long ull;
char s[100111],ts[200111];
int plen[200111];
int n,k;
void manacher(int n,char s[],int ans[])
{
 int mx=0,id=0;
 for(int i=1;i<=n;i++)
 {
  if(mx>=i)ans[i]=min(ans[2*id-i],mx-i);
  else ans[i]=0;
  while(i-ans[i]>1&&i+ans[i]<n&&s[i-ans[i]-1]==s[i+ans[i]+1])ans[i]++;
  if(i+ans[i]>mx)
  {
   mx=i+ans[i];
   id=i;
  }
 }
}
ull hs[100111],pw[100111];
inline ull geths(int x,int len){return hs[x+len-1]-hs[x-1]*pw[len];}
int len[100111],pos[100111];
int main()
{
 pw[0]=1;
 for(int i=1;i<100010;i++)pw[i]=pw[i-1]*1221;
 scanf("%s",s+1);
 n=strlen(s+1);
 for(int i=1;i<=n*2;i+=2)ts[i]='#',ts[i+1]=s[(i+1)/2];
 ts[n*2+1]='#';
 manacher(n*2+1,ts,plen);
 for(int i=1;i<=n;i++)hs[i]=hs[i-1]*1221+s[i];
 int it=0;
 ull ths=0;
 for(int i=1;i<=n;i++)
 {
  ths=ths*1221+s[n-i+1];
  while(it+i<=n&&geths(it+1,i)!=ths)it++;
  if(it+i<=n)len[it+i]=i,pos[it+i]=it+i;
 }
 for(int i=1;i<=n;i++)len[i]=max(len[i-1],len[i]),pos[i]=max(pos[i-1],pos[i]);
 int ans=0,tmp=0;
 for(int i=2;i<=2*n;i+=2)
 {
  int st=(i-plen[i])/2+1,ed=(i+plen[i])/2;
  if(st>ed)continue;
  int curans=min(len[st-1],n-ed)*2+plen[i];
  if(curans>ans)
  {
   ans=curans;
   tmp=i;
  }
 }
 int st=(tmp-plen[tmp])/2+1,ed=(tmp+plen[tmp])/2;
 int tlen=min(len[st-1],n-ed);
 if(tlen==0)
 {
  cout<<1<<endl;
  cout<<st<<" "<<plen[tmp]<<endl;
 }
 else
 {
  cout<<3<<endl;
  cout<<pos[st-1]-tlen+1<<" "<<tlen<<endl;
  cout<<st<<" "<<plen[tmp]<<endl;
  cout<<n-tlen+1<<" "<<tlen<<endl;
 }
 return 0;
}


# 3 "data/330.cpp"
using namespace std;




int sa[300008],rak[300008],cal[300008],tp[300008],height[300008];
int s[300008];
int l1;int n;
char buf[300008];int m;
void radixsort()
{
 for(int i=1;i<=m;i++) cal[i]=0;
 for(int i=1;i<=n;i++) cal[rak[i]]++;
 for(int i=1;i<=m;i++) cal[i]+=cal[i-1];
 for(int i=n;i>=1;i--) sa[cal[rak[tp[i]]]--]=tp[i];
}
int lg2[300008];
int to[22][300008];
void getsa()
{
 for(int i=1;i<=n;i++) rak[i]=s[i],tp[i]=i;
 m=8000;
 radixsort();
 for(int w=1;w<n;w<<=1)
 {
  int p=0;
  for(int i=n-w+1;i<=n;i++) tp[++p]=i;
  for(int i=1;i<=n;i++) if(sa[i]>w) tp[++p]=sa[i]-w;
  radixsort();
  swap(rak,tp);
  rak[sa[1]]=p=1;
  for(int i=2;i<=n;i++)
  {
   if(tp[sa[i]]==tp[sa[i-1]] and tp[sa[i]+w]==tp[sa[i-1]+w]) p--;
   rak[sa[i]]=++p;
  }
  m=p;
 }
 int k=0;
 memset(to,0x3f,sizeof(to));
 for(int i=1;i<=n;i++)
 {
  if(rak[i]==1) continue;
  if(k) k--;
  int j=sa[rak[i]-1];
  while(i+k<=n and j+k<=n and s[i+k]==s[j+k]) k++;
  height[rak[i]]=k;
  to[0][rak[i]]=k;
 }
 for(int i=1;i<=21;i++)
  for(int j=1;j<=n;j++)
  if(j+(1<<i-1)<300008)
   to[i][j]=min(to[i-1][j],to[i-1][j+(1<<(i-1))]);
}
int askh(int x,int y)
{
 int l=y-x+1;l=lg2[l];
 return min(to[l][x],to[l][y-(1<<l)+1]);
}
int lcp(int x,int y)
{
 if(x==y) return 1e9;
 if(x>y) swap(x,y);
 return askh(x+1,y);
}
int man[300008];
void getman()
{
 int l=1;man[1]=0;
 for(int i=2;i<=n;i++)
 {
  int ref=l*2-i;
  if(i<=l+man[l] and i+man[ref]<l+man[l])
  {
   man[i]=man[ref];
   continue;
  }
  int z=l+man[l]-i;if(z<0) z=0;
  while(i-z>=1 and i+z<=n and s[i+z]==s[i-z]) z++;
  man[i]=z-1;
  l=i;
 }
}
int stretch[300008];
int ans;int pa,pb,pc;
vector<int> v[300008];

struct binarysearch{
 int a[300008];
 void upd(int c[])
 {
  for(int i=1;i<=n;i++) a[i]=c[i];
 }
 int ask(int l,int r,int y)
 {
  if(a[l]>y or l>r) return -1;
  int res=0;
  while(l<=r)
  {
   int mid=(l+r)/2;
   if(a[mid]<y)
    res=mid,l=mid+1;
   else r=mid-1;
  }
  return res;
 }
}noel;
int c[300008];
int back[300008];
int can(int &x,int y)
{
 if(x<y) x=y;
 else return 0;
 return 1;
}
int main()
{
 int p=2;
 for(int i=1;i<300008;i++)
 {
  lg2[i]=lg2[i-1];
  if(i==p) lg2[i]++,p=p+p;
 }
 scanf("%s",buf+1);
 int len=strlen(buf+1);
 for(int i=1;i<=len;i++) s[++n]=buf[i];getman();
 s[++n]=1000;
 for(int i=len;i>=1;i--) s[++n]=buf[i];
 getsa();
 int j=1;
 for(int i=1;i<=n;i++)
 {
  while(j<=len and lcp(rak[j],rak[len+2])<i)
  {
   j++;
  }
  if(j>len or j+i-1>=len-i+1) break;
  stretch[i]=j;back[j]=i;





 }
 n=len;
 for(int i=1;i<=n;i++)
 {
  v[man[i]+i].push_back(i-man[i]);
  if(can(ans,man[i]*2+1))
  {
   pa=pc=0;
   pb=i-man[i];
  }
 }
 for(int i=1;i<=n;i++) if(stretch[i]) c[i]=stretch[i]+i-1;else c[i]=1e9;
 noel.upd(c);int maxi=n;
 for(int i=n;i>=1;i--)
 {
  for(int j=0;j<v[i].size();j++)
  {
   int x=v[i][j];maxi=min(maxi,(i+x)/2);
   int d=noel.ask(1,n-i,x);
   if(d==-1) continue;
   if(can(ans,d*2+i-x+1))
   {
    pa=stretch[d];
    pb=x;
    pc=n-d+1;
   }
  }
  int lb=maxi*2-(i-1);
  if(c[i]<lb)
   if(can(ans,i*2+(i-1)-lb+1))
   {
    pa=stretch[i];
    pb=lb;
    pc=n-i+1;
   }
 }

 for(int i=1;i<=n;i++)
  v[-man[i]+i].push_back(i-man[i]);
 for(int i=1;i<=n;i++) if(back[i]) c[i]=back[i];else c[i]=0;
 noel.upd(c);maxi=0;
 for(int i=1;i<=n;i++)
 {
  for(int j=0;j<v[i].size();j++)
  {
   int x=v[i][j];maxi=max(maxi,(i+x)/2);
  }
  int lb=maxi*2-(i-1);
  if(c[i]>lb)
   if(can(ans,i*2+(i-1)-lb+1))
   {
    pa=i;
    pb=lb;
    pc=n-back[i]+1;
   }
 }
 int k=3;
 if(pa) k--;if(pb) k--;if(pc) k--;
 cout<<3-k<<"\n";
 if(pa) cout<<pa<<" "<<n-pc+1<<"\n";
 if(pb) cout<<pb<<" "<<ans-((pc==0)?(0):(n-pc+1)*2)<<"\n";
 if(pc) cout<<pc<<" "<<n-pc+1<<"\n";
 return 0;
}

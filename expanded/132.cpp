


int getint() {
 int ret=0,flag=1;
 char c=getchar();
 while(c<'0'||c>'9') {
  if(c=='-')flag=-1;
  c=getchar();
 }
 while(c<='9'&&c>='0') {
  ret=(ret<<3)+(ret<<1)+c-'0';
  c=getchar();
 }
 return ret*flag;
}
void pc(char x) {
 if(p2>=1000000)fwrite(wb,1,1000000,
# 27 "data/132.cpp" 3 4
                                   stdout
# 27 "data/132.cpp"
                                         ),p2=0;
 wb[p2++]=x;
}
void wrt(int x) {
 if(x<0)pc('-'),x=-x;
 int c[24]= {0};
 if(!x)return pc('0'),void();
 while(x)c[++c[0]]=x%10,x/=10;
 while(c[0])pc(c[c[0]--]+'0');
}
int n,ans;
int p[100005];
void manacher(char *c) {
 int mx=0,pl=0,len=strlen(c+1);
 for(int i=1; i<=len; i++) {
  if(mx>=i)p[i]=min(p[pl*2-i],mx-i);
  else p[i]=0;
  while(c[i-p[i]]==c[i+p[i]])++p[i];
  if(i+p[i]>mx)mx=i+p[i],pl=i;
 }
}
char c[100005];
int kmp[100005];
long long h1[100005],h2[100005];
long long pw[100005];
int Hash(int l,int r,bool flg) {
 return flg?(h2[l]-h2[r+1]*pw[r-l+1]%998244353 +998244353)%998244353:(h1[r]-h1[l-1]*pw[r-l+1]%998244353 +998244353)%998244353;
}
int a[100005],g[100005],id[100005],mx[100005];
int pl1,pl2,pl3,l1,l2,l3;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
int main() {
 pw[0]=1;
 for(int i=1; i<=100000; i++)pw[i]=pw[i-1]*233%998244353;
 c[0]='#';
 scanf("%s",c+1);
 manacher(c);
 n=strlen(c+1);
 for(int i=1; i<=n; i++)h1[i]=(h1[i-1]*233 +c[i])%998244353;
 for(int i=n; i>=1; i--)h2[i]=(h2[i+1]*233 +c[i])%998244353;
 for(int i=1; i<=n; i++) {
  int l=0,r=n-i+1;
  while(l<=r) {
   int mid=(l+r)>>1;
   if(Hash(i,i+mid,0)==Hash(n-mid,n,1))l=mid+1;
   else r=mid-1;
  }
  a[i]=l-1;
 }
 for(int i=1; i<=n; i++) {
  while(!q.empty()&&q.top().first+q.top().second<i)q.pop();
  if(a[i]>=0)q.push(make_pair(i,a[i]));
  if(!q.empty())g[i]=i-q.top().first+1,id[i]=i;
  if(g[i-1]>g[i])g[i]=g[i-1],id[i]=id[i-1];
 }
 for(int i=1; i<=n; i++) {
  if(p[i]*2-1+min(g[i-p[i]],n-(i+p[i]-1))*2>ans) {
   ans=p[i]*2-1+min(g[i-p[i]],n-(i+p[i]-1))*2;
   pl1=id[i-p[i]]-g[i-p[i]]+1,l1=min(g[i-p[i]],n-(i+p[i]-1));
   pl2=i-p[i]+1,l2=p[i]*2-1;
   pl3=n-l1+1,l3=min(g[i-p[i]],n-(i+p[i]-1));
  }
 }
 if(l1||l3)ans=3;
 else ans=1;
 wrt(ans),pc('\n');
 if(l1)wrt(pl1),pc(' '),wrt(l1),pc('\n');
 wrt(pl2),pc(' '),wrt(l2),pc('\n');
 if(l3)wrt(pl3),pc(' '),wrt(l3),pc('\n');
 fwrite(wb,1,p2,
# 96 "data/132.cpp" 3 4
               stdout
# 96 "data/132.cpp"
                     );
 return 0;
}

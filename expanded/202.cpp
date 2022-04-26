# 5 "data/202.cpp" 2

# 5 "data/202.cpp"
using namespace std;
const int N=400005,SZ=26;
int n;
char s[N];

struct GSAM
{
 int S,lst,tot;
 int ch[N][SZ],fa[N],len[N];
 GSAM (){S=lst=tot=1;}
 void cpy(int u,int v){memcpy(ch[v],ch[u],SZ<<2);fa[v]=fa[u];}
 void ins(int c)
 {
  int u=lst;
  if(ch[u][c])
  {
   int v=ch[u][c];
   if(len[v]==len[u]+1){lst=v;return;}
   int x=++tot;
   cpy(v,x);len[x]=len[u]+1;
   for(;u&&ch[u][c]==v;u=fa[u])
    ch[u][c]=x;
   lst=fa[v]=x;
   return;
  }
  int cur=++tot;
  len[cur]=len[lst]+1;lst=cur;
  for(;u&&!ch[u][c];u=fa[u])
   ch[u][c]=cur;
  if(!u){fa[cur]=S;return;}
  int v=ch[u][c];
  if(len[v]==len[u]+1){fa[cur]=v;return;}
  int x=++tot;
  cpy(v,x);len[x]=len[u]+1;
  for(;u&&ch[u][c]==v;u=fa[u])
   ch[u][c]=x;
  fa[cur]=fa[v]=x;
 }
 int substring(){int res=0;for(int i=1;i<=tot;i++)res+=len[i]-len[fa[i]];return res;}
}sm;
int pc;
int col[N],pos[N][2],cnt[N],id[N];
struct ps
{
 int l,r,w;
 ps (int L=0,int R=0,int W=0){l=L;r=R;w=W;}
 bool operator < (const ps &x)const{return r<x.r;}
}p[N];
void calc()
{
 for(int i=1;i<=sm.tot;i++)
  if(!pos[i][0])pos[i][0]=N;
 for(int i=1;i<=sm.tot;i++)cnt[sm.len[i]]++;
 for(int i=n;i>=0;i--)cnt[i]+=cnt[i+1];
 for(int i=1;i<=sm.tot;i++)id[cnt[sm.len[i]]--]=i;
 for(int i=1;i<=sm.tot;i++)
 {
  int u=id[i],v=sm.fa[u];
  if(col[u]==3&&sm.len[u]&&pos[u][1]+sm.len[u]-1==n)p[++pc]=(ps){pos[u][0],pos[u][1],sm.len[u]};
  col[v]|=col[u];pos[v][0]=min(pos[v][0],pos[u][0]);pos[v][1]=max(pos[v][1],pos[u][1]);
 }
}




int pr[N];
struct password
{
 pair<int,int> tp,tm,ts;
 password (pair<int,int> TP=pair<int,int>(0,0),pair<int,int> TM=pair<int,int>(0,0),pair<int,int> TS=pair<int,int>(0,0)){tp=TP;tm=TM;ts=TS;}
 bool operator < (const password &x)const{return tp.second+tm.second+ts.second<x.tp.second+x.tm.second+x.ts.second;}
}ans;
struct query
{
 int l,r,id;
 bool operator < (const query &x)const{return r<x.r;}
}q[N];
struct BIT
{
 ps c[N];
 void upd(int x,const ps &y){for(;x<=n;x+=x&(-x))if(y.w>c[x].w)c[x]=y;}
 ps qmax(int x)const{ps y;for(;x;x-=x&(-x))if(c[x].w>y.w)y=c[x];return y;}
}bt;
void manacher()
{
 for(int i=1,j=0;i<=n;i++)
 {
  int k=j+pr[j]-1>=i?min(pr[2*j-i],j+pr[j]-i):0;
  while(i+k<=n&&i-k>=1&&s[i+k]==s[i-k])k++;
  if(i+(pr[i]=k)>j+pr[j])j=i;
  q[i]=(query){i-pr[i],i+pr[i],i};
 }
 sort(p+1,p+pc+1);sort(q+1,q+n+1);
 for(int i=n,j=pc;i>=1;i--)
 {
  while(j&&p[j].r>=q[i].r)bt.upd(p[j].l,p[j]),j--;
  int x=q[i].id;
  ps resp=bt.qmax(q[i].l);
  password res(pair<int,int>(resp.l-resp.w+1,resp.w),pair<int,int>(x-pr[x]+1,2*pr[x]-1),pair<int,int>(resp.r,resp.w));
  if(ans<res)ans=res;
 }
}

int main()
{
 scanf("%s",s+1);n=strlen(s+1);
 for(int i=1;i<=n;i++)sm.ins(s[i]-'a'),col[sm.lst]|=1,pos[sm.lst][0]=i;
 sm.lst=sm.S;
 for(int i=n;i>=1;i--)sm.ins(s[i]-'a'),col[sm.lst]|=2,pos[sm.lst][1]=i;

 calc();
 manacher();
 printf("%d\n",(ans.tp.second>0)+1+(ans.ts.second>0));
 if(ans.tp.second)printf("%d %d\n",ans.tp.first,ans.tp.second);
 printf("%d %d\n",ans.tm.first,ans.tm.second);
 if(ans.ts.second)printf("%d %d\n",ans.ts.first,ans.ts.second);
 return 0;
}

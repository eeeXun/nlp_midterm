# 5 "data/853.cpp" 2

# 5 "data/853.cpp"
using namespace std;

const int MAXN=2e5+5;
const int INF=0x3f3f3f3f;
char s[MAXN];
int n,r[MAXN],f[MAXN],mn[MAXN];

inline int read()
{
 int x=0;char ch=getchar();
 while(!isdigit(ch)) ch=getchar();
 while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
 return x;
}

template <typename T1,typename T2>
inline void Max(T1 &x,T2 y)
{
 if(x<y) x=y;
}
template <typename T1,typename T2>
inline void Min(T1 &x,T2 y)
{
 if(x>y) x=y;
}

namespace Suffix_Automaton
{
 int c[MAXN],ord[MAXN];
 int lst=1,cnt=1,len[MAXN];
 int fa[MAXN],ch[MAXN][26];

 inline void insert(int c,int pos)
 {
  int p=lst,np=lst=++cnt;
  len[np]=len[p]+1,mn[lst]=pos;
  while(p&&!ch[p][c]) ch[p][c]=np,p=fa[p];
  if(!p) return fa[np]=1,void(); int q=ch[p][c];
  if(len[q]==len[p]+1) return fa[np]=q,void();
  int nq=++cnt; fa[nq]=fa[q],fa[q]=fa[np]=nq;
  len[nq]=len[p]+1,memcpy(ch[nq],ch[q],sizeof(ch[nq]));
  while(ch[p][c]==q) ch[p][c]=nq,p=fa[p];
 }

 inline void insert()
 {
  for(int i=1;i<=n;i++)
   insert(s[i]-'a',i);
 }

 inline void prepare()
 {
  for(int i=1;i<=cnt;i++) c[len[i]]++;
  for(int i=1;i<=n;i++) c[i]+=c[i-1];
  for(int i=cnt;i;i--) ord[c[len[i]]--]=i;
  for(int i=cnt;i;i--) Min(mn[fa[ord[i]]],mn[ord[i]]);
 }

 inline void solve()
 {
  int p=1;
  for(int i=n;i;i--)
  {
   if(!ch[p][s[i]-'a']) break;
   p=ch[p][s[i]-'a'],Min(f[mn[p]],i);
  }
  for(int i=1;i<=n;i++) Min(f[i],f[i-1]);
 }
}

namespace Manacher
{
 char ss[MAXN]; int len;

 inline void change()
 {
  len=(n<<1)+1;
  for(int i=n;i;i--)
   ss[i<<1]=s[i];
  for(int i=1;i<=len;i+=2)
   ss[i]='#';
 }

 inline void solve()
 {
  change(); int mid=1;
  for(int i=1;i<=len;i++)
  {
   r[i]=min(r[mid*2-i],r[mid]+mid-i);
   while(i+r[i]<=len&&i-r[i]>=1&&ss[i+r[i]]==ss[i-r[i]])
    r[i]++;
   if(r[i]+i>r[mid]+mid) mid=i;
  }
  for(int i=1;i<=n;i++) r[i]=r[i<<1]-1;
 }
}

inline void solve()
{
 memset(mn,0x3f,sizeof(mn));
 memset(f,0x3f,sizeof(f));
 Suffix_Automaton::insert();
 Suffix_Automaton::prepare();
 Suffix_Automaton::solve();
 Manacher::solve();
 int ans=0,id1,id2,id3;







 for(int i=1;i<=n;i++)
 {
  int rr=r[i]>>1;
  int x=max(f[i-rr-1],i+rr+1);
  x=max(0,n-x+1)*2+r[i];
  if(x>ans) ans=x,id2=i;
 }
 int rr=r[id2]>>1; id3=max(f[id2-rr-1],id2+rr+1);
 for(int i=n;i;i--) if(f[i]<=id3) id1=i;
 if(id3==INF) printf("1\n%d %d\n",id2-rr,r[id2]);
 else
 {
  puts("3");
  printf("%d %d\n",id1-n+id3,n-id3+1);
  printf("%d %d\n",id2-rr,r[id2]);
  printf("%d %d\n",id3,n-id3+1);
 }
}

int main()
{
 scanf("%s",s+1);
 n=strlen(s+1);
 return solve(),0;
}

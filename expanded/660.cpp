      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/660.cpp" 2





# 6 "data/660.cpp"
using namespace std;

char s[200048];int len;
char ss[200048];int len2;
int fail[200048];
int maxlen[200048];
int RL[200048],tmp[100048];
int p[100048],f[100048];
# 33 "data/660.cpp"
struct node
{
 int next[30];
 int pos,fail;
 inline void init()
 {
  memset(next,0,sizeof(next));
  pos=fail=0;
 }
}trie[200048];int tot=1;

inline void Insert()
{
 int i,w,cur=1;
 for (i=1;i<=len2;i++)
 {
  w=ss[i]-'a'+1;

  if (!trie[cur].next[w])
  {
   trie[cur].next[w]=++tot;
   trie[tot].init();
  }
  cur=trie[cur].next[w];
  trie[cur].pos=i;
 }
}

queue<int> q;
inline void construct_fail()
{
 int i,cur;q.push(1);
 while (!q.empty())
 {
  cur=q.front();q.pop();
  for (i=1;i<=27;i++)
   if (trie[cur].next[i])
   {
    int tmp=trie[cur].fail;
    while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
    trie[trie[cur].next[i]].fail=(tmp?trie[tmp].next[i]:1);
    q.push(trie[cur].next[i]);
   }
 }
}

inline void getRL()
{
 memset(ss,'\0',sizeof(ss));
 int i,slen=0;
 for (i=1;i<=len;i++)
 {
  ss[++slen]='#';
  ss[++slen]=s[i];
 }
 ss[++slen]='#';
 int maxright=0,pos=0;
 for (i=1;i<=slen;i++)
 {
  if (i<maxright) RL[i]=min(maxright-i,RL[2*pos-i]); else RL[i]=1;
  while (i+RL[i]<=slen && i-RL[i]>=1 && ss[i+RL[i]]==ss[i-RL[i]]) RL[i]++;
  if (i+RL[i]-1>maxright) maxright=i+RL[i]-1,pos=i;
 }
 for (i=1;i<=len;i++) tmp[i]=RL[i*2];
 for (i=1;i<=len;i++) RL[i]=tmp[i]-1;
}

int main ()
{
 int i;
 scanf("%s",s+1);len=strlen(s+1);
 for (i=1;i<=len;i++) ss[i]=s[len-i+1];
 len2=len;ss[++len2]='z'+1;
 for (i=len2+1;i<=len2+len;i++) ss[i]=s[i-len2];
 len2+=len;
 Insert();construct_fail();
 for (i=2;i<=tot;i++) fail[trie[i].pos]=trie[trie[i].fail].pos;
 for (i=len+2;i<=len2;i++) maxlen[i-len-1-fail[i]+1]=max(maxlen[i-len-1-fail[i]+1],fail[i]);
 getRL();
 memset(p,0,sizeof(p));
 for (i=1;i<=len;i++)
 {
  int cp=maxlen[i];
  while (cp && !p[cp]) p[cp--]=i;
 }
 memset(f,0,sizeof(f));
 for (i=len;i;i--)
 {
  if (!p[i]) continue;
  int cp=p[i]+i;
  while (cp<=len && !f[cp]) f[cp++]=i;
 }
 pair<int,int> ans1=make_pair(-1,-1),ans2=make_pair(-1,-1),ans3=make_pair(-1,-1);int anslen=0,curans;
 for (i=1;i<=len;i++)
 {
  curans=RL[i];
  if (curans>anslen)
  {
   anslen=curans;
   ans1=ans3=make_pair(-1,-1);ans2=make_pair(i-RL[i]/2,RL[i]);
  }
  int left=i-RL[i]/2,right=i+RL[i]/2;
  int add=min(f[left],len-right);
  if (add && curans+add*2>anslen)
  {
   anslen=curans+add*2;
   ans1=make_pair(p[add],add);ans2=make_pair(i-RL[i]/2,RL[i]);ans3=make_pair(len-add+1,add);
  }
 }
 if (ans1.first==-1)
 {
  printf("1\n");
  printf("%d %d\n",ans2.first,ans2.second);
 }
 else
 {
  printf("3\n");
  printf("%d %d\n%d %d\n%d %d\n",ans1.first,ans1.second,ans2.first,ans2.second,ans3.first,ans3.second);
 }
 return 0;
}

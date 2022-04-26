# 1374 "/usr/include/c++/11.2.0/bits/specfun.h" 3
  template<typename _Tpa, typename _Tpb, typename _Tpc, typename _Tp>
    inline typename __gnu_cxx::__promote_4<_Tpa, _Tpb, _Tpc, _Tp>::__type
    hyperg(_Tpa __a, _Tpb __b, _Tpc __c, _Tp __x)
    {
      typedef typename __gnu_cxx::__promote_4<_Tpa, _Tpb, _Tpc, _Tp>
  ::__type __type;
      return std::__detail::__hyperg<__type>(__a, __b, __c, __x);
    }



}


#pragma GCC visibility pop
# 1928 "/usr/include/c++/11.2.0/cmath" 2 3


}
# 17 "data/31.cpp" 2
# 26 "data/31.cpp"

# 26 "data/31.cpp"
using namespace std;

const int MOD=1e9+7;
const long long LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int len,slen;
char s[300048],ss[300048];
int RL[300048],maxright,pos,maxlen[300048],mlen[300048],minpos[300048];
int fail[300048];
int f[300048];

void getfail()
{
 int k=-1,j=0;
 fail[0]=-1;
 while (j<=slen)
 {
  if (k==-1 || ss[j+1]==ss[k+1])
   fail[++j]=++k;
  else
   k=fail[k];
 }
}

void getRL()
{
 memset(ss,'\0',sizeof(ss));
 int i,cur=1;
 for (i=1;i<=len;i++)
 {
  ss[cur++]='#';
  ss[cur++]=s[i];
 }
 ss[cur]='#';slen=cur;
 maxright=pos=0;
 for (i=1;i<=slen;i++)
 {
  if (i<maxright)
   RL[i]=min(maxright-i,RL[2*pos-i]);
  else
   RL[i]=1;
  while (i-RL[i]>=1 && i+RL[i]<=slen && ss[i-RL[i]]==ss[i+RL[i]]) RL[i]++;
  if (i+RL[i]>maxright)
  {
   maxright=i+RL[i];
   pos=i;
  }
 }
}

int main ()
{


 int i,j;
 scanf("%s",s+1);len=strlen(s+1);
 for (i=1;i<=len;i++) ss[i]=s[len-i+1];
 ss[len+1]='$';
 for (i=len+2;i<=len+2+len-1;i++) ss[i]=s[i-len-1];
 slen=strlen(ss+1);
 getfail();
 for (i=len+2;i<=slen;i++) mlen[i-len-1-fail[i]+1]=max(mlen[i-len-1-fail[i]+1],fail[i]);
 for (i=1;i<=len;i++)
  for (j=mlen[i];j>=1 && !minpos[j];j--)
   minpos[j]=i;
 getRL();

 for (i=1;i<=slen;i++) if (ss[i]!='#') maxlen[i/2]=RL[i]-1;

 for (i=len;i>=1;i--)
  if (minpos[i])
   for (j=minpos[i]+i;j<=len && !f[j];j++)
    f[j]=i;

 pair<int,int> ans1=make_pair(-1,-1),ans2=make_pair(-1,-1),ans3=make_pair(-1,-1);int anslen=0;
 for (i=1;i<=len;i++)
 {
  int ll=i-(maxlen[i]-1)/2,rr=i+(maxlen[i]-1)/2;
  int add=min(len-rr,f[ll]);
  if (maxlen[i]+add+add>anslen)
  {
   anslen=maxlen[i]+add+add;
   ans2=make_pair(i-(maxlen[i]-1)/2,maxlen[i]);
   if (add)
   {
    ans1=make_pair(minpos[add],add);
    ans3=make_pair(len-add+1,add);
   }
   else
    ans1=ans3=make_pair(-1,-1);
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
  printf("%d %d\n",ans1.first,ans1.second);
  printf("%d %d\n",ans2.first,ans2.second);
  printf("%d %d\n",ans3.first,ans3.second);
 }
 return 0;
}

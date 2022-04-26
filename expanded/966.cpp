# 2 "data/966.cpp" 2

# 2 "data/966.cpp"
using namespace std;
const int NR=3e5+10;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int n,N;
char a[NR],b[NR];
char s[NR<<1];
int pi[NR],num[NR];
int f[NR],id[NR];
int tot;
int getnxt(int x,char ch)
{
 if(b[x+1]==ch)return x+1;
 return x?getnxt(pi[x],ch):0;
}
void init(){s[0]='~',s[1]='#';for(int i=1;i<=n;i++)s[i<<1]=a[i],s[i<<1|1]='#';}
int read()
{
 int x=0,f=1;char ch=getchar();
 while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
 while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
 return x*f;
}
int main()
{


 scanf("%s",a+1);n=strlen(a+1);for(int i=1;i<=n;i++)b[i]=a[n-i+1];
 pi[0]=pi[1]=0;for(int i=2;i<=n;i++)pi[i]=getnxt(pi[i-1],b[i]);
 for(int i=1,j=0;i<=n;i++)j=getnxt(j,a[i]),num[i]=j,id[i]=i;
 for(int i=1;i<=n;i++)if(num[i-1]>num[i])num[i]=num[i-1],id[i]=id[i-1];
 init();N=n*2+1;int mx=1,mid=1;
 for(int i=1;i<=N;i++)
 {
  f[i]=(i<=mx)?min(f[mid*2-i],mx-i):0;
  while(i-f[i]-1>0&&i+f[i]+1<=N&&s[i-f[i]-1]==s[i+f[i]+1])f[i]++;
  if(mx<i+f[i])mx=i+f[i],mid=i;
 }int ans=0;
 int L[3]={-1,-1,-1},R[3]={-1,-1,-1};
 for(int i=1;i<=N;i++)
 {
  int pos,dis,flag,l,r;
  if(s[i]=='#')
  {
   continue;
   pos=i/2,dis=f[i]/2,flag=1;
   l=pos-dis+1,r=pos+dis;
  }
  else
  {
   pos=i/2,dis=f[i]/2,flag=1;
   l=pos-dis,r=pos+dis;
  }
  if(ans<r-l+1+min(n-r,num[l-1])*2)
  {
   for(int j=0;j<3;j++)L[j]=R[j]=-1;
   ans=r-l+1+min(n-r,num[l-1])*2;
   int TTT=min(n-r,num[l-1]);
   L[0]=id[l-1]-(num[l-1]-TTT)-TTT+1,R[0]=id[l-1]-(num[l-1]-TTT);
   if(!num[l-1])L[0]=l,R[0]=r,flag=0;
   else L[flag]=l,R[flag]=r;
   if(num[l-1])
   {
    if(n-r<num[l-1]&&!flag)R[flag]=n;
    else L[flag+1]=n-TTT+1,R[flag+1]=n,flag++;
   }
   tot=flag;
  }
 }printf("%d\n",tot+1);
 for(int i=0;i<=tot;i++)printf("%d %d\n",L[i],R[i]-L[i]+1);
 return 0;
}

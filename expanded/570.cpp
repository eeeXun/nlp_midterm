using namespace std;

namespace TYC
{
 typedef pair<int,int> pa;
 const int N=1e5+10;

 char str[N];
 int n,ans,flag,Log[N],fail[N],len[N],f[N],st[19][N];
 pa Pre,Suf,Mid;

 void Manacher()
 {
  static int p[N<<1];
  static char c[N*2+10];
  c[0]='$',c[1]='#';
  for(int i=0;i<n;i++)
   c[i*2+2]=str[i],c[i*2+3]='#';
  int id=0,mx=0,len=n*2+2;
  c[len]='@';
  for(int i=1;i<len;i++)
  {
   if(i<mx) p[i]=min(p[id*2-i],mx-i);
   else p[i]=1;
   while(1<=i-p[i]&&i+p[i]<len&&c[i-p[i]]==c[i+p[i]]) p[i]++;
   if(i+p[i]>mx) mx=i+p[i],id=i;
  }
  for(int i=0;i<n;i++)
  {
   f[i]=p[i*2+2]-1;
   st[0][i]=i;
   if(f[i]>ans)
   {
    flag=1,ans=f[i];
    Pre=pa(i-(f[i]-1)/2,f[i]);
   }
  }
 }

 inline int tmax(const int &x,const int &y)
 {
  return f[x]>f[y]?x:y;
 }

 void init()
 {
     for(int i=1;i<=18;i++)
   for(int j=0;j+(1<<i)-1<n;j++)
    st[i][j]=tmax(st[i-1][j],st[i-1][j+(1<<(i-1))]);
  int tmp=0;
  for(int i=1;i<=n;i++)
  {
   if(i==(1<<(tmp+1))) tmp++;
   Log[i]=tmp;
  }
 }

 inline int Max(int l,int r)
 {
  if(l>r) return -1;
  int k=Log[r-l+1];
  return tmax(st[k][l],st[k][r-(1<<k)+1]);
 }

 void KMP()
 {
  static char c[N];
  memcpy(c,str,sizeof(c));
  reverse(c,c+n);
  fail[0]=fail[1]=0;
  for(int i=1;i<n;i++)
  {
   int tmp=fail[i];
   while(tmp&&c[tmp]!=c[i])
    tmp=fail[tmp];
   fail[i+1]=(c[tmp]==c[i]?tmp+1:0);
  }
  int tmp=0;
  for(int i=0;i<n;i++)
  {
   while(tmp&&str[i]!=c[tmp])
    tmp=fail[tmp];
   if(str[i]==c[tmp]) tmp++;
   len[i]=tmp;
  }
 }

 void work()
 {
  scanf("%s",str);
  n=strlen(str);
  Manacher();
  init();
  KMP();
  for(int i=0;i<n;i++)
   if(len[i]&&n-len[i]>i)
   {
    int l=0,r=(n-len[i]-i)/2,mid,tmp=0,p;
    while(l<=r)
    {
     mid=(l+r)>>1;
     int pos=Max(i+mid,n-len[i]-mid);
     if(~pos&&(f[pos]+1)/2>=mid) p=pos,tmp=mid*2-1,l=mid+1;
     else r=mid-1;
    }
    if(!tmp) continue;
    int length=len[i]*2+tmp;
    if(length>ans)
    {
     ans=length;
     flag=0;
     Pre=pa(i-len[i]+1,len[i]);
     Mid=pa(p-(tmp-1)/2,tmp);
     Suf=pa(n-len[i],len[i]);
    }
   }
  if(flag)
   printf("1\n%d %d\n",Pre.first+1,Pre.second);
  else
  {
   printf("3\n");
   printf("%d %d\n",Pre.first+1,Pre.second);
   printf("%d %d\n",Mid.first+1,Mid.second);
   printf("%d %d\n",Suf.first+1,Suf.second);
  }
 }
}

int main()
{
 TYC::work();
 return 0;
}

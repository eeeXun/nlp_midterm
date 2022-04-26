

# 5 "data/889.cpp"
using namespace std;







const int NN=100005;

int n,m,pp[3],ll[3],nxt[NN],far[NN],Log[NN],p[NN*2],Max[NN][20],Who[NN][20];
char s[NN],t[NN],S[NN*2];

void Manachar()
{
 int N=0,id=0,mx=0;for (int i=(1);i<=(n);i++) S[++N]='*',S[++N]=s[i];S[++N]='*';
 for (int i=(1);i<=(N);i++)
 {
  p[i]=(mx>i?min(p[id*2-i],mx-i):1);
  while (i-p[i]>=1&&i+p[i]<=N&&S[i-p[i]]==S[i+p[i]]) p[i]++;
  if (i+p[i]>mx) id=i,mx=i+p[i];
 }
 for (int i=(1);i<=(N);i++) if (!(i&1)) far[i/2]=p[i]-1;
}
pair<int,int> get(int L,int R)
{
 int Lg=Log[R-L+1],x=Max[L][Lg],y=Max[R-(1<<Lg)+1][Lg];
 if (x>=y) return make_pair(x,Who[L][Lg]);
 else return make_pair(y,Who[R-(1<<Lg)+1][Lg]);
}
void Rmq()
{
 Log[0]=-1;for (int i=(1);i<=(n);i++) Log[i]=Log[i>>1]+1;
 for (int i=(1);i<=(n);i++) Max[i][0]=far[i],Who[i][0]=i;
 for (int j=(1);j<=(Log[n]);j++) for (int i=(1);i<=(n-(1<<j)+1);i++)
 {
  int x=Max[i][j-1],y=Max[i+(1<<j-1)][j-1];
  if (x>=y) Max[i][j]=x,Who[i][j]=Who[i][j-1];
  else Max[i][j]=y,Who[i][j]=Who[i+(1<<j-1)][j-1];
 }
}
pair<int,int> getmax(int L,int R)
{
 int l=0,r=(R-L)/2,mid;pair<int,int> res;
 while (l<=r)
 {
  mid=l+(r-l>>1);pair<int,int> tmp=get(L+mid,R-mid);
  if (tmp.first<2*mid+1) r=mid-1;
  else res=make_pair(mid,tmp.second),l=mid+1;
 }
 return res;
}
int main()
{
 scanf("%s",s+1);n=strlen(s+1);Manachar();Rmq();
 pair<int,int> tmp=getmax(1,n);pp[1]=tmp.second-tmp.first,ll[1]=2*tmp.first+1;
 for (int R=n,L=0,j1=0,j2=0;;R--)
 {
  t[++m]=s[R];
  if (m>1)
  {
   while (j1&&t[j1+1]!=t[m]) j1=nxt[j1];
   if (t[j1+1]==t[m]) j1++;nxt[m]=j1;
  }
  for (L++;L<=n;L++)
  {
   while (j2&&t[j2+1]!=s[L]) j2=nxt[j2];
   if (t[j2+1]==s[L]) j2++;if (j2==m) break;
  }
  if (L+1>R-1) break;pair<int,int> tmp=getmax(L+1,R-1);
  if (2*m+2*tmp.first+1>ll[0]+ll[1]+ll[2])
  {
   pp[0]=L-m+1,ll[0]=m;
   pp[1]=tmp.second-tmp.first,ll[1]=2*tmp.first+1;
   pp[2]=R,ll[2]=m;
  }
 }
 if (!pp[0]) {printf("1\n");printf("%d %d\n",pp[1],ll[1]);}
 else {printf("3\n");for (int i=(0);i<=(2);i++) printf("%d %d\n",pp[i],ll[i]);}
 return 0;
}

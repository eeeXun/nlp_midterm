
# 4 "data/647.cpp"
using namespace std;
int N,R[200005],MX=1,P=1,Ans,l,r,mid,cnt,X[4],L[4],Nxt[200005],F[200005],Id[200005],zj1,zj2,zj3,zj4,zj5;
char s[200005],S[200005];
int main()
{
 scanf(" %s",s+1);
 N=strlen(s+1);
 for(int i=1;i<=N;i++)
 {
  S[i*2-1]=s[i];
  S[i*2]='#';
 }
 N=N*2-1;
 for(int i=2;i<=N;i++)
 if(MX<i)
 {
  MX=i;
  while(S[MX+1]==S[i-(MX-i)-1]&&MX<N)
  MX++;
  R[i]=MX-i;
  P=i;
 }
 else
 {
  if(i+R[2*P-i]<MX)
  R[i]=R[2*P-i];
  else
  {
   while(S[MX+1]==S[i-(MX-i)-1]&&MX<N)
   MX++;
   R[i]=MX-i;
   P=i;
  }
 }
 for(int i=1;i<=N;i++)
 s[i]=S[N-i+1];
 int j=0;
 for(int i=2;i<=N;i++)
 {
  while(j&&s[j+1]!=s[i])
  j=Nxt[j];
  if(s[j+1]==s[i])
  j++;
  Nxt[i]=j;
 }
 j=0;
 for(int i=1;i<=N;i++)
 {
  while(j&&s[j+1]!=S[i])
  j=Nxt[j];
  if(s[j+1]==S[i])
  j++;
  if(j>F[i-1])
  F[i]=j,Id[i]=i;
  else
  F[i]=F[i-1],Id[i]=Id[i-1];
 }
 for(int i=1;i<=N;i+=2)
 if(R[i]/2*2+1+min(N-i-R[i],F[i-R[i]-1])>Ans)
 {
  Ans=R[i]/2*2+1+min((N-i-R[i]+1)/2*2,(F[i-R[i]-1]+1)/2*2);
  zj1=Id[i-R[i]]/2;
  zj2=min((N-i-R[i]+1)/2*2,(F[i-R[i]-1]+1)/2*2)/2;
  zj3=i/2+1;
  zj4=R[i]/2;
  zj5=N/2+1-zj2+1;
 }
 N=N/2+1;
 if(!zj2)
 {
  cnt=1;
  X[1]=zj3-zj4;
  L[1]=Ans;
 }
 else
 {
  cnt=3;
  X[1]=zj1-zj2+1;
  L[1]=zj2;
  X[2]=zj3-zj4;
  L[2]=zj4*2+1;
  X[3]=zj5;
  L[3]=zj2;
 }
 printf("%d\n",cnt);
 for(int i=1;i<=cnt;i++)
 printf("%d %d\n",X[i],L[i]);
 return 0;
}

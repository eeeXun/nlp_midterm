# 3 "data/414.cpp" 2



# 5 "data/414.cpp"
using namespace std;




char s1[(int)1e6+5],S[(int)1e6+5*2+3];
int n,m,len,r[(int)1e6+5*2+3],ans=0,z[(int)1e6+5*2+3],N;
int dp[(int)1e6+5],pos[(int)1e6+5];


inline void prepare()
{
 S[++len]='@';
 S[++len]='$';
 for (int i=0;i<n;i++)
 {
  S[++len]=s1[i];
  S[++len]='$';
 }
 S[len+1]='\0';
}

inline void manacher()
{
 int right=0,mid=0;
 for (int i=1;i<=len;i++)
 {
  int x;
  if (right<i) x=1;
  else x=min(r[mid*2-i],right-i);
  while (S[i+x]==S[i-x]) x++;
  if (i+x>right)
  {
   right=i+x;
   mid=i;
  }
  r[i]=x;
 }
}


inline void getZ()
{
 z[1]=N;
 int j=1,k;
 for (int i=2;i<=N;i=k)
 {
  if (j<i) j=i;
  while (S[j-i+1]==S[j]) j++;
  z[i]=j-i;
  k=i+1;
  while (k+z[k-i+1]<j) {k++;z[k]=z[k-i+1];}
 }
}


int main()
{
 cin>>s1;
 n=strlen(s1);
 prepare();
 manacher();

 for (int i=1;i<=len;i++)
    ans=max(ans,r[i]-1);
 if ((n&1) && ans==n) {printf("1\n1 %d\n",n);return 0;}

 memset(S,0,sizeof(S));
 memcpy(S+1,s1,sizeof(s1));
 reverse(S+1,S+1+n);
 S[n+1]='$';
 for (int i=n+2,cnt=0;cnt<n;i++,cnt++) S[i]=s1[cnt];
 N=2*n+1;
 getZ();
 for (int i=1;i<=n;i++)
  {
    int x=z[n+1+i];
  if (x>dp[i+x-1]) dp[i+x-1]=x,pos[i+x-1]=i;
 }
 for (int i=n-1;i;i--) if (dp[i]>dp[i-1]+1) {dp[i-1]=dp[i]-1;pos[i-1]=pos[i];}
 for (int i=2;i<=n-1;i++)
  if (dp[i-1]>dp[i]) dp[i]=dp[i-1],pos[i]=pos[i-1];
 ans=0;
 int S1,S2,S3,L1,L2,L3;
 for (int i=1;i<=n;i++)
 {
  int xx=r[(i<<1)+1]-1;
  int x=xx>>1;
         int l=i-x,r=i+x;
  int ls=dp[l-1];
  if (ls>n-r) ls=n-r;
  if (xx+2*ls>ans)
  {
   ans=xx+2*ls;
   S1=pos[l-1];S2=l;S3=n-ls+1;
   L1=ls;L2=xx;L3=ls;
  }
 }
 if (L1==0) {printf("1\n%d %d\n",S2,L2);return 0;}
 printf("3\n");
 printf("%d %d\n%d %d\n%d %d\n",S1,L1,S2,L2,S3,L3);
 return 0;
}

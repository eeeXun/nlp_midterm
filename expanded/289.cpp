


# 5 "data/289.cpp"
int a[101000],_a[101000],n,p[101000],
 f[101000],_f[101000],Q[1010000],
 MaxLeft[101000],MaxRight[101000],
 Maxp[101000][20],
 Ans,Ans1,Ans2,Ans3,x[3],y[3];

char Str[101000];

int Max(int a,int b){return p[a]>p[b]?a:b;}

int Query(int a,int b)
{
 int k=Q[b-a+1];
 return Max(Maxp[a][k],Maxp[b-(1<<k)+1][k]);
}

void GetMax(int A,int B,int&x,int&y)
{
 x=-1;y=-1;
 int Now(0),L,R,M;
 L=0;R=(B-A)/2+1;
 for(;L+1<R;)
 {
  M=(L+R)/2;
  if(p[Query(A+M,B-M)]>M)
   L=M;
  else
   R=M;
 }
 if(2*L+1>Now)
 {
  Now=2*L+1;
  M=Query(A+L,B-L);
  x=M-L;
  y=M+L;
 }
}

int main()
{
 int i,j,k;


 for(i=0;i<17;i++)
  for(j=1<<i;j<(2<<i);j++)
   Q[j]=i;

 scanf("%s",Str);
 n=strlen(Str);
 for(i=0;i<n;i++)a[i]=_a[n-i-1]=Str[i]-'a';
 a[n]=-2;_a[n]=-1;

 for(k=i=0;i<n;i++)
 if(i+p[2*k-i]>=k+p[k])
 {
  for(p[i]=(k+p[k]-i)<0?0:(k+p[k]-i);i-p[i]>=0&&a[i+p[i]]==a[i-p[i]];p[i]++);
  k=i;
 }
 else p[i]=p[2*k-i];

 memset(MaxLeft,-1,sizeof MaxLeft);
 memset(MaxRight,63,sizeof MaxRight);

 for(i=0;i<n;i++)
 {
  Maxp[i][0]=i;
  if(MaxLeft[i-p[i]+1]<i)
   MaxLeft[i-p[i]+1]=i;
  if(MaxRight[i+p[i]-1]>i)
   MaxRight[i+p[i]-1]=i;
 }
 for(i=1;i<n;i++)
  if(MaxLeft[i]<MaxLeft[i-1])
   MaxLeft[i]=MaxLeft[i-1];
 for(i=n-2;i>=0;i--)
  if(MaxRight[i]<MaxRight[i+1])
   MaxRight[i]=MaxRight[i+1];
 for(k=1;k<20;k++)
  for(i=0;i+(1<<k)<=n;i++)
   Maxp[i][k]=Max(Maxp[i][k-1],Maxp[i+(1<<k-1)][k-1]);

 _f[0]=-1;
 for(k=0,i=1;i<n;i++)
 if(i+_f[i-k]>=k+_f[k])
 {
  for(_f[i]=(k+_f[k]-i<0)?0:(k+_f[k]-i);_a[i+_f[i]]==_a[_f[i]];_f[i]++);
  k=i;
 }
 else _f[i]=_f[i-k];

 f[0]=-1;
 for(k=i=0;i<n;i++)
 if(i+_f[i-k]>=k+f[k])
 {
  for(f[i]=(k+f[k]-i<0)?0:(k+f[k]-i);a[i+f[i]]==_a[f[i]];f[i]++);
  k=i;
 }
 else f[i]=_f[i-k];

 for(i=0;i<n;i++)
 {
  if(f[i]>(n-i-1)/2)f[i]=(n-i-1)/2;
  GetMax(i+f[i],n-1-f[i],j,k);
  if(j==-1&&k==-1)continue;
  if(k-j+1+2*f[i]>Ans)
  {
   Ans=k-j+1+2*f[i];
   Ans1=i;
   Ans2=j;
   Ans3=k;
  }
 }
 if(!f[Ans1]){printf("1\n%d %d\n",Ans2+1,Ans3-Ans2+1);return 0;}
 x[0]=Ans1;
 y[0]=Ans1+f[Ans1]-1;
 x[1]=Ans2;
 y[1]=Ans3;
 x[2]=n-f[Ans1];
 y[2]=n-1;
 if(y[0]+1==x[1]&&y[1]+1==x[2])
 {
  printf("1\n%d %d\n",x[0]+1,y[2]+1);
  return 0;
 }
 printf("3\n");
 for(i=0;i<3;i++)
  printf("%d %d\n",x[i]+1,y[i]-x[i]+1);
 return 0;
}

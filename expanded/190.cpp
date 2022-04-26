
# 4 "data/190.cpp"
void Get(int &T)
{
 char C;bool F=0;
 for(;C=getchar(),C<'0'||C>'9';)if(C=='-')F=1;
 for(T=C-'0';C=getchar(),C>='0'&&C<='9';T=T*10+C-'0');
 F&&(T=-T);
}

char S[100005];
char Inv[100005];
int N;

void Init()
{
 gets(S+1);
 N=strlen(S+1);

 for(int i=1;i<=N;i++)
  Inv[N-i+1]=S[i];
}

int Last[100005];
int Far[100005];
int Pos[100005];

void KMP()
{
 for(int i=2;i<=N;i++)
 {
  for(int j=Last[i-1];;j=Last[j])
  {
   if(Inv[j+1]==Inv[i])
   {
    Last[i]=j+1;
    break;
   }
   if(j==0) break;
  }
 }

 for(int i=1,j=0;i<=N;i++)
 {
  for(;;j=Last[j])
  {
   if(S[i]==Inv[j+1])
   {
    j=j+1;
    break;
   }

   if(j==0)
   {
    break;
   }
  }
  Far[i]=j;
 }
}

int Length[100005];

void Pali()
{
 S[0]='(';
 S[N+1]=')';

 for(int i=1;i<=N;)
 {
  for(int j=Length[i];;j++)
   if(S[i+j]!=S[i-j])
   {
    Length[i]=j;
    break;
   }

  for(int j=1;j<=Length[i];j++)
  {
   if(j==Length[i])
   {
    i=i+j;
    break;
   }

   if(i+j+Length[i-j]>=i+Length[i])
   {
    Length[i+j]=Length[i]-j;
    i=i+j;break;
   }
   else
    Length[i+j]=Length[i-j];
  }
 }
}

int Ans;
int Pos1,Len1;
int Pos2,Len2;
int Pos3,Len3;

void Work()
{
 KMP();
 Pali();

 for(int i=1;i<=N;i++)
 {
  Pos[i]=i;
  if(Far[i]<Far[i-1])
  {
   Far[i]=Far[i-1];
   Pos[i]=Pos[i-1];
  }
 }

 for(int i=1;i<=N;i++)
 {
  int Len20=Length[i];
  int Len10=Far[i-Length[i]];
  int Pos10=Pos[i-Length[i]]-Len10+1;

  if(N-(i+Len20-1)<Len10)
  {
   Len10=N-(i+Len20-1);
  }

  if(Ans<Len10+Len10+Len20+Len20-1)
  {
   Ans=Len10+Len10+Len20+Len20-1;

   Len2=Len20+Len20-1;
   Len1=Len10;
   Pos1=Pos10;
   Pos2=i-Len20+1;
   Len3=Len1;
   Pos3=N-Len3+1;
  }
 }
}

void Output()
{
 puts(Len1==0?"1":"3");

 if(Len1>0) printf("%d %d\n",Pos1,Len1);
 if(Len2>0) printf("%d %d\n",Pos2,Len2);
 if(Len3>0) printf("%d %d\n",Pos3,Len3);
}

int main()
{
 Init();
 Work();
 Output();
 return 0;
}

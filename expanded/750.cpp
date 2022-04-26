                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 8 "data/750.cpp" 2


# 9 "data/750.cpp"
using namespace std;

const int Seed=19961021;
const int inf=1000000000;

long long H0[100001],H1[100001],Pow[100001];

long long Get0(int L,int R)
{
  return H0[R+1]-H0[L]*Pow[R-L+1];
}

long long Get1(int L,int R)
{
  return H1[L]-H1[R+1]*Pow[R-L+1];
}

int main()
{
  int N=0;char c;
  static char S[100000];
  while(c=getchar(),c>='a'&&c<='z')S[N++]=c;
  H0[0]=0;for(int i=0;i<N;i++)H0[i+1]=H0[i]*Seed+S[i];
  H1[N]=0;for(int i=N-1;i>=0;i--)H1[i]=H1[i+1]*Seed+S[i];
  Pow[0]=1;for(int i=0;i<N;i++)Pow[i+1]=Pow[i]*Seed;
  static int Best[100001];
  for(int i=0;i<=N;i++)Best[i]=inf;
  for(int i=0;i<N;i++)
    {
      int Left=0,Right=(N-i)/2;
      while(Left<Right)
        {
          int Mid=(Left+Right+1)/2;
          if(Get0(i,i+Mid-1)==Get1(N-Mid,N-1))
            Left=Mid;
          else
            Right=Mid-1;
        }
      Best[Left]=min(Best[Left],i-1);
    }
  for(int i=N;i;i--)
    {
      Best[i-1]=min(Best[i-1],Best[i]);
      Best[i]+=i;
    }
  int Ans=0,X0,L0,X1,L1,X2,L2;
  for(int i=0;i<N;i++)
    {
      int Left=0,Right=min(i,N-1-i);
      while(Left<Right)
        {
          int Mid=(Left+Right+1)/2;
          if(Get0(i-Mid,i)==Get1(i,i+Mid))
            Left=Mid;
          else
            Right=Mid-1;
        }
      int Len=Left;Left=0;Right=N-(i+Len)-1;
      while(Left<Right)
        {
          int Mid=(Left+Right+1)/2;
          if(Best[Mid]<i-Len)
            Left=Mid;
          else
            Right=Mid-1;
        }
      if(Len*2+1+Left*2>Ans)
        {
          Ans=Len*2+1+Left*2;
          X0=Best[Left]-Left+2;L0=Left;
          X1=i-Len+1;L1=Len*2+1;
          X2=N-Left+1;L2=Left;
        }
    }
  if(L0)
    printf("3\n%d %d\n%d %d\n%d %d\n",X0,L0,X1,L1,X2,L2);
  else
    printf("1\n%d %d\n",X1,L1);
  return 0;
}

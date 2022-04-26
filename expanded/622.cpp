# 5 "data/622.cpp" 2

# 5 "data/622.cpp"
using namespace std;

const int N=1e5+5;

char s[N];
char tmp[N];
int pi[N],d[N];
int l[N],start[N];

int n;

int findNext(int k,char c)
{
 if(tmp[k+1]==c)
  return k+1;

 if(k==0)
  return 0;

 return findNext(pi[k],c);
}

void KMP()
{
 pi[0]=pi[1]=0;
 for(int i=2;i<=n;i++)
  pi[i]=findNext(pi[i-1],tmp[i]);
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    s[n+1]='#';


 int maxr=0,p=0;
 for(int i=1;i<=n;i++)
  d[i]=1;

 for(int i=2;i<=n;i++)
 {
  if(i<=maxr)
   d[i]=min(d[maxr+p-i],maxr-i+1);

  while(i+d[i]<=n && i-d[i]>=1 && s[i+d[i]]==s[i-d[i]])
   d[i]++;

  if(i+d[i]-1>maxr)
  {
   maxr=i+d[i]-1;
   p=i-d[i]+1;
  }
 }


    for(int i=1;i<=n;i++)
     tmp[i]=s[n+1-i];
    KMP();

    int cur=0;
    for (int i=1;i<=n;i++)
    {
     cur=findNext(cur,s[i]);
     l[i]=cur;

        if(cur==n)
         cur=pi[cur];

        if(l[i]>0)
         start[i]=i-l[i]+1;
    }


    for(int i=1;i<=n;i++)
     if(l[i-1]>l[i])
     {
      l[i]=l[i-1];
      start[i]=start[i-1];
     }

    bool flag=false;
    int ans=0,pos=0;
    for(int i=1;i<=n;i++)
     if(2*d[i]-1>ans)
     {
      ans=2*d[i]-1;
      pos=i-d[i]+1;
     }

    for(int i=1;i<=n;i++)
    {
        int tmp=i-d[i];


        if(2*min(l[tmp],n-(i+d[i]-1))+2*d[i]-1>ans)
        {
         flag=true;
         ans=2*min(l[tmp],n-(i+d[i]-1))+2*d[i]-1;
         pos=i;
        }
    }

    if(!flag)
    {
     printf("1\n");
     printf("%d %d\n",pos,ans);
    }
    else
    {
     printf("3\n");
     printf("%d %d\n", start[pos-d[pos]],l[pos-d[pos]]);
     printf("%d %d\n",pos-d[pos]+1,2*d[pos]-1);
     printf("%d %d\n",n-l[pos-d[pos]]+1,l[pos-d[pos]]);
    }

    return 0;
}

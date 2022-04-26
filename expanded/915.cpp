# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 6 "data/915.cpp" 2

# 6 "data/915.cpp"
using namespace std;

int n,l,ans,s,s1,w1,w2,l1;
int rad[200010],f[100010],next[100010],g[100010],w[100010];
char a[100010],b[200010];

void manacher()
{int i,j=0;

 for(i=1;i<=l;i++)
 { if(j+rad[j]>i)
   rad[i]=min(j+rad[j]-i,rad[j*2-i]);
 else
  rad[i]=1;
 while(i-rad[i]>0 && i+rad[i]<=l && b[i-rad[i]]==b[i+rad[i]]) rad[i]++;
  if(i+rad[i]>j+rad[j]) j=i;
 }
}

void kmp()
{int i,j=0;

 for(i=2;i<=n;i++)
 { while(j!=0 && b[j+1]!=b[i]) j=next[j];
  if(b[j+1]==b[i])
  { next[i]=j+1;
   j++;
  }
 else
   next[i]=j;
 }

 j=0;
 for(i=1;i<=n;i++)
 { while(j!=0 && b[j+1]!=a[i]) j=next[j];
  if(b[j+1]==a[i])
  { g[i]=j+1;
   j++;
  }
  else
   g[i]=j;
 }
}

int main()
{int i,j;

 scanf("%s",a);
 n=strlen(a);

 for(i=n;i>=1;i--)
  a[i]=a[i-1];
 a[0]=' ';

 for(i=1;i<=n;i++)
 { b[i*2-1]='#';
  b[i*2]=a[i];
 }
 b[n*2+1]='#';

 l=n*2+1;

 manacher();

 for(i=1;i<=n;i++)
  f[i]=rad[i*2]/2;

 for(i=1;i<=n;i++)
  b[i]=a[n+1-i];

 kmp();



 for(i=1;i<=n;i++)
  if(g[i]>g[i-1])
   w[i]=i;
  else
 { g[i]=g[i-1];
  w[i]=w[i-1];
 }




 ans=0;
 for(i=1;i<=n;i++)
 { s=f[i];
  s1=g[i-f[i]];


 if(s1>0)
 { if(s*2-1+2*min(s1,n-i-f[i]+1)>ans)
  { ans=s*2-1+2*min(s1,n-i-f[i]+1);
   l1=(ans-(s*2-1))/2;
   w1=w[i-f[i]]-l1+1;
   w2=i;
  }
  }
  else
  { if(s*2-1>ans)
   { ans=s*2-1;
    l1=0;
    w2=i;
   }
  }
 }

 if(l1!=0)
 { printf("%d\n",3);
  printf("%d %d\n",w1,l1);
  printf("%d %d\n",w2-f[w2]+1,f[w2]*2-1);
  printf("%d %d\n",n-l1+1,l1);
 }
 else
 { printf("%d\n",1);
  printf("%d %d\n",w2-f[w2]+1,f[w2]*2-1);
 }

 return 0;
}

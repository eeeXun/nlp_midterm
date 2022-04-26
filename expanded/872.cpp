  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;
# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 14 "data/872.cpp" 2
# 1 "/usr/include/c++/11.2.0/cstdio" 1 3
# 39 "/usr/include/c++/11.2.0/cstdio" 3
       
# 40 "/usr/include/c++/11.2.0/cstdio" 3
# 15 "data/872.cpp" 2

# 15 "data/872.cpp"
using namespace std;
#pragma comment(linker, "/STACK:16777216")
# 30 "data/872.cpp"
char s[111111];
char t[222222];
int d[111111];
int sf[222222];
int mx[111111];
int mps[111111];
int n;
void pals()
{
 int l=0,r=-1;
 for(int (i)=0;(i)<(n);++(i))
 {
  int maxs=((i>r)?(0):min(d[l+r-i],r-i))+1;
  while(i+maxs<n&&i-maxs>=0&&s[i-maxs]==s[i+maxs])
   ++maxs;
  d[i]=--maxs;
  if (i+maxs>r)
   l=i-maxs,r=i+maxs;
 }
}
void kmp()
{
 int m=0;
 for(int i=n-1;i>=0;--i)
  t[m++]=s[i];
 t[m++]='!';
 for(int (i)=0;(i)<(n);++(i))
  t[m++]=s[i];
 sf[0]=-1;
 for(int i=1;i<m;++i)
 {
  int j=sf[i-1];
  while(j!=-1&&t[j+1]!=t[i])
   j=sf[j];
  if (t[j+1]==t[i])
   sf[i]=j+1;
  else
   sf[i]=-1;
 }
}
int main()
{
 gets(s);
 n=(int)strlen(s);
 pals();
 kmp();
 mx[0]=sf[n+1]+1;
 mps[0]=0;
 for(int i=1;i<n;++i)
  if (mx[i-1]>sf[n+1+i]+1)
  {
   mx[i]=mx[i-1];
   mps[i]=mps[i-1];
  }
  else
  {
   mx[i]=sf[n+1+i]+1;
   mps[i]=i;
  }
 int ans=0;
 int pos1=0,pos2=0,pos3=0,len1=0,len2=0;
 for(int (i)=0;(i)<(n);++(i))
  if (d[i]==i&&ans<2*d[i]+1)
  {
   ans=2*d[i]+1;
   pos1=pos3=-1;
   pos2=i+1-d[i];
   len1=0;
   len2=ans;
  }
  else
   if (d[i]+i==n-1&&ans<2*d[i]+1)
   {
    ans=2*d[i]+1;
    pos1=pos3=-1;
    pos2=i+1-d[i];
    len1=0;
    len2=ans;
   }
   else
    if (ans<2*d[i]+1+2*min(mx[i-d[i]-1],n-1-(i+d[i])))
    {
     ans=2*d[i]+1+2*min(mx[i-d[i]-1],n-1-(i+d[i]));
     len1=min(mx[i-d[i]-1],n-1-(i+d[i]));
     pos1=mps[i-d[i]-1]+1-len1+1;
     len2=2*d[i]+1;
     pos2=i+1-d[i];
     pos3=n+1-len1;
    }
 if (len1==0)
 {
  cout<<1<<endl;
  cout<<pos2<<" "<<len2<<endl;
 }
 else
 {
  cout<<3<<endl;
  cout<<pos1<<" "<<len1<<endl;
  cout<<pos2<<" "<<len2<<endl;
  cout<<pos3<<" "<<len1<<endl;
 }
}

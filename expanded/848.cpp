# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/848.cpp" 2



# 7 "data/848.cpp"
using namespace std;



const int maxn=100010;
const unsigned long long seed=10007;

unsigned long long pre[maxn],back[maxn];

int f[maxn],l,g[maxn];

char s[maxn];

vector< pair < int , int > > ans;

bool cmp(vector < pair < int , int > > a,vector < pair < int , int > > b)
{
 int v1=0,v2=0;
 for (unsigned int c=0;c<a.size();c++)
  v1+=a[c].second;
 for (unsigned int c=0;c<b.size();c++)
  v2+=b[c].second;
 return v1<v2;
}

void ma()
{
 f[1]=1;
 int nowm=1,nowr=1,nowl=1;
 for (int a=2;a<=l;a++)
  if (a>nowr)
  {
   nowm=a;
   nowl=1;
   nowr=a;
   f[a]=1;
   while (a+nowl<=l && a-nowl>=1 && s[a+nowl]==s[a-nowl])
    nowl++,nowr++,f[a]+=2;
   nowl--;
  }
  else
  {
   f[a]=min((nowr-a+1)*2-1,f[nowm*2-a]);
   f[a]=f[a]/2+1;
   while (a+f[a]<=l && a-f[a]>=1 && s[a+f[a]]==s[a-f[a]])
    f[a]++;
   f[a]--;
   if (a+f[a]>nowr)
   {
    nowm=a;
    nowl=f[a];
    nowr=a+f[a];
   }
   f[a]=f[a]*2+1;
  }
}

unsigned long long back_hash(int l)
{
 return back[l];
}

unsigned long long mul(unsigned long long a,int b)
{
 unsigned long long ans=1;
 while (b)
 {
  if (b & 1) ans*=a;
  a*=a;
  b>>=1;
 }
 return ans;
}

unsigned long long hash(int l,int r)
{
 return pre[r]-pre[l-1]*mul(seed,r-l+1);
}

int main()
{
 scanf("%s",s+1);
 l=strlen(s+1);
 ma();
 for (int a=1;a<=l;a++)
  pre[a]=pre[a-1]*seed+s[a];
 for (int a=l;a>=1;a--)
  back[a]=back[a+1]*seed+s[a];
 for (int a=1;a<=l;a++)
  if (s[a]==s[l])
  {
   g[1]=a;
   break;
  }
 for (int a=2;a<=l;a++)
 {
  if (!g[a-1]) break;
  if (s[l-a+1]==s[g[a-1]+a-1]) g[a]=g[a-1];
  else
  {
   unsigned long long nowh=back_hash(l-a+1);
   g[a]=g[a-1]+1;
   while (g[a]+a-1<=l && hash(g[a],g[a]+a-1)!=nowh)
    g[a]++;
   if (g[a]+a-1>l)
   {
    g[a]=0;
    break;
   }
  }
 }
 for (int a=1;a<=l;a++)
 {
  vector< pair < int , int > > nowans;
  nowans.push_back(make_pair(a-f[a]/2,f[a]));
  if (cmp(ans,nowans)) ans=nowans;
  if (a+f[a]/2<l)
  {
   int left=1,right=l-(a+f[a]/2)+1;
   while (left+1!=right)
   {
    int m=(left+right)>>1;
    if (g[m] && g[m]+m-1<a-f[a]/2) left=m;
    else right=m;
   }
   if (g[left] && g[left]+left-1<a-f[a]/2)
   {
    nowans.clear();
    nowans.push_back(make_pair(g[left],left));
    nowans.push_back(make_pair(a-f[a]/2,f[a]));
    nowans.push_back(make_pair(l-left+1,left));
    if (cmp(ans,nowans)) ans=nowans;
   }
  }
 }
 printf("%d\n",(int)ans.size());
 for (unsigned int a=0;a<ans.size();a++)
  printf("%d %d\n",ans[a].first,ans[a].second);

 return 0;
}

# 63 "/usr/include/c++/11.2.0/set" 2 3
# 71 "/usr/include/c++/11.2.0/set" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

  namespace pmr
  {
    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 6 "data/905.cpp" 2


# 7 "data/905.cpp"
using namespace std;



typedef long long ll;

char s[201000];
int n;
int r[201000];
# 29 "data/905.cpp"
void manacher()
{
    int p=0;
    int mx=-1;
    for(int i=1; i<=n; i++)
    {
        if(mx>i)
            r[i]=min(r[2*p-i],mx-i);
        else
            r[i]=1;
        while(s[i+r[i]]==s[i-r[i]])
            r[i]++;
        if(i+r[i]>mx)
        {
            mx=i+r[i];
            p=i;
        }
    }
}


char str[201000];
int z[201000];
int z_n;
void z_func()
{
    int L = 0, R = 0;
    for (int i = 1; i < z_n; i++)
    {
        if (i > R)
        {
            L = R = i;
            while (R < z_n && str[R-L] == str[R]) R++;
            z[i] = R-L;
            R--;
        }
        else
        {
            int k = i-L;
            if (z[k] < R-i+1) z[i] = z[k];
            else
            {
                L = i;
                while (R < z_n && str[R-L] == str[R]) R++;
                z[i] = R-L;
                R--;
            }
        }
    }
}

pair<int,int> prefix_max[201000];

int main()
{
    int Max,Maxidex;
    int ans;
    int len;
    scanf("%s",s+1);
    n=strlen(s+1);
    s[0]='$';
    manacher();
    for(int i=1;i<=n;i++)
        r[i]-=1;

    z_func();
    z_n=0;
    for(int i=n;i>=1;i--)
        str[z_n++]=s[i];
    for(int i=1;i<=n;i++)
        str[z_n++]=s[i];
    z_func();
    for(int i=0;i<=n;i++)
        prefix_max[i]=make_pair(0,0);

    int mx=n-1;
    for(int i=n;i<2*n;i++)
    {
        if(i+z[i]-1>mx)
        {
            for(int j=mx+1;j<=i+z[i]-1;j++)
                prefix_max[j-n+1]=make_pair(j-i+1,i-n+1);
            mx=i+z[i]-1;
        }
    }

    for(int i=2;i<=n;i++)
        prefix_max[i]=max(prefix_max[i],prefix_max[i-1]);




    ans=0;
    for(int i=1;i<=n;i++)
    {
        len=n-(i+r[i]);
        ans=max(ans,2*r[i]+1+2*min(len,prefix_max[i-r[i]-1].first));
    }
    for(int i=1;i<=n;i++)
    {
        len=n-(i+r[i]);
        len=min(len,prefix_max[i-r[i]-1].first);
        if(ans==2*len+2*r[i]+1)
        {
            if(len==0)
            {
                puts("1");
                printf("%d %d\n",i-r[i],2*r[i]+1);
            }
            else
            {
                puts("3");
                printf("%d %d\n",prefix_max[i-r[i]-1].second,len);
                printf("%d %d\n",i-r[i],2*r[i]+1);
                printf("%d %d\n",n-len+1,len);
            }
            break;
        }
    }
}

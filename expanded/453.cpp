
  namespace pmr
  {
    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 8 "data/453.cpp" 2

# 8 "data/453.cpp"
using namespace std;
# 17 "data/453.cpp"
char s[100010];
int f[100010],next[100010],g[100010],h[100010];
int main()
{

    int i,j,n,m,k;
    while(~scanf("%s",s+1))
    {
        n=strlen(s+1);
        next[n]=j=n+1;
        for(i=n-1;i>=1;i--)
        {
            while(j<=n&&s[j-1]!=s[i])j=next[j];
            if(s[j-1]==s[i])j--;next[i]=j;
        }
        g[0]=j=n+1;
        for(i=1;i<=n;i++)
        {
            while(j<=n&&s[j-1]!=s[i])j=next[j];
            if(s[j-1]==s[i])j--;
            if(j<g[i-1])g[i]=j,h[i]=i;
            else g[i]=g[i-1],h[i]=h[i-1];
        }
        k=0;f[0]=0;
        int ans=0,first=0,second,z,l,L;
        for(i=1;i<=n;i++)
        {
            if(i<k+f[k]&&i+f[k+k-i]<k+f[k])f[i]=f[k+k-i];
            else
            {
                f[i]=i<k+f[k]?k+f[k]-i:0;
                while(i-f[i]&&i+f[i]<=n&&s[i-f[i]]==s[i+f[i]])f[i]++;
                if(i+f[i]>k+f[k])k=i;
            }
            if(ans<2*f[i]-1)ans=2*f[i]-1,second=i,L=0;
            int w=g[i-f[i]],now=h[i-f[i]];
            if(w<i+f[i])now-=i+f[i]-w,w=i+f[i];
            l=n-w+1;
            if(ans<2*(f[i]+l)-1)ans=2*(f[i]+l)-1,first=now-l+1,second=i,z=w,L=l;
        }
        if(L)
        {
            printf("3\n%d %d\n%d %d\n%d %d\n",first,L,second-f[second]+1,2*f[second]-1,z,L);
        }
        else printf("1\n%d %d\n",second-f[second]+1,2*f[second]-1);
    }
    return 0;
}

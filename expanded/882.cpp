
# 3 "data/882.cpp"
const int maxn=100005;
int n,f[maxn],g[maxn],dl[maxn],m[maxn];
long long hl[maxn],hr[maxn],cm[maxn];
char str[maxn];
long long hash(int s,int e)
{
     if(s<e)return hl[e]-hl[s]*cm[e-s];
     return hr[e]-hr[s]*cm[s-e];
}
__inline int min(int a,int b)
{
         if(a<b)return a;
         return b;
}
int calc(int x)
{
    int s=x-f[x]+1,e=x+f[x]-1;
    return (f[x]<<1)-1+(min(g[m[s-1]],n-e)<<1);
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++)hl[i]=hl[i-1]*999983+str[i];
    for(int i=n;i>=1;i--)hr[i]=hr[i+1]*999983+str[i];
    cm[0]=1;
    for(int i=1;i<=n;i++)cm[i]=cm[i-1]*999983;
    for(int i=1;i<=n;i++)
    {
      int l,r,mid;
      l=1;
      r=min(i,n-i+1);
      while(l<r)
      {
        mid=l+r+1>>1;
        if(hash(i,i+mid-1)==hash(i,i-mid+1))l=mid;
        else r=mid-1;
      }
      f[i]=l;
    }
    for(int i=1,s=1,e=0;i<=n;i++)
    {
      if(str[i]==str[n])dl[++e]=i;
      while(s<=e&&hash(dl[s],i)!=hash(n,n-(i-dl[s]))&&n-(i-dl[s])>i)s++;
      if(s>e)g[i]=0;
      else g[i]=i-dl[s]+1;
    }
    for(int i=1;i<=n;i++)
    {
      m[i]=m[i-1];
      if(g[m[i]]<g[i])m[i]=i;
    }
    int ans=0,bh;
    for(int i=1;i<=n;i++)
    {
      int tmp=calc(i);
      if(ans<tmp)
      {
        ans=tmp;
        bh=i;
      }
    }
    int s=bh-f[bh]+1,e=bh+f[bh]-1;
    int j=min(g[m[s-1]],n-e),k=m[s-1]-g[m[s-1]]+1;
    if(j)printf("3\n%d %d\n%d %d\n%d %d\n",k,j,s,e-s+1,n-j+1,j);
    else printf("1\n%d %d\n",s,e-s+1);
    return 0;
}

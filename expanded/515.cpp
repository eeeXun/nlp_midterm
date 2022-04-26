}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/515.cpp" 2

# 5 "data/515.cpp"
using namespace std;
int n,i,j,k,f[100011],g[100011],dl[100011],m[100011],s,e,mid,ans;
unsigned hl[100011],hr[100011],pow[100011];
char c[100011];

unsigned hashit(int s,int e)
{
    if (s<e) return hl[e]-hl[s]*pow[e-s];
    else return hr[e]-hr[s]*pow[s-e];
}

int calc(int x)
{
    int s=x-f[x]+1,e=x+f[x]-1;
    return f[x]*2-1+min(g[m[s-1]],n-e)*2;
}

int main()
{

    scanf("%s",c+1);
    n=(int)strlen(c+1);
    for (i=1;i<=n;i++) hl[i]=hl[i-1]*29+c[i];
    for (i=n;i>=1;i--) hr[i]=hr[i+1]*29+c[i];
    pow[0]=1;
    for (i=1;i<=n;i++) pow[i]=pow[i-1]*29;
    for (i=1;i<=n;i++)
    {
        s=1;
        e=min(i,n-i+1);
        while (s!=e)
        {
            mid=s+e-(s+e)/2;
            if (hashit(i,i+mid-1)==hashit(i,i-mid+1)) s=mid;
            else e=mid-1;
        }
        f[i]=s;
    }
    s=1;
    e=0;
    for (i=1;i<=n;i++)
    {
        if (c[i]==c[n]) dl[++e]=i;
        while (s<=e && hashit(dl[s],i)!=hashit(n,n-(i-dl[s])) && n-(i-dl[s])>i) s++;
        if (s>e) g[i]=0;
        else g[i]=i-dl[s]+1;
    }
    for (i=1;i<=n;i++)
    {
        m[i]=m[i-1];
        if (g[m[i]]<g[i]) m[i]=i;
    }
    for (i=1;i<=n;i++)
        ans=max(ans,calc(i));
    for (i=1;i<=n;i++)
        if (ans==calc(i))
        {
            s=i-f[i]+1;
            e=i+f[i]-1;
            j=min(g[m[s-1]],n-e);
            k=m[s-1]-g[m[s-1]]+1;
            if (j) cout << 3 << endl
                << k << " " << j << endl
                << s << " " <<e-s+1 << endl
                << n-j+1 << " " << j << endl;
            else cout << 1 << endl << s << " " << e-s+1 << endl;
            return 0;
        }
    return 0;
}

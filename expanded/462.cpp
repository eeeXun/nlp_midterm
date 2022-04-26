}
}
# 5 "data/462.cpp" 2


# 6 "data/462.cpp"
using namespace std;

const int maxn = 200010;

int sa[maxn],rank1[maxn],rank2[maxn],height[maxn],c[maxn],*x,*y,r[maxn],s[maxn];

int f[maxn],last[maxn],id[maxn],p[maxn],g[3][2];

char str[maxn];

void radix_sort(int n,int sz)
{
    memset(c,0,sizeof(c));
    for(int i=0;i<n;i++) c[x[y[i]]]++;
    for(int i=1;i<sz;i++) c[i]+=c[i-1];
    for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
}

void get_sa(int *s,int n,int sz=222)
{
    int i,len;
    x=rank1,y=rank2;
    for(int i=0;i<n;i++)
        x[i]=s[i],y[i]=i;
    radix_sort(n,sz);
    for(len=1;len<n;len<<=1)
    {
        int yid=0;
        for(i=n-len;i<n;i++) y[yid++]=i;
        for(i=0;i<n;i++) if(sa[i]>=len) y[yid++]=sa[i]-len;
        radix_sort(n,sz);
        swap(x,y);
        x[sa[0]]=yid=0;
        for(i=1;i<n;i++)
        {
            if(y[sa[i]]==y[sa[i-1]]&&sa[i]+len<n&&sa[i-1]+len<n&&y[sa[i]+len]==y[sa[i-1]+len])
                x[sa[i]]=yid;
            else
                x[sa[i]]=++yid;
        }
        sz=yid+1;
        if(sz>=n)
            break;
    }
    for(i=0;i<n;i++)
        rank1[i]=x[i];
}

void get_height(int *s,int n)
{
    int k=0;
    height[0]=0;
    for(int i=0;i<n;i++)
    {
        if(rank1[i]==0) continue;
        k=max(0,k-1);
        int j=sa[rank1[i]-1];
        while(i+k<n&&j+k<n&&s[i+k]==s[j+k]) k++;
        height[rank1[i]]=k;
    }
}

int main()
{
    int flag=0;
    scanf("%s",str+1);
    int n=strlen(str+1);
    str[0]='$';
    str[n+1]='#';
    for(int i=1;i<=n;i++)
        str[n+1+i]=str[n-i+1];
    int m=2*n+2;
    for(int i=0;i<m;i++)
        r[i]=(int)str[i];
    get_sa(r,m);
    get_height(r,m);
    memset(f,0,sizeof(f));
    int fuck=rank1[n+2];
    int now=n+1;
    for(int i=fuck;i>0;i--)
    {
        now=min(now,height[i]);
        f[sa[i-1]+now-1]=max(f[sa[i-1]+now-1],now);
    }
    now=n+1;
    for(int i=fuck+1;i<m;i++)
    {
        now=min(now,height[i]);
        f[sa[i]+now-1]=max(f[sa[i]+now-1],now);
    }
    for(int i=n-1;i>=1;i--)
    {
        if(f[i+1]-1>f[i])
            f[i]=f[i+1]-1;
    }
    last[0]=0;
    id[0]=0;
    for(int i=1;i<=n;i++)
    {
        if(f[i]>last[i-1])
        {
            last[i]=f[i];
            id[i]=i;
        }
        else
        {
            last[i]=last[i-1];
            id[i]=id[i-1];
        }
    }
    int maxx=-1,t;
    int ans=-1;
    for(int i=1;i<=n;i++)
    {
        if(maxx>i)
            p[i]=min(p[2*t-i],maxx-i);
        else
            p[i]=1;
        while(str[i+p[i]]==str[i-p[i]])
            p[i]++;
        if(p[i]+i>maxx)
        {
            maxx=p[i]+i;
            t=i;
        }
        int l=i-p[i];
        int cao=min(last[l],n-(i+p[i]-1));
        int now=2*p[i]-1+cao*2;
        if(now>ans)
        {
            if(cao)
            {
                ans=now;
                g[0][0]=id[l]-last[l]+1;
                g[0][1]=cao;
                g[1][0]=i-p[i]+1;
                g[1][1]=2*p[i]-1;
                g[2][0]=n-cao+1;
                g[2][1]=cao;
                flag=0;
            }
            else
            {
                    ans=now;
                    g[0][0]=i-p[i]+1;
                    g[0][1]=2*p[i]-1;
                    flag=1;
            }
        }
    }
    if(flag==1)
    {
        printf("1\n");
        printf("%d %d\n",g[0][0],g[0][1]);
    }
    else
    {
        printf("3\n");
        for(int i=0;i<3;i++)
            printf("%d %d\n",g[i][0],g[i][1]);
    }
    return 0;
}

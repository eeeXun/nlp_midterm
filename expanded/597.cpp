
# 3 "data/597.cpp"
using namespace std;
const int maxn=201000;
char s[maxn],rs[maxn];
int n,pos[maxn],fail[maxn],p[maxn];
int mp[maxn][20],pt[20],lo[1000000];
int ans=0,emp,pm,lm,ps;
void getfail()
{
    fail[1]=fail[2]=1;
    for(int i=2;i<=n;i++)
    {
        int j=fail[i];
        while(j!=1&&rs[i]!=rs[j])
            j=fail[j];
        fail[i+1]=j+(rs[i]==rs[j]);
    }
}
void kmp()
{
    int j=1;
    memset(pos,0x7f,sizeof pos);
    pos[n+1]=0;
    for(int i=1;i<=n;i++)
    {
        while(j!=1&&s[i]!=rs[j])
            j=fail[j];
        j+=(s[i]==rs[j]);
        if(j>1)
            pos[n-j+2]=min(pos[n-j+2],i);
    }
}
void manacher()
{
    s[0]='z'+1;
    p[1]=1;
    int mxp=1,mx=1;
    for(int i=2;i<=n;i++)
    {
        p[i]=1;
        if(mx>=i)
            p[i]=min(mx-i+1,p[mxp*2-i]);
        while(s[i+p[i]]==s[i-p[i]])
            p[i]++;
        if(i+p[i]-1>mx)
            mxp=i,mx=i+p[i]-1;
    }
}
int cmp(int x,int y)
{return p[x]>p[y]?x:y;}
void sparse_table()
{
    pt[0]=1;
    for(int i=1;i<=19;i++)
        pt[i]=pt[i-1]<<1;
    for(int i=0;i<19;i++)
        for(int j=pt[i];j<pt[i+1];j++)
            lo[j]=i;
    for(int i=1;i<=n;i++)
        mp[i][0]=i;
    for(int j=1;j<=19;j++)
        for(int i=1;i+pt[j]-1<=n;i++)
            mp[i][j]=cmp(mp[i][j-1],mp[i+pt[j-1]][j-1]);
}
int rmq(int l,int r)
{
    if(r<l)
        return 0;
    int loo=lo[r-l+1];
    return cmp(mp[l][loo],mp[r-pt[loo]+1][loo]);
}
int dichotomy(int ll,int rr)
{
    int l=1,r=(rr-ll+2)/2+1;
    while(l+1<r)
        p[rmq(ll+((l+r)>>1)-1,rr-((l+r)>>1)+1)]>=((l+r)>>1)?l=((l+r)>>1):r=((l+r)>>1);
    return rmq(ll+l-1,rr-l+1);
}
int main()
{




    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        rs[n-i+1]=s[i];
    getfail();
    kmp();
    manacher();




    sparse_table();
    for(int i=n+1;i>=1;i--)
        if(pos[i]<i-1)
        {
            int po=dichotomy(pos[i]+1,i-1);
            int len=min(min(po-pos[i],i-po),p[po]);
            if(len*2-1+2*(n-i+1)>ans)
            {
                ans=len*2-1+2*(n-i+1);
                ps=i;lm=len*2-1;pm=po-len+1;
            }
        }

    if(ps!=n+1)
        printf("3\n%d %d\n%d %d\n%d %d\n",pos[ps]-n+ps,n-ps+1,pm,lm,ps,n-ps+1);
    else
        printf("1\n%d %d\n",pm,lm);
    return 0;
}

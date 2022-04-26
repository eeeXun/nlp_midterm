}
# 6 "data/487.cpp" 2


# 7 "data/487.cpp"
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char s[100010],t[100010*2],ch[100010];
int n,len;
void prework()
{
    for(int i=1;i<=2*n+1;i++)
    {
        if(i&1) t[i]='#';
        else t[i]=s[i/2];
    }
    len=n*2+1;
}
int R[100010*2];
void Manacher()
{
    int mx=1,p=1;
    for(int i=2;i<=len;i++)
    {
        if(mx<i) R[i]=1;
        else{
            int j=2*p-i;
            R[i]=min(R[j],mx-i);
        }
        while(t[i+R[i]]==t[i-R[i]]&&i+R[i]<=len&&i-R[i]>=1) R[i]++;
        if(i+R[i]-1>mx)
        {
            mx=i+R[i]-1;
            p=i;
        }
    }
}
int fail[100010];
void kmp()
{
    fail[1]=0;
    for(int i=2;i<=n;i++)
    {
        int j=fail[i-1];
        while(j&&ch[j+1]!=ch[i]) j=fail[j];
        if(ch[j+1]==ch[i]) j++;
        fail[i]=j;
    }
}
int f[100010],pos[100010];
void com()
{
    int now=0;
    for(int i=1;i<=n;i++)
    {
        while(now&&ch[now+1]!=s[i]) now=fail[now];
        if(ch[now+1]==s[i]) now++;
        f[i]=now;
    }
    pos[1]=1;
    for(int i=2;i<=n;i++)
    {
        pos[i]=i;
        if(f[i-1]>f[i]) pos[i]=pos[i-1],f[i]=f[i-1];
    }
}
int ans;
int ansl[4],anslen[4];
void solve()
{
    for(int i=2;i<=len;i+=2)
    {
        int l=i-R[i]+1,r=i+R[i]-1;
        l=(l+1)/2;r/=2;
        if(l>r) continue;
        int tmp=r-l+1+min(f[l-1],n-r)*2;
        if(tmp>ans)
        {
            ansl[1]=pos[l-1]-min(f[l-1],n-r)+1;;anslen[1]=min(f[l-1],n-r);
            ansl[2]=l;anslen[2]=r-l+1;
            ansl[3]=n-min(f[l-1],n-r)+1;anslen[3]=min(f[l-1],n-r);
            ans=tmp;
        }
    }
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    prework();
    Manacher();
    for(int i=1;i<=n;i++) ch[n-i+1]=s[i];
    kmp();
    com();
    solve();
    int cnt=0;
    for(int i=1;i<=3;i++)
    {
        if(anslen[i]) cnt++;
    }
    printf("%d\n",cnt);
    for(int i=1;i<=3;i++)
    {
        if(anslen[i]) printf("%d %d\n",ansl[i],anslen[i]);
    }
    return 0;
}

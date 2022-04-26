# 5 "data/731.cpp" 2

# 5 "data/731.cpp"
using namespace std;

const int N=2e5+5;

char s[N];
char tmp[N];
int pi[N],d[N];
int start[N];

int n,m;

int findNext(int k,char c)
{
    if(s[k+1]==c)
        return k+1;

    if(k==0)
        return 0;

    return findNext(pi[k],c);
}

void KMP()
{
    pi[0]=pi[1]=0;
    for(int i=2;i<=m;i++)
        pi[i]=findNext(pi[i-1],s[i]);
}

void Manacher()
{
    int maxr=0,p=0;
    for(int i=1;i<=n;i++)
        d[i]=1;

    for(int i=2;i<=n;i++)
    {
        if(i<=maxr)
            d[i]=min(d[maxr+p-i],maxr-i+1);

        while(i+d[i]<=n && i-d[i]>=1 && s[i+d[i]]==s[i-d[i]])
            d[i]++;

        if(i+d[i]-1>maxr)
        {
            maxr=i+d[i]-1;
            p=i-d[i]+1;
        }
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    s[n+1]='#';


    Manacher();


    memcpy(tmp,s,sizeof(tmp));
    for(int i=1;i<=n;i++)
        d[i+n+1]=d[i];

    for(int i=1;i<=n;i++)
        s[i]=tmp[n-i+1];
    for(int i=n+2;i<=n*2+1;i++)
        s[i]=tmp[i-n-1];
    m=n*2+1;
    KMP();

    for(int i=n+2;i<=m;i++)
    {
        if(pi[i]<=pi[i-1])
            start[i]=start[i-1];
        else
            start[i]=i;
        pi[i]=max(pi[i],pi[i-1]);
    }

    int cur=0;
    for(int i=n+2;i<=m;i++)
        if(d[i]>d[cur])
            cur=i;

    int ans=0,cnt=0,cntnum=0;
    for(int i=n+2;i<=m;i++)
    {
        int num=min(pi[i-d[i]],m-i-d[i]+1);


        if(num*2+d[i]*2-1>ans)
        {
            ans=num*2+d[i]*2-1;
            cnt=i;
            cntnum=num;
        }
    }

    if(ans==d[cur]*2-1)
    {
        printf("1\n");
        printf("%d %d\n",cur-d[cur]-n,d[cur]*2-1);
    }
    else
    {
        printf("3\n");

        printf("%d %d\n", min(cnt-d[cnt]-n-cntnum,start[cnt-d[cnt]]-n-cntnum),cntnum);
        printf("%d %d\n",cnt-d[cnt]-n,d[cnt]*2-1);
        printf("%d %d\n", n-cntnum+1,cntnum);
    }
    return 0;
}

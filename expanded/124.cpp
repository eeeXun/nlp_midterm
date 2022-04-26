    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 11 "data/124.cpp" 2


# 12 "data/124.cpp"
using namespace std;



int NEXT[200005],extend[200005];

void EKMP(char s[],char t[])
{
    int i,j,p,l;
    int len=strlen(t);
    int len1=strlen(s);
    memset(NEXT,0,sizeof(NEXT));
    memset(extend,0,sizeof(extend));
    NEXT[0]=len;
    j=0;
    while(1+j<len&&t[j]==t[1+j])j++;
    NEXT[1]=j;
    int a=1;
    for(i=2; i<len; i++)
    {
        p=NEXT[a]+a-1;
        l=NEXT[i-a];
        if(i+l<p+1)NEXT[i]=l;
        else
        {
            j=max(0,p-i+1);
            while(i+j<len&&t[i+j]==t[0+j])j++;
            NEXT[i]=j;
            a=i;
        }
    }
    j=0;
    while(j<len1&&j<len&&s[j]==t[j])j++;
    extend[0]=j;
    a=0;
    for(i=1; i<len1; i++)
    {
        p=extend[a]+a-1;
        l=NEXT[i-a];
        if(l+i<p+1)extend[i]=NEXT[i-a];
        else
        {
            j=max(0,p-i+1);
            while(i+j<len1&&j<len&&s[i+j]==t[j])j++;
            extend[i]=j;
            a=i;
        }
    }
}
char s[200005];
struct node
{
    int x,xl;
    int y,yl;
    int z,zl;
}P;
int p[200005];
char ss[200005];
void Manacher()
{
    int id;
    int mx=0;
    int len=strlen(s);
    ss[0]='$';
    for(int i=1;i<=len;i++) ss[i]=s[i-1];
    ss[len+1]='#';
    ss[len+2]='\0';
    len=strlen(ss);
    int fin=0;
    for(int i=1;i<len;i++)
    {
        if(mx>i) p[i]=min(p[2*id-i],mx-i);
        else p[i]=1;
        for(;ss[i+p[i]]==ss[i-p[i]];p[i]++);
        if(p[i]+i>mx)
        {
            mx=p[i]+i;
            id=i;
        }
    }
     for(int i=1;i<=len;i++) p[i-1]=p[i];
     len=strlen(s);

}

int lg[200005];
int dp[200005][20];
void init(int n)
{
    lg[1]=0;
    for(int i=2;i<n;i++) lg[i]=lg[i/2]+1;
    for(int i=0;i<n;i++) dp[i][0]=i;
    for(int j=1,k=0;j<n;j*=2,k++)
    {
        for(int i=0;i<n;i++)
        {
            if(i+j*2>n) break;
            if(p[dp[i][k]]>p[dp[i+j][k]]) dp[i][k+1]=dp[i][k];
            else dp[i][k+1]=dp[i+j][k];
        }
    }
}
int cal(int a,int b)
{
    int t=lg[b-a+1];
    int temp=p[dp[a][t]]>p[dp[b-(1<<t)+1][t]]?dp[a][t]:dp[b-(1<<t)+1][t];
    return temp;
}
pair<int,int> solve(int L,int R)
{
    int l=1,r=(R-L+1)/2+1;
    int fin=0;
    int idx;
    while(l<=r)
    {
        int mid=(l+r)/2;
        int ll=L+mid-1;
        int rr=R-mid+1;
        int now=cal(ll,rr);

        if(p[now]>=mid)
        {
            idx=now-mid+1;
            fin=mid*2-1;
            l=mid+1;
        }
        else r=mid-1;
    }
    return make_pair(idx,fin);
}
int main()
{
    scanf("%s",s);
    Manacher();
    int len=strlen(s);
    init(len);

    for(int i=len;i<len*2;i++) s[i]=s[i-len];
    for(int i=0;i<len;i++) s[i]=s[len*2-i-1];
    s[len*2]='\0';
    EKMP(s,s);
    int fin=0;
    for(int i=len;i<2*len;i++)
    {
        int now=extend[i];
        int L=i-len+now;
        int R=len-now-1;
        if(L>R)
        {
            int temp=2*len-i;
            if(temp%2==0)
            {
                if(fin>temp) continue;
                fin=temp;
                P.x=i-len;P.xl=temp/2-1;
                P.y=2*len-i-P.xl;P.yl=temp/2-1;
                P.z=P.x+P.xl;P.zl=1;
            }
            else
            {
                if(fin>temp) continue;
                fin=temp;
                P.x=i-len;P.xl=temp;
                P.yl=0;P.zl=0;
            }
        }
        else
        {


            pair<int,int>temp=solve(L,R);
            if(temp.second+now*2>fin)
            {
                fin=temp.second+now*2;
                P.x=i-len;P.xl=now;
                P.y=len-now;P.yl=now;
                P.z=temp.first;P.zl=temp.second;
            }
        }
    }
    int ok=0;
    if(P.xl!=0) ok++;
    if(P.zl!=0) ok++;
    if(P.yl!=0) ok++;
    printf("%d\n",ok);
    if(P.xl!=0) printf("%d %d\n",P.x+1,P.xl);
    if(P.zl!=0) printf("%d %d\n",P.z+1,P.zl);
    if(P.yl!=0) printf("%d %d\n",P.y+1,P.yl);

}

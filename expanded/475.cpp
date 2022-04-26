 return std::_Hash_impl::hash(__b._M_getdata(), __clength);
      }
    };

  template<>
    struct hash<std::bitset<0>>
    : public __hash_base<size_t, std::bitset<0>>
    {
      size_t
      operator()(const std::bitset<0>&) const noexcept
      { return 0; }
    };


}
# 15 "data/475.cpp" 2

# 15 "data/475.cpp"
using namespace std;
# 26 "data/475.cpp"
const int ha1=443,ha2=317,modd=776555473;
const int maxn=100000+100;
struct Hash
{
    int x,y;
    Hash() { x=y=0; }
    Hash(int a,int b) { x=a,y=b; }
    Hash operator + (const Hash &a) const
    {
        return Hash((x+a.x) %modd, (y+a.y) %modd);
    }
    Hash operator - (const Hash &a) const
    {
        return Hash((x-a.x+modd) %modd, (y-a.y+modd) %modd);
    }
    Hash operator * (const Hash &a) const
    {
        return Hash((long long)x*a.x %modd,(long long)y*a.y %modd);
    }
    bool operator == (const Hash &a) const
    {
        return x==a.x && y==a.y;
    }
}po[maxn],hs[maxn];
int N,P[maxn],sp[maxn];
char s[maxn];

void Manacher(char *s,int *P)
{
    int n=strlen(s+1);
    s[0]='#',s[n+1]=0;
    P[1]=1;
    int id=1,mx=2;
    for (int i=2; i<=n; i++)
    {
        int j=(i<mx ? min(mx-i,P[id*2-i]) : 0);
        for (; s[i-j]==s[i+j]; j++);
        P[i]=j;
        if (i+j>mx) mx=i+j,id=i;
    }
}

bool check(int j,int i,const Hash &b)
{
    int len=N-i+1;
    Hash a=hs[j]-hs[j-len]*po[len];
    return a==b;
}

void Prepare(char *s,int *sp)
{
    N=strlen(s+1);
    po[0]=Hash(1,1);
    po[1]=Hash(ha1,ha2);
    for (int i=2; i<=N; i++)
        po[i]=po[i-1]*po[1];
    hs[0]=Hash(0,0);
    for (int i=(1),_i=(N); i<=_i; i++) hs[i]=(hs[i-1]+Hash(s[i],s[i]))*po[1];
    for (int i=(1),_i=(N); i<=_i; i++) sp[i]=-1;
    Hash tt=Hash(0,0);
    for (int i=N,j=1; i>=j; i--,j++)
    {
        tt=(tt+Hash(s[i],s[i]))*po[1];
        for (; j<=i && !check(j,i,tt); j++);
        if (j<=i) sp[i]=j;
    }

}

void Done()
{
    int maxmid=1,maxsuf=N+1;
    int maxlen=1;
    for (int i=(1),_i=(N); i<=_i; i++)
    {
        int j=i-P[i]+1;
        int le=i+P[i]-1,ri=N;
        while(le+1<ri)
        {
            int mid=(le+ri)>>1;
            if (sp[mid]!=-1 && sp[mid]<j) ri=mid;
                else le=mid;
        }
        if (sp[ri]==-1 || sp[ri]>=j || ri<=i+P[i]-1) ri=N+1;
        int ret=P[i]*2-1+(N-ri+1)*2;
        if (ret>maxlen) maxlen=ret,maxmid=i,maxsuf=ri;
    }
    int k=1+2*(maxsuf<=N);
    printf("%d\n",k);
    if (maxsuf<=N) printf("%d %d\n",sp[maxsuf]-(N-maxsuf),N-maxsuf+1);
    printf("%d %d\n",maxmid-P[maxmid]+1,P[maxmid]*2-1);
    if (maxsuf<=N) printf("%d %d\n",maxsuf,N-maxsuf+1);
}

int main()
{
    for (; scanf("%s",s+1)!=
# 122 "data/475.cpp" 3 4
                           (-1)
# 122 "data/475.cpp"
                              ; )
    {
        Manacher(s,P);
        Prepare(s,sp);
        Done();
    }
    return 0;
}

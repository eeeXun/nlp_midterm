
# 4 "data/696.cpp"
using namespace std;





char ch[100005];
int n,m,ii,k;
int same_suf[100005];

struct Hash_dui
{
    long long base,mod;
    int sz;
    vector<int>Rev,Forw,P;
    Hash_dui(){}
    Hash_dui(const char* s,long long b,long long m)
    {
        sz=strlen(s),base=b,mod=m;
        Rev.resize(sz+2,0),Forw.resize(sz+2,0),P.resize(sz+2,1);
        for(int i=1;i<=sz;i++)P[i]=(base*P[i-1])%mod;
        for(int i=1;i<=sz;i++)Forw[i]=(Forw[i-1]*base+(s[i-1]-'a'+1))%mod;
        for(int i=sz;i>=1;i--)Rev[i]=(Rev[i+1]*base+(s[i-1]-'a'+1))%mod;
    }
    void Single_char_ad(char cc)
    {
        P.push_back((P.back()*base)% mod);
        Forw.push_back((Forw.back()*base+(cc-'a'+1))% mod);
    }
    inline int Range_Hash(int l,int r)
    {
        int re_hash=Forw[r+1]-((long long)P[r-l+1]*Forw[l]%mod);
        if(re_hash<0)re_hash+=mod;
        return re_hash;
    }
    inline int Reverse_Hash(int l,int r)
    {
        int re_hash=Rev[l+1]-((long long)P[r-l+1]*Rev[r+2]%mod);
        if(re_hash<0)re_hash+=mod;
        return re_hash;
    }
};
struct Hash_Main
{
    Hash_dui h1,h2;
    Hash_Main(){}
    Hash_Main(const char* s)
    {
        h1=Hash_dui(s,1949313259, 2091573227);
        h2=Hash_dui(s,1997293877, 2117566807);
    }
    void Char_Add(char cc)
    {
        h1.Single_char_ad(cc);
        h2.Single_char_ad(cc);
    }
    inline long long Range_Hash(int l,int r)
    {
        return ((long long)h1.Range_Hash(l,r)<<32)^h2.Range_Hash(l,r);
    }
    inline long long Reverse_Hash(int l,int r)
    {
        return ((long long)h1.Reverse_Hash(l,r)<<32)^h2.Reverse_Hash(l,r);
    }
};

int oddPlen[100005],evenPlen[100005];

void Manachers()
{
   int l=0,r=-1;
   for(int i=0;i<n;i++)
   {
     int k=(i>r)?1:min(oddPlen[l+r-i],r-i+1);
     while(k<=i && i+k<n && ch[i-k]==ch[i+k])
     {
       k++;
     }
     oddPlen[i]=k--;
     if(i+k>r){
      l=i-k;
      r=i+k;
     }
   }

   l=0,r=-1;
   for(int i=0;i<n;i++)
   {
     int k=(i>r)?0:min(evenPlen[l+r-i+1],r-i+1);
     while(k+1<=i && i+k<n && ch[i-k-1]==ch[i+k])
     {
       k++;
     }
     evenPlen[i]=k--;
     if(i+k>r){
      l=i-k-1;
      r=i+k;
     }
   }


}

pair<int,int> ST[100005][20];
int Jump_LOG[100005];

void Build_Sparse()
{
    for(int i=1;i<=n;i++)ST[i][0]={same_suf[i],i};

    for(int i=2;i<=n;i++)Jump_LOG[i]=Jump_LOG[i-1]+!(i&(i-1));

    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;(i+(1<<j)-1)<=n;i++)
        {
           ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
        }
    }
}

pair<int,int> query(int i,int j)
{
    int boro_lav=Jump_LOG[j-i+1];
    return max(ST[i][boro_lav],ST[j-(1<<boro_lav)+1][boro_lav]);
}

void solve()
{
    scanf("%s",ch);
    n=strlen(ch);
    Hash_Main h(ch);
    Manachers();
    for(int i=1;i<=n;i++)
    {
        int be=1,en=(n-i)/2;
        int val=0;
        while(be<=en)
        {
            int mid=(be+en)/2;
            if(h.Range_Hash(i-1,i+mid-2)==h.Reverse_Hash(n-mid,n-1))
            {
                val=mid;
                be=mid+1;
            }
            else en=mid-1;
        }
        same_suf[i]=val;

    }

    Build_Sparse();
    vector<pair<int,int>>re;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int pal_len=oddPlen[i-1]*2-1;
        if(ans<pal_len)
        {
            ans=pal_len;
            re.clear();
            re.emplace_back(i-oddPlen[i-1]+1,ans);
        }
        int right=i-oddPlen[i-1];
        if(right==0 || i==n)continue;
        int free=n-(i+oddPlen[i-1]-1);
        int be=1,en=min(free,i-oddPlen[i-1]);

        int ex=0;
        int id=0;
        while(be<=en)
        {
            int mid=(be+en)/2;
            pair<int,int>tmp=query(1,i-oddPlen[i-1]-mid+1);

            if(tmp.first>=mid)
            {
                ex=mid;
                id=tmp.second;
                be=mid+1;
            }
            else en=mid-1;
        }
        if((ex+ex+oddPlen[i-1]*2-1)>ans)
        {
            ans=(ex+ex+oddPlen[i-1]*2-1);
            re.clear();
            re.emplace_back(id,ex);
            re.emplace_back(i-oddPlen[i-1]+1,oddPlen[i-1]*2-1);
            re.emplace_back(n-ex+1,ex);
        }

    }
    printf("%d\n",(int)re.size() );
    for(auto [a,b]:re)printf("%d %d\n",a,b );
}

int main()
{
    int t=1;

    while(t--)solve();
    return 0;
}

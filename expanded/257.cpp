    : private __detail::__variant::_Variant_hash_base<
 variant<_Types...>, std::index_sequence_for<_Types...>>,
      public __variant_hash_call_base<_Types...>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = variant<_Types...>;
    };

  template<>
    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/257.cpp" 2


# 3 "data/257.cpp"
using namespace std;

typedef unsigned long long ULL;
typedef long long LL;
typedef pair<int, int> pr;
typedef pair<LL, LL> lpr;
typedef pair<double, double> dpr;
typedef pair<long double, long double> ldpr;
typedef double db;
typedef long double ld;

typedef pair<ld,ld> pt;
# 49 "data/257.cpp"
const int next_x[8] = {0, 1, -1, 0, 1, 1, -1, -1};
const int next_y[8] = {1, 0, 0, -1, 1, -1, -1, 1};
const int inf = 1e9+5;
const LL linf = 1e18;
const double PI = acos(-1.0);

const int MAXN = 2e5+100;
const int N = MAXN*2;







int n;
char s[MAXN];
int d1[MAXN],d2[MAXN];

namespace manacher
{
    int p[MAXN*2];
    string a;
    void run(char s[],int d1[],int d2[])
    {
        int len=strlen(s+1);
        a.clear(),a.push_back('$'),a.push_back('#');
        for (register int i = (1), I = (len) + 1; i < I; ++i)a.push_back(s[i]),a.push_back('#');
        a.push_back('\0');
        int n=a.size()-1,id=0,mx=0;
        for(int i=1;i<=n;i++)
        {
            if(mx>i) p[i]=min(p[2*id-i],mx-i-1);
            else p[i]=1;
            while(a[i+p[i]]==a[i-p[i]]) p[i]++;
            if(i+p[i]-1>mx) mx=i+p[i]-1,id=i;
        }
        for (register int i = (1), I = (len) + 1; i < I; ++i) d1[i]=p[(i)*2]-1;
        for (register int i = (1), I = (len-1) + 1; i < I; ++i)d2[i]=p[(i)*2+1]-1;
    }
}

namespace st
{
    int f[MAXN][20];
    void init(int n,int a[])
    {
        for (register int i = (1), I = (n) + 1; i < I; ++i)f[i][0]=a[i];
        for(int j=1;(1<<j)<=n;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    }
    int query(int l,int r)
    {
        if(l>r)return 0;
        int k=log2(r-l+1);
        return max(f[l][k],f[r-(1<<k)+1][k]);
    }
}

namespace SAM
{
    int root,cnt,last;
    int nx[N][26],par[N],len[N],mn[N];
    int buc[N],seq[N];
    int newnode()
    {
        cnt++;
        memset(nx[cnt], 0, sizeof(nx[cnt]));
        par[cnt]=len[cnt]=0;
        mn[cnt]=inf;
        return cnt;
    }
    void init(){cnt=0,last=root=newnode();}
    void insert(int c)
    {
        int np=newnode(),p=last;
        len[np]=len[last]+1;
        while(p&&!nx[p][c])nx[p][c]=np,p=par[p];
        if(p)
        {
            int q=nx[p][c];
            if(len[q]==len[p]+1)par[np]=q;
            else
            {
                int nq=newnode();
                len[nq]=len[p]+1;
                par[nq]=par[q];
                memcpy(nx[nq],nx[q],sizeof(nx[q]));
                while(p&&nx[p][c]==q)nx[p][c]=nq,p=par[p];
                par[q]=par[np]=nq;
            }
        }
        else par[np]=root;
        last=np;
    }
    void sort()
    {
        memset(buc, 0, sizeof(buc));
        for (register int i = (1), I = (cnt) + 1; i < I; ++i)buc[len[i]]++;
        for (register int i = (1), I = (N-1) + 1; i < I; ++i)buc[i]+=buc[i-1];
        for (register int i = (1), I = (cnt) + 1; i < I; ++i)seq[buc[len[i]]--]=i;
    }
    void solve(char s[])
    {
        int n=strlen(s+1),cur=root;
        for (register int i = (1), I = (n) + 1; i < I; ++i)insert(s[i]-'a');
        for (register int i = (1), I = (n) + 1; i < I; ++i)
        {
            cur=nx[cur][s[i]-'a'];
            mn[cur]=min(mn[cur],i);
        }
        sort();
        for (register int i = (cnt), I = (1)-1; i > I; --i)
        {
            cur=seq[i];
            mn[par[cur]]=min(mn[par[cur]],mn[cur]);
        }

        int tl,tr,tlen,ans=0;
        cur=root;



        for (register int i = (n), I = (1)-1; i > I; --i)
        {
            if(!nx[cur][s[i]-'a'])break;
            cur=nx[cur][s[i]-'a'];
            int L=mn[cur]+1,R=i-1;
            if(R>=L)
            {
                int l=1,r=(R-L+1),t=1;
                while(l<=r)
                {
                    if(st::query(L+((l+r)/2)/2,R-((l+r)/2)/2)>=((l+r)/2))t=((l+r)/2),l=((l+r)/2)+1;
                    else r=((l+r)/2)-1;
                }
                if(t%2==0)t--;
                if((n-i+1)*2+t>ans)
                    tl=mn[cur],tr=i,tlen=t,ans=(n-i+1)*2+t;

            }
        }
        int pos=0;
        for (register int i = (1), I = (n) + 1; i < I; ++i)if(d1[i]>d1[pos])pos=i;
        if(d1[pos]>=ans)
        {
            printf("1\n");

            printf("%d %d\n",pos-d1[pos]/2,d1[pos]);



        }
        else
        {
            printf("3\n");
            printf("%d %d\n",tl-(n-tr+1)+1,(n-tr+1));
            for (register int i = (tl+1+tlen/2), I = (tr-1-tlen/2) + 1; i < I; ++i)if(d1[i]>=tlen)
            {
                printf("%d %d\n",i-tlen/2,tlen);
                break;
            }
            printf("%d %d\n",tr,(n-tr+1));
        }
    }
}

int work()
{
    scanf("%s",s+1),n=strlen(s+1);
    manacher::run(s,d1,d2);
    st::init(n,d1);
    SAM::init();
    SAM::solve(s);
    return 0;
}
# 243 "data/257.cpp"
int main()
{







    freopen("input.txt", "r", 
# 252 "data/257.cpp" 3 4
                             stdin
# 252 "data/257.cpp"
                                  );


    work();

    freopen("CON", "r", 
# 257 "data/257.cpp" 3 4
                       stdin
# 257 "data/257.cpp"
                            );
    freopen("CON", "w", 
# 258 "data/257.cpp" 3 4
                       stdout
# 258 "data/257.cpp"
                             );
    fflush(
# 259 "data/257.cpp" 3 4
          stdout
# 259 "data/257.cpp"
                );
    cout << "time:" << clock() << "ms" << endl;
    system("pause");

    return 0;
}

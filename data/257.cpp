#include "bits/stdc++.h"

using namespace std;
 
typedef unsigned long long ULL;
typedef long long LL;
typedef pair<int, int> pr;
typedef pair<LL, LL> lpr;
typedef pair<double, double> dpr;
typedef pair<long double, long double> ldpr;
typedef double db;
typedef long double ld;
//typedef complex<double> cp;
typedef pair<ld,ld> pt;
 
#define dbgs(x) #x << " = " << x
#define dbgs2(x, y) dbgs(x) << ", " << dbgs(y)
#define dbgs3(x, y, z) dbgs2(x, y) << ", " << dbgs(z)
#define dbgs4(w, x, y, z) dbgs3(w, x, y) << ", " << dbgs(z)

#define mst(s, x) memset(s, x, sizeof(s))
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define mp make_pair
#define all(x) x.begin(), x.end()
#define unq(x) x.erase(unique(x.begin(), x.end()), x.end())
#define rg register
#define fp(i, a, b) for (rg int i = (a), I = (b) + 1; i < I; ++i)
#define fd(i, a, b) for (rg int i = (a), I = (b)-1; i > I; --i)
#define ub upper_bound
#define lb lower_bound
#define bitcount __builtin_popcount
#define sqr(x) ((x)*(x))

#define go(u) for (rg int i = pre[u], v = e[i].v; i; i = e[i].next, v = e[i].v)
#define gow(u) for (rg LL i = pre[u], v = e[i].v, w = e[i].w; i; i = e[i].next, v = e[i].v, w = e[i].w)
#define EDGE(N,M) struct edge{int u,v,w,next;}e[M];int pre[N],edge_cnt=0;void addedge(int u,int v,int w=0){edge_cnt=edge_cnt+1,e[edge_cnt].u=u,e[edge_cnt].v=v,e[edge_cnt].w=w,e[edge_cnt].next=pre[u],pre[u]=edge_cnt;}
#define CLEAR_EDGE(N) {edge_cnt=0,memset(pre,0,sizeof(int)*(N+1));}

#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')

#define MC int _CASE;scanf("%d",&_CASE);fp(case_num,1,_CASE)
 
const int next_x[8] = {0, 1, -1, 0, 1, 1, -1, -1};
const int next_y[8] = {1, 0, 0, -1, 1, -1, -1, 1};
const int inf = 1e9+5;//7;
const LL linf = 1e18;
const double PI = acos(-1.0);
 
const int MAXN = 2e5+100;
const int N    = MAXN*2;

#define mid ((l+r)/2) 
//#define ls (cnt<<1)
//#define rs (cnt<<1|1)
 
/*----------head----------*/

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
        a.clear(),a.pb('$'),a.pb('#');
        fp(i,1,len)a.pb(s[i]),a.pb('#');
        a.pb('\0');
        int n=a.size()-1,id=0,mx=0;
        for(int i=1;i<=n;i++)
        {
            if(mx>i) p[i]=min(p[2*id-i],mx-i-1);
            else p[i]=1;
            while(a[i+p[i]]==a[i-p[i]]) p[i]++;
            if(i+p[i]-1>mx) mx=i+p[i]-1,id=i;
        }
        fp(i,1,len)  d1[i]=p[(i)*2]-1;
        fp(i,1,len-1)d2[i]=p[(i)*2+1]-1;
    }
}

namespace st
{
    int f[MAXN][20];
    void init(int n,int a[])
    {
        fp(i,1,n)f[i][0]=a[i];
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
        mst(nx[cnt],0);
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
    void sort() //seq 倒序为 叶子 -> 根
    {
        mst(buc,0);
        fp(i,1,cnt)buc[len[i]]++;
        fp(i,1,N-1)buc[i]+=buc[i-1];
        fp(i,1,cnt)seq[buc[len[i]]--]=i;
    }
    void solve(char s[])
    {
        int n=strlen(s+1),cur=root;
        fp(i,1,n)insert(s[i]-'a');
        fp(i,1,n)
        {
            cur=nx[cur][s[i]-'a'];
            mn[cur]=min(mn[cur],i);
        }
        sort();
        fd(i,cnt,1)
        {
            cur=seq[i];
            mn[par[cur]]=min(mn[par[cur]],mn[cur]);
        }
        
        int tl,tr,tlen,ans=0;
        cur=root;

        //fp(i,1,n)printf("%d ",d1[i]);printf("\n");
        
        fd(i,n,1)
        {
            if(!nx[cur][s[i]-'a'])break;
            cur=nx[cur][s[i]-'a'];
            int L=mn[cur]+1,R=i-1;//,len=;
            if(R>=L)
            {
                int l=1,r=(R-L+1),t=1;
                while(l<=r)
                {
                    if(st::query(L+mid/2,R-mid/2)>=mid)t=mid,l=mid+1;
                    else r=mid-1;
                }           
                if(t%2==0)t--;
                if((n-i+1)*2+t>ans)
                    tl=mn[cur],tr=i,tlen=t,ans=(n-i+1)*2+t;
                // cout << dbgs3(L,R,t) << endl;
            }
        }
        int pos=0;
        fp(i,1,n)if(d1[i]>d1[pos])pos=i;
        if(d1[pos]>=ans)
        {
            printf("1\n");
            //cout << dbgs2(pos,d1[pos]) << endl;
            printf("%d %d\n",pos-d1[pos]/2,d1[pos]);
            // fp(i,pos-d1[pos]/2,pos+d1[pos]/2)
            //     putchar(s[i]);
            // putchar('\n');
        }
        else
        {
            printf("3\n");
            printf("%d %d\n",tl-(n-tr+1)+1,(n-tr+1));
            fp(i,tl+1+tlen/2,tr-1-tlen/2)if(d1[i]>=tlen)
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

//#define ONLINE_JUDGE

// 小数 二分/三分 注意break条件
// 浮点运算 sqrt(a^2-b^2) 可用 sqrt(a+b)*sqrt(a-b) 代替，避免精度问题
// long double -> %Lf 别用C11 (C14/16)
// 控制位数 cout << setprecision(10) << ans;
// reverse vector 注意判空 不然会re
// 分块注意维护块上标记 来更新块内数组a[]
// vector+lower_bound常数 < map/set
// map.find不会创建新元素 map[]会 注意空间
// 别对指针用memset
// 用位运算表示2^n注意加LL  1LL<<20
// 注意递归爆栈
// 注意边界
// 注意memset 多组样例会T
 
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
#ifdef ONLINE_JUDGE
    //freopen("triatrip.in", "r",stdin );
    //freopen("triatrip.out","w",stdout);
#endif // ONLINE_JUDGE
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    work();
#ifndef ONLINE_JUDGE
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
    fflush(stdout);
    cout << "time:" << clock() << "ms" << endl;
    system("pause");
#endif
    return 0;
}
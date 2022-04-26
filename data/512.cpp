/*
Nahid Hossain
Jahangirnagar University
Roll:54
*/
#include<bits/stdc++.h>
#define ll          long long int
#define db          double
#define pf          printf
#define sf          scanf
#define ff          first
#define ss          second
#define clr         clear()
#define sz          size()
#define pb          push_back
#define mk          make_pair
#define pi          acos(-1)
#define inf         100000000000000000
#define mod         1000000007
#define ull         unsigned long long int
#define f(i,k,n)    for(ll i=k;i<n;i++)
#define fr(i,n,k)   for(i=n;i>=k;i--)
#define ent(a)      scanf("%lld",&a)
#define ent2(a,b)   scanf("%lld%lld",&a,&b)
#define ent3(a,b,c) scanf("%lld%lld%lld",&a,&b,&c)
#define mem(a)      memset(a,0,sizeof(a))
#define vec(v,s)    vector<ll>v[s]
#define arr(a,s)    ll a[s];
#define bitone(x)   __builtin_popcount(x)
//#define check(n,pos) (n&(1<<pos))
//#define set(n,pos)  (n|(1<<pos))
//knight and king//

//for(i=x;i>0;i=(i-1)&x)
int dr[]= {2, 2, -2, -2, 1, -1, 1, -1};
int dc[]= {1,-1,  1, -1, 2,  2,-2, -2};
int dr1[]= {0, 0, 1, 1, 1, -1, -1, -1};
int dc1[]= {-1, 1,-1, 0, 1, -1, 0,   1};
int dr2[]= {-1, 0, 0, 1};
int dc2[]= {-1,-1, -2, -1 };
////////////////////////////
using namespace std;
#define ma 300005


////*************/////////////////////////

ll siz,last,b[ma],occ[ma];

struct automata
{
    ll len,link,next[30];
} st[ma];


void inser(char c,ll x)
{
    ll now=++siz;
    st[now].len=st[last].len+1;
    ll p,q,cl;
    b[now]=x;
    occ[now]=1;

    for(p=last; p!=-1&&!st[p].next[c]; p=st[p].link)
        st[p].next[c]=now;
    if(p==-1)
        st[now].link=0;
    else
    {
        q=st[p].next[c];
        if(st[p].len+1==st[q].len)
            st[now].link=q;

        else
        {
            cl=++siz,st[cl].len=st[p].len+1;

            st[cl].link=st[q].link;

            memcpy(st[cl].next,st[q].next,sizeof(st[cl].next));

            for(; p!=-1&&st[p].next[c]==q; p=st[p].link)
                st[p].next[c]=cl;

            st[now].link=st[q].link=cl;
        }

    }

    last=now;
}

vector<ll>adj[ma];

void process(ll x)
{
    ll i,j;
    for(i=1;i<=siz;i++)
    {
        ll p=st[i].len;
        adj[p].pb(i);
    }

    for(i=x;i>=1;i--)
    {
        for(j=0;j<adj[i].sz;j++)
        {
             occ[st[adj[i][j]].link]+=occ[adj[i][j]];
            ll p=st[adj[i][j]].link;
            b[p]=min(b[p],b[adj[i][j]]);

        }
    }
}


////////////*********///////////////////////

vector<int> manacar(string s)
{
    ll n=s.sz,i,j;
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }
    return d1;

}

ll suf[ma];


int main()
{
    ll i,j;
    siz=0;
    memset(st,0,sizeof(st));
    st[0].link=-1;
    string t;
    cin>>t;

    for(i=0;i<ma;i++)
    {
        b[i]=inf;
        suf[i]=inf;
    }


    for(i=0;i<t.sz;i++)inser(t[i]-'a',i);
    process(t.sz);

    vector<int>v=manacar(t);
    vector<pair<ll,ll> >ans1;

    ll len=t.sz;

    ll max1=0,ind;

    for(i=0;i<v.sz;i++)
    {
            if(v[i]*2-1>max1)
            {
                ind=i-v[i]+1;
                max1=v[i]*2-1;
            }
    }

    ll now=0;
    ans1.pb(mk(ind,max1));


    for(i=len-1;i>=0;i--)
    {
        ll p=st[now].next[t[i]-'a'];
        if(p==0)break;
        now=p;
        if(b[now]>=i)
        {
            continue;
        }
        suf[i]=b[now];

    }


    for(i=0;i<v.sz;i++)
    {
        ll x=i-v[i]+1;
        ll y=i+v[i];
        ll lo=y,hi=len-1,mid,ans=-1;
        while(lo<=hi)
        {
            ll mid=(lo+hi)>>1;
            if(suf[mid]<x)
            {
                ans=mid;
                hi=mid-1;
            }
            else lo=mid+1;
        }
        if(ans==-1)continue;
        ll k=(len-ans)*2+(v[i]*2-1);
        if(k>max1)
        {
            max1=k;
            ans1.clr;
            ll r=len-ans;
            ans1.pb(mk(suf[ans]-r+1,r));
            ans1.pb(mk(x,v[i]*2-1));
            ans1.pb(mk(ans,r));

        }
    }

    cout<<ans1.sz<<endl;
    for(i=0;i<ans1.sz;i++)cout<<ans1[i].ff+1<<" "<<ans1[i].ss<<endl;









    return 0;
}


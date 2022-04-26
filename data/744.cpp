/************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <iterator>
#include <functional>
#include <numeric>
#include <limits>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double lf;
#define _N cout<<endl
#define MP make_pair
#define F first
#define S second
#define PB push_back
#define LIM 100005
#define MAXN 1000005
#define MOD 1000000007
#define lp(i,s,e) for(int i = s; i < (e); ++i)
#define lpr(i,e,s) for(int i = e; i >= s; --i)
#define lpit(i,c) for(i = (c).begin(); i != (c).end(); ++i)
#define all(x) (x).begin(), (x).end()
#define zero(a) memset((a), 0, sizeof(a))
#define iinf (1<<31)-1
#define linf (1ll<<63)-1
const double PI = acos(-1.0);
const double EPS = 1e-8;

template <class T> T abs(T a)
{
    return a>=0?a:-a;
}
template <class T> T sqr(T a)
{
    return a*a;
}
template <class T> T gcd(T a,T b)
{
    return b?gcd(b,a%b):a;
}
template <class T> T mod(T a,T b)
{
    return (a%b+b)%b;
}
template <class T> T addmod(T a,T b,T c)
{
    return (T)mod((ll)a+b,(ll)c);
}
template <class T> T mulmod(T a,T b,T c)
{
    return (T)mod((ll)a*b,(ll)c);
}
template <class T> T powmod(T a,T b,T c)
{
    return (T)mod(b?mulmod(mod(sqr((ll)powmod(a,b>>1,c)),(ll)c),(b&1LL)?a:1LL,(ll)c):1LL,(ll)c);
}
template <class T> void maxe(T &a,T b)
{
    a=max(a,b);
}
template <class T> void mine(T &a,T b)
{
    a=min(a,b);
}
template <class T> void mode(T &a,T b)
{
    a=mod(a,b);
}
template <class T> void addmode(T &a,T b,T c)
{
    a=addmod(a,b,c);
}
template <class T> void mulmode(T &a,T b,T c)
{
    a=mulmod(a,b,c);
}
template <class T> void powmode(T &a,T b,T c)
{
    a=powmod(a,b,c);
}
int iszero(lf a)
{
    return abs(a)<=EPS;
}

template <class T> void geti(T &a)
{
    a=0;
    ll b=1;
    char c=getchar();
    if(c=='-')b=-1;
    else a=c-48;
    while((c=getchar())!=' '&&c!='\n')a=a*10+c-48;
    a*=b;
}


typedef vector<int> vint;
typedef vector<bool> vbool;
typedef vector<ll> vint64;
typedef pair<int, int> pii;
typedef vector<pii > vpii;
typedef pair<ll, ll> pllll;


void fileio_in_out()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
}
void fileio_txt()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
/************************************************************************/
char s[LIM];
int m[LIM],pi[LIM],pi1[LIM],r[LIM],in[LIM];
int main()
{
    gets(s+1);
    int ln=strlen(s+1);
    for(int i=1,j=1; i<ln+1;)
    {
        // cout<<i<<" "<<j<<endl;
        while(i-(j-i)>0&&j<=ln&&s[j]==s[i-(j-i)])m[i]=j-i+1,j++;
        //cout<<m[i]<<endl;getchar();
        int ni=i+1;
        while(ni<j)
        {
            if(m[i-(ni-i)]!=j-ni)
            {
                m[ni]=min(j-ni,m[i-(ni-i)]);
                ni++;
            }
            else
            {
                m[ni]=m[i-(ni-i)];
                break;
            }
        }
        i=ni;
    }
//pi
    pi[ln]=ln+1;
    for(int i=ln-1; i>0; i--)
    {
        int j=i+1;
        while(j<ln+1&&s[i]!=s[pi[j]-1])
            j=pi[j];
        if(j==ln+1)pi[i]=ln+1;
        else pi[i]=pi[j]-1;


    }
   // lp(i,1,ln+1)cout<<pi[i]<<" ";
    pi[ln+1]=ln+2;
    pi1[0]=ln+1;
    lp(i,1,ln+1)
    {
        int j=pi1[i-1];
        while(j-1<=ln&&s[i]!=s[j-1])
            j=pi[j];
        if(j-1>ln)pi1[i]=ln+1;
        else pi1[i]=j-1;
    }
    lp(i,1,ln+1)pi1[i]=ln+1-pi1[i];
    //_N;
    //lp(i,1,ln+1)cout<<pi1[i]<<" ";
    lp(i,1,ln+1)
    {
        r[i]=max(pi1[i],r[i-1]);
        if(pi1[i]>r[i-1])
        {
            r[i]=pi1[i];
            in[i]=i-pi1[i]+1;
        }
        else
        {
            r[i]=r[i-1];
            in[i]=in[i-1];
        }
    }

  //  _N;lp(i,1,ln+1)cout<<r[i]<<" ";_N;
    int mid=0,mx=0;
    lp(i,1,ln+1){
        int ml=m[i];
        int rest=min(r[i-m[i]],ln-(i+m[i]-1));
        if(ml*2-1+rest*2>mx){mx=ml*2-1+rest*2;mid=i;}
    }
int rest=min(r[mid-m[mid]],ln-(mid+m[mid]-1));
if(rest>0){
cout<<3<<endl;
cout<<in[mid-m[mid]]<<" "<<rest<<endl;
cout<<mid-m[mid]+1<<" "<<2*m[mid]-1<<endl;
cout<<ln-rest+1<<" "<<rest<<endl;
}
else{cout<<1<<endl;cout<<mid-m[mid]+1<<" "<<2*m[mid]-1<<endl;}

    return 0;
}

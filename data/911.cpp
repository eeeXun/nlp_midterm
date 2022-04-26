#define y1 y__1
#include<algorithm>/*{{{*/
#include<cctype>
#include<cassert>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<vector>
using namespace std;
typedef long long lld;
typedef long double lf;
typedef unsigned long long uld;
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
namespace RA{
    int r(int p){return 1ll*rand()*rand()%p;}
    int r(int L,int R){return r(R-L+1)+L;}
}/*}}}*/
/******************heading******************/
const int N=1e5+5;

int n;
char s[N],rs[N];
int nex[N],l[N],p[N];
int h[N];

void get_next(char *s,int len){
    nex[1]=0;
    int i=1,j=0;
    while(i<=len){
        if(j==0||s[i]==s[j])++i,++j,nex[i]=j;
        else j=nex[j];
    }
}

int main(){
    scanf("%s",s+1);
    n=strlen(s+1);

    memcpy(rs,s,sizeof(s));
    reverse(rs+1,rs+n+1);

    get_next(rs,n+1);
    //FOR(i,1,n)printf("%c%c",rs[i]," \n"[i==n]);
    //FOR(i,1,n)printf("%d%c",nex[i]," \n"[i==n]);
    int pos=1,j=1;
    while(pos<=n){
        if(j==0||s[pos]==rs[j]){
            l[pos]=j;
            ++pos,++j;
        }
        else j=nex[j];
        if(j>n)j=nex[j];
    }
    //FOR(i,1,n)printf("%c%c",s[i]," \n"[i==n]);
    FOR(i,1,n)if(l[i])p[i]=i-l[i]+1;
    //FOR(i,1,n)printf("%d%c",l[i]," \n"[i==n]);
    //FOR(i,1,n)printf("%d%c",p[i]," \n"[i==n]);
    FOR(i,1,n) if(l[i-1]>l[i])l[i]=l[i-1],p[i]=p[i-1];
    //puts("---");
    //FOR(i,1,n)printf("%d%c",l[i]," \n"[i==n]);
    //FOR(i,1,n)printf("%d%c",p[i]," \n"[i==n]);

    int L=0,R=0;
    FOR(i,1,n){
        if(i<R)h[i]=min(R-i,h[L+R-i]);
        while(1<=i-h[i]-1&&i+h[i]+1<=n&&s[i-h[i]-1]==s[i+h[i]+1])++h[i];
        if(i+h[i]>R)L=i-h[i],R=i+h[i];
    }
    //FOR(i,1,n)printf("%d%c",h[i]," \n"[i==n]);
    int ans=0;
    FOR(i,1,n)ans=max(ans,h[i]*2+1+2*min(l[i-h[i]-1],n-i-h[i]));
    //printf("%d\n",ans);
    FOR(i,1,n){
        if(ans==h[i]*2+1+2*min(l[i-h[i]-1],n-i-h[i])){
            int x1=p[i-h[i]-1],y1=min(l[i-h[i]-1],n-i-h[i]);
            int x2=i-h[i],y2=h[i]*2+1;
            int x3=n-y1+1,y3=y1;
            int k=!!y1+!!y2+!!y3;
            printf("%d\n",k);
            if(y1)printf("%d %d\n",x1,y1);
            if(y2)printf("%d %d\n",x2,y2);
            if(y3)printf("%d %d\n",x3,y3);
            return 0;
        }
    }
    return 0;
}

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <queue>
using namespace std;
#define   sqr(a)         ((a)*(a))
#define   rep(i,a,b)  for(i=(a);i<(b);i++)
#define   per(i,a,b)  for(i=((a)-1);i>=(b);i--)
#define   PER(i,n)     per(i,n,0)
#define   REP(i,n)     rep(i,0,n)
#define   clr(a)      memset((a),0,sizeof (a));
#define   mabs(a)     ((a)>0?(a):(-(a)))
#define   inf         1000000000
#define  MAXV     100001
#define  MAXN     201000
#define  eps      1e-6
int N;
char cs[MAXN];
int r[MAXN];
int tx[MAXN];
int ty[MAXN];
int pai[MAXN];
int sa[MAXN];
bool deng(int *y,int a,int b,int l)
{
	return y[a]==y[b]&&y[a+l]==y[b+l];
}
void dasuffix(int*r,int n,int m)
{
    int*x=tx,*y=ty;
	int i,j;
	REP(i,m) pai[i]=0;
	REP(i,n) pai[x[i]=r[i]]++;
	rep(i,1,m) pai[i]+=pai[i-1];
	PER(i,n) sa[--pai[x[i]]]=i;
	int p=1;
	for (j=1;p<n;j<<=1,m=p)
	{
		p=0;
		rep(i,n-j,n) y[p++]=i;
		REP(i,n) if(sa[i]>=j) y[p++]=sa[i]-j;
        REP(i,m) pai[i]=0;
    	REP(i,n) pai[x[y[i]]]++;
	    rep(i,1,m) pai[i]+=pai[i-1];
	    PER(i,n) sa[--pai[x[y[i]]]]=y[i];
		swap(x,y);
		x[sa[0]]=0,p=1;
		rep(i,1,n) x[sa[i]]=deng(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rank[MAXN];
int height[MAXN];
void calheight(int *r,int n)
{
	int i,j;
    REP(i,n+1) rank[sa[i]]=i;
	int k=0;
	REP(i,n)
	{
		if(k>0) k--;
		j=sa[rank[i]-1];
		for (;r[i+k]==r[j+k];k++);
		height[rank[i]]=k;
	}
}
int M[MAXN][20];
void initrmq(int n)
{
	int i,j;
    REP(i,n) M[i][0]=height[i];
	for (j=1;(1<<j)<=n;j++)
	{
	    for (i=0;i+(1<<(j-1))<n;i++)
	    {
            M[i][j]=min(M[i][j-1],M[i+(1<<(j-1))][j-1]);
	    }
	}
}
int askrmq(int a,int b)
{
    int i;
	REP(i,20) if((1<<i)>b-a+1) break;
	i--;
	return min(M[a][i],M[b-(1<<i)+1][i]);
}
int lcp(int a,int b)
{
	a=rank[a];
	b=rank[b];
	if(a>b) a^=b,b^=a,a^=b;
	return askrmq(a+1,b);
}
int main()
{
	int i,j,k;
    scanf("%s",cs);
	int tn=strlen(cs);
	cs[tn]=1;
	REP(i,tn) cs[2*tn-i]=cs[i];
	cs[tn*2+1]=0;
	N=strlen(cs);
    REP(i,N+1) r[i]=cs[i];
	dasuffix(r,N+1,128);
	calheight(r,N);
	initrmq(N+1);
	int rpos[MAXN];
	REP(i,MAXN) rpos[i]=inf;
	j=0;
	rep(i,1,tn+1)
	{
	    for(;j<tn;j++) if(lcp(j,tn+1)>=i)break;
	    if(j==tn)break;
	    rpos[i]=j+i-1;
    }
    int qr[MAXN];clr(qr);
    j=0;
    REP(i,tn)
    {
        while (rpos[j+1] <= i)++j;
        qr[i] = j;
    }
    int len=-1;
    vector<pair<int,int> > ans;
    REP(i,tn)
    {
        int zl=lcp(i,N-i-1);
        int lt=i-zl;
        int rt=i+zl;
        int l=(lt>=0)?min(qr[lt],tn-rt):0;
        int tret=zl*2-1+2*l;
        if(tret<=len) continue;
        len=tret;
        ans.clear();
        if(l>0) ans.push_back(make_pair(rpos[l]-l+1,l));
        ans.push_back(make_pair(i-zl+1,2*zl-1));
        if(l>0) ans.push_back(make_pair(tn-l,l));
    }
    printf("%d\n",ans.size());
	REP(i,ans.size())
	{
	    printf("%d %d\n",ans[i].first+1,ans[i].second);
    }
}


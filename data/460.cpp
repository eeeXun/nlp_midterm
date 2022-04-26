#define _CRT_SECURE_NO_DEPRECATE
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#pragma comment(linker, "/STACK:16777216")
using namespace std;
#define pb push_back
#define ppb pop_back
#define pi 3.1415926535897932384626433832795028841971
#define mp make_pair
#define x first
#define y second
#define sqr(a) (a)*(a)
#define D(a,b) sqrt(((a).x-(b).x)*((a).x-(b).x)+((a).y-(b).y)*((a).y-(b).y))
#define pii pair<int,int>
#define pdd pair<double,double>
#define INF 1000000000
#define FOR(i,a,b) for (int _n(b), i(a); i <= _n; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;i--)
#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))
#define rep(i,n) FOR(i,1,(n))
#define rept(i,n) FOR(i,0,(n)-1)
#define L(s) (int)((s).size())
#define C(a) memset((a),0,sizeof(a))
#define VI vector <int>
#define ll long long
int a,b,c,d,i,j,n,m,k,ans,bo;
vector<pii> abl;
char str[111111];
int len[111111];
const int MX=1<<17;
int mx1[MX*2];
inline void update1(int l,int a)
{
	l+=MX;
	for (mx1[l]=a;l>>=1;) mx1[l]=max(mx1[l*2],mx1[l*2+1]);
}
inline int fnd1(int l,int r)
{
	int ans=-INF;
	for (l+=MX,r+=MX;l<=r;l=(l+1)/2,r=(r-1)/2) ans=max(ans,max(mx1[l],mx1[r]));
	return ans;
}
unsigned ll h1[111111],h2[111111],pw[111111],so;
const int pp=37;
inline void check(int beg,char *str,unsigned ll *h1,unsigned ll *h2,unsigned ll sub,int n)
{
	int l=0,r=n/2;
	while (r-l>1)
	{
		int xx=(r+l)/2;
		if (h1[xx]-sub*pw[xx+1]==h2[n-xx-1]) l=xx; else
		r=xx;
	}
	if (h1[r]-sub*pw[r+1]==h2[n-r-1]) l=r;
	if (h1[l]-sub*pw[l+1]==h2[n-l-1]) ++l; else
	l=0;
	int bl=l;
	int fl=bl,fr=n-l-1;
	
	l=0,r=fr-fl+1;
	while (r-l>1)
	{
		int xx=(r+l)/2;
		int nl=fl+xx,nr=fr-xx;
		if (fnd1(nl+beg,nr+beg)>=xx) l=xx; else
		r=xx;
	}
	if (fnd1(fl+r+beg,fr-r+beg)>=r) l=r;
	if (2*bl+2*l+1>ans)
	{
		ans=2*bl+2*l+1;
		bo=beg;
		so=sub;
	}
}
inline void build(int beg,char *str,unsigned ll *h1,unsigned ll *h2,unsigned ll sub,int n)
{
	int l=0,r=n/2;
	while (r-l>1)
	{
		int xx=(r+l)/2;
		if (h1[xx]-sub*pw[xx+1]==h2[n-xx-1]) l=xx; else
		r=xx;
	}
	if (h1[r]-sub*pw[r+1]==h2[n-r-1]) l=r;
	if (h1[l]-sub*pw[l+1]==h2[n-l-1]) ++l; else
	l=0;
	l=min(l,n/2);
	if (l==n/2 && n%2==0) --l;
	int bl=l;
	int fl=bl,fr=n-l-1;
	abl.clear();
	FOR(i,fl,fr)
	{
		int rr=len[i+beg];
		rr=min(rr,i-fl);
		rr=min(rr,fr-i);
		int cur=2*bl+2*rr+1;
		if (cur==ans)
		{
			abl.pb(mp(beg+1,bl));
			abl.pb(mp(i+beg-rr+1,2*rr+1));
			abl.pb(mp(n+beg-bl+1,bl));
			return;
		}
	}
}
int main()
{
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	gets(str);
	n=(int)strlen(str);
	{
		int l=0, r=-1;
		for (int i=0; i<n; ++i) {
			int k = (i>r ? 0 : min (len[l+r-i], r-i)) + 1;
			while (i+k < n && i-k >= 0 && str[i+k] == str[i-k])  ++k;
			len[i] = --k;
			if (i+k > r)
				l = i-k,  r = i+k;
			update1(i,len[i]);
		}
	}
	rept(i,n)
	{
		if (!i) h1[i]=str[i]-'a'+1; else
		h1[i]=h1[i-1]*pp+str[i]-'a'+1;
	}
	FORD(i,n-1,0)
	{
		if (i==n-1) h2[i]=str[i]-'a'+1; else
		h2[i]=h2[i+1]*pp+str[i]-'a'+1;
	}
	pw[0]=1;
	rep(i,n) pw[i]=pw[i-1]*pp;
	ans=0;
	unsigned ll sub=0;
	rept(i,n)
	{
		check(i,str+i,h1+i,h2+i,sub,n-i);
		sub=sub*pp+str[i]-'a'+1;
	}
	build(bo,str+bo,h1+bo,h2+bo,so,n-bo);
	a=0;
	rept(i,L(abl)) if (abl[i].y!=0) ++a;
	printf("%d\n",a);
	rept(i,L(abl)) if (abl[i].y!=0) printf("%d %d\n",abl[i].x,abl[i].y);
}

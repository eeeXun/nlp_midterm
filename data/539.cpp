#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker,"/STACK:16777216")
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#define FOR(i,a,n) for(int i=(a);i<(n);i++)
#define REP(i,n) FOR(i, 0, n)
#define mp make_pair
#define pb push_back
#define all(v) v.begin(),v.end()
#define lint long long
#define PII pair <int,int>
#define PDD pair <double,double>
#define VI vector <int>
#define VII vector < PII >
#define X first
#define Y second
#define sz(a) (int)(a.size())
using namespace std;


const int DIM=110*1000;
char s[DIM];
int ls,pol[DIM];
lint st[DIM],hh[DIM],hr[DIM];
int tr[4*DIM],trp[4*DIM];
void push(int x,int val,int v=1,int vl=0,int vr=ls-1){
	if (vl==vr){
		tr[v]=val;
		trp[v]=vl;
		return;
	}
	int vs=(vl+vr)/2;
	if (x<=vs) push(x,val,v*2,vl,vs);
	else push(x,val,v*2+1,vs+1,vr);
	if (tr[v*2]>tr[v*2+1]) trp[v]=trp[v*2];
	else trp[v]=trp[v*2+1];
	tr[v]=max(tr[v*2],tr[v*2+1]);
}
int get(int l,int r,int v=1,int vl=0,int vr=ls-1){
	if (vl==l && vr==r) return trp[v];
	int vs=(vl+vr)/2;
	if (r<=vs) return get(l,r,v*2,vl,vs);
	else if (l>vs) return get(l,r,v*2+1,vs+1,vr);
	else {
		int p1=get(l,vs,v*2,vl,vs);
		int p2=get(vs+1,r,v*2+1,vs+1,vr);
		if (pol[p1]>pol[p2]) return p1;
		else return p2;
	}
}
bool eq(int l1,int l2,int s){
	if (l1<0 || l2<0 || l1+s>ls || l2+s>ls) return false;
	lint h1=hh[l1+s]-hh[l1]*st[s];
	lint h2=hr[l2]-hr[l2+s]*st[s];
	return (h1==h2);
}
void init(){
	st[0]=1;
	FOR(i,1,DIM) st[i]=st[i-1]*137;
	REP(i,ls) hh[i+1]=hh[i]*137+s[i];
	for (int i=ls-1;i>=0;i--) hr[i]=hr[i+1]*137+s[i];
	REP(i,ls){
		int l=0,r=ls,s;
		while (r-l>1){
			s=(l+r)/2;
			if (eq(i-s,i+1,s)) l=s;
			else r=s;
		}
		pol[i]=l;
		push(i,pol[i]);
	}
}
int main(){
	//freopen("t.in","r",stdin);
	scanf("%s",s);
	ls=strlen(s);
	init();
	int tpos=get(0,ls-1),ts2=ls,ts1=0,td;
	td=pol[tpos];
	lint th=0;
	int best;
	VI ans(4,0);
	ans[0]=ts1;
	ans[1]=ts2;
	ans[2]=tpos;
	ans[3]=td;
	best=2*td+1;
	while (1){
		ts2--;
		while (ts1+ls-ts2<ts2 && !eq(ts1,ts2,ls-ts2)) ts1++;
		if (ts1+ls-ts2>=ts2) break;
		if (tpos-td<ts1+ls || tpos+td>=ts2){
			bool f=false;
			while (1){
				if (td<0) break;
				int l=ts1+ls-ts2+td,r=ts2-1-td;
				if (l<=r){
					int pp=get(l,r);
					if (pol[pp]>=td){
						tpos=pp;
						f=true;
						break;
					}
				}
				td--;
			}
			if (!f) break;
		}
		if ((ls-ts2)*2+td*2+1>best){
			ans[0]=ts1;
			ans[1]=ts2;
			ans[2]=tpos;
			ans[3]=td;
			best=td*2+1+(ls-ts2)*2;
		}
	}
	VI v;
	if (ans[1]!=ls){
		v.pb(ans[0]);
		v.pb(ls-ans[1]);
		v.pb(ans[2]-ans[3]);
		v.pb(ans[3]*2+1);
		v.pb(ans[1]);
		v.pb(ls-ans[1]);
	} else {
		v.pb(ans[2]-ans[3]);
		v.pb(ans[3]*2+1);
	}
	printf("%d\n",sz(v)/2);
	REP(i,sz(v)/2) {
		printf("%d %d\n",v[i*2]+1,v[i*2+1]);
	}
	return 0;
}


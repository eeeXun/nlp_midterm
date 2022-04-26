#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define fi first
#define se second
const int mo[]={998244353,1000000007};
const pii se={2333,9973};
pii operator + (const pii & a,const pii & b)
{
	return pii((a.fi+b.fi)%mo[0],(a.se+b.se)%mo[1]);
}
pii operator - (const pii & a,const pii & b)
{
	return pii((a.fi-b.fi+mo[0])%mo[0],(a.se-b.se+mo[1])%mo[1]);
}
pii operator * (const pii & a,const pii & b)
{
	return pii((ll)a.fi*b.fi%mo[0],(ll)a.se*b.se%mo[1]);
}
pii rs[100005],hs[100005],powse[100005];
pii gethash(pii * h,int l,int r)
{
	return h[r] - h[l-1]*powse[r-l+1];
}
char S[100005];
int f1[100005],f2[100005];
int Max(int x,int y)
{
	if(f2[x] < f2[y])
		return y;
	else 
		return x;
}
int maxn[19][100005],lg2[100005];
int askmax(int l,int r)
{
	if(l > r)
		return 0;
	int len = lg2[r-l+1];
	return Max(maxn[len][l],maxn[len][r-(1<<len)+1]);
}
int main()
{
	scanf("%s",S+1);
	int n = strlen(S+1);
	powse[0] = pii(1,1);
	for(int i=1;i<=n;i++)
		powse[i] = powse[i-1] * se;
	
	hs[0] = pii(0,0);
	for(int i=1;i<=n;i++)
		hs[i] = hs[i-1] * se + pii(S[i],S[i]);
	rs[0] = pii(0,0);
	for(int i=1;i<=n;i++)
		rs[i] = rs[i-1] * se + pii(S[n-i+1],S[n-i+1]);
	
	for(int i=1;i<=n;i++) {
		int l=1,r=(n-i+1)/2,res=0;
		while(l<=r) {
			int mid = (l + r) >> 1;
			if(gethash(rs,1,mid) == gethash(hs,i,i+mid-1))
				res = mid , l = mid + 1;
			else 
				r = mid - 1;
		}
		f1[i] = res;
		
		l=1,r=min(i,n-i+1),res=-1;
		while(l<=r) {
			int mid = (l + r) >> 1;
			if(gethash(hs,i,i+mid-1) == gethash(rs,n-i+1,n-i+mid))
				res = mid , l = mid + 1;
			else 
				r = mid - 1;
		}
		f2[i] = res;
	}
	for(int i=1;i<=n;i++)
		f1[i] = max(f1[i] , f1[i-1]);
	for(int i=1;i<=n;i++)
		maxn[0][i] = i;
	for(int j=1;j<=18;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			maxn[j][i] = Max(maxn[j-1][i] , maxn[j-1][i+(1<<(j-1))]);
	lg2[1]=0;
	for(int i=2;i<=n;i++)
		lg2[i] = lg2[i>>1] + 1;

	pii ansf[3];
	int ans = 0;
	for(int j=1,i=1;i<=n;i++) {
		while(j<=n && f1[j] < i)
			j++;
		if(f1[j] < i)
			break;
		int l=1,r=n,res=-1;
		int res2=-1;
		while(l<=r) {
			int mid = (l + r) >> 1;
			int lt = j+f1[j]+mid-1;
			int rt = n-f1[j]-mid+1;
			int pos = askmax(lt,rt);
			if(lt <= rt && f2[pos] >= mid)
				res2 = mid , res = pos , l = mid + 1;
			else 
				r = mid - 1;
		}
		if(res != -1) {
			int tmp = f1[j]*2 + res2*2-1;
			if(tmp > ans) {
				ans = tmp;
				ansf[0] = pii(j,f1[j]);
				ansf[1] = pii(res-res2+1,res2*2-1);
				ansf[2] = pii(n-f1[j]+1,f1[j]);
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(f2[i]*2-1 > ans) {
			ans = f2[i]*2;
			ansf[0] = pii(i-f2[i]+1,f2[i]*2-1);
			ansf[1] = ansf[2] = pii(-1,-1);
		}
	if(ansf[0].fi+ansf[0].se == ansf[1].fi && ansf[1].fi+ansf[1].se == ansf[2].fi) {
		ansf[0] = pii(ansf[0].fi,ansf[0].se+ansf[1].se+ansf[2].se);
		ansf[1] = ansf[2] = pii(-1,-1);
	}
	if(ansf[1] == pii(-1,-1)) {
		cout << 1 << endl;
		cout << ansf[0].fi << ' ' << ansf[0].se << endl;
	} else {
		cout << 3 << endl;
		for(int k=0;k<3;k++)
			cout << ansf[k].fi << ' ' << ansf[k].se << endl;
	}
	return 0;
}

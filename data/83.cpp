#include<bits/stdc++.h>
#define pub push_back
using namespace std;

typedef long long ll;

const int N = 2e6+10;
const int Mb = 256;
const int Mod = 1e9+7;
const int LG=20;

int n;
string s;
vector <ll> h[N];
int mxp[N],mx[LG][N];
int ind,len,g1,ans;

void Build_hash();
void Find_mxpal();
void Solve();
void Build_dp_mx();
int Get(int,int);
ll Get_hash(int,int,int);
ll Tavan(ll,ll);
void Output();

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> s, n = s.size();
	Build_hash();
	Find_mxpal();
	Build_dp_mx();
	Solve();
	Output();
}

void Build_hash(){
	h[0].pub(s[0]);
	for(int i = 1;i < n;i++)
		h[0].pub((h[0].back()*Mb + s[i]) % Mod);
	h[1].pub(s[n-1]);
	for(int i = n-2;0 <= i;i--)
		h[1].pub((h[1].back()*Mb + s[i]) % Mod);
	reverse(h[1].begin(),h[1].end());
}


void Find_mxpal(){
	for(int i = 0;i < n;i++){
		int t=1, f = min(i+2,n-i+1);
		while(f-t != 1){
			int mid = (t+f)/2;
			if(Get_hash(0,i-mid+1,i) == Get_hash(1,i+1,i+mid))
				t = mid;
			else
				f = mid;
//			cout<<Get_hash(0,i-mid+1,i)<<endl;
		}
		mxp[i] = t;
//		cout<<"i="<<i<<" mxp="<<mxp[i]<<endl;
		if(2*t-1 > ans)
			ans = max(ans,2*t-1), g1 = t;
	}
}

// [ )
ll Get_hash(int type,int l,int r){
	if(type == 0){
		if(l==0)
			return h[0][r-1];
		return ((h[0][r-1]-h[0][l-1]*Tavan(Mb,r-l)) % Mod + Mod)%Mod; 
	}
	if(r == n)
		return h[1][l];
	return ((h[1][l]-h[1][r]*Tavan(Mb,r-l)) % Mod + Mod)%Mod; 
}
// l r
// 

void Solve(){
	int pnt1 = 0,pnt2;
	for(int i=1;i<=n/2;i++){
		pnt2 = n-i;
		while(pnt1 + i < pnt2 and Get_hash(0,pnt1,pnt1+i) != Get_hash(1,n-i,n))
			pnt1++;
		if(pnt1+i >= pnt2)
			break;
		int t = 1,f = n+1;
		while(f-t!=1){
			int mid = (f+t)/2;
			if(Get(pnt1+i-1+mid,pnt2-mid+1) >= mid)
				t = mid;
			else
				f = mid;
		//	if(mid == 2)
//				cout<<pnt1+i-1+mid<<" "<<pnt2-mid+1<<" "<<Get(1,0,n,pnt1+i-1+mid,pnt2-mid+1)<<endl;
		}
		if(2*i+2*t-1 > ans)
			ans = 2*i+2*t-1, len=i, ind = pnt1, g1 = t;
//		cout<<"i="<<i<<" t="<<t<<endl;
	}
}

int Get(int L,int R){
	int res=0;
	for(int i = LG - 1;0 <= i;i--)
		if(L+(1<<i) <= R)
			res = max(res,mx[i][L]), L+=(1<<i);
	return res;
}

void Build_dp_mx(){
	for(int i=0;i<LG;i++)
		for(int j=0;j<n;j++)
			if(i==0)
				mx[i][j] = mxp[j];
			else
				mx[i][j] = max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
}


ll Tavan(ll x,ll y){
	if(y==0)
		return 1;
	ll z = Tavan(x,y/2);
	z = (z*z) % Mod;
	if(y & 1)
		return (z*x)%Mod;
	return z;
}

void Output(){
	int l1 = ind;
	int l3 = n-len, l2;
	for(int i = ind + len + g1-1;i < n-len;i++){
		if(mxp[i] == g1){
			l2 = i-g1+1;
			break;
		}
	}
	if(len!=0){
		cout<<3<<endl;
		cout<<l1+1<<" "<<len<<endl;
		cout<<l2+1<<" "<<g1*2-1<<endl;
		cout<<l3+1<<" "<<len<<endl;
	}else{
		cout<<1<<endl;
		cout<<l2+1<<" "<<g1*2-1<<endl;
	}
}




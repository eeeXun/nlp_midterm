#include <bits/stdc++.h>
#include <iomanip>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define FAST std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define DECIMAL(n)  std::cout << std::fixed;std::cout << std::setprecision(n);
#define hell 1000000007
#define narak 998244353
#define PI 3.14159265358979323844
#define mp make_pair
#define pb push_back
#define fi first 
#define se second
#define ALL(v) v.begin(), v.end()
#define SORT(v) sort(ALL(v))  
#define REVERSE(v) reverse(ALL(v))
#define endl "\n"
#define maxc(v) max_element(all(v))
#define minc(v) min_element(all(v))
#define sqr(a) (a)*(a)
#define GCD(m,n) __gcd(m,n)
#define LCM(m,n) m*(n/GCD(m,n))
#define inputarr(a,n) for(int xxx=0;xxx<n;++xxx) cin>>a[xxx]
#define initarr(a,n,x) for (int xxx=0;xxx<n;++xxx) a[xxx]=x
#define rep(i,l,r)    for(int i = l; r>=l?(r>=i):(r<=i); i+=(-1+2*(r>=l)))
#define trav(a, x) for(auto& a : x)
#define sz(a) (int)a.size()
#define sl(a) (int)a.length()
#define invect(data,n,commands) for(int xxx = 0;xxx<n;xxx++){int tmp;cin>>tmp;data.pb(tmp);commands}
#define inset(data,n,commands) for(int xxx = 0;xxx<n;xxx++){int tmp;cin>>tmp;data.insert(tmp);commands}
#define display(x) trav(a,x) cout<<a<<" ";cout<<endl
#define debug cerr<<"bhau"<<endl

#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    std::cerr << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');std::cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}

template<typename T, typename U> static inline void amin(T &x, U y) 
{ 
    if (y < x) 
        x = y; 
}
template<typename T, typename U> static inline void amax(T &x, U y) 
{ 
    if (x < y) 
        x = y; 
}

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

#define ll long long
#define ld long double 
#define pii std::pair<int, int> 
#define pll std::pair<ll, ll>  
#define vi vector<int>  
#define vvi vector<vi > 
#define vii vector<pii >
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 

/*----------------------Graph Moves----------------*/
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
/*------------------------------------------------*/

//primes for hashing 937,991,1013,1409,1741

pii operator+(pii a, pii b)
{
	return {a.fi+b.fi,a.se+b.se};
}
pll operator+(pll a, pll b)
{
	return {a.fi+b.fi,a.se+b.se};
}
std::ostream& operator<<(std::ostream& out,pii a)
{
	out<<a.fi<<" "<<a.se<<endl;
	return out;
}
std::ostream& operator<<(std::ostream& out,pll a)
{
	out<<a.fi<<" "<<a.se<<endl;
	return out;
}
std::istream& operator>>(std::istream& in,pii &a)
{
    in>>a.fi>>a.se;
    return in;
}
std::istream& operator>>(std::istream& in,pll &a)
{
    in>>a.fi>>a.se;
    return in;
}

using namespace std;
using namespace __gnu_pbds;
const int MAXN=100005;
const int MAX_LOGN=18;
class SparseTable{
	int dp[MAX_LOGN][MAXN];
public:
	void build(vector<int> b)
	{
		int n=sz(b);
		for (int i = 0; i < n; ++i)
		{
			dp[0][i]=b[i];
		}
		int t=n;
		int log=0;
		while(t>1)
			log++,t>>=1;
		for (int i = 1; i <=log; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				dp[i][j]=dp[i-1][j];
				if(j+(1<<(i-1))<n)
				{
					amax(dp[i][j],dp[i-1][j+(1<<(i-1))]);
				}
			}
		}
	}
	int query(int l,int r)
	{
		if(l>r)return 0;
		int len=(r-l+1);
		int log=0;
		while(len>1)
			log++,len>>=1;
		return max(dp[log][l],dp[log][r-(1<<log)+1]);
	}
};
ll modInverse(ll a, ll m) 
{ 
    ll m0 = m; 
    ll y = 0, x = 1; 
  
    if (m == 1) 
      return 0; 
  
    while (a > 1) 
    { 
        // q is quotient 
        ll q = a / m; 
        ll t = m; 
  
        // m is remainder now, process same as 
        // Euclid's algo 
        m = a % m, a = t; 
        t = y; 
  
        // Update y and x 
        y = x - q * y; 
        x = t; 
    } 
  
    // Make x positive 
    if (x < 0) 
       x += m0; 
  
    return x; 
}
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
void meow()
{
	string x;
	cin>>x;
	ll p1=937;
	ll p2=991;
	ll pp1[sl(x)]={1};
	ll pp2[sl(x)]={1};
	ll mp1[sl(x)]={1};
	ll mp2[sl(x)]={1};
	for (int i = 1; i < sl(x); ++i)
	{
		pp1[i]=(pp1[i-1]*p1)%hell;
		pp2[i]=(pp2[i-1]*p2)%hell;		
		mp1[i]=modInverse(pp1[i],hell);
		mp2[i]=modInverse(pp2[i],hell);
	}
	ll prefh1[sl(x)]={x[0]};
	ll prefh2[sl(x)]={x[0]};
	ll suffh1[sl(x)];
	ll suffh2[sl(x)];
	suffh1[sl(x)-1]=x[sl(x)-1];
	suffh2[sl(x)-1]=x[sl(x)-1];
	rep(i,1,sl(x)-1)
	{
		prefh1[i]=(prefh1[i-1] + pp1[i]*x[i])%hell;
		prefh2[i]=(prefh2[i-1] + pp2[i]*x[i])%hell;
	}
	rep(i,sl(x)-2,0)
	{
		suffh1[i]=(suffh1[i+1] + pp1[sl(x)-i-1]*x[i])%hell;
		suffh2[i]=(suffh2[i+1] + pp2[sl(x)-i-1]*x[i])%hell;
	}
	// display(suffh1);
	// display(prefh1);
	// display(suffh2);
	// display(prefh2);
	int maxp[sl(x)];
	for (int i = 0; i < sl(x); ++i)
	{
		int low=0;
		int high=min(i,sl(x)-i-1);
		while(high-low>0)
		{
			int mid=(high+low+1)/2;
			ll fh1,fh2,bh1,bh2;
			// range is [i-mid,i+mid]
			fh1=(prefh1[i+mid])%hell;
			fh2=(prefh2[i+mid])%hell;
			if(i-mid-1>=0)
			{
				fh1=(fh1-prefh1[i-mid-1]+hell)%hell;
				fh2=(fh2-prefh2[i-mid-1]+hell)%hell;
			}
			bh1=(suffh1[i-mid])%hell;
			bh2=(suffh2[i-mid])%hell;
			if(i+mid+1<sl(x))
			{
				bh1=(bh1-suffh1[i+mid+1]+hell)%hell;
				bh2=(bh2-suffh2[i+mid+1]+hell)%hell;
			}
			fh1=(fh1*mp1[i-mid])%hell;
			fh2=(fh2*mp2[i-mid])%hell;

			bh1=(bh1*mp1[sl(x)-1-(i+mid)])%hell;
			bh2=(bh2*mp2[sl(x)-1-(i+mid)])%hell;
			int flag=(fh1==bh1)&&(fh2==bh2);
			if(flag)
				low=mid;
			else high=mid-1;
		}
		maxp[i]=low;
	}
	//display(maxp);
	string y="";
	for (int i = 0; i < sl(x); ++i)
	{
		y+=x[sl(x)-1-i];
	}
	vi z=z_function(y + '$' + x);
	//display(y+'$'+x);
	//display(z);
	vi zz(sl(x),0);
	for (int i = sl(x)+1; i < 2*sl(x)+1; ++i)
	{
		amax(zz[i+z[i]-sl(x)-2],z[i]);
	}
	rep(i,sl(x)-2,0)
	{
		amax(zz[i],zz[i+1]-1);
	}
	//display(zz);
	int prefs,preflen,mids,midlen;
	int maxl=0;
	SparseTable st;
	st.build(zz);
	int leftmostocc[sl(x)+1];
	initarr(leftmostocc,sl(x)+1,hell);
	for (int i = 0; i < sl(x); ++i)
	{
		amin(leftmostocc[zz[i]],i);
	}
	//display(leftmostocc);
	for (int i = 0; i < sl(x); ++i)
	{
		int midl=maxp[i]*2 + 1;
		int prefl=0;
		if(i-maxp[i]>0)
			prefl=min(i-maxp[i],st.query(0,i-maxp[i]-1));
		amin(prefl,sl(x)-(i+maxp[i])-1);
		amax(maxl,2*prefl+midl);
		//trace(prefl,midl);
		if(maxl==(2*prefl+midl))
		{
			prefs=leftmostocc[prefl]-prefl+2;
			preflen=prefl;
			mids=i-maxp[i]+1;
			midlen=midl;
		}
	}
	//trace(sl(x));
	if(preflen==0)
	{
		cout<<1<<endl;
		cout<<mids<<" "<<midlen;
	}else{
		cout<<3<<endl;
		cout<<prefs<<" "<<preflen<<endl;
		cout<<mids<<" "<<midlen<<endl;
		cout<<(sl(x)-preflen+1)<<" "<<preflen<<endl;
	}
}
int main()
{
    FAST;
    int testcases=1;
    //cin>>testcases;
    for(int i=0;i<testcases;++i)
    {
    	meow();
    }
    return 0;
}
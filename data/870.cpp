#include<iostream>
#include<algorithm>
#include<vector>
#define MOD 1000000007
#define f first
#define s second
#define mp make_pair
#define SECURITY 4
using namespace std;

pair<int, int> eea(int a, int b) {
	if(b == 0)
		return mp(1, 0);
	auto ret = eea(b, a%b);
	return mp(ret.s, ret.f - a/b*ret.s);
}

struct Modint {
	int val;
	
	Modint(int nval = 0) {
		val = nval;
	}
	
	Modint& operator+=(Modint r) {
		val = (val + r.val) % MOD;
		return *this;
	}
	Modint& operator-=(Modint r) {
		val = (val + MOD - r.val) % MOD;
		return *this;
	}
	Modint& operator*=(Modint r) {
		val = 1LL * val * r.val % MOD;
		return *this;
	}
	Modint& operator/=(Modint r) {
		int ret = (eea(r.val, MOD).f + MOD) % MOD;
		return operator*=(ret);
	}
	
	Modint operator+(Modint r) {return Modint(*this)+=r;}
	Modint operator-(Modint r) {return Modint(*this)-=r;}
	Modint operator*(Modint r) {return Modint(*this)*=r;}
	Modint operator/(Modint r) {return Modint(*this)/=r;}
};

Modint hpow[100001], hpowrev[100001];

struct Hashstring {
	vector<Modint> hash;
	
	void construct(string base, int offset) {
		hash.resize(base.size() + 1, 0);
		for(int i=0;i<(int)base.size();i++)
			hash[i+1] = hash[i] + hpow[i] * ( (base[i]-'a' + offset) % 30);
	}
	
	Modint segment(int l, int r) {
		return (hash[r] - hash[l]) * hpowrev[l];
	}
};


pair<int, int> inReverse(pair<int, int> val, int n) {
	return mp(n - val.s, n - val.f);
}


Hashstring forwhash[SECURITY], revhash[SECURITY];

bool valid(pair<int, int> span, pair<int, int> revspan) {
	for(int i=0;i<SECURITY;i++)
		if(forwhash[i].segment(span.f, span.s).val != revhash[i].segment(revspan.f, revspan.s).val)
			return false;
	return true;
}

bool isPalindrome(pair<int, int> span, int n) {
	pair<int, int> revspan = mp(0, span.f+1);
	revspan.f = revspan.s - (span.s - span.f);
	
	if(span.s > n || revspan.f < 0)
		return false;
	return valid(span, inReverse(revspan, n) );
}


//--------------------------------------------------------
//Main function here

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	hpow[0] = 1;
	hpowrev[0] = 1;
	hpow[1] = 30;
	hpowrev[1] = Modint(1) / hpow[1];
	
	for(int i=2;i<=100000;i++) {
		hpow[i] = hpow[i-1] * hpow[1];
		hpowrev[i] = hpowrev[i-1] * hpowrev[1];
	}
	
	//Preprocessing done
	string s;
	cin >> s;
	int n = s.size();
	
	for(int i=0;i<SECURITY;i++)
		forwhash[i].construct(s, i);
	reverse(s.begin(), s.end() );
	for(int i=0;i<SECURITY;i++)
		revhash[i].construct(s, i);
	
	
	vector<int> edgelen(n+1, 0), edgelast(n+1, 0);
	
	{
		for(int i=0;i<n;i++) {
			int len = 0;
			
			for(int tpow = (1<<19); tpow >0; tpow /= 2)
				if(i+len+tpow <= n && valid(mp(i, i+len+tpow), mp(0, len+tpow) ) )
					len += tpow;
			edgelen[i+len] = max(edgelen[i+len], len);
		}
		
		edgelast[n] = n;
		for(int i=n-1;i>=0;i--) {
			edgelast[i] = i;
			edgelen[i] = max(edgelen[i], edgelen[i+1] - 1);
		}
		
		for(int i=1;i<=n;i++)
			if(edgelen[i-1] > edgelen[i]) {
				edgelen[i] = edgelen[i-1];
				edgelast[i] = edgelast[i-1];
			}
		
	}
	
	
	//Finally find all the palindromes
	pair<int, vector<pair<int, int> > > result;
	for(int i=0;i<n;i++) {
		
		int len = 0;
		for(int tpow = 1<<19; tpow > 0; tpow /= 2)
			if(isPalindrome(mp(i, i+len+tpow), n) )
				len += tpow;
		
		int elen = min(edgelen[i-len+1], n - len - i);
		int csz = elen * 2 + len*2-1;
		vector<pair<int, int> > spans;
		
		if(elen > 0)
			spans.push_back(mp(edgelast[i-len+1] - edgelen[i-len+1], elen) );
		
		spans.push_back(mp(i-len+1, 2*len-1));
		
		if(elen > 0)
			spans.push_back(mp(n-elen, elen) );
		
		result = max(result, mp(csz, spans) );
	}
	
	cout << result.s.size() << '\n';
	for(auto c : result.s)
		cout << c.f+1 << ' ' << c.s << '\n';
	return 0;
}













































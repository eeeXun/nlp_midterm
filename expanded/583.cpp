  extern template class basic_stringbuf<wchar_t>;
  extern template class basic_istringstream<wchar_t>;
  extern template class basic_ostringstream<wchar_t>;
  extern template class basic_stringstream<wchar_t>;




}
# 1218 "/usr/include/c++/11.2.0/sstream" 2 3
# 13 "data/583.cpp" 2



# 15 "data/583.cpp"
using namespace std;
# 30 "data/583.cpp"
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; for(int i=int(0); i<=int((static_cast<int>((v).size()))-1); ++i) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

struct Hashes {
    const int n;
    VL h1, h2, pow;
    Hashes(const string& s) : n(static_cast<int>((s).size())) {
        h1.resize(n+1);
        for(int i=int(0); i<=int((n)-1); ++i) {
            h1[i+1]=(h1[i]*kP+int(s[i]))%kM;
        }
        h2.resize(n+1);
        for(int i=int((n)-1); i>=int(0); --i) {
            h2[i]=(h2[i+1]*kP+int(s[i]))%kM;
        }
        pow.resize(n+1);
        pow[0]=1;
        for(int i=int(0); i<=int((n)-1); ++i) pow[i+1]=pow[i]*kP%kM;
    }
    bool is_mirror(int i1, int j1, int i2, int j2) const {
        
# 61 "data/583.cpp" 3 4
       (static_cast <bool> (
# 61 "data/583.cpp"
       j1-i1==j2-i2
# 61 "data/583.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 61 "data/583.cpp"
       "j1-i1==j2-i2"
# 61 "data/583.cpp" 3 4
       , "data/583.cpp", 61, __extension__ __PRETTY_FUNCTION__))
# 61 "data/583.cpp"
                           ;
        LL v1=((h1[j1]-h1[i1]*pow[j1-i1])%kM+kM)%kM;
        LL v2=((h2[i2]-h2[j2]*pow[j2-i2])%kM+kM)%kM;
        return v1==v2;
    }
private:
    static constexpr LL kP=107;
    static constexpr LL kM=LL(1e9)+7;
};

VI compute_palin(const Hashes& hashes) {
    VI r(hashes.n);
    for(int i=int(0); i<=int((hashes.n)-1); ++i) {
        int le=1, ri=min(i+1, hashes.n-i);
        while(le<ri) {
            int mid=(le+ri+1)/2;
            if(hashes.is_mirror(i-mid+1, i+1, i, i+mid)) {
                le=mid;
            } else {
                ri=mid-1;
            }
        }
        r[i]=le-1;
    }
    return r;
}

struct RMQ {
    vector<VPI> c;
    VI log;

    RMQ(const VI& a) {
        const int n=static_cast<int>((a).size());
        constexpr int kLog=20;
        c.resize(n, VPI(kLog));
        for(int i=int(0); i<=int((n)-1); ++i) {
            c[i][0]=make_pair(a[i], i);
        }
        for(int j=int(1); j<=int((kLog)-1); ++j) {
            for(int i=int(0); i<=int((n-(1<<j)+1)-1); ++i) {
                c[i][j]=max(c[i][j-1], c[i+(1<<(j-1))][j-1]);
            }
        }
        log.resize(n+1);
        for(int j=int(0); j<=int((kLog)-1); ++j) {
            for(int i=int(1<<j); i<=int((min(n+1,1<<(j+1)))-1); ++i) {
                log[i]=j;
            }
        }
    }
    PII getmax(int l, int r) {
        int j=log[r-l];
        return max(c[l][j], c[r-(1<<j)][j]);
    }
};

int main() {
    string s; cin>>s;
    const int n=static_cast<int>((s).size());

    Hashes hashes(s);

    VI palin=compute_palin(hashes);

    RMQ rmq(palin);



    const auto find_palin=[&](int l, int r) {
        int le=0, ri=(r-l-1)/2;
        while(le<ri) {
            int mid=(le+ri+1)/2;
            if(rmq.getmax(l+mid, r-mid).first>=mid) {
                le=mid;
            } else {
                ri=mid-1;
            }
        }
        int i=rmq.getmax(l+le, r-le).second;
        return PII(i-le, i+le+1);
    };
    pair<int, VPI> ans;
    {
        auto p=find_palin(0, n);
        ans=make_pair(p.second-p.first, VPI{p});
    }
    int i=0;
    for(int j=int((n)-1); j>=int(0); --j) {
        const int len=n-j;
        bool ok=false;
        while(1) {
            if(i+len>=j) break;

            if(hashes.is_mirror(i, i+len, j, n)) {
                ok=true; break;
            }
            ++i;
        }
        if(!ok) break;

        PII p=find_palin(i+len, j);
        setmax(ans, make_pair(len*2+p.second-p.first, VPI{{i,i+len}, p, {j,n}}));
    }
    cout<<static_cast<int>((ans.second).size())<<endl;
    for(const auto& p: ans.second) {
        cout<<p.first+1<<" "<<p.second-p.first<<endl;
    }

    return 0;
}

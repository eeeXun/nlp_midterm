    }




  extern template class basic_stringbuf<char>;
  extern template class basic_istringstream<char>;
  extern template class basic_ostringstream<char>;
  extern template class basic_stringstream<char>;


  extern template class basic_stringbuf<wchar_t>;
  extern template class basic_istringstream<wchar_t>;
  extern template class basic_ostringstream<wchar_t>;
  extern template class basic_stringstream<wchar_t>;




}
# 1218 "/usr/include/c++/11.2.0/sstream" 2 3
# 12 "data/3.cpp" 2



# 14 "data/3.cpp"
using namespace std;
# 29 "data/3.cpp"
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

VI manacher(const string& s) {
    VI ans(static_cast<int>((s).size()));
    int p=-1, r=-1;
    for(int i=int(0); i<=int((static_cast<int>((s).size()))-1); ++i) {
        int cur=1;
        if(r>i) {
            cur=min(ans[p*2-i], r-i);
        }
        while(i-cur>=0 && i+cur<static_cast<int>((s).size()) && s[i-cur]==s[i+cur]) {
            ++cur;
        }
        ans[i]=cur;
        if(setmax(r, i+cur)) {
            p=i;
        }
    }
    return ans;
}

VI kmp(const string& s) {
    string t=s; reverse((t).begin(), (t).end());

    VI fail(static_cast<int>((t).size())+1);
    int j=fail[0]=-1;
    for(int i=int(0); i<=int((static_cast<int>((t).size()))-1); ++i) {
        while(j>=0 && t[j]!=t[i]) j=fail[j];
        fail[i+1]=++j;
    }

    VI ans(static_cast<int>((s).size()));
    j=0;
    for(int i=int(0); i<=int((static_cast<int>((s).size()))-1); ++i) {
        while(j>=0 && t[j]!=s[i]) j=fail[j];
        ans[i]=++j;
    }
    return ans;
}

int main() {
    string s; cin>>s;
    const int n=static_cast<int>((s).size());

    VI palin=manacher(s);
    VI matches=kmp(s);

    VPI mx(n+1);
    for(int i=int(0); i<=int((n)-1); ++i) {
        mx[i+1]=max(mx[i], make_pair(matches[i], i));
    }
    pair<int, VPI> ans;
    for(int p=int(0); p<=int((n)-1); ++p) {
        const int w=palin[p];
        int len=mx[p-w+1].first, i=mx[p-w+1].second-len+1;
        setmin(len, n-(p+w));
        if(len>0) {
            setmax(ans, make_pair(w*2-1+len*2, VPI{{i,i+len}, {p-w+1,p+w}, {n-len,n}}));
        } else {
            setmax(ans, make_pair(w*2-1, VPI{{p-w+1,p+w}}));
        }
    }
    cout<<static_cast<int>((ans.second).size())<<endl;
    for(const auto p: ans.second) {
        cout<<p.first+1<<" "<<p.second-p.first<<endl;
    }

    return 0;
}

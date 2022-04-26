

}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 9 "data/191.cpp" 2

# 9 "data/191.cpp"
using namespace std;
const int mx = 1e5 + 5;
int d[2][mx];



void manacher( const string& s ) {
    int n = s.size();
    for (int z = 0; z < 2; z++) {
        for (int i = 0, l = 0, r = 0; i < n; i++) {
            int t = r - i + !z;
            if (i < r) d[z][i] = min( t, d[z][l + t] );
            int L = i - d[z][i], R = i + d[z][i] - !z;
            while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
                d[z][i]++, L--, R++;
            if (R > r) l = L, r = R;
        }
    }
}
vector<int> fail( string& s )
{
    int n = s.size();
    vector<int>pi( n );
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
int main() {
    string str;
    cin >> str;
    manacher( str );
    int n = str.size();
    string srt = str;
    reverse( srt.begin(), srt.end() );
    srt = srt + "#" + str;
    vector<int>pi = fail( srt );
    int table[n + 1] = { 0 };
    int maxs = 0;
    for (int i = n + 1; i < srt.size(); i++) {
        if (pi[i] > maxs) {
            int pos = i - (n + 1);
            int k = 0;
            for (int j = pi[i]; j > maxs; j--) {
                table[j] = pos - k;
                k--;
            }
            maxs = pi[i];
        }
    }
    int ans = 0;
    vector<pair<int, int>>v;
    for (int i = 0; i < n; i++) {
        int k = d[1][i];
        int l = i - k - 1;
        int r = i + k + 1;
        int tot = 2 * k + 1;
        if (l >= 0 && r < n) {
            int last = n - r;
            int mins = min( maxs, last );
            int lo = 1, hi = mins, best = -1, sol = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (table[mid] <= l) {
                    best = mid;
                    sol = table[mid];
                    lo = mid + 1;
                } else hi = mid - 1;
            }
            if(best+1){
                tot+=2*best;
                if(tot>ans){
                    ans = tot;
                    v.clear();
                    v.push_back({sol-best+1+1,best});
                    v.push_back({l+1+1,2*k+1});
                    v.push_back({n-best+1,best});
                }
            }else if(tot>ans){
                ans = tot;
                v.clear();
                v.push_back({l+1+1,2*k+1});
            }
        }else{
            if(tot>ans){
                ans = tot;
                v.clear();
                v.push_back({l+1+1,2*k+1});
            }
        }

    }
    cout<<v.size()<<endl;
    for(auto x:v)cout<<x.first<<' '<<x.second<<endl;
    return 0;
}

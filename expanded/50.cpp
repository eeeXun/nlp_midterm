# 2 "data/50.cpp"
using namespace std;
typedef vector< int >VI;




VI p[2];

void manacher(const string s) {
 int n = s.size();
 p[0] = VI(n+1);
 p[1] = VI(n);

 for (int z=0; z<2; z++)
        for (int i=0, l=0, r=0; i<n; i++)
        {
            int t = r - i + !z;
            if (i<r) p[z][i] = min(t, p[z][l+t]);
            int L = i-p[z][i], R = i+p[z][i] - !z;
            while (L>=1 && R+1<n && s[L-1] == s[R+1])
                p[z][i]++, L--, R++;
            if (R>r) l=L, r=R;
        }
}


vector< int >prefixFunction(const string& s)
{
    int n = s.size();
    int k = 0;

    vector< int >v(n+1);
    v[1] = 0;

    for (int i = 2; i <= n; i++) {
        while (k > 0 && s[k]!=s[i-1]) k = v[k];
        if (s[k]==s[i-1]) k++;
        v[i] = k;
    }

    return v;
}

typedef pair< int , int >PII;
vector< PII >kmpMatcher(const string& text, const string& pattern)
{
    vector< int >pi = prefixFunction(pattern);

    int k = 0;

    vector< PII >z;

    for (int i = 0; i < text.size(); i++) {
        while (k > 0 && text[i]!=pattern[k]) k = pi[k];
        if (text[i]==pattern[k]) k++;

        z.emplace_back(k, i-k+1);
        if (i) {
            if (z[i-1].first >= z[i].first)
                z[i] = z[i-1];
        }

        if (k==pattern.size()) {

            k = pi[k];
        }
    }

    return z;
}

int main()
{
    string s;
    cin>>s;
    int n = s.size();

    manacher(s);

    string rs = s;
    reverse(rs.begin(), rs.end());

    vector< PII >z = kmpMatcher(s, rs);




    int mx = -1;
    vector< PII >ans;

    for (int i = 0; i < n; i++) {
        int l = i-p[1][i];
        int r = i+p[1][i];

        if (mx < 2*p[1][i]+1) {
            mx = 2*p[1][i]+1;
            ans.clear();
            ans.emplace_back(l, mx);
        }

        if (l==0||r==n-1) continue;

        l--;

        if (z[l].first) {
            int rsz = min(n-1-r, z[l].first);

            if (mx < 2*p[1][i]+1 + 2*rsz) {
                mx = 2*p[1][i]+1 + 2*rsz;
                ans.clear();
                ans.emplace_back(z[l].second, rsz);
                ans.emplace_back(l+1, 2*p[1][i]+1);
                ans.emplace_back(n-rsz, rsz);
            }
        }
    }

    cout << ans.size() << endl;
    for (PII p : ans) cout << p.first+1 << " " << p.second << endl;


    return 0;
}

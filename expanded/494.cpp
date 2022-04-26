
PLL pb[N];

void pre() {
    pb[0] = make_pair(1,1);
    for (int i=1; i<N; i++)
        pb[i] = (pb[i-1] * base)%M;
}


vector<PLL> hashList(string s) {
    int n = s.size();
    vector<PLL> ans(n+1);
    ans[0] = make_pair(0,0);

    for (int i=1; i<=n; i++)
        ans[i] = (ans[i-1] * base + s[i-1])%M;
    return ans;
}


PLL Hash(vector<PLL> &hashlist, int l, int r) {
    int len = (r-l+1);
    return ((hashlist[r] - hashlist[l-1]*pb[len])%M+M)%M;
}

string s;
int n;
vector<PLL> hs, hr;

int a[N];
void build()
{
    hs = hashList(s);
    string t(s.rbegin(), s.rend());
    hr = hashList(t);
    n = s.size();

    for (int i=1; i<=n; i++) {
        int lo = 0, hi = min(i-1, n-i);
        while(lo < hi) {
            int m = (lo + hi + 1)/2;
            PLL right = Hash(hs, i+1, i+m);
            PLL left = Hash(hr, n-i+2, n-i+1+m);
            if (left == right) lo = m;
            else hi = m-1;
        }
        a[i] = lo;
    }
}

int lg[N];
void precalc() {
    lg[1] = 0;
    for (int i = 2; i < N; i++)
        lg[i] = lg[i/2] + 1;
}

PII st[N][K];
void buildSparseTable()
{
    for (int i = 1; i <= n; i++)
        st[i][0] = make_pair(a[i], i);

    for (int j = 1; j < K; j++)
        for (int i=1; i + (1<<j)<=n+1; i++)
            st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
}

PII query(int L, int R)
{
    int j = lg[R - L + 1];
    return max(st[L][j], st[R - (1 << j) + 1][j]);
}

int query(int l, int r, int &xx)
{
    int lo = 0, hi = (r-l)/2;
    xx=l;

    while(lo < hi) {
        int m = (lo+hi+1)/2;
        int L = l+m, R = r-m;
        
# 108 "data/494.cpp" 3 4
       (static_cast <bool> (
# 108 "data/494.cpp"
       L<=R
# 108 "data/494.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 108 "data/494.cpp"
       "L<=R"
# 108 "data/494.cpp" 3 4
       , "data/494.cpp", 108, __extension__ __PRETTY_FUNCTION__))
# 108 "data/494.cpp"
                   ;
        PII qq = query(L, R);
        if (qq.first>=m) lo = m, xx = qq.second-m;
        else hi = m-1;
    }
    return 2*lo+1;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    pre();
    precalc();
    cin>>s;
    build();
    buildSparseTable();

    int ans = 0;
    int cur = 1;

    int st[3], ln[3];

    for (int i=0; i<=n; i++) {
        PLL h = Hash(hr, 1, i);
        while (cur+i-1<=n-i) {
            if (Hash(hs, cur, cur+i-1) == h) break;
            else cur++;
        }

        if (cur+i>n-i) break;

        int l = cur + i, r = n-i, xx;
        
# 143 "data/494.cpp" 3 4
       (static_cast <bool> (
# 143 "data/494.cpp"
       l<=r
# 143 "data/494.cpp" 3 4
       ) ? void (0) : __assert_fail (
# 143 "data/494.cpp"
       "l<=r"
# 143 "data/494.cpp" 3 4
       , "data/494.cpp", 143, __extension__ __PRETTY_FUNCTION__))
# 143 "data/494.cpp"
                   ;
        int mid = query(l, r, xx);
        int len = 2*i + mid;

        if (len < ans) continue;

        ans = len;
        st[0] = cur, st[2] = n-i+1, st[1] = xx;
        ln[0] = ln[2] = i; ln[1] = mid;

    }

    int k = 0;
    for (int i=0; i<3; i++)
        k+= (ln[i] != 0);

    cout<<k<<endl;
    for (int i=0; i<3; i++)
        if (ln[i])
            cout<<st[i]<<" "<<ln[i]<<endl;
}

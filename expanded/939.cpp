    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/939.cpp" 2

# 2 "data/939.cpp"
using namespace std;



const long long MOD = 1e9 + 7;
const int N = 1e5 + 9;
int n;
string y[2];
int v[N];
pair<int, int> tree[4 * N];

void manacher(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = -1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, (l + r - i >= 0 && l + r - i <= n + 1 ? p[l + (r - i)] : 0)));
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    for (int i = 1; i <= n; i++) v[i - 1] = 2 * p[i] - 1;
}

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

void merge(int l, int r, int m, pair<int, int>& ed, pair<int, int>& lft, pair<int, int>& rgt) {
    if (lft.first > rgt.first) ed = lft;
    else ed = rgt;
}

void build(int p, int l, int r) {
    if (l == r) return void(tree[p] = { v[l], l });
    int m = (l + r) / 2;
    build(p << 1, l, m);
    build(p << 1 | 1, m + 1, r);
    merge(l, r, m, tree[p], tree[p << 1], tree[p << 1 | 1]);
}

const pair<int, int> neg = { -1, -1 };

pair<int, int> get(int p, int l, int r, int ul, int ur) {
    if (ul > r || l > ur) return neg;
    if (ul <= l && r <= ur) return tree[p];
    int m = (l + r) / 2;
    pair<int, int> ans = neg;
    pair<int, int> lft = get(p << 1, l, m, ul, ur);
    pair<int, int> rgt = get(p << 1 | 1, m + 1, r, ul, ur);
    if (lft == neg) return rgt;
    if (rgt == neg) return lft;
    merge(l, r, m, ans, lft, rgt);
    return ans;
}



void build() {
    cin >> y[0];
    n = y[0].length();
    y[1] = y[0];
    reverse(y[1].begin(), y[1].end());
    manacher(y[0]);
    build(1, 0, n - 1);
}

void solve(int tc) {
    build();
    pair<int, int> tway = tree[1];
    tway.second -= (tway.first - 1) / 2;
    int maxi = tway.first;
    swap(tway.first, tway.second);
    vector<pair<int, int>> ans = { tway };
    auto print = [&]() {
        cout << ans.size() << "\n";
        for (auto& u : ans) cout << u.first + 1 << " " << u.second << "\n";
    };
    vector<int> p = prefix_function(y[1] + "#" + y[0]);
    for (int i = n + 1; i < 2 * n + 1; i++) if (p[i] > 0 && i - n + 1 <= n - p[i]) {
        int l = i - n, r = n - p[i] - 1;
        int len = r - l + 1; len = len - ((len + 1) & 1);
        int L = 1, R = len;
        auto tmp = (l + len / 2 <= r - len / 2 ? get(1, 0, n - 1, l + len / 2, r - len / 2) : neg);
        auto maximize = [&](int leng, int center) {
            if (2 * p[i] + leng > maxi) {
                maxi = 2 * p[i] + leng;
                ans = { {i - n - p[i], p[i]}, {center - leng / 2, leng}, {n - p[i], p[i]} };
            }
        };
        if (tmp.first >= len)
            maximize(len, tmp.second);
        else {
            while (R - L > 2) {
                int m = (L + R) / 2;
                if ((m & 1) == 0) m--;
                if (m < L) break;
                if (l + m / 2 <= r - m / 2 && get(1, 0, n - 1, l + m / 2, r - m / 2).first >= m) L = m;
                else R = m;
            }
            maximize(L, get(1, 0, n - 1, l + L / 2, r - L / 2).second);
        }
    }
    print();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1, tc = 1;
    while (t--) solve(tc++);
}

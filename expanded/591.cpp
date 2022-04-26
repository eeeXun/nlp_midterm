# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/591.cpp" 2

# 5 "data/591.cpp"
char s[100001];
long long hash[100000], hashrev[100000], pow[100000];
int l, f[100000];
struct rec {
    int i, l;
} g[100000];
std::set<int> T;
std::set<std::pair<int, int> > T2;
bool compare(int x, int y, int t) {
    long long a = hash[x+t-1];
    if (x) a -= hash[x-1] * pow[t];
    long long b = hashrev[l+t-y-2];
    if (y<l-1) b -= hashrev[l-y-2] * pow[t];
    return a == b;
}
int extend(int x, int y) {
    int ll = 0, rr = l-x;
    if (y+1 < rr) rr = y+1;
    for (; ll < rr; ) {
        int mid = ll+rr+1>>1;
        if (compare(x, y, mid)) ll = mid;
        else rr = mid-1;
    }
    return ll;
}
int cmp(rec a, rec b) {
    return a.i - a.l < b.i - b.l;
}
int main() {
    scanf("%s", s);
    l = strlen(s);
    pow[0] = 1;
    for (int i = 1; i < l; i++) pow[i] = pow[i-1]*27;
    hash[0] = s[0]-97;
    for (int i = 1; i < l; i++) hash[i] = hash[i-1]*27+s[i]-97;
    hashrev[0] = s[l-1]-97;
    for (int i = 1; i < l; i++) hashrev[i] = hashrev[i-1]*27+s[l-1-i]-97;
    for (int i = 0; i < l; i++) f[i] = extend(i, l-1), g[i].i = i, g[i].l = extend(i, i);
    std::sort(g, g+l, cmp);
    int max = 0, ans = 0, maxi, ans1i, ans1l, ans2i, ans2l;
    for (int i = -1, t = 0; i < l; i++) {
        if (i >= 0 && f[i]) {
            T.insert(i);
            T2.insert(std::pair<int, int>(i+f[i], i));
        }
        std::set<std::pair<int, int> >::iterator j = T2.lower_bound(std::pair<int, int>(i, 0)), k;
        for (; j != T2.end() && j->first == i; k = j, k++, T2.erase(j), j = k) {
            if (j->first - j->second > max) max = j->first - j->second, maxi = j->second;
            T.erase(j->second);
        }
        int cur = 0, curi;
        if (T.begin() != T.end()) cur = i-*T.begin()+1, curi = *T.begin();
        if (max > cur) cur = max, curi = maxi;
        for (; t < l && g[t].i - g[t].l == i; t++) {
            int cur_ = cur;
            if (l-g[t].i-g[t].l < cur_) cur_ = l-g[t].i-g[t].l;
            if (2*cur_ + 2*g[t].l-1 > ans) {
                ans = 2*cur_ + 2*g[t].l-1;
                ans1i = curi, ans1l = cur_, ans2i = g[t].i, ans2l = g[t].l;
            }
        }
    }
    if (ans1l) printf("3\n%d %d\n%d %d\n%d %d\n", ans1i+1, ans1l, ans2i-ans2l+2, 2*ans2l-1, l-ans1l+1, ans1l);
    else printf("1\n%d %d\n", ans2i-ans2l+2, 2*ans2l-1);
    return 0;
}


# 2 "data/94.cpp"
using namespace std;
vector <int> build_suff (string s){
    int n = s.size ();
    vector <int> p (n), c (n), br (max (n, 256), 0);
    for (int i = 0; i < n; i ++) br [s [i]] ++;
    for (int i = 1; i < 256; i ++) br [i] += br [i - 1];
    for (int i = 0; i < n; i ++) p [--br [s [i]]] = i;
    c [p [0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i ++){
        if (s [p [i]] != s [p [i - 1]]) classes ++;
        c [p [i]] = classes - 1;
    }
    vector <int> p1 (n), c1 (n);
    for (int k = 0; (1 << k) < n; k ++){
        for (int i = 0; i < n; i ++) p1 [i] = (p [i] + n - (1 << k)) % n;
        fill (br.begin (), br.begin () + classes, 0);
        for (int i = 0; i < n; i ++) br [c [i]] ++;
        for (int i = 1; i < classes; i ++) br [i] += br [i - 1];
        for (int i = n - 1; i >= 0; i --) p [--br [c [p1 [i]]]] = p1 [i];
        c1 [p [0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i ++){
            pair <int, int> curr = {c [p [i]], c [(p [i] + (1 << k)) % n]}, prev = {c [p [i - 1]], c [(p [i - 1] + (1 << k)) % n]};
            if (curr != prev) classes ++;
            c1 [p [i]] = classes - 1;
        }
        c = c1;
    }
    return p;
}
vector <int> build_lcp (string s, vector <int> p){
    int n = s.size ();
    vector <int> pos (n), lcp (n - 1);
    for (int i = 0; i < n; i ++) pos [p [i]] = i;
    int k = 0;
    for (int i = 0; i < n; i ++){
        if (pos [i] == n - 1){
            k = 0;
            continue;
        }
        int j = p [pos [i] + 1];
        while (s [i + k] == s [j + k]) k ++;
        lcp [pos [i]] = k;
        if (k) k --;
    }
    return lcp;
}
string s, x;
int n, m;
vector <int> suff, lcp, pref;
int tree [800005], tree2 [400005];
void build_tree (int l, int r, int pos){
    if (l == r){
        tree [pos] = lcp [l];
        return;
    }
    int mid = l + r >> 1;
    build_tree (l, mid, pos << 1);
    build_tree (mid + 1, r, pos << 1 | 1);
    tree [pos] = min (tree [pos << 1], tree [pos << 1 | 1]);
}
int query (int l, int r, int pos, int ql, int qr){
    if (l >= ql && r <= qr) return tree [pos];
    if (l > qr || r < ql) return 1000000000;
    int mid = l + r >> 1;
    return min (query (l, mid, pos << 1, ql, qr), query (mid + 1, r, pos << 1 | 1, ql, qr));
}
void build_tree2 (int l, int r, int pos){
    if (l == r){
        tree2 [pos] = pref [l];
        return;
    }
    int mid = l + r >> 1;
    build_tree2 (l, mid, pos << 1);
    build_tree2 (mid + 1, r, pos << 1 | 1);
    tree2 [pos] = min (tree2 [pos << 1], tree2 [pos << 1 | 1]);
}
int query2 (int l, int r, int pos, int r1, int r2){
    if (l > r1) return -1;
    if (l == r){
        if (tree2 [pos] <= r2) return l;
        return -1;
    }
    int mid = l + r >> 1;
    if (r <= r1){
        if (tree2 [pos << 1 | 1] <= r2) return query2 (mid + 1, r, pos << 1 | 1, r1, r2);
        if (tree2 [pos << 1] <= r2) return query2 (l, mid, pos << 1, r1, r2);
        return -1;
    }
    int q = query2 (mid + 1, r, pos << 1| 1, r1, r2);
    if (q == -1) return query2 (l, mid, pos << 1, r1, r2);
    return q;
}
int main (){

    cin >> s;
    n = s.size ();
    m = 2 * n + 2;
    x = s;
    reverse (x.begin (), x.end ());
    x += "0" + s + "$";
    suff = build_suff (x);
    lcp = build_lcp (x, suff);
    vector <int> pos (m);
    for (int i = 0; i < m; i ++) pos [suff [i]] = i;
    build_tree (0, m - 2, 1);
    int x = pos [0], y;
    for (int i = 0; i < n; i ++) pref.push_back (n - 1);
    for (int i = 0; i < n; i ++){
        y = pos [n + 1 + i];
        int len;
        if (x < y) len = query (0, m - 2, 1, x, y - 1);
        else len = query (0, m - 2, 1, y, x - 1);
        pref [len] = min (pref [len], i);
    }
    for (int i = n - 1; i >= 0; i --){
        pref [i - 1] = min (pref [i - 1], pref [i]);
        pref [i] += i - 1;
    }
    pref [0] = -1;
    build_tree2 (0, n - 1, 1);
    int maxlen = 0, midstart, midlen;
    for (int i = 0; i < n; i ++){
        x = pos [i];
        y = pos [m - 2 - i];
        int len;
        if (x < y) len = query (0, m - 2, 1, x, y - 1);
        else len = query (0, m - 2, 1, y, x - 1);
        int z = query2 (0, n - 1, 1, i - len + 1, n - 1 - i - len);
        if (2 * len - 1 + 2 * z > maxlen){
            maxlen = 2 * len - 1 + 2 * z;
            midstart = n - i - len;
            midlen = 2 * len - 1;
        }
    }
    if (maxlen - midlen == 0) cout << "1\n" << midstart + 1 << ' ' << midlen << '\n';
    else{
        int preflen = maxlen - midlen >> 1, prefstart = pref [preflen] - preflen + 1;
        cout << "3\n" << prefstart + 1 << ' ' << preflen << '\n' << midstart + 1 << ' ' << midlen << '\n' << n - preflen + 1 << ' ' << preflen << '\n';
    }

}

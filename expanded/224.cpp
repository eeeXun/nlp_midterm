
# 4 "data/224.cpp"
using namespace std;
typedef pair <int, int> pii;
const int N = 1e5 + 1;
const int M = 2e5 + 5;
int lps[M];
int lp[N];
int pr[N];
int ans;
int n;

pii opt;
string T;
string P;

int l(int i) {
    return (i < 0? 0: pr[i]);
}

int r(int i) {
    return n - i;
}

void prefix() {
    int k = lp[0] = 0;
    for(int i = 1; i < n; ++i) {
        while(k && P[i] != P[k]) {
            k = lp[k - 1];
        }
        if(P[i] == P[k]) {
            k++;
        }
        lp[i] = k;
    }
}

void kmp() {
    int k = 0;
    for(int i = 0; i < n; ++i) {
        while(k && T[i] != P[k]) {
            k = lp[k - 1];
        }
        if(T[i] == P[k]) {
            k++;
        }
        pr[i] = k;
        if(i) {
            pr[i] = max(pr[i], pr[i - 1]);
        }
    }
}

void manacher() {
    string S;
    S += "&#";
    for(char c: T) {
        S += c;
        S += "#";
    }
    S += "@";
    int c = 1;
    int r = 1;
    for(int i = 1; i < S.size() - 1; ++i) {
        if(r > i) {
            lps[i] = min(r - i, lps[c - (i - c)]);
        }
        while(S[i - ++lps[i]] == S[i + lps[i]]); lps[i]--;
        if(i + lps[i] > r) {
            r = i + lps[i];
            c = i;
        }
    }
}

void input() {
    cin >> T;
    n = T.size(), P = T;
    reverse(P.begin(), P.end());
}

void solve() {
    prefix(), kmp(), manacher();
    for(int i = 0; i < n; ++i) {
        int len = lps[2 * (i + 1)];
        int L = i - len / 2;
        int R = i + len / 2;
        if(len + 2 * min(l(L - 1), r(R + 1)) > ans) {
            ans = len + 2 * min(l(L - 1), r(R + 1));
            opt = {i, len};
        }
    }
    if(opt.second == ans) {
        cout << "1\n";
        cout << opt.first - opt.second / 2 + 1 << " " << opt.second << "\n";
        return;
    }
    cout << "3\n";
    for(int i = 0; i < n; ++i) {
        if(pr[i] && pr[i] == (ans - opt.second) / 2) {
            cout << i - pr[i] + 2 << " " << (ans - opt.second) / 2 << "\n";
            break;
        }
    }
    cout << opt.first - opt.second / 2 + 1 << " " << opt.second << "\n";
    cout << n - (ans - opt.second) / 2 + 1 << " " << (ans - opt.second) / 2 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    input();
    solve();
}

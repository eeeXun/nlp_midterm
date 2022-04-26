


# 4 "data/995.cpp"
using namespace std;
typedef long long LL;
typedef pair<LL, int> P;

const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

int f[maxn], R[maxn];

void kmp(string &p) {
    int n = p.size();
    int i, j;
    for(i = 1; i < n; i++) {
        j = i;
        while(j > 0) {
            j = f[j];
            if(p[j] == p[i]) {
                f[i + 1] = j + 1;
                break;
            }
        }
    }
}

void Manacher(string &S) {
    int k = 0, mx = 0;
    int len = S.size();
    for(int i = 0; i < len; i++) {
        if(mx > i)
            R[i] = R[2 * k - i] < mx - i ? R[2 * k - i] : mx - i;
        else
            R[i] = 1;
        while(S[i + R[i]] == S[i - R[i]])
            R[i]++;
        if(R[i] + i > mx) {
            mx = R[i] + i;
            k = i;
        }
    }
}

string s, p;
int l[maxn];

int main() {



    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, i, u, v, mx = 0;
    cin >> s;
    n = s.size();
    p = s;
    reverse(s.begin(), s.end());
    s = s + "#" + p;
    kmp(s);
    for(i = 1; i <= n; i++) l[i] = max(l[i - 1], f[i + n + 1]);
    p = "$" + p;
    Manacher(p);
    for(i = 1; i <= n; i++) {
        if(R[i] * 2 - 1 + min(l[i - R[i]],n - i - R[i] + 1) * 2 > mx) {
            mx = R[i] * 2 - 1 + min(l[i - R[i]],n - i - R[i] + 1) * 2;
            u = i;
        }
    }
    if(mx == R[u] * 2 - 1) printf("1\n%d %d\n",u - R[u] + 1,R[u] * 2 - 1);
    else {
        puts("3");
        v = min(l[u - R[u]],n - u - R[u] + 1);
        for(i = 1;i <= u - R[u]; i++) {
            if(f[i + n + 1] == v) break;
        }
        printf("%d %d\n",i - f[i + n + 1] + 1,v);
        printf("%d %d\n",u - R[u] + 1,R[u] * 2 - 1);
        printf("%d %d\n",n - v + 1,v);
    }
    return 0;
}

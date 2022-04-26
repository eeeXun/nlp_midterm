
# 3 "data/770.cpp"
using namespace std;
const int N = 1e5+5;
string S;
char Ma[N * 2];
int Mp[N * 2];
void manacher(string S, int len) {
    int l = 0;
    Ma[l++] = '$';
    Ma[l++] = '#';
    for (int i = 0; i < len; i++) {
        Ma[l++] = S[i];
        Ma[l++] = '#';
    }
    Ma[l] = 0;
    int mx = 0, id = 0;
    for (int i = 0; i < l; i++) {
        Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
        while (Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i]++;
        if (i + Mp[i] > mx) {
            mx = i + Mp[i];
            id = i;
        }
    }
}
int next[N * 2];
void kmp(string S, int len, int next[]) {
    next[0] = -1;
    for (int i = 1, j = -1; i < len; i++) {
        for (;;) {
            if (S[i] == S[j + 1]) {
                j++;
                break;
            } else {
                if (j >= 0) j = next[j];
                else break;
            }
        }
        next[i] = j;
    }
}

vector<pair<int, int> > P;
int mx[N];
int main() {
    while (cin >> S) {
        int len = S.size();
        manacher(S, len);
        for (int i = 2; i < len * 2 + 2; i+=2) {
            Mp[i / 2 - 1] = (Mp[i] - 2) / 2;
        }
        string ss = S;
        reverse(ss.begin(), ss.end());
        ss += "$" + S;
        kmp(ss, ss.size(), next);
        mx[0] = 0;
        for (int i = 1; i <= len; i++) {
            mx[i] = max(mx[i - 1], next[len + i] + 1);
        }
        int ans = -1, pos;
        for (int i = 0; i < len; i++) {
            int l = i - Mp[i];
            int r = len - (i + Mp[i] + 1);
            int t = min(mx[l], r);
            int res = Mp[i] * 2 + 1 + t * 2;
            if (res > ans) {
                ans = res;
                pos = i;
            }
        }
        if (Mp[pos] * 2 + 1 < ans) {
            int t = ans - Mp[pos] * 2 - 1;
            t /= 2;
            cout << 3 << endl;
            for (int i = 0; i < len; i++) {
                if (next[len + i + 1] + 1 == t) {
                    cout << i - t + 2 << ' ' << t << endl;
                    break;
                }
            }
            cout << pos - Mp[pos] + 1<< ' ' << Mp[pos] * 2 + 1 << endl;
            cout << len - t + 1 << ' ' << t << endl;
        } else {
            cout << 1 << endl;
            cout << pos - Mp[pos] + 1<< ' ' << ans << endl;
        }
    }
    return 0;
}

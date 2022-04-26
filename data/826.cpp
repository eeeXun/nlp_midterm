#include <bits/stdc++.h>

#define F first
#define S second
#define ll long long
#define ull unsigned long long
#define pb push_back

using namespace std;
const ll mod = 1e9 + 7;
ll h[200000], rh[200000], b[200000], L, a[200000];
string s;
vector < pair < int, int > > ans;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s;
    a[0] = 1;
    for (int i = 1; i <= s.length(); i++)
        a[i] = 27 * a[i - 1] % mod;
    for (int i = 0; i < s.length(); i++)
        h[i + 1] = (27 * h[i] + (s[i] - 'a' + 1)) % mod;
    for (int i = s.length() - 1; i >= 0; i--)
        rh[s.length() - i] = (27 * rh[s.length() - i - 1] + (s[i] - 'a' + 1)) % mod;
    for (int i = 1; i <= s.length(); i++) b[i] = 1e7;
    int l = 1, r = 0;
    while(l + r <= s.length()){
        if (rh[l] == (h[r + l] - h[r] * a[l] + mod * mod) % mod){
            b[l] = r;
            l++;
        } else r++;
    }
    for (ll i = 0; i < s.length(); i++){
        ll l = 1, r = min(i + 1, s.length() - i) + 1;
        while(r - l > 1){
            int mid = (r + l) / 2;
            if ((h[i + 1] - h[i + 1 - mid] * a[mid] + mod * mod) % mod == (rh[s.length() - i] - rh[s.length() - i - mid] * a[mid] + mod * mod) % mod)
            l = mid; else r = mid;
        }
        int d = l;
        l = 0, r = s.length() - i - d + 1;
        while(r - l > 1){
            int mid = (r + l) / 2;
            if (b[mid] + mid - 1 < i - d + 1) l = mid; else r = mid;
        }
        if (L < 2 * l + 2 * d - 1){
            L = 2 * l + 2 * d - 1;
            ans.clear();
            ans.pb({b[l] + 1, l});
            ans.pb({i + 2 - d, 2 * d - 1});
            ans.pb({s.length() - l + 1, l});
        }
    }
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    if (ans[0].S == 0) t1 = 1;
    if (ans[1].S == 0) t2 = 1;
    if (ans[2].S == 0) t3 = 1;
    {
        cout << 3 - t1 - t2 - t3 << endl;
        if (!t1)
        cout << ans[0].F << " " << ans[0].S << endl;
        if (!t2)
        cout << ans[1].F << " " << ans[1].S << endl;
        if (!t3)
        cout << ans[2].F << " " << ans[2].S << endl;
    }
}

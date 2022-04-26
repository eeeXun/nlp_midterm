#include <bits/stdc++.h>
using namespace std;

const int DIM = 1e5 + 5;

char str[DIM], aux[DIM];
int pos[DIM], len[DIM], pre[DIM], dp[DIM];

pair<int, int> sol[4];

int main(void)
{
    cin >> (str + 1); str[0] = -1;
    int n = (int) strlen(str + 1);
    
    // manacher
    
    int le = 0, ri = 0;
    for (int i = 1; i <= n; ++i) {
        if (i <= ri)
            len[i] = min(len[le + ri - i], ri - i + 1);
        else
            len[i] = 1;
        
        while (str[i - len[i]] == str[i + len[i]])
            ++len[i];
        
        if (i + len[i] - 1 > ri)
            le = i - len[i] + 1, ri = i + len[i] - 1;
    }
    
    // suffix kmp;
    
    memset(dp, 0x3f, sizeof dp);
    memcpy(aux, str, sizeof str);
    reverse(aux + 1, aux + n + 1);
    
    for (int i = 2, l = 0; i <= n; ++i) {
        while (l and aux[i] != aux[l + 1])
            l = pre[l];
        if (aux[i] == aux[l + 1])
            ++l;
        pre[i] = l;
    }
    
    // prefix kmp and dp
    
    for (int i = 1, l = 0; i <= n; ++i) {
        while (l and str[i] != aux[l + 1])
            l = pre[l];
        if (str[i] == aux[l + 1])
            ++l;
        
        dp[l] = min(dp[l], i);
    }
    
    // final phase (binary search)
    
    int mxm = 0, nrsol = 0;
    for (int i = 1; i <= n; ++i) {
        int le = i - len[i] + 1, ri = i + len[i] - 1;
        
        if (ri == n or dp[1] >= le) {
            if (mxm < len[i] * 2 - 1) {
                mxm = len[i] * 2 - 1; nrsol = 1;
                sol[1] = make_pair(le, len[i] * 2 - 1);
            }
        } else {
            int pos = -1;
            for (int l = 1, r = n - ri; l <= r; ) {
                int m = (l + r) >> 1;
                
                if (dp[m] < le)
                    l = m + 1, pos = m;
                else
                    r = m - 1;
            }
            
            if (mxm < len[i] * 2 - 1 + pos * 2) {
                mxm = len[i] * 2 - 1 + pos * 2; nrsol = 3;
                sol[1] = make_pair(dp[pos] - pos + 1, pos);
                sol[2] = make_pair(le, len[i] * 2 - 1);
                sol[3] = make_pair(n - pos + 1, pos);
            }
        }
    }
    
    cout << nrsol << "\n";
    for (int i = 1; i <= nrsol; ++i)
        cout << sol[i].first << " " << sol[i].second << "\n";
    
    return 0;
}

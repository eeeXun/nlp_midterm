#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
string s, rs, s2;
int b[N], nxt[N], c[N], d[N << 1], n;
void getnxt(string s){
    int n = s.length();
    int i, j;
    i = 0, j = -1;
    nxt[i] = j;
    while(i < n){
        if(j == -1 || s[i] == s[j]){
            i++;
            j++;
            nxt[i] = j;
        }
        else j = nxt[j];
    }
}
void match(string s1, string s2){
    int n = s1.length();
    int i = 0, j = 0;
    while(i < n && j < n){
        if(j == -1 || s1[i] == s2[j]){
            b[i] = j + 1;
            i++;
            j++;
            if(j == n) j = nxt[j];
        }
        else{
            j = nxt[j];
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>s;
    //cout<<s.length()<<endl;
    //cout<<s[28]<<s[29]<<endl;
    //cout<<s[36]<<s[37]<<endl;
    //cout<<s[48]<<s[49]<<endl;
    n = s.length();
    rs = s;
    reverse(rs.begin(), rs.end());
    //cout<<s<<endl;
    //cout<<rs<<endl;
    getnxt(rs);
    match(s, rs);
    //for(int i = 0; i < n; i++) cout<<b[i]<<" ";
    //cout<<endl;
    for(int i = 1; i < n; i++) c[i] = -1;
    for(int i = 0; i < n; i++){
        if(c[b[i]] == -1) c[b[i]] = i;
    }
    for(int i = 1; i < n; i++) b[i] = max(b[i - 1], b[i]);
    s2 += "#|";
    for(int i = 0; i < n; i++){
        s2 += s[i];
        s2 += "|";
    }
    for(int i = 0, r = 2, mid = 2; i < s2.length(); i++){
        if(i >= mid) d[i] = min(r - i + 1, d[2 * mid - i]);
        while(s2[i - d[i]] == s2[i + d[i]]) d[i]++;
        if(i + d[i] > r) r = i + d[i] - 1, mid = i;
    }
    //cout<<s2<<endl;
    //for(int i = 0; i < s2.length(); i++) cout<<d[i]<<" ";
    //cout<<endl;
    int ansL, ansR, mm = 0;
    for(int i = 2; i < s2.length() - 1; i++){
        int L, R, mid;
        mid = i / 2;
        if(d[i] - 1 == 0) continue;
        if(i % 2){
            L = mid - (d[i] - 1 >> 1) + 1;
            R = mid + (d[i] - 1 >> 1);
        }
        else{
            L = mid - (d[i] - 1 >> 1);
            R = mid + (d[i] - 1 >> 1);
        }
        L--;
        R--;
        int res = R - L + 1 + ((L > 0) ? min(b[L - 1], n - 1 - R) * 2 : 0);
        if(res % 2 == 0) continue;
        if(mm < res){
            mm = res;
            ansL = L;
            ansR = R;
        }
    }
    if(ansL == 0 || ansR == n - 1){
        cout<<1<<endl;
        cout<<ansL + 1<<" "<<ansR + 1 - (ansL + 1) + 1<<endl;
    }
    else{
        //int t = c[b[ansL - 1]];
        int len = min(b[ansL - 1], n - 1 - ansR);
        if(len == 0){
            cout<<1<<endl;
            cout<<ansL + 1<<" "<<ansR + 1 - (ansL + 1) + 1<<endl;
        }
        else{
            cout<<3<<endl;
            int t = c[len];
            cout<<t - len + 2 <<" "<<t + 1 - (t - len + 2) + 1<<endl;
            cout<<ansL + 1 <<" "<<ansR + 1 - (ansL + 1) + 1<<endl;
            cout<<n - len + 1<<" "<<n - (n - len + 1) + 1<<endl;
        }

    }
    return 0;
}
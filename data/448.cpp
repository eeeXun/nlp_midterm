/*#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<map>
#include<set>*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define per(i,a,b) for (int i=(b);i>=(a);i--)
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)x.size())
typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> pii;
//head

const int N = 101111;


// e.g. s = "\0#a#b#a#b#a#"
void manacher(char s[], int p[], int n) {
    int maxid=0;//,ans=0;
    for (int i=1;i<=n;i++) {
        if (maxid+p[maxid]>=i) p[i]=min(p[maxid*2-i],maxid+p[maxid]-i);
        else p[i]=0;
        while (i+p[i]<n && s[i+p[i]+1]==s[i-p[i]-1]) p[i]++;
        if (i+p[i]>maxid+p[maxid]) maxid=i;
        //if (p[i]>ans) ans=p[i];
    }
    //return ans;
}

void kmp(char s[], int fail[], int n){
    memset(fail, 0, sizeof(fail));
    for (int i = 2; i <= n; i++){
        int p = fail[i - 1];
        while (p && s[i] != s[p + 1])
            p = fail[p];
        if (s[i] == s[p + 1])
            fail[i] = p + 1;
        //else
            //fail[i] = 0;
    }
}




char S[N], rev[N];
int fail[N];
pii lst[N];
int t[N], n;
int main(){
    scanf("%s", S + 1);
    n = strlen(S + 1);
    manacher(S, t, n);
    rep(i, 1, n){
        rev[i] = S[n - i + 1];
    }
    /*
    memset(fail, 0, sizeof(fail));
    rep(i, 2, n){
        int p = fail[i - 1];
        while (p && rev[i] != rev[p + 1])
            p = fail[p];
        if (rev[i] == rev[p + 1])
            fail[i] = p + 1;
        else
            fail[i] = 0;
    }*/
    kmp(rev, fail, n);
    int p = 0;
    rep(i, 1, n){
        while (p && rev[p + 1] != S[i])
            p = fail[p];
        if (rev[p + 1] == S[i])
            p++;
        else
            p = 0;
        lst[i] = pii(p, i);
    }
    rep(i, 2, n){
        lst[i] = max(lst[i], lst[i - 1]);
    }
    pii ans = pii(0, 0);
    rep(i, 1, n){
        int tmp = t[i] * 2 + 1;
        int right_len = n - (i + t[i]);
        tmp += min(right_len, lst[i - t[i] - 1].fi) * 2;
        ans = max(ans, pii(tmp, i));
    }
    if (ans.fi == t[ans.se] * 2 + 1){
        printf("1\n%d %d\n", ans.se - t[ans.se], t[ans.se] * 2 + 1);
    }
    else{
        printf("3\n");
        int p = ans.se;
        {
            int right_len = n - (p + t[p]), left_pos = lst[p - t[p] - 1].se;
            if (right_len < lst[p - t[p] - 1].fi)
                printf("%d %d\n", left_pos - lst[left_pos].fi + 1, right_len);
            else
                printf("%d %d\n", left_pos - lst[left_pos].fi + 1, lst[left_pos].fi);
        }
        printf("%d %d\n", p - t[p], t[p] * 2 + 1);
        printf("%d %d\n", n - (ans.fi - (t[ans.se] * 2 + 1)) / 2 + 1, (ans.fi - (t[ans.se] * 2 + 1)) / 2);
    }
    return 0;
}

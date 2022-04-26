#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <bitset>
#define INF 0x3f3f3f3f
#define eps 1e-8
#define FI first
#define SE second
using namespace std;
typedef long long LL;
const int N = 1e5 + 5;
int next[N], extand[N];

void getnext(char *T) {// next[i]: 以第i位置开始的子串 与 T的公共前缀
    int i, length = strlen(T);
    next[0] = length;
    for(i = 0; i < length - 1 && T[i] == T[i + 1]; i++);
    next[1] = i;
    int a = 1;
    for(int k = 2; k < length; k++) {
        int p = a + next[a] - 1, L = next[k - a];
        if((k - 1) + L >= p) {
            int j = (p - k + 1) > 0 ? (p - k + 1) : 0;
            while(k + j < length && T[k + j] == T[j]) j++;// 枚举(p+1，length) 与(p-k+1,length) 区间比较
            next[k] = j, a = k;
        }
        else next[k] = L;
    }
}

void getextand(char *S, char *T) {
    memset(next, 0, sizeof(next));
    getnext(T);
    int Slen = strlen(S), Tlen = strlen(T), a = 0;
    int MinLen = Slen > Tlen ? Tlen : Slen;
    while(a < MinLen && S[a] == T[a]) a++;
    extand[0] = a, a = 0;
    for(int k = 1; k < Slen; k++) {
        int p = a + extand[a] - 1, L = next[k - a];
        if((k - 1) + L >= p) {
            int j = (p - k + 1) > 0 ? (p - k + 1) : 0;
            while(k + j < Slen && j < Tlen && S[k + j] == T[j]) j++;
            extand[k] = j; a = k;
        }
        else extand[k] = L;
    }
}

char s1[N], s2[N], str[N * 2];
int minp[N], p[N * 2];

void pre_process(char *s)
{
    str[0] = '$';
    int cc = 1;
    for(int i = 0; s[i]; ++i)
    {
        str[cc++] = '#';
        str[cc++] = s[i];
    }
    str[cc++] = '#';
    str[cc] = 0;
}

void solve()
{
    int i;
    int mx = 0;
    int id;
    for(i=1; str[i]; i++)
    {
        if( mx > i )
            p[i] = min( p[2*id-i], p[id]+id-i );
        else
            p[i] = 1;
        for(; str[i+p[i]] == str[i-p[i]]; p[i]++);
        if( p[i] + i > mx )
        {
            mx = p[i] + i;
            id = i;
        }
    }
}

struct node {
    int pos, len;
    inline node() {}
    inline node(int _p, int _l) {
        pos = _p; len = _l;
    }
    bool operator < (const node &a) const {
        return len < a.len;
    }
};
priority_queue <node> Q;

vector < pair<int,int> > ans;
set <int> st;
int main() {
    scanf("%s", s1);
    int n = strlen(s1);
    strcpy(s2, s1);
    reverse(s2, s2 + n);
    getextand(s1, s2);
    memset(minp, 0x3f, sizeof(minp));
    for(int i = n - 1; i >= 0; --i) minp[extand[i]] = i;
    for(int i = n; i >= 0; --i) minp[i] = min(minp[i], minp[i + 1]);
    pre_process(s1);
    solve();
    for(int i = 1; str[i]; ++i) {
        if(str[i] == '#') continue;
        Q.push(node(i / 2 - 1, p[i] - 1));
    }
    int sum_len = 0;
    for(int i = 0; i * 2 < n; ++i) {
        if(minp[i] == INF) continue;
        int l = minp[i] + i, r = n - 1 - i;
        int len = i * 2;
        int val1 = -1, st1, val2 = -1, st2;
        while(!Q.empty()) {
            node t = Q.top();
            if(l > t.pos - t.len / 2 || r < t.pos + t.len / 2) {
                st.insert(t.pos);
                Q.pop();
                continue;
            }
            val1 = t.len; st1 = t.pos - t.len / 2;
            break;
        }
        int mid = (l + r) >> 1;
        set <int>::iterator it = st.lower_bound(mid);
        if(it != st.end()) {
            val2 = min(*it - l, r - *it) * 2 + 1;
            st2 = *it - val2 / 2;
        }
        if(it != st.begin()) {
            --it;
            if(min(*it - l, r - *it) * 2 + 1 > val2) {
                val2 = min(*it - l, r - *it) * 2 + 1;
                st2 = *it - val2 / 2;
            }
        }
        if(val1 == -1 && val2 == -1) break;
        int val, st;
        if(val1 > val2) {
            val = val1;
            st = st1;
        }
        else {
            val = val2;
            st = st2;
        }
        if(len + val > sum_len) {
            sum_len = len + val;
            ans.clear();
            if(i) ans.push_back(make_pair(minp[i], i));
            ans.push_back(make_pair(st, val));
            if(i) ans.push_back(make_pair(n - i, i));
        }
    }
    printf("%d\n", (int)ans.size());
    for(int i = 0; i < (int)ans.size(); ++i) printf("%d %d\n", ans[i].FI + 1, ans[i].SE);
    return 0;
}

	 	   			 		 		  				 		  		 		
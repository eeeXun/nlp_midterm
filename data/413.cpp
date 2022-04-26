#include<bits/stdc++.h>
#define fi first
#define se second
#define lson l,mid,o<<1
#define rson mid+1,r,o<<1|1
#define fio ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> P;
const LL INF = 0x3f3f3f3f;
const int N = 1e5 + 10;
const LL mod = 1e9 + 7;
const bool debug = false;


char s[N], ss[N];
char t[N << 1 | 1];
int ret[N << 1 | 1];
int net[N];
P mx[N];
struct Node{
    int len, k;
    P gg[5];
}ans;
void Manacher(char *s){
    int len = strlen(s), lens;
    lens = len;
    for(int i = 0; i < len; ++i){
        t[i << 1] = '#';
        t[i << 1 | 1] = s[i];
    }
    t[len << 1] = '#';
    len = len << 1 | 1;
    int r = 0, id = 0;
    ans.len = 0;
    for(int i = 0; i < len; ++i){
        if(r > i)   ret[i] = min(ret[2 * id - i], r - i);
        else    ret[i] = 1;
        while(i - ret[i] >= 0 && i + ret[i] < len && t[i - ret[i]] == t[i + ret[i]])    ret[i]++;
        if(i + ret[i] > r){
            r = i + ret[i];
            id = i;
        }
        if(i & 1){
            int _l = (i >> 1) - (ret[i] >> 1), _r = (i >> 1) + (ret[i] >> 1);
            int _ans = ret[i] - 1, _add = 0;
            if(_l >= 0)  _add = min(mx[_l].fi, lens - _r);
            if(_ans + _add * 2 > ans.len){
                ans.len = _ans + _add * 2;
                if(_add){
                    ans.k = 3;
                    ans.gg[1] = {mx[_l].se, _add};
                    ans.gg[2] = {_l + 2, _ans};
                    ans.gg[3] = {lens - _add + 1, _add};
                }
                else{
                    ans.k = 1;
                    ans.gg[1] = {_l + 2, _ans};
                }
            }
        }
    }
}
void get_next(char *s, int *net){
    int len = strlen(s);
    net[0] = -1;
    for(int i = 1, j = -1; i < len; ++i){
        while( ~j && s[i] != s[j + 1])  j = net[j];
        net[i] = s[j + 1] == s[i] ? ++j : j;
    }
}
void kmp(char *s, char *t, int *net){
    int now = -1;
    int lens = strlen(s), lent = strlen(t);
    for(int i = 0; i < lens; ++i){
        while(~now && s[i] != t[now + 1]) now = net[now];
        now += t[now + 1] == s[i];
        mx[i] = {now + 1, i - now + 1};
        if(i)   mx[i] = max(mx[i], mx[i - 1]);
        if(now == lent - 1) now = net[now];
    }
}

int main()
{
    scanf("%s", &s);
    int len = strlen(s);
    for(int i = 0; i < len; ++i)    ss[i] = s[len - 1 - i];
    get_next(ss, net);
    kmp(s, ss, net);
    Manacher(s);
    printf("%d\n", ans.k);
    for(int i = 1; i <= ans.k; ++i){
        printf("%d %d\n", ans.gg[i].fi, ans.gg[i].se);
    }
    return 0;
}

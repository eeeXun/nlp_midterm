

}
# 7 "data/80.cpp" 2

# 7 "data/80.cpp"
using namespace std;
typedef unsigned long long ULL;
const int MAXL = 100010;
const ULL SEED = 31;
int len;
char str[MAXL];
int plen[MAXL], mxv[MAXL];
void manacher (char * s, int clen) {
    int mxp = 1;
    plen[1] = 0;
    for(int i = 1; i<=clen; i++) {
        if(mxp+plen[mxp] > i) plen[i] = min(plen[mxp-(i-mxp)], mxp+plen[mxp]-i);
        else plen[i] = 0;
        while(i-plen[i] > 0 && i+plen[i] <= clen && s[i-plen[i]] == s[i+plen[i]]) plen[i]++;
        plen[i] --;
        if(i+plen[i] > mxp+plen[mxp]) mxp = i;
    }
    memset(mxv, 0, sizeof mxv);
    for(int i = clen; i>=1; i--) {
        mxv[i-plen[i]] = max(mxv[i-plen[i]], plen[i]*2+1);
        mxv[i] = max(mxv[i], mxv[i+1]);
    }
}
ULL hashv[MAXL], powr[MAXL];
inline ULL hcodeInv (int l, int r) {
    return hashv[r]-hashv[l-1]*powr[r-l+1];
}
pair<int, int> check (int suflen) {
    ULL sufcode = 0;
    for(int i = len; i>=len-suflen+1; i--)
        sufcode = sufcode*SEED+str[i];
    manacher(str, len-suflen);
    for(int i = 1; i<=len-(suflen<<1); i++)
        if(hcodeInv(i, i+suflen-1) == sufcode)
            return pair<int, int>(i, suflen*2+mxv[i+suflen]);
    return pair<int, int>(0, -1);
}
int main () {
    scanf("%s", str+1);
    len = strlen(str+1);
    powr[0] = 1;
    for(int i = 1; i<=len; i++)
        hashv[i] = hashv[i-1]*SEED+str[i], powr[i] = powr[i-1]*SEED;
    int l = 0, r = len, alen;
    pair<int, int> ans(0, 0);
    while(l < r) {
        int mlen = r-l;
        int midl = l+mlen/3;
        int midr = r-mlen/3;

        pair<int, int> vall = check(midl);
        pair<int, int> valr = check(midr);
        if((vall.second >= valr.second && vall.second != -1) || valr.second == -1) {
            r = midr-1;
            if(vall.second > ans.second) ans = vall, alen = midl;
        } else {
            l = midl+1;
            if(valr.second > ans.second) ans = valr, alen = midr;
        }
    }
    manacher(str, len-alen);
    memset(mxv, 0, sizeof mxv);
    for(int i = ans.first+alen; i<=len-alen; i++)
        mxv[i-plen[i]] = max(mxv[i-plen[i]], plen[i]*2+1);
    int mpos;
    for(int i = ans.first+alen; i<=len-alen; i++)
        if(ans.second-(alen<<1) == mxv[i]) {mpos = i; break;}
    if(alen == 0) {
        printf("1\n%d %d\n", mpos, ans.second);
        return 0;
    }
    if(ans.first+alen == mpos && mpos+(ans.second-(alen<<1)) == len-alen+1) {
        printf("1\n%d %d\n", ans.first, len-ans.first+1);
        return 0;
    }
    printf("3\n%d %d\n%d %d\n%d %d\n", ans.first, alen, mpos, ans.second-(alen<<1), len-alen+1, alen);
    return 0;
}

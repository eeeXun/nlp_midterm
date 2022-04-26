#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5;
int p[N],len,cnt,nxt[N],sta[N],f[N];
char s[N],cir[N],t[N];//开两倍空间

void manacher(){
    len <<= 1;
    int id = 0,mx = 0;
    for(int i = 1;i <= len;i++){
        if(i < mx) p[i] = min(p[2*id-i],mx-i+1);
        else  p[i] = 1;
        while(cir[i - p[i]] == cir[i + p[i]]) p[i]++;
        if(i + p[i] > mx) {
            mx = i + p[i] - 1;
            id = i;
        }
    }
    len >>= 1;
}

signed main(){
    scanf("%s",s+1);
    len = strlen(s+1);
    cir[0] = '*';    //特殊字符
    for(int i = 1;i <= len;i++){
        cir[(i << 1) - 1] = '#';
        cir[(i << 1)] = s[i];
    }
    cir[2 * len + 1] = '#';
    manacher();
    for(int i = 1;i <= len;i++) t[i] = s[len-i+1];t[len+1] = '#';
    for(int i = 1;i <= len;i++) t[i+len+1] = s[i];len = 2*len+1;
    for(int i = 2,j = 0;i <= len;i++){
        while(j && t[j+1] != t[i]) j = nxt[j];
        if(t[j+1] == t[i]) nxt[i] = ++j;
    }
    len = len/2;
    for(int i = 1;i <= len;i++) nxt[i] = nxt[i+len+1];
    for(int i = 1;i <= len;i++){
        if(nxt[i] < f[i-1]) sta[i] = sta[i-1],f[i] = f[i-1];
        else{
            sta[i] = i - nxt[i] + 1;
            f[i] = nxt[i];
        }
    }
    int mid_pos = 0,mid_len,l = 0,ll,ans = 0,mxl,mxlen = 0;
    for(int i = 1;i <= len;i++){
        int mid = p[i*2] - 1,pl = i - mid/2,pr = i + mid/2;
        if(mid == len) { cout<<1<<endl<<1<<" "<<len;exit(0);}
        if(mid > mxlen) {mxl = pl,mxlen = mid;ans = max(ans,mid);}
        if(ans < mid + f[pl-1] * 2){
            if(f[pl-1] + pr > len) continue;
            l = sta[pl-1];
            ll = f[pl-1];
            mid_pos = pl;
            mid_len = mid;
            ans = mid + f[pl-1] * 2;
        }
    }
    if(l){
        cout<<3<<endl<<l<<" "<<ll<<endl<<mid_pos<<" "<<mid_len<<endl<<len-ll+1<<" "<<ll<<endl;
    }else
        cout<<1<<endl<<mxl<<" "<<mxlen;
    return 0;
}

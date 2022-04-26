#include<bits/stdc++.h>
using namespace std;
#define N 111009
int rad[2 *N];
int T;
int x[2 * N];
void KMP(char *t) {
    T=strlen(t);
    for(int i=1, j=0; i<T;)t[i]==t[j] ? i++,j++,x[i]=j : j ? j=x[j] : i++;
}
int ss(char*text, int n) {
    int i, j, k;
    for(i = j = 0; i < 2*n; i += k, j = max(j-k, 0)) {
        while(i - j >= 0 && i+j+1 < 2*n && text[(i-j)/2] == text[(i+j+1)/2]){
            ++j;
        }
        rad[i]=j;
        for(k = 1; i-k >= 0 && rad[i] - k >= 0 && rad[i-k] != rad[i]-k; ++k)
            rad[i+k] = min(rad[i-k], rad[i]-k);
    }
    return *max_element(rad, rad + 2 * n);
}

int z[2 * N];
char s[2 * N];
int mx[2 * N], pos[2 * N];
char t[N];
int main(){
    //freopen("E.in", "r", stdin);
    scanf("%s", s);
    strcpy(t, s);
    strrev(s);
    int len = strlen(s);
    ss(s, len);
   // puts(s);
    strcat(s, "&"), strcat(s, t);
    KMP(s);
    mx[len + 1] = 0, pos[len + 1] = 0;
   // puts(s);
    for(int i = len + 2; i <= 2 * len + 1; i ++) {
        mx[i] = max(mx[i-1], x[i]);
        if(mx[i] == x[i]) pos[i] = i - len - 1;
        else pos[i] = pos[i-1];
       // printf("i = %d %d %d\n", i - len - 1, mx[i], pos[i]);
    }
    int central, XX, PO, MX = -1;
    for(int i = 0; i < 2 * len; i += 2) {
        int RAD = rad[i] / 2;
        int st = i / 2 - RAD, en = RAD + i / 2;
        int po = pos[len + len - en];
        int xx = mx[len + len - en];
        if(xx > st) po -= xx - st;
        xx = min(xx, st);
        //printf("%d %d %d %d xx = %d po = %d len = %d\n", i / 2, st, en, rad[i], xx, po, xx * 2 + rad[i]);
       // printf("%d %d %d\n", i / 2, xx, rad[i]);
        MX = max(MX, xx * 2 + rad[i]);
        if(MX == xx * 2 + rad[i]) central = i / 2, XX = xx, PO = po;
    }
    //printf("%d %d %d\n", XX, PO, rad[2 * central]);
    if(!XX) {
        puts("1");
        int RAD = rad[central * 2] / 2;
        int en = central + RAD;
        printf("%d %d\n", len - en, 2 * RAD + 1);
    }
    else {
        puts("3");
        printf("%d %d\n", PO - XX + 1, XX);
        int RAD = rad[central * 2] / 2;
        int en = central + RAD;
        printf("%d %d\n", len - en, 2 * RAD + 1);
        printf("%d %d\n", len - XX + 1, XX);
    }

    return 0;
}


# 3 "data/680.cpp"
using namespace std;





char s[200011], t[200011];
int x[200011], mx[200011], pos[200011];
int rad[200011 << 1];
int stt[3], le[3];

void kmp(char *t){
    int T = strlen(t);
    memset(x, 0, sizeof(x));
    int i, j;
    for(i=1, j=0; i<T;)t[i]==t[j] ? i++,j++,x[i]=j : j ? j=x[j] : i++;
}

void Manacher(char *s){
 int n = strlen(s);
 int rlt = 0;
 for (int i = 0, j = 0, k; i < n * 2 - 1; i += k, j = ((j - k) > (0) ? (j - k) : (0))) {
  while (i - j >= 0 && i + j + 1 < n * 2 && s[(i - j) / 2] == s[(i + j + 1) / 2]) j ++;
  rad[i] = j;
  for (k = 1; i - k >= 0 && rad[i] - k >= 0 && rad[i - k] != rad[i] - k; k ++) rad[i + k] = ((rad[i - k]) < (rad[i] - k) ? (rad[i - k]) : (rad[i] - k));
 }
}

int main(){

    scanf("%s", s);

    strcpy(t, s);
    int len = strlen(t);
    reverse(t, t + len);
    strcat(t, "&");
    strcat(t, s);

    kmp(t);
    Manacher(t);

    mx[len + 1] = 0, pos[len + 1] = len;
    for(int i = len + 2; i <= 2 * len + 1; i ++) {
        mx[i] = ((mx[i - 1]) > (x[i]) ? (mx[i - 1]) : (x[i]));
        pos[i] = pos[i - 1];
        if(mx[i - 1] < x[i]) pos[i] = i - 1;
    }





    int ans = 0;
    int tp, r1, len1, r2, len2, r3, len3;
    for(int i = 0; i <= 2 * len - 2; i += 2) if(rad[i]) {
        int rlt = rad[i];
        int st = i / 2 - (rad[i] - 1) / 2;
        int en = i / 2 + (rad[i] - 1) / 2;
        if(i % 2){
            st = i / 2 - rad[i] / 2 + 1;
            en = i / 2 + rad[i] / 2;
        }

        int r = ((st) < (mx[2 * len - en]) ? (st) : (mx[2 * len - en]));
        if(ans < rlt + 2 * r) {

            ans = rlt + 2 * r;
            if(r == 0){
                tp = 1, stt[0] = en, le[0] = ans;
            }
            else {
                tp = 3;
                int ps = pos[2 * len - en] - mx[2 * len - en] + r;
                stt[2] = 2 * len - ps + r - 1, le[2] = r;
                stt[1] = en, le[1] = rad[i];
                stt[0] = r - 1, le[0] = r;

                if(stt[0] == stt[1] - le[1] && stt[1] == stt[2] - le[2]) {
                    tp = 1;
                    stt[0] = stt[2], le[0] = ans;
                }
            }
        }
    }



    printf("%d\n", tp);
    for(int i = tp - 1; i >= 0; i --){
        printf("%d %d\n", len - stt[i], le[i]);
    }

}

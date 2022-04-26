# 40 "/usr/include/c++/11.2.0/cstdio" 3
# 5 "data/897.cpp" 2


# 6 "data/897.cpp"
using namespace std;

const int N = 100010;

char str1[N] = {0};
char str2[2*N] = {0};
int nxt[2*N] = {0};
int p[N] = {0};
int ne[N] = {0};
int mm[N] = {0};

void getnext(char s[], int nxt[])
{
    int m = strlen(s);
    nxt[0] = 0;
    for (int i = 1; i < m; i++) {
        int k = nxt[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = nxt[k - 1];
        }
        if (s[i] == s[k]) nxt[i] = k + 1;
        else nxt[i] = 0;
    }



}

void pk(char str[], int p[])
{
    int i;
    int mx = 0;
    int id;
    int m = strlen(str);
    for(i = 0; i < m; i++) {
        if (mx > i) {
            p[i] = min(p[2 * id - i], mx - i );
        }
        else {
            p[i] = 1;
        }
        while (i - p[i] >= 0 && i + p[i] < m && str[i + p[i]] == str[i - p[i]]) {
            p[i]++;
        }
        if (p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
    }
}

int main()
{
 scanf("%s", str1);
 int len1 = strlen(str1);
 int len2 = 2 * len1;
 for (int i = 0; i < len1; i++) {
  str2[i] = str1[len1 - 1 - i];
 }
 str2[len1] = '#';
 for (int i = len1 + 1; i <= len2; i++) {
  str2[i] = str1[i - len1 - 1];
 }
 getnext(str2, nxt);
 pk(str1, p);
 for (int i = 0; i < len1; i++) {
  ne[i] = nxt[i + len1 + 1];
 }
 mm[0] = 0;
 for (int i = 1; i < len1; i++) {
  if (ne[mm[i-1]] > ne[i]) {
   mm[i] = mm[i-1];
  }
  else mm[i] = i;
 }

 int posl = -1;
 int posm = 0;
 int maxl = 1;
 for (int i = 1; i < len1; i++) {
        int tposl = i - p[i];
  int templ = 0;
  if (tposl >= 0) {
   tposl = mm[tposl];
   templ += ne[tposl] * 2;
  }
  templ += min(p[i] * 2 - 1, (len1 - ne[tposl] - i) * 2 - 1);
  templ = min(templ, len1);
  if (templ > maxl) {
   maxl = templ;
   posm = i;
   posl = tposl;
  }
 }

 if (posl >= 0 && ne[posl] > 0) {
  cout << "3" << endl;
  cout << posl - ne[posl] + 2 << " " << ne[posl] << endl;
  int lenm = min(p[posm] * 2 - 1, (len1 - ne[posl] - posm) * 2 - 1);
  cout << posm - p[posm] + 2 << " " << lenm << endl;
  cout << len1 - ne[posl] + 1 << " " << ne[posl] << endl;
 }
 else {
  cout << "1" << endl;
  cout << posm - p[posm] + 2 << " " << p[posm] * 2 - 1 << endl;
 }

 return 0;
}

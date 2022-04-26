# 4 "data/927.cpp" 2


# 5 "data/927.cpp"
using namespace std;

typedef long long LL;

const int maxn = 200010, mo = 1000000007, x = 213, X = 233;
int n, w[maxn], l[maxn], r[maxn], ans;
LL hl[maxn], hr[maxn], HL[maxn], HR[maxn], e[maxn], E[maxn];
char s[maxn];

inline int min(int x, int y){return x < y ? x : y;}
inline int max(int x, int y){return x > y ? x : y;}
inline pair<LL, LL> get(int st, int len){
 LL v = ((hl[st + len - 1] - hl[st - 1] * e[len]) % mo + mo) % mo,
    V = ((HL[st + len - 1] - HL[st - 1] * E[len]) % mo + mo) % mo;
 return make_pair(v, V);
}

int main(){
 scanf("%s", s + 1); n = strlen(s + 1);
 int right = 1, mid = 1;
 for (int i = 2; i <= n; i++){
  if (right >= i) w[i] = min(w[mid + mid - i], right - i);
  while (i - w[i] - 1 > 0 && i + w[i] + 1 <= n && s[i - w[i] - 1] == s[i + w[i] + 1]) w[i]++;
  if (i + w[i] > right) right = i + w[i], mid = i;
 }
 e[0] = E[0] = 1;
 for (int i = 1; i <= n; i++)
  hl[i] = (hl[i - 1] * x) % mo + s[i], hr[n - i + 1] = (hr[n - i + 2] * x) % mo + s[n - i + 1], e[i] = (e[i - 1] * x) % mo,
  HL[i] = (HL[i - 1] * X) % mo + s[i], HR[n - i + 1] = (HR[n - i + 2] * X) % mo + s[n - i + 1], E[i] = (E[i - 1] * X) % mo;
 int left = 1;
 for (int i = 1; i <= n; i++){
  while (left + i + i - 1 < n && get(left, i) != make_pair(hr[n - i + 1], HR[n - i + 1])) left++;
  if (left + i + i - 1 >= n) break;
  l[i] = left;
 }
 int length = 0;
 for (int i = 1; i <= n; i++){
  r[i] = r[i - 1];
  while (l[length + 1] && l[length + 1] + length == i) length++;
  r[i] = max(r[i], length);
 }
 for (int i = 1; i <= n; i++){
  int tmp = w[i] + w[i] + 1 + 2 * min(n - i - w[i], r[i - w[i] - 1]);
  if (tmp > ans){
   ans = tmp; mid = i;
   length = min(n - i - w[i], r[i - w[i] - 1]);
  }
 }
 if (length == 0) printf("1\n%d %d", mid - ans / 2, ans);
 else{
  for (int i = 1; i <= n; i++)
   if (get(i, length) == make_pair(hr[n - length + 1], HR[n - length + 1])){
    printf("3\n%d %d\n%d %d\n%d %d", i, length, mid - (ans - length * 2) / 2, ans - length * 2, n - length + 1, length);
    break;
   }
 }
}

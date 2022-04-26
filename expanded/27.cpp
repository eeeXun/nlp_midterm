

# 4 "data/27.cpp"
const int maxn = 200010;
int n, w[maxn], l[maxn], r[maxn], ans, hl[maxn], hr[maxn], e[maxn];
char s[maxn];

inline int min(int x, int y){return x < y ? x : y;}
inline int max(int x, int y){return x > y ? x : y;}
inline int get(int st, int len){return hl[st + len - 1] - hl[st - 1] * e[len];}

int main(){
 scanf("%s", s + 1); n = strlen(s + 1);
 int right = 1, mid = 1;
 for (int i = 2; i <= n; i++){
  if (right >= i) w[i] = min(w[mid + mid - i], right - i);
  while (i - w[i] - 1 > 0 && i + w[i] + 1 <= n && s[i - w[i] - 1] == s[i + w[i] + 1]) w[i]++;
  if (i + w[i] > right) right = i + w[i], mid = i;
 }
 e[0] = 1;
 for (int i = 1; i <= n; i++)
  hl[i] = hl[i - 1] * 97 + s[i], hr[n - i + 1] = hr[n - i + 2] * 97 + s[n - i + 1], e[i] = e[i - 1] * 97;
 int left = 1;
 for (int i = 1; i <= n; i++){
  while (left + i + i - 1 <= n && get(left, i) != hr[n - i + 1]) left++;
  if (left + i + i - 1 > n) break;
  l[i] = left;
 }
 int length = 0;
 for (int i = 1; i <= n; i++){
  r[i] = r[i - 1];
  while (l[length + 1] == i && length + length <= n) length++;
  r[i] = max(r[i], min(length, i - l[length] + 1));
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
   if (get(i, length) == hr[n - length + 1]){
    printf("3\n%d %d\n%d %d\n%d %d", i, length, mid - (ans - length * 2) / 2, ans - length * 2, n - length + 1, length);
    break;
   }
 }
}

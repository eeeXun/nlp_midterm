# 4 "data/960.cpp" 2


# 5 "data/960.cpp"
using namespace std;

const int MAX_N = 100007;
const long long INF = 1LL<<61;
const int SEED = 127;

char str[MAX_N];
long long dp[MAX_N];
long long pre[MAX_N], tail[MAX_N], Pow[MAX_N];

long long getPre(int l, int r) {
 return pre[r + 1] - pre[l] * Pow[r - l + 1];
}

long long getTail(int l, int r) {
 return tail[l] - tail[r + 1] * Pow[r - l + 1];
}

int main() {
 scanf("%s", str);
 int len = strlen(str);
 pre[0] = 0;
 for (int i = 1; i <= len; ++i) {
  pre[i] = pre[i - 1] * SEED + str[i - 1];
 }
 tail[len] = 0, tail[len - 1] = str[len - 1];
 for (int i = len - 2; i >= 0; --i) {
  tail[i] = tail[i + 1] * SEED + str[i];
 }
 Pow[0] = 1;
 for (int i = 1; i < len; ++i) {
  Pow[i] = Pow[i - 1] * SEED;
 }
 for (int i = 0; i <= len; ++i) {
  dp[i] = INF;
 }
 for (int i = 0; i < len; ++i) {
  int l = 0, r = (len - i) / 2;
  while (l < r) {
   int mid = (l + r + 1) / 2;
   if (getPre(i, i + mid - 1) == getTail(len - mid, len - 1))
    l = mid;
   else r = mid - 1;
  }
  dp[l] = min(dp[l], (long long)i - 1);
 }

 for (int i = len; i >= 0; --i) {
  dp[i - 1] = min(dp[i - 1], dp[i]);
  dp[i] += i;
 }

 int Max = 0;
 int x1, x2, x3, l1, l2, l3;
 for (int i = 0; i < len; ++i) {
  int l = 0, r = min(i, len - i - 1);
  while (l < r) {
   int mid = (l + r + 1) / 2;
   if (getPre(i - mid, i) == getTail(i, i + mid))
    l = mid;
   else r = mid - 1;
  }
  int midLen = l;
  l = 0, r = len - i - midLen - 1;
  while (l < r) {
   int mid = (l + r + 1) / 2;
   if (dp[mid] + midLen < i)
    l = mid;
   else r = mid - 1;
  }
  if (midLen * 2 + 1 + l * 2 > Max) {
   Max = midLen * 2 + 1 + l * 2;
   x1 = dp[l] - l + 2, l1 = l;
   x2 = i - midLen + 1, l2 = midLen * 2 + 1;
   x3 = len - l + 1, l3 = l;
  }
 }

 if (l3)
  printf("3\n%d %d\n%d %d\n%d %d\n", x1, l1, x2, l2, x3, l3);
 else {
  if (x1 != 0 && l1 != 0)
   printf("1\n%d %d\n", x1, l1);
  else if (x2 != 0 && l2 != 0)
   printf("1\n%d %d\n", x2, l2);
  else printf("1\n%d %d\n", x3, l3);
 }
 return 0;
}

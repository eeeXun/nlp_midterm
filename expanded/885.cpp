# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/885.cpp" 2






# 10 "data/885.cpp"
using namespace std;
using Pii = pair<int, int>;

constexpr int MAX = 400010;

char str[MAX], buff[MAX];
int rad[MAX], nxt[MAX];

struct RMQ {
  Pii val[MAX][20];
  int w[MAX], sz;

  void init(const int* a, int n) {
    w[0] = -1; sz = n;
    for (int i = 1; i <= n; ++i) {
      w[i] = (i & (i - 1)) ? w[i - 1] : w[i - 1] + 1;
    }
    for (int i = 1; i <= n; ++i) val[i][0] = {a[i], i};
    for (int i = 1; (1 << i) <= n; ++i) {
      for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
        val[j][i] = max(val[j][i - 1], val[j + (1 << (i - 1))][i - 1]);
      }
    }
  }

  int query(int l, int r) const {
    int x = w[r - l + 1];
    return max(val[l][x], val[r - (1 << x) + 1][x]).second;
  }
} rmq;

int manacher(const char* str) {
  int w = 1, l = 0, r = 0, i, ret = -1;
  buff[0] = '$';
  for (i = 0; str[i]; ++i) buff[w++] = str[i];
  buff[w] = 0;
  for (i = 1; i < w; ++i) {
    rad[i] = r > i ? min(rad[2 * l - i], r - i) : 1;
    for (; buff[i + rad[i]] == buff[i - rad[i]]; ++rad[i]);
    if (i + rad[i] > r) {
      l = i; r = i + rad[i];
    }
    ret = max(ret, rad[i]);
  }
  return ret - 1;
}

void getNext(const char* p, int* next) {
  int l = 1, r = -1, i, j;
  for (next[0] = 0, i = 1; p[i]; ++i) {
    if (i + next[i - l] - 1 < r) next[i] = next[i - l];
    else {
      for (j = max(r - i + 1, 0); p[i + j] && p[i + j] == p[j]; ++j);
      next[i] = j; l = i; r = i + j - 1;
    }
  }
  next[0] = i;
}

Pii bsearch(int l, int r) {
  int low = 1, high = (r - l + 2) >> 1;
  Pii ret{-1, -1};
  while (low <= high) {
    int mid = (low + high) >> 1;
    int x = rmq.query(l + mid - 1, r - mid + 1);
    if (rad[x] >= mid) {
      ret = {x, mid}; low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return ret;
}

int main() {
  while (~scanf("%s", str)) {
    manacher(str);
    int n = strlen(str);
    rmq.init(rad, n);
    for (int i = 0; i < n; ++i) str[i + n] = str[i];
    str[n << 1] = 0;
    reverse(str, str + n);
    getNext(str, nxt);
    int ans = 0, pa = -1, la = -1, pb = -1, lb = -1, pc = -1, lc = -1;
    for (int i = 0; i < n; ++i) {
      int w = nxt[i + n], l = w + i + 1, r = n - w;
      if (l > r) {
        l = (i + 1 + n) >> 1; r = i + 1 + n - l; w = l - i - 1;
      }
      auto cur = bsearch(l, r);
      if ((w << 1) + (cur.second << 1) - 1 > ans) {
        ans = (w << 1) + (cur.second << 1) - 1;
        pa = i + 1; la = w;
        pb = cur.first - cur.second + 1; lb = (cur.second << 1) - 1;
        pc = n - w + 1; lc = w;
      }
    }
    Pii seg[3];
    int cnt = 0;
    if (~pa && la > 0) seg[cnt++] = {pa, la};
    if (~pb && lb > 0) seg[cnt++] = {pb, lb};
    if (~pc && lc > 0) seg[cnt++] = {pc, lc};
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i) printf("%d %d\n", seg[i].first, seg[i].second);
  }
  return 0;
}

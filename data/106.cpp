#include <bits/stdc++.h>
using namespace std;

const int N = 1.1e5;
char a[N];
int n, f[N], p[N], px[N], pl[N], nx[N];
int b1, b2, b3, b4, b5, b6, ans;

void upd(int pv, int pi) {
  int a1 = pi, a2 = pl[pi];
  int a3 = pv - f[pv], a4 = f[pv] * 2 + 1;

  if (a1 + a2 > a3) { a2 = a3 - a1; }
  if (n - 1 - a2 < pv + f[pv]) { a2 = n - 1 - pv - f[pv]; }

  int a5 = n - a2, a6 = a2;
  if (a2 == 0) a1 = a3;

  //cerr<< ">"<<a1<<" "<<a2<< " "<<a3 <<" "<<a4<<" "<<a5<<" "<<a6<<endl;

  if (a2 + a4 + a6 > ans) {
    ans = a2 + a4 + a6;
    b1 = a1;
    b2 = a2;
    b3 = a3;
    b4 = a4;
    b5 = a5;
    b6 = a6;
  }
}

void out() {
  if (b1 + b2 == b3 && b3 + b4 == b5 || !b2) {
    puts("1");
    printf("%d %d\n", b1 + 1, b2 + b4 + b6);
    exit(0);
  }
/*
  if (b1 + b2 == b3) {
    puts("2");
    printf("%d %d\n", b1 + 1, b2 + b4);
    printf("%d %d\n", b5 + 1, b6);
    exit(0);
  }
  if (b3 + b4 == b5) {
    puts("2");
    printf("%d %d\n", b1 + 1, b2);
    printf("%d %d\n", b3 + 1, b4 + b6);
    exit(0);
  }
*/
  puts("3");
  printf("%d %d\n", b1 + 1, b2);
  printf("%d %d\n", b3 + 1, b4);
  printf("%d %d\n", b5 + 1, b6);
}

int main() {
  scanf("%s", &a);
  n = strlen(a);
  f[0] = 0;
  for (int i = 1; i < n; ++i) {
    int x = 0;
    if (f[i-1])
      x = min(f[i-2], f[i-1] - 1);
    while (i + x + 1 < n && i - x - 1 >= 0)
      if (a[i+x+1] == a[i-x-1]) ++x; else break;
    f[i] = x;
  }
  //for (int i = 0; i < n; ++i) cerr << f[i] << " ";

  for (int i = 1; i <= n; ++i) {
    int ml = i - 1;
    while (ml) {
      ml = nx[ml];
      if (a[n - i] == a[n - ml - 1]) {
        ++ml;
        break;
      }
    };
    nx[i] = ml;
  }

  //for (int i = 0; i <= n; ++i) cerr << nx[i] << "# "; cerr<<endl;

  int ml = 0;
  for (int i = 0; i < n; ++i) {
    if (i>0)px[i] = px[i-1];

    if (a[i] == a[n - ml - 1]) {
      ++ml;
    } else do {
      ml = nx[ml];
      if (a[i] == a[n - ml - 1]) {
        ++ml;
        break;
      }
    } while (ml);
    pl[i-ml+1] = ml;
    if (ml > pl[px[i]]) {
      px[i] = i-ml+1;
    }
    cerr << ml << "# ";
  }
  for (int i = 0; i < n; ++i) {
    upd(i, px[i - f[i]]);
  }
  out();
}

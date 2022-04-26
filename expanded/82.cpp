}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 5 "data/82.cpp" 2

# 5 "data/82.cpp"
using namespace std;






typedef long long LL;

template <class T> bool chkmin(T& a, T b) { return a > b ? a = b, true : false; }
template <class T> bool chkmax(T& a, T b) { return a < b ? a = b, true : false; }

template <class T> void read(T& a) {
 char c = getchar(); T f = 1; a = 0;
 for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
 for(; isdigit(c); c = getchar()) a = a * 10 + c - '0';
 a *= f;
}

const int maxN = 1e5 + 5;

typedef pair<int, int> pii;





int N;
int mid, mid_len, pre, pre_len, suf, suf_len;
int s[maxN];
int r[maxN];
int LOG[maxN];
int fail[maxN];
int g[maxN][20];
int pos[maxN][20];
char inp[maxN], ant[maxN];

void getfail() {
 int cur = 0;
 memcpy(ant, inp, sizeof(inp));
 reverse(ant + 1, ant + N + 1);
 for(int i = (2), _ = (N); i <= _; ++ i) {
  while(cur && ant[cur + 1] != ant[i])
   cur = fail[cur];
  if(ant[cur + 1] == ant[i])
   cur ++;
  fail[i] = cur;
 }




}

void manacher() {
 int mid_pos = 0, mx_pos = 0;
 for(int i = (1), _ = (N); i <= _; ++ i) {
  int pre = max(mid_pos * 2 - i, 0);
  int ret = max(min(r[pre], mx_pos - i + 1), 1);



  while(inp[i - ret + 1] == inp[i + ret - 1] && (i - ret + 1) && (i + ret - 1 <= N))
   ++ ret;

  r[i] = ret - 1;
  if(chkmax(mx_pos, i + ret - 1))
   mid_pos = i;

  if(chkmax(mid_len, r[i] * 2 - 1))
   mid = i - r[i] + 1;
 }



}

pii rmax(int p1, int l1, int p2, int l2) {
 return g[p1][l1] > g[p2][l2] ? make_pair(g[p1][l1], pos[p1][l1]) : make_pair(g[p2][l2], pos[p2][l2]);
}

pii getmax(int L, int R) {
 int len = R - L + 1;
 return rmax(L, LOG[len], R - (1 << LOG[len]) + 1, LOG[len]);
}

void init_rmq() {
 for(int i = (1), _ = (N); i <= _; ++ i) g[i][0] = r[i], pos[i][0] = i;
 for(int i = (2), _ = (N); i <= _; ++ i) LOG[i] = LOG[i >> 1] + 1;
 for(int j = (1), _ = (17); j <= _; ++ j) {
  for(int i = (1), _ = (N - (1 << j) + 1); i <= _; ++ i) {
   pii ret = rmax(i, j - 1, i + (1 << (j - 1)), j - 1);
   g[i][j] = ret.first;
   pos[i][j] = ret.second;
  }
 }



}

int main() {





 gets(inp + 1);
 N = strlen(inp + 1);


 getfail();
 manacher();
 init_rmq();




 int cur = 0;
 for(int i = (1), _ = (N); i <= _; ++ i) {
  while(cur && inp[i] != ant[cur + 1])
   cur = fail[cur];

  if(ant[cur + 1] == inp[i])
   ++ cur;

  int lbnd = i + 1, rbnd = N - cur;
  if(lbnd > rbnd) break;


  int l = 1, r = (rbnd - lbnd) / 2 + 2, ret_pos = getmax(lbnd, rbnd).second;
  while(l + 1 < r) {
   int mid = (l + r) >> 1;
   pii R = getmax(lbnd + mid - 1, rbnd - mid + 1);
   if(R.first >= mid) {
    l = mid;
    ret_pos = R.second;
   } else
    r = mid;
  }



  if(cur * 2 + l * 2 - 1> mid_len + pre_len * 2) {
   mid_len = l * 2 - 1;
   pre_len = suf_len = cur;
   mid = ret_pos - l + 1;
   pre = i - cur + 1;
  }
 }

 if(pre == 0) {
  puts("1");
  printf("%d %d\n", mid, mid_len);
 } else {
  puts("3");
  printf("%d %d\n%d %d\n%d %d\n", pre, pre_len, mid, mid_len, N - pre_len + 1, pre_len);
 }

 return 0;
}

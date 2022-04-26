}

const int MAXN = 1.1e5 + 5;
const int MAXD = 20;

namespace RMQ {
    int log2[MAXN];
    int maxv[MAXD][MAXN];
    int pos[MAXD][MAXN];

    void exec(int *a, int n) {
 int i, d, *now, *last;
 for (i=0; i<n; ++i) maxv[0][i] = a[i], pos[0][i] = i;
 for (log2[0]=log2[1]=0, i=2; i<=n; ++i)
     log2[i] = log2[i>>1]+1;
 for (d=1; 1<<d<=n; ++d) {
     now = maxv[d], last = maxv[d-1];
     for (i=0; i+(1<<d) <= n; ++i) {
  now[i] = std::max(last[i], last[i+(1<<(d-1))]);
  pos[d][i] = now[i]==last[i]? pos[d-1][i] : pos[d-1][i+(1<<(d-1))];
     }
 }
    }

    int getmax(int l, int r) {
 int d = log2[r-l];
 return std::max(maxv[d][l], maxv[d][r-(1<<d)]);
    }

    int getpos(int l, int r) {
 int d = log2[r-l];
 return getmax(l,r) == maxv[d][l]? pos[d][l] : pos[d][r-(1<<d)];
    }
}

namespace MNC {
    void exec(char *s, int *maxv, int n) {
 int i, id;
 for (i=id=0; i<n; ++i) {
     maxv[i] = std::min(maxv[id*2-i], id+maxv[id]-i);
     while (i+maxv[i]<n
     && i-maxv[i]>=0
     && s[i+maxv[i]] == s[i-maxv[i]])
  ++ maxv[i];
     if (i+maxv[i] > id+maxv[id])
  id = i;
 }
    }
}

namespace MP {
    void exec(char *s, int *fa, int n) {
 int i, j;
 for (fa[0]=fa[1]=0, i=1; i<n; ++i) {
     j = fa[i];
     while (j && s[j] != s[i]) j = fa[j];
     fa[i+1] = j + (s[j] == s[i]);
 }
 s[n] = 'z'+1;
    }
}

int n;
char s[MAXN];
char fs[MAXN];
int fa[MAXN];
int maxv[MAXN];
std::pair<int, int> ans1, ans2, ans3;

void exec() {
    int i, j, l, r, mid, ans;
    scanf("%s", s), n = strlen(s);
    memcpy(fs, s, sizeof(*s)*n);
    std::reverse(fs, fs+n);
    MP::exec(fs, fa, n);
    MNC::exec(s, maxv, n);

    RMQ::exec(maxv, n);
    ans = RMQ::getmax(0, n)*2-1;
    ans2.first = RMQ::getpos(0, n)-ans/2;
    ans2.second = ans;
    for (i=j=0; i<n; ++i) {
     while (j && fs[j] != s[i]) j = fa[j];
     if (s[i] == fs[j]) ++ j;
 l = -1, r = (n-j-i)/2 + 1;
 while (mid = l+(r-l)/2, r-l > 1)
     (RMQ::getmax(i+mid, n-j-mid+1) >= mid? l : r) = mid;

 if (l>0 && chkmax(ans, l*2-1+j*2)) {
     ans1 = std::make_pair(i-j+1, j);
     ans2 = std::make_pair(RMQ::getpos(i+l, n-j-l+1)-l+1, l*2-1);
     ans3 = std::make_pair(n-j, j);
 }
    }
    ++ans1.first, ++ans2.first, ++ans3.first;
    if (!ans1.second)
 printf("%d\n%d %d\n", 1, ans2.first, ans2.second);
    else if (ans1.first + ans1.second == ans2.first
      && ans2.first + ans2.second == ans3.first)
 printf("%d\n%d %d\n", 1, ans1.first, ans1.second+ans2.second+ans3.second);
    else
 printf("%d\n%d %d\n%d %d\n%d %d\n", 3, ans1.first, ans1.second, ans2.first, ans2.second, ans3.first, ans3.second);
}

int main() {
    if (fopen("E.in", "r") != 
# 117 "data/323.cpp" 3 4
                             __null
# 117 "data/323.cpp"
                                 ) {
 freopen("E.in", "r", 
# 118 "data/323.cpp" 3 4
                     stdin
# 118 "data/323.cpp"
                          );
 freopen("E.out", "w", 
# 119 "data/323.cpp" 3 4
                      stdout
# 119 "data/323.cpp"
                            );
    }

    exec();

    return 0;
}

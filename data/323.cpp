#include <cstdio>
#include <cstring>
#include <algorithm>

#define x first
#define y second
#define pii std::pair<int, int>
#define mk std::make_pair

template <typename T> inline bool chkmax(T &x, T y) {
    return x<y? x=y, true : false;
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
pii ans1, ans2, ans3;

void exec() {
    int i, j, l, r, mid, ans;
    scanf("%s", s), n = strlen(s);
    memcpy(fs, s, sizeof(*s)*n);
    std::reverse(fs, fs+n);
    MP::exec(fs, fa, n);
    MNC::exec(s, maxv, n);
    // for (i=0; i<n; ++i) fprintf(stderr, "%d ", maxv[i]);
    RMQ::exec(maxv, n);
    ans = RMQ::getmax(0, n)*2-1;
    ans2.x = RMQ::getpos(0, n)-ans/2;
    ans2.y = ans;
    for (i=j=0; i<n; ++i) {
    	while (j && fs[j] != s[i]) j = fa[j];
    	if (s[i] == fs[j]) ++ j;
	l = -1, r = (n-j-i)/2 + 1;
	while (mid = l+(r-l)/2, r-l > 1)
	    (RMQ::getmax(i+mid, n-j-mid+1) >= mid? l : r) = mid;
	// fprintf(stderr, "i=%d j=%d n-j=%d r=%d l=%d %c\n", i, j, n-j, (n-j-i)/2 + 1, l, s[i]);
	if (l>0 && chkmax(ans, l*2-1+j*2)) {
	    ans1 = mk(i-j+1, j);
	    ans2 = mk(RMQ::getpos(i+l, n-j-l+1)-l+1, l*2-1);
	    ans3 = mk(n-j, j);
	}
    }
    ++ans1.x, ++ans2.x, ++ans3.x;
    if (!ans1.y)
	printf("%d\n%d %d\n", 1, ans2.x, ans2.y);
    else if (ans1.x + ans1.y == ans2.x
	     && ans2.x + ans2.y == ans3.x)
	printf("%d\n%d %d\n", 1, ans1.x, ans1.y+ans2.y+ans3.y);
    else
	printf("%d\n%d %d\n%d %d\n%d %d\n", 3, ans1.x, ans1.y, ans2.x, ans2.y, ans3.x, ans3.y);
}

int main() {
    if (fopen("E.in", "r") != NULL) {
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
    }

    exec();

    return 0;
}

   	   			 		   	 		     			
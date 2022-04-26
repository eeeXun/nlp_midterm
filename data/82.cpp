// think twice code once
// Start:2016-11-30 20:51:45
// End  :
#include <bits/stdc++.h>
using namespace std;

#define rep(i, x, y) for(int i = (x), _ = (y); i <= _; ++ i)
#define per(i, x, y) for(int i = (x), _ = (y); i >= _; -- i)
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#define disp(x) cout << #x << " = " << x << "; "

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

#define x first
#define y second
#define mp make_pair

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
	rep(i, 2, N) {
		while(cur && ant[cur + 1] != ant[i]) 
			cur = fail[cur];
		if(ant[cur + 1] == ant[i])
			cur ++;
		fail[i] = cur;
	}

//	rep(i, 1, N) {
//		disp(i), disp(fail[i]), puts("");
//	}
}

void manacher() {
	int mid_pos = 0, mx_pos = 0;
	rep(i, 1, N) {
		int pre = max(mid_pos * 2 - i, 0);
		int ret = max(min(r[pre], mx_pos - i + 1), 1);
//		disp(i), disp(mid_pos), disp(mx_pos), puts("");
//		disp(pre), disp(ret), puts("");
		
		while(inp[i - ret + 1] == inp[i + ret - 1] && (i - ret + 1) && (i + ret - 1 <= N))
			++ ret;

		r[i] = ret - 1;
		if(chkmax(mx_pos, i + ret - 1))
			mid_pos = i;

		if(chkmax(mid_len, r[i] * 2 - 1))
			mid = i - r[i] + 1;
	}

//	rep(i, 1, N) printf("%4c", inp[i]); puts("");
//	rep(i, 1, N) printf("%4d", r[i]); puts("");
}

pii rmax(int p1, int l1, int p2, int l2) {
	return g[p1][l1] > g[p2][l2] ? mp(g[p1][l1], pos[p1][l1]) : mp(g[p2][l2], pos[p2][l2]);
}

pii getmax(int L, int R) {
	int len = R - L + 1;
	return rmax(L, LOG[len], R - (1 << LOG[len]) + 1, LOG[len]);
}

void init_rmq() {
	rep(i, 1, N) g[i][0] = r[i], pos[i][0] = i;
	rep(i, 2, N) LOG[i] = LOG[i >> 1] + 1;
	rep(j, 1, 17) {
		rep(i, 1, N - (1 << j) + 1) {
			pii ret = rmax(i, j - 1, i + (1 << (j - 1)), j - 1);
			g[i][j] = ret.x;
			pos[i][j] = ret.y;
		}
	}

//	rep(i, 1, N) rep(j, i, N)
//		disp(i), disp(j), disp(getmax(i, j).x), disp(getmax(i, j).y), puts("");
}

int main() {
#ifdef Leeson
	freopen("tmp.in", "r", stdin);
	freopen("tmp.out", "w", stdout);
#endif

	gets(inp + 1);
	N = strlen(inp + 1);
//	puts(inp + 1);

	getfail();
	manacher();
	init_rmq();

//	disp(mid);
//	disp(mid_len), puts("");

	int cur = 0;
	rep(i, 1, N) {
		while(cur && inp[i] != ant[cur + 1])
			cur = fail[cur];

		if(ant[cur + 1] == inp[i])
			++ cur;

		int lbnd = i + 1, rbnd = N - cur;
		if(lbnd > rbnd) break;
//		printf("while "); disp(lbnd), disp(rbnd), puts("");
		
		int l = 1, r = (rbnd - lbnd) / 2 + 2, ret_pos = getmax(lbnd, rbnd).y;
		while(l + 1 < r) {
			int mid = (l + r) >> 1;
			pii R = getmax(lbnd + mid - 1, rbnd - mid + 1);
			if(R.x >= mid) {
				l = mid;
				ret_pos = R.y;
			} else
				r = mid;
		}

//		disp(cur), disp(l), puts("");

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

		   			 		    			  			 		 	 	
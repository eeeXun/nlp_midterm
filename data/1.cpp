#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 5;
const int logN = 18;

struct SufxAuto {
  static const int V = N << 1;
  static const int S = 26;

  int ch[V][S], link[V], len[V], epos[V];
  int total, last;

  SufxAuto() {
    total = last = 1;
    memset(ch, 0, sizeof(ch));
    memset(len, 0, sizeof(len));
    memset(link, 0, sizeof(link));
    memset(epos, 0, sizeof(epos));
  }
  inline void extend(int c, int i) {
		int p = last, np = last = ++total;
		len[np] = len[p] + 1, epos[np] = i;
		for (; p && !ch[p][c]; p = link[p]) ch[p][c] = np;
		if (!p) { link[np] = 1; return; }
		int q = ch[p][c];
		if (len[q] == len[p] + 1) { link[np] = q; return; }
		int nq = ++total;
		memcpy(ch[nq], ch[q], S << 2), link[nq] = link[q], epos[nq] = epos[q];
		len[nq] = len[p] + 1, link[np] = link[q] = nq;
		for (; p && ch[p][c] == q; p = link[p]) ch[p][c] = nq;
	}
  void solve();
} SAM;
// lgrekfxcxkagcbtwczwvmqeiyvnacwglobshlqqm
char s[N];
int n, p[N];

std::pair<int, int> st[logN][N];
int lg2[N];
void init_st() {
	for (int i = 1; i <= n; i++)
		st[0][i] = std::make_pair(p[i], i);
	for (int j = 1; j < logN; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[j][i] = std::max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	lg2[0] = -1;
	for (int i = 1; i <= n; i++)
		lg2[i] = lg2[i >> 1] + 1;
}
std::pair<int, int> get_max(int l, int r) {
	int t = lg2[r - l + 1];
	return std::max(st[t][l], st[t][r - (1 << t) + 1]);
}

void manacher() {
	s[0] = '&', s[n + 1] = '|';
	for (int i = 1, x = 0; i <= n; i++) {
		if (p[x] + x >= i) p[i] = std::min(p[x * 2 - i], x - i + p[x]);
		for (; s[i + p[i] + 1] == s[i - p[i] - 1]; p[i]++);
		if (p[x] + x < p[i] + i) x = i;
	}
}

void SufxAuto::solve() {
	int maxlen = 0;
	std::vector<std::pair<int, int> > ans;
  for (int x = 1, p = n; p > (n + 1) / 2; p--) {  	
    if (!(x = ch[x][s[p] - 'a'])) break;
		int curlen = (n - p + 1) * 2;
		
		int tl = epos[x] + 1, tr = p - 1;
		int sl = 0, sr = (tr - tl) / 2;
		if (tl > tr) break;
		std::pair<int, int> res(-1, -1);
		while (sl <= sr) {
			int mid = (sl + sr) >> 1;
			std::pair<int, int> tmp = get_max(tl + mid, tr - mid);
			tmp.first = std::min(tmp.first, mid);
			if (tmp.first == mid) res = tmp, sl = mid + 1;
			else sr = mid - 1;
		}
		
		if (res.first == -1) continue;
		curlen += res.first * 2 + 1;
		
		if (curlen > maxlen) {
			maxlen = curlen, ans.clear();
			ans.push_back(std::make_pair(epos[x] - n + p, n - p + 1));
			ans.push_back(std::make_pair(p, n - p + 1));
			ans.push_back(std::make_pair(res.second - res.first, res.first * 2 + 1));
		}
  }
  
  int *lp = std::max_element(p + 1, p + 1 + n);
  if (*lp * 2 + 1 > maxlen) {
  	printf("1\n%d %d\n", lp - p - *lp, *lp * 2 + 1);
  	return;
	}
  
  if (ans.empty()) {
  	puts("1\n1 1");
  	return;
	}
  
  std::sort(ans.begin(), ans.end());
  printf("%d\n", (int)ans.size());
  for (int i = 0; i < (int)ans.size(); i++)
  	printf("%d %d\n", ans[i].first, ans[i].second);
}

signed main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  
  if (n == 1) {
  	puts("1\n1 1");
  	return 0;
	} else if (n == 2) {
		if (s[1] == s[2]) puts("1\n1 2");
		else puts("1\n1 1");
		return 0;
	}
  
  manacher();
  init_st();
  
  for (int i = 1; i <= n; i++)
    SAM.extend(s[i] - 'a', i);
  SAM.solve();
  return 0;
}
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

// KL : max length, KN : logL
const int L = 204800, KN = 19;

class SuffixArray {
private:
	// sn : total length, a : string, sa[rank[i]] = i
	// rank[i] : the index of lexicographic ith suffix
	// h[i] = maxPrefix(sa[i], sa[i-1]), hei[i] : hei[i] = h[sa[i]]
	int sn, a[L], sa[L], rank[L], h[L], hei[L];
	// RMQ Table
	int st[KN][L];
	inline int less(int t0, int r0, int t1, int r1) const 
		{ return t0 < t1 || (t0 == t1 && r0 <= r1); }
	inline int less(int t0, int r0, int c0, int t1, int r1, int c1) const 
		{ return t0 < t1 || (t0 == t1 && less(r0, c0, r1, c1)); }
	void radixSort(int*, int*, int*, int, int);
	void suffixBuild(int*, int*, int, int);
	void initHR();
	void initRMQ();
	// query the LCS of range [min, max) in SA
	int querySA(int, int) const;
public:
	// query the LCS of position [min, max) in original string
	int query(int x, int y) const { return querySA(rank[x], rank[y]); }
	void make(char*, int, int);
};
void SuffixArray::radixSort(int* a, int* b, int* r, int n, int K) {
	int *c = new int[K+1]; memset(c, 0, sizeof(int)*(K+1));
	for(int i = 0; i < n; i++) c[r[a[i]]]++;
	for(int i = 0, sum = 0; i <= K; i++)
		{ int t = c[i]; c[i] = sum; sum += t; }
	for(int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i];
	delete[] c;
}
// T : [1, K], T[n] = T[n+1] = T[n+2] = 0;
void SuffixArray::suffixBuild(int* T, int* SA, int n, int K) {
	int n0 = (n+2)/3, n1 = (n+1)/3, n2 = n/3, n02 = n0+n2;
	int *R = new int[n02+3], *R0 = new int[n0]; R[n02] = R[n02+1] = R[n02+2] = 0;
	int *SA12 = new int[n02+3], *SA0 = new int[n0]; 
	SA12[n02] = SA12[n02+1] = SA12[n02+2] = 0;
	for(int i = 0, j = 0; i < n+(n0-n1); i++)
		if(i%3) R[j++] = i;
	radixSort(R, SA12, T+2, n02, K);
	radixSort(SA12, R, T+1, n02, K);
	radixSort(R, SA12, T, n02, K);
	int name = 0, c0 = -1, c1 = -1, c2 = -1;
	for(int i = 0; i < n02; i++) {
		if(T[SA12[i]] != c0 || T[SA12[i]+1] != c1 || T[SA12[i]+2] != c2)
			{ name++; c0 = T[SA12[i]]; c1 = T[SA12[i]+1]; c2 = T[SA12[i]+2]; }
		if(SA12[i] % 3 == 1) R[SA12[i]/3] = name;
		else R[SA12[i]/3+n0] = name;
	}
	if(name != n02) {
		suffixBuild(R, SA12, n02, name);
		for(int i = 0; i < n02; i++) R[SA12[i]] = i + 1;
	} else
		for(int i = 0; i < n02; i++) SA12[R[i]-1] = i;
	for(int i = 0, j = 0; i < n02; i++)
		if(SA12[i] < n0) R0[j++] = SA12[i]*3;
	radixSort(R0, SA0, T, n0, K);
	for(int i = 0, j = 0, k = n0-n1; i < n; i++) {
#define getI(m) (SA12[m] < n0 ? SA12[m]*3+1 : (SA12[m]-n0)*3+2)
		int p = getI(k), t = SA0[j];
		if(SA12[k] < n0 ?
			less(T[p], R[SA12[k]+n0], T[t], R[t/3]) :
			less(T[p], T[p+1], R[SA12[k]-n0+1], T[t], T[t+1], R[t/3+n0])) {
			SA[i] = p; k++;
			if(k != n02) continue;
			for(i++; i < n; i++, j++) SA[i] = SA0[j];
		} else {
			SA[i] = t; j++;
			if(j != n0) continue;
			for(i++; i < n; i++, k++) SA[i] = getI(k);
		}
	}
	delete[] R; delete[] R0; delete[] SA12; delete[] SA0;
}
void SuffixArray::initHR() {
	for(int i = 0; i < sn; i++) rank[sa[i]] = i;
	for(int i = 0; i < sn; i++) {
		if(rank[i] == 0) { h[i] = 0; continue; }
		int j = i, k = sa[rank[i]-1], p = (i == 0 || h[i-1] <= 1) ? 0 : h[i-1]-1;
		for(; a[j+p] == a[k+p]; j++, k++);
		h[i] = j-i+p;
	}
	for(int i = 0; i < sn; i++) hei[i] = h[sa[i]];
}
void SuffixArray::initRMQ() {
	for(int i = 0; i < sn; i++) st[0][i] = hei[i];
	for(int i = 1, k = 2; k < sn; i++, k <<= 1)
		for(int j = 0; j < sn; j++) {
			int sk = j+(k>>1); st[i][j] = st[i-1][j];
			if(sk < sn) st[i][j] = min(st[i][j], st[i-1][sk]);
		}
}
int SuffixArray::querySA(int x, int y) const {
	if(x > y) swap(x, y);
	int len = y-x, bl;
	for(bl = -1; len != 0; bl++) len >>= 1;
	return min(st[bl][x+1], st[bl][y-(1<<bl)+1]);
}
void SuffixArray::make(char* arr, int n, int m) {
	sn = n;
	for(int i = 0; i < sn; i++) a[i] = arr[i]-'a'+1;
	a[sn] = a[sn+1] = a[sn+2] = 0;
	suffixBuild(a, sa, sn, m);
	initHR(); initRMQ();
}

typedef pair<int, int> PII;

class SegTree {
public:
	SegTree *left, *right;
	int x, y, minx;
	SegTree(int, int);
	~SegTree() { if(y-x != 1) { delete left; delete right; } }
	void insert(int, int);
	PII find(int, int);
};
SegTree::SegTree(int _x, int _y) : left(NULL), right(NULL), x(_x), y(_y), minx(L) {
	if(y-x == 1) return;
	int mid = (y+x)/2;
	left = new SegTree(x, mid);
	right = new SegTree(mid, y);
}
void SegTree::insert(int px, int py)
{
	int mid = (y+x)/2;
	minx = min(minx, py);
	if(y-x == 1) return;
	
	if(px < mid) left->insert(px, py);
	else right->insert(px, py);
}
PII SegTree::find(int px, int py) {
	// printf("%d %d %d, %d %d\n", x, y, minx, px, py);
	if(minx > py) return PII(-1, 0);
	if(x >= px) return PII(-1, 0);
	if(y-x == 1) return PII(minx, x);
	int mid = (y+x)/2;
	PII r = right->find(px, py);
	if(r.second <= 0) return left->find(px, py);
	else return r;
}

char str[L];

SuffixArray sa;

int main()
{
	scanf("%s", str);
	int l = strlen(str);
	str[l] = 'z'+1;
	for(int i = 0; i < l; i++) str[l+i+1] = str[l-1-i];
	str[2*l+1] = 0;
	sa.make(str, 2*l+1, 28);
	
	SegTree *root = new SegTree(0, l+1);
	
	root->insert(0, 0);
	int b = 0;
	for(int i = 1; i <= l; i++) {
		// index is 2*l-i
		for(; b < l; b++) if(sa.query(l+1, b) >= i) break;
		
		if(b == l) break;
		root->insert(i, b+i);
		
		// printf("( %d, %d )\n", i, b+i);
		
	}
	int d[3], len[3], res = 0;
	for(int i = 0; i < l; i++) {
		int ml = sa.query(i, 2*l-i);
		
		int r1 = i-ml+1, r2 = i+ml;
		
		PII x = root->find(l-r2+1, r1);
		int totl = x.second*2+2*ml-1;
		
		// printf("%d %d, %d %d, %d %d, %d\n", i, ml, r1, l-r2, x.first, x.second, totl);
		
		if(res >= totl) continue;
		res = totl;
		d[0] = x.first-x.second;
		len[0] = x.second;
		d[1] = i-ml+1;
		len[1] = 2*ml-1;
		d[2] = l-x.second;
		len[2] = x.second;
	}
	int cc = 0;
	for(int i = 0; i < 3; i++) if(len[i] != 0) cc++;
	printf("%d\n", cc);
	for(int i = 0; i < 3; i++) if(len[i] != 0) printf("%d %d\n", d[i]+1, len[i]);
	
	return 0;
}


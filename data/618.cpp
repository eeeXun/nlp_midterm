//Count the number of the same substring in two given string
//the pairs of the same substrings are not shorter than N
#include<cstdio>
#include<cstring>

inline bool leq(int a1, int a2, int b1, int b2) { // lexicographic order
	return a1 < b1 || (a1 == b1 && a2 <= b2);
} // for pairs

inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
	return a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3));
} // and triples
// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r

inline void radixPass(int* a, int* b, int* r, int n, int K) { // count occurrences
	int* c = new int[K + 1]; // counter array
	for (int i = 0; i <= K; i++) c[i] = 0; // reset counters
	for (int i = 0; i < n; i++) c[r[a[i]]]++; // count occurrences
	for (int i = 0, sum = 0; i <= K; i++) { // exclusive prefix sums
		int t = c[i]; c[i] = sum; sum += t;
	}
	for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i]; // sort
	delete [] c;
}

// find the suffix array SA of T[0..n-1] in {1..K}^n
// require T[n]=T[n+1]=T[n+2]=0, n>=2
inline void suffixArray(int* T, int* SA, int n, int K) {
	int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
	int* R = new int[n02 + 3]; R[n02]= R[n02+1]= R[n02+2]=0;
	int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
	int* R0 = new int[n0];
	int* SA0 = new int[n0];
	//******* Step 0: Construct sample ********
	// generate positions of mod 1 and mod 2 suffixes
	// the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
	for (int i=0, j=0; i < n+(n0-n1); i++) if (i%3 != 0) R[j++] = i;
	//******* Step 1: Sort sample suffixes ********
	// lsb radix sort the mod 1 and mod 2 triples
	radixPass(R , SA12, T+2, n02, K);
	radixPass(SA12, R , T+1, n02, K);
	radixPass(R , SA12, T , n02, K);
	// find lexicographic names of triples and
	// write them to correct places in R
	int name = 0, c0 = -1, c1 = -1, c2 = -1;
	for (int i = 0; i < n02; i++) {
		if (T[SA12[i]] != c0 || T[SA12[i]+1] != c1 || T[SA12[i]+2] != c2){
			name++; c0 = T[SA12[i]]; c1 = T[SA12[i]+1]; c2 = T[SA12[i]+2];
		}
		if (SA12[i] % 3 == 1) { R[SA12[i]/3] = name; } // write to R1
		else { R[SA12[i]/3 + n0] = name; } // write to R2
	}
	// recurse if names are not yet unique
	if (name < n02) {
		suffixArray(R, SA12, n02, name);
		// store unique names in R using the suffix array
		for (int i = 0; i < n02; i++) R[SA12[i]] = i + 1;
	} else // generate the suffix array of R directly
		for (int i = 0; i < n02; i++) SA12[R[i] - 1] = i;
		//******* Step 2: Sort nonsample suffixes ********
		// stably sort the mod 0 suffixes from SA12 by their first character
	for (int i=0, j=0; i < n02; i++) if (SA12[i] < n0) R0[j++] = 3*SA12[i];
	radixPass(R0, SA0, T, n0, K);
	//******* Step 3: Merge ********
	// merge sorted SA0 suffixes and sorted SA12 suffixes
	for (int p=0, t=n0-n1, k=0; k < n; k++) {
		#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
		int i = GetI(); // pos of current offset 12 suffix
		int j = SA0[p]; // pos of current offset 0 suffix
		if (SA12[t] < n0 ? // different compares for mod 1 and mod 2 suffixes
			leq(T[i], R[SA12[t] + n0], T[j], R[j/3]) :
			leq(T[i],T[i+1],R[SA12[t]-n0+1], T[j],T[j+1],R[j/3+n0])){ // suffix from SA12 is smaller
				SA[k] = i; t++;
				if (t == n02) // done --- only SA0 suffixes left
					for (k++; p < n0; p++, k++) SA[k] = SA0[p];
				} else { // suffix from SA0 is smaller
					SA[k] = j; p++;
					if (p == n0) // done --- only SA12 suffixes left
						for (k++; t < n02; t++, k++) SA[k] = GetI();
				}
	}
	delete [] R; delete [] SA12; delete [] SA0; delete [] R0;
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

// LCP(i,j)=min{hgt[k]|i+1<=k<=j}
// hgt[k]=LCP(i-1,i)
// O(4n)
inline void calcHeight(int* T, int* SA, int* H, int n) {
	int * rank = new int[n+3];
	int * h = new int[n+3];
	for(int i = 0; i < n; i++) rank[SA[i]] = i;
	for(int i = 0; i < n; i++) {
		if(!rank[i]) h[i]=0;
		else if (!i || h[i - 1] <= 1) {
			int t1 = i, t2 = SA[rank[i] - 1], cnt = 0, mmax = min(n - t1, n - t2);
			for (int j = 0; j < mmax; j++) {
				if (T[t1 + j] == T[t2 + j]) cnt++;
				else break;
			}
			h[i] = cnt;
		} else {
			int t1 = i, t2 = SA[rank[i] - 1], cnt = h[i - 1] - 1, mmax = min(n - t1, n - t2);
			for (int j = h[i - 1] - 1; j < mmax; j++) {
				if (T[t1+j] == T[t2+j]) cnt++;
				else break;
			}
			h[i] = cnt;
		}
	}
	for (int i = 0; i < n; i++) H[i] = h[SA[i]];
	delete [] rank;
	delete [] h;
}

#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

const int MAXN = 200020 + 1;
const int MAXM = 22 + 1;

int n, T[MAXN], SA[MAXN], RANK[MAXN], H[MAXN], RMQ[MAXM][MAXN], LOG2[MAXN];
char str[MAXN], revstr[MAXN];

inline void calcRMQ(int n, int * H) {
	for (int i = 0; i < n; i++) RMQ[0][i] = H[i];
	for (int len = 1; 1 << len <= n; len++) {
		for (int i = n - (1 << len); i >= 0; i--) RMQ[len][i] = min(RMQ[len - 1][i], RMQ[len - 1][i + (1 << (len - 1))]);
	}
}

inline void initLOG2(int n) {
	for (int i = 0; 1 << i <= n; i++) LOG2[1 << i] = i;
	for (int mask = 2; mask <= n; mask++) {
		if (!LOG2[mask]) LOG2[mask] = LOG2[mask - 1];
	}
}

inline int queryRMQ(int x, int y) {
	int len = LOG2[y - x + 1];
	return min(RMQ[len][x], RMQ[len][y - (1 << len) + 1]);
}

int fail[MAXN], fit[MAXN], maxlen[MAXN], mmax[MAXN], prev[MAXN];

inline void KMP(int lenstr, const char * str, int lenpat, const char * pat) {
	int i, j;
	memset(fail, 0xFF, sizeof(int) * (lenpat + 1));
	for (j = 1; j < lenpat; j++) {
		for (i = fail[j - 1]; i >= 0 && pat[i + 1] != pat[j]; i = fail[i]);
		if (pat[i + 1] == pat[j]) fail[j] = i + 1;
		else fail[j] = -1;
	}
	for (i = j = 0; i < lenstr; i++) {
		if (str[i] == pat[j]) {
			fit[i] = ++j;
			if (j == lenpat) j = fail[j - 1] + 1;
		} else if (j) {
			j = fail[j - 1] + 1;
			i--;
		}
	}
}

vector < pair <int, int> > ans;

int main() {
	scanf("%s", str);
	n = (int)strlen(str);
	for (int i = 0, j = (n << 1) - 1; i < n; i++, j--) T[i] = T[j] = str[i] - 'a' + 1;
	suffixArray(T, SA, n << 1, 26);
	for (int i = 0; i < n << 1; i++) RANK[SA[i]] = i;
	calcHeight(T, SA, H, n << 1);
	calcRMQ(n << 1, H);
	initLOG2(n << 1);
	for (int i = 0; i < n; i++) {
		int x = min(RANK[i], RANK[(n << 1) - 1 - i]) + 1, y = max(RANK[i], RANK[(n << 1) - 1 - i]);
		maxlen[i] = min(queryRMQ(x, y), n - i);
	}
	strcpy(revstr, str);
	reverse(revstr, revstr + n);
	KMP(n, str, n, revstr);
//printf("revstr = \"%s\" str = \"%s\"\n", revstr, str);
	mmax[0] = fit[0];
	prev[0] = 0;
	for (int i = 1; i < n; i++) {
		if (fit[i] > mmax[i - 1]) {
			mmax[i] = fit[i];
			prev[i] = i;
		} else {
			mmax[i] = mmax[i - 1];
			prev[i] = prev[i - 1];
		}
	}
//for (int i = 0; i < n; i++) printf("fit[%d] = %d mmax[%d] = %d\n", i, fit[i], i, mmax[i]);
	int res = 0;
	for (int i = 0; i < n; i++) {
		int x = i - maxlen[i] + 1, y = i + maxlen[i] - 1, tmplen;
		vector < pair <int, int> > tmpans;
		if (!x || y == n - 1) {
			tmplen = y - x + 1;
			tmpans.push_back(make_pair(x, y));
		} else {
			int idx = lower_bound(mmax, mmax + x, n - y) - mmax - 1;
			if (idx < 0 || !mmax[idx]) {
				tmplen = y - x + 1;
				tmpans.push_back(make_pair(x, y));
			} else {
				tmplen = (mmax[idx] << 1) + (y - x + 1);
				tmpans.push_back(make_pair(prev[idx] - mmax[idx] + 1, prev[idx]));
				tmpans.push_back(make_pair(x, y));
				tmpans.push_back(make_pair(n - mmax[idx], n - 1));
			}
		}
		if (res < tmplen) {
			res = tmplen;
			ans = tmpans;
		}
	}
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); i++) printf("%d %d\n", ans[i].first + 1, ans[i].second - ans[i].first + 1);
	return 0;
}

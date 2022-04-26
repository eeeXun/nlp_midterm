#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n;
char s[100010], t[100010];
int nxt[100010], f[100010], maxi[100010], maxi_p[100010];
int p[100010], ans, k, a[5], b[5];
void get_nxt() {
	nxt[1] = 0;
	for (int i = 2, j = 0; i <= n; i++) {
		while (j && t[i] != t[j + 1]) j = nxt[j];
		if (t[i] == t[j + 1]) j++;
		nxt[i] = j;
	}
}
void kmp() {
	for (int i = 1, j = 0; i <= n; i++) {
		while (j && s[i] != t[j + 1]) j = nxt[j];
		if (s[i] == t[j + 1]) j++;
		f[i] = j;
		if (f[i] > maxi[i - 1]) {
			maxi[i] = f[i];
			maxi_p[i] = i - f[i] + 1;
		} else {
			maxi[i] = maxi[i - 1];
			maxi_p[i] = maxi_p[i - 1];
		}
	}
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) t[i] = s[n - i + 1];
	get_nxt();
	kmp();
	s[0] = -1;
	int id = 0, mx = 0;
	for (int i = 1; i <= n; i++) {
		p[i] = ((mx > i) ? min(p[id * 2 - i], mx - i) : 1);
		while (s[i + p[i]] == s[i - p[i]]) p[i]++;
		if (mx < i + p[i]) {
			mx = i + p[i];
			id = i;
		}
//		cout << p[i] << endl;
		int mini = min(maxi[i - p[i]], n - (i + p[i]) + 1);
		int tmp = 2 * p[i] - 1 + 2 * mini;
		if (ans < tmp) {
			ans = tmp;
			if (mini == 0) {
				k = 1;
				a[2] = i - p[i] + 1; b[2] = ans;
			} else {
				k = 3;
				a[1] = maxi_p[i - p[i]]; b[1] = mini;
				a[2] = i - p[i] + 1; b[2] = 2 * p[i] - 1;
				a[3] = n - mini + 1; b[3] = mini;
			}
		}
		ans = max(ans, 2 * p[i] - 1 + 2 * min(maxi[i - p[i]], n - (i + p[i]) + 1));
	}
	cout << k << endl;
	if (k == 1) {
		cout << a[2] << " " << b[2] << endl;
	} else {
		cout << a[1] << " " << b[1] << endl;
		cout << a[2] << " " << b[2] << endl;
		cout << a[3] << " " << b[3] << endl;
	}
	
	return 0;
} 
		  	 			   	 	   	    			   		
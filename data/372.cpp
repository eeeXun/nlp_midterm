#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;

const int maxN = 100005;

struct Data{
	int v, next;
}dat[maxN];
int fir[maxN], dats;

char str[maxN];
int n;
int f[maxN], g[maxN];
int p[maxN];
int selfkmp[maxN], kmp[maxN];
int arrs, arr[maxN];

void insertdata(int u, int v){
	dats++;
	dat[dats].v=v;
	dat[dats].next = fir[u];
	fir[u] = dats;
}

void Readln(){
	scanf( "%s", str );
	n = strlen(str);
	for (int i=1; i<=n; i++) f[i] = g[n-i+1] = str[i-1]-96;
}

void manacher(){
	p[1] = 1;
	int maxi = 1, maxL = 1;
	for (int i=2; i<=n; i++){
		if (i > maxL) p[i] = 1;
			else p[i] = min(maxL - i + 1, p[maxi + maxi - i]);
		while (f[i+p[i]] == f[i-p[i]] && i+p[i] <= n && i-p[i] >= 0) p[i]++;
		if (i+p[i]-1 > maxL){
			maxL = i + p[i] - 1;
			maxi = i;
		}
	}
}

void ext_kmp(){
	selfkmp[2] = 0;
	while (g[1+selfkmp[2]] == g[2+selfkmp[2]] && 2+selfkmp[2] <= n) selfkmp[2]++;
	int maxi = 2, maxL = 2+selfkmp[2]-1;
	for (int i=3; i<=n; i++){
		int now;
		if (i > maxL) now = 0;
			else now = min(maxL - i + 1, selfkmp[i - maxi + 1]);
		while (g[i+now] == g[1+now] && i+now <= n) now ++;
		if (i + now - 1 > maxL){
			maxL = i + now - 1;
			maxi = i;
		}
		selfkmp[i] = now;
	}
	kmp[1] = 0;
	while (f[1+kmp[1]] == g[1+kmp[1]] && 1+kmp[1] <= n) kmp[1]++;
	maxi = 1; maxL = 1+kmp[1]-1;
	for (int i=2; i<=n; i++){
		int now;
		if (i > maxL) now = 0;
			else now = min(maxL - i + 1, selfkmp[i-maxi+1]);
		while (f[i+now] == g[1+now] && i+now <= n) now ++;
		if (i + now - 1 > maxL){
			maxL = i + now - 1;
			maxi = i;
		}
		kmp[i] = now;
	}
}

void Solve(){
	manacher();
	ext_kmp();
	for (int i=1; i<=n; i++) insertdata(i-p[i]+1, i+p[i]-1);
	int arrs = 0;
	int ans = 0;
	int A = 0, B = 0;
	for (int i=1; i<=n; i++){
		for (int j=fir[i]; j!=0; j=dat[j].next){
			int tLen = dat[j].v - i + 1;
			if (arrs == 0){
				if (tLen > ans){
					ans = tLen;
					B = (i + dat[j].v) >> 1;
					A = 0;
				}
			}else{
				int L = 0, R = arrs+1;
				while (L + 1 < R){
					int mid = (L + R) >> 1;
					if (arr[mid] + kmp[arr[mid]] - 1 < i)
						L = mid; else R = mid;
				}
				if (0 < L){
					if (tLen + 2*min(kmp[arr[L]], n-dat[j].v) > ans){
						ans = tLen + 2*min(kmp[arr[L]], n-dat[j].v);
						B = (i + dat[j].v) >> 1;
						A = arr[L];
					}
				}
				if (R <= arrs){
					if (tLen + 2*min(i-arr[R], n-dat[j].v) > ans){
						ans = tLen + 2*min(i-arr[R], n-dat[j].v);
						B = (i + dat[j].v) >> 1;
						A = arr[R];
					}
				}
			}
		}
		if (kmp[i] > kmp[arr[arrs]]) arr[++arrs] = i;
	}
	if (A == 0){
		printf( "1\n" );
		printf( "%d %d\n", B-p[B]+1, 2*p[B]-1 );
	}else{
		printf( "3\n" );
		int Len = min(B-p[B]+1-A, n-(B+p[B]-1));
		Len = min(Len, kmp[A]);
		printf( "%d %d\n", A, Len );
		printf( "%d %d\n", B-p[B]+1, 2*p[B]-1 );
		printf( "%d %d\n", n-Len+1, Len );
	}
}

int main(){
	Readln();
	Solve();
	return 0;
}
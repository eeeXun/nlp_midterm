#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
//#include <cmath>
#define ran2 (rand() % 32000 * 32000 + rand() % 32000)
using namespace std;

int m,n,j,k,l,i,o,p,__t;

char ch;
void read(int &a){
	for (ch = getchar();(ch < '0' || ch > '9') && (ch != '-');ch = getchar());
	if (ch == '-') a = 0,__t = -1; else a = ch - '0',__t = 1;
	for (ch = getchar();ch >= '0' && ch <= '9';ch = getchar()) a = a * 10 + ch - '0';
	a *= __t;
}
#define mx 400000
char S[mx],revS[mx];
int next[mx],first[mx],N[mx];

void force(int P){
	for (int i = P - N[P] - 1,j = P + N[P] + 1;i > 0 && j <= m && S[i] == S[j];i --,j ++) N[P] ++;
}

int maxi[mx][22],ER[mx];

void prepare(){
	for (int i = 1;i <= m;i ++)
		maxi[i][0] = i;
	for (int j = 1,k = 1;(1 << j) <= m;j ++,k *= 2){
		for (int i = 1;i + k + k - 1 <= m;i ++)
			if (N[maxi[i][j - 1]] < N[maxi[i + k][j - 1]])
				maxi[i][j] = maxi[i + k][j - 1]; else
				maxi[i][j] = maxi[i][j - 1];
				
	}
	for (int i = 2,j = 0;i < mx;i ++){
		if ((1 << (j + 1)) == i) j ++;
		ER[i] = j;
	}
}

int calc(int L,int R){
	int len = (R - L + 1);
	if (N[maxi[L][ER[len]]] > N[maxi[R - (1 << ER[len]) + 1][ER[len]]])
		return maxi[L][ER[len]]; else 
		return maxi[R - (1 << ER[len]) + 1][ER[len]];
}
int ans,a0,a1,a2,x0,x1,x2;

int main(){
	//freopen("E.in","r",stdin);
	//freopen("E.out","w",stdout);

	gets(S + 1);
	for (m = 1;S[m] > 0;m ++) revS[m] = S[m];
	m --;
	reverse(revS + 1,revS + 1 + m);
	next[1] = 0;
	for (int i = 2;i <= m;i ++){
		int pre = next[i - 1];
		for (;pre != 0 && revS[pre + 1] != revS[i];pre = next[pre]);
		if (pre == 0 && revS[1] != revS[i]) next[i] = 0; else 
		next[i] = pre + 1;
	}
	
	for (int i = 1,j = 1;i <= m;i ++){
		int temp = j - 1;
		for (;temp != 0 && S[i] != revS[temp + 1];temp = next[temp]);
		if (temp == 0 && S[i] != revS[1]) j = 1; else 
		j = temp + 2;
		if (first[j - 1] == 0) first[j - 1] = i;
	}
	
	int P = 1;
	ans = 1,a0 = 1,x0 = 1;
	for (int i = 2;i <= m;i ++){
		if (i > P + N[P]){
			force(i);
			P = i;
			if (N[P] * 2 + 1 > ans){
				ans = N[P] * 2 + 1;
				a1 = a2 = 0;
				a0 = i - N[i]; x0 = N[i] * 2 + 1;
			}
			continue;
		}
		int flect = 2 * P - i;
		if (flect - N[flect] > P - N[P])
			N[i] = N[flect]; else
			N[i] = P + N[P] - i,force(i);
		if (i + N[i] > P + N[P]) P = i;
		if (N[P] * 2 + 1 > ans){
			ans = N[P] * 2 + 1;
			a1 = a2 = 0;
			a0 = i - N[i]; x0 = N[i] * 2 + 1;
		}
	}
	prepare();
	
	for (int len = 1;len <= m;len ++){
		if (first[len] == 0) break;
		int l = first[len] + 1;
		int r = m - len;
		if (l > r) break;
		int best = -1,ok = -1;
		for (int lef = 0,rig = m;lef <= rig;){
			int mid = (lef + rig) / 2;
			int L = l + mid;
			int R = r - mid;
			if (L > R) rig = mid - 1; else {
				if (N[calc(L,R)] >= mid) lef = mid + 1,best = mid,ok = calc(L,R); else
				rig = mid - 1;
			}
		}
		int nimas = 2 * best + 1;
		if (nimas < 0) nimas = 0;
		if (nimas + len * 2 > ans){
			ans = nimas + len * 2;
			a0 = first[len] - len + 1,x0 = len;
			if (best == -1) a1 = 0,x1 = 0; else 
			a1 = ok - best,x1 = best * 2 + 1;
			a2 = m - len + 1,x2 = len;
		}
	}
	int print = 0;
	//if (a0 != 0) print += x0;
	//if (a1 != 0) print += x1;
	//if (a2 != 0) print += x2;
	//cout << print << endl;
	if (a0 != 0) print ++;
	if (a1 != 0) print ++;
	if (a2 != 0) print ++;
	printf("%d\n",print);
	//if (a0 == 62639) printf("%d\n",first[7]);
	if (a0 != 0) printf("%d %d\n",a0,x0);
	if (a1 != 0) printf("%d %d\n",a1,x1);
	if (a2 != 0) printf("%d %d\n",a2,x2);
	//fclose(stdin); fclose(stdout);
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 4e5 + 5;
char s[maxn], t[maxn];
ll n, d[maxn], p, maxr;
ll nex[maxn], mx[maxn], id[maxn];
ll l1, len1, mid;
int main(){
	cin >> s + 1;
	n = strlen(s + 1);
	for(int i = 1;i <= n;i++) d[i] = 0;
	p = maxr = 0;
	for(int i = 1;i <= n;i++){
		if(i <= maxr){
			d[i] = min(d[maxr + p - i], maxr - i + 1);
		}
		while(i - d[i] > 0 && i + d[i] <= n &&
		s[i - d[i]] == s[i + d[i]]) ++d[i];
		if(i + d[i] - 1 > maxr){
			p = i - d[i] + 1, maxr = i + d[i] - 1;
		}
	}
	for(int i = 1;i <= n;i++) t[i] = s[n - i + 1];
	t[n + 1] = '#';
	for(int i = 1;i <= n;i++){
		t[n + i + 1] = s[i];
	}
	ll N = 2 * n + 1;
	ll now = 0; nex[0] = -1;
	for(int i = 1;i <= N;i++){
		now = nex[i - 1];
		while(~now && t[now + 1] != t[i]) now = nex[now];
		nex[i] = now + 1;
	}
	for(int i = n + 1;i <= N;i++){
		if(nex[i] >= mx[i - 1]){
			mx[i] = nex[i];
			id[i] = i;
		} else {
			mx[i] = mx[i - 1];
			id[i] = id[i - 1];
		}
	}
	ll mmx = 0;
	for(int i = n + 2;i <= N;i++){
		if(2 * d[i - n - 1] - 1 + 2 * min(mx[i - d[i - n - 1]], N - i - d[i - n - 1] + 1
		) > mmx){
			mmx = 2 * d[i - n - 1] - 1 + 2 * min(mx[i - d[i - n - 1]], 
			N - i - d[i - n - 1] + 1);
			l1 = id[i - d[i - n - 1]]; mid = i;
			len1 = min(mx[i - d[i - n - 1]], N - i);
		}
	}
	if(l1 == 0 || len1 == 0){
		cout << 1 << endl;
		cout << mid - d[mid - n - 1] + 1 - n - 1 << " " << 2 * d[mid - n - 1] - 1 << endl;
	} else {
		cout << 3 << endl;
		cout << l1 - len1 + 1 - n - 1 << " " << len1 << endl;
		cout << mid - d[mid - n - 1] + 1 - n - 1 << " " << 2 * d[mid - n - 1] - 1 << endl;
		cout << n - len1 + 1 << " " << len1 << endl; 
	}
	return 0;
}
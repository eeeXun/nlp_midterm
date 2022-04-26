#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<climits>
#include<sstream>
using namespace std;
#define int long long

const int N = 1e6 + 10;

char c[N];
char s[N];
char t[N];
int net[N] , suf[N] , sux[N] , sua[N];
int p[N];

signed main()
{
	ios::sync_with_stdio(false);
	cin >> (c + 1);
	int n = strlen(c + 1);
	//s[0] = '$';
	//s[n * 2 + 1] = '#';
	/*for (register int i = 1; i <= n; i++)
	{
		s[i * 2 - 1] = c[i];
		s[i * 2] = '#';
	}*/
	for (int i = 1; i <= n; ++i) {
		s[i * 2 - 1] = c[i];
		s[i * 2] = '#';
	}
	/*int r = 1, mid = 1;
	p[1] = 1;
	for (register int i = 2; i <= (n << 1); i++)
	{
		if (i < r)
		{
			p[i] = min(p[(mid << 1) - i], p[mid] + mid - i);
		}
		else
		{
			p[i] = 1;
		}
		while (s[i + p[i]] == s[i - p[i]])
		{
			p[i]++;
		}
		if (p[i] + i > r)
		{
			r = p[i] + i;
			mid = i;
		}
	}
	for (register int i = 3; i <= (n << 1); i += 2)
	{
		if (s[i + p[i]] == '#')
		{
			p[i]--;
		}
		else
		{
			p[i] -= 2;
		}
		p[(i >> 1) + 1] = p[i] + 1;
	}*/
	p[1] = 1; int mid = 1, Maxr(1);
	for (int i = 2, N = n << 1; i <= N; ++i) {
		if (i < Maxr) p[i] = std::min(p[(mid << 1) - i], p[mid] - (i - mid));
		else p[i] = 1;
		while (s[i - p[i]] == s[i + p[i]]) ++p[i];
		if (i + p[i] > Maxr) {
			Maxr = i + p[i]; mid = i;
		}

	}
	for (int i = 3; i <= (n << 1); i += 2) {
		if (s[i + p[i]] == '#') p[i]--;
		else p[i] -= 2;
		p[(i >> 1) + 1] = p[i] + 1;
	}
	for (register int i = 1; i <= (n >> 1); i++)
	{
		t[i] = c[n + 1 - i];
		t[n + 1 - i] = c[i];
	}
	for (register int i = 2, j = 0; i <= n; i++)
	{
		while (t[j + 1] != t[i] && j != 0)
		{
			j = net[j];
		}
		if (t[j + 1] == t[i])
		{
			j++;
			net[i] = j;
		}
		else
		{
			net[i] = 0;
		}
	}
	for (register int i = 1, j = 0; i <= n; i++)
	{
		while (t[j + 1] != c[i] && j != 0)
		{
			j = net[j];
		}
		if (t[j + 1] == c[i])
		{
			j++;
			suf[i] = j;
		}
		else
		{
			suf[i] = 0;
		}
	}
	for (register int i = 1; i <= n; i++)
	{
		if (suf[i] >= sux[i - 1])
		{
			sux[i] = suf[i];
			sua[i] = i;
		}
		else
		{
			sux[i] = sux[i - 1];
			sua[i] = sua[i - 1];
		}
	}
	int ans = 0;
	int az = 0, al = 0;
	for (register int i = 1; i <= n; i++)
	{
		//cout << p[i] + (std::min((sux[i - (p[i] >> 1) - 1]), n - (i + (p[i] >> 1))) << 1) << endl;
		if (ans < p[i] + (min((sux[i - (p[i] >> 1) - 1]), n - (i + (p[i] >> 1))) << 1))
		{
			ans = p[i] + (min((sux[i - (p[i] >> 1) - 1]), n - (i + (p[i] >> 1))) << 1);
			az = i;
			al = sua[i - (p[i] >> 1) - 1];
		}
	}
	if ((n - (az + (p[az] >> 1))) && al && suf[al])
	{
		cout << 3 << endl;
		int len = min(suf[al], n - (az + (p[az] >> 1)));
		cout << al - len + 1 << " " << len << endl;
		cout << az - (p[az] >> 1) << " " << p[az] << endl;
		cout << n - len + 1 << " " << len;
	}
	else
	{
		cout << 1 << endl;
		cout << az - (p[az] >> 1) << " " << p[az];
	}
	return 0;
}
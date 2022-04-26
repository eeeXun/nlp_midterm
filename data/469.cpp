//#pragma comment(linker,"/STACK:256000000")

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cassert>
#include <stdio.h>
#include <string>
#include <memory.h>

using namespace std;

#define ldb long double
#define LL long long
#define nextline() {int c; while ((c = getchar()) != 10 && c != EOF);}

#define PI 3.1415926535897932384626433832795
#define EPS 1e-9

#define sqr(x) ((x) * (x))
#define ABS(a) ((a)<0?-(a):(a))
#define EQ(a,b) (ABS((a)-(b))<EPS)

#define all(a) a.begin(), a.end()
#define two(i) (1 << (i))
#define has(mask, i) ((((mask) & two(i)) == 0) ? false : true)

const int INF = 1000 * 1000 * 1000;
const LL INF64 = 1000LL * 1000LL * 1000LL * 1000LL * 1000LL * 1000LL;

char s[100500];

string x;
int z[2 * 100500];
pair <int, int> ref[100500];
int pal[100500];
int n;

inline void z_func()
{
	int l, r, q;
	z[0] = l = r = 0;
	for (int k = 1; k < (int)x.size(); k++)
	{
		if (k > r)
		{
			q = k;
			while (q < (int)x.size() && x[q] == x[q - k])
				q++;
			z[k] = q - k;
			l = k;
			r = q - 1;
		}
		else
		{
			if (z[k - l] < r - k + 1)
				z[k] = z[k - l];
			else
			{
				q = r + 1;
				while (q < (int)x.size() && x[q] == x[q - k])
					q++;
				z[k] = q - k;
				l = k;
				r = q - 1;
			}
		}
	}
}


void Load()
{
	gets (s);
	n = strlen(s);
	x = (string)s;
	reverse (x.begin(), x.end());
	x = x + "#" + (string)s;
}

void Solve()
{
	for (int i = 0; i < n; i++)
		ref[i].first = ref[i].second = -1;

	z_func();
	int last = 0;

	for (int i = n + 1; i < (int)x.size(); i++)
		if (z[i] > last)
		{
			if (i + (z[i] << 1) + 1 < (int)x.size())
			{
				ref[i - n - 1].first = z[i];
				ref[i - n - 1].second = i - n - 1;
			}
			last = z[i];
		}
	for (int i = 1; i < n; i++)
		ref[i] = max (ref[i], ref[i - 1]);

	int l, r, k, mx;
	mx = 0;
	l = 0, r = -1;
	for (int i = 0; i < n; i++)
	{
		k = (r < i ? 0 : min (pal[l + r - i], r - i)) + 1;		
		while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
			k++;
		pal[i] = --k;
		if (i + k > r) 	
		{
			l = i - k;
			r = i + k;
		}

		int pre_len = 0;
		int pos = i - pal[i] - 1;
		if (pos < 0)
			mx = max (mx, (pal[i] << 1) + 1);
		else
		{
			pre_len = ref[pos].first;
			if (pre_len == -1)
				mx = max (mx, (pal[i] << 1) + 1);
			else
			{
				pre_len = min (pre_len, pos - ref[pos].second + 1);
				pre_len = min (pre_len, n - i - pal[i] - 1);
				mx = max (mx, (pal[i] << 1) + 1 + (pre_len << 1) + 1);
			}
				
		}
	}

	for (int i = 0; i < n; i++)
	{
		int pre_len = 0;
		int pos = i - pal[i] - 1;
		if (pos < 0)
			k = (pal[i] << 1) + 1;
		else
		{
			pre_len = ref[pos].first;
			if (pre_len == -1)
				k = (pal[i] << 1) + 1;
			else
			{
				pre_len = min (pre_len, pos - ref[pos].second + 1);
				pre_len = min (pre_len, n - i - pal[i] - 1);
				k = (pal[i] << 1) + 1 + (pre_len << 1) + 1;
			}
				
		}
		if (k == mx)
		{
			if ((pal[i] << 1) + 1 == k)
				printf ("1\n%d %d", pos + 2, (pal[i] << 1) + 1);
			else
			{
				printf ("3\n");	
				printf ("%d %d\n", ref[pos].second + 1, pre_len);
				printf ("%d %d\n", pos + 2, (pal[i] << 1) + 1);
				printf ("%d %d\n", n - pre_len + 1, pre_len);
			}

			return;
		}
	}
}
                
int main()
{
	//ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
	freopen("in", "rt", stdin);
	freopen("out", "wt", stdout);
#endif
	Load();
	Solve();
	return 0;
}

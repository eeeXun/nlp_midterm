#include <cstdio>
#include <cstring>
#include <algorithm>

int n;
char s[200000], t[200000];
int fail[200000];
int ans, ansl, ansr;
int im[200000];
int last, pos;
int maxx[200000];
int mx[200000][20];
int right[200000];

void getfail()
{
	int j = 0;
	for (int i = 2; i <= n; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		fail[i] = j;
	}
}

int query(int l, int r)
{
	int tmp = im[r - l + 1];
	return std::max(mx[l][tmp], mx[r - (1 << tmp) + 1][tmp]);
}

void calc()
{
	int j = 0;
	for (int i = 1; i <= n; i++)
	{
		while (j && s[j + 1] != t[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == t[i])
		{
			j++;
		}
		if (! right[j])
		{
			right[j] = n - (i - j + 1) + 1;
		}
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n / 2; i++)
	{
		std::swap(s[i], s[n - i + 1]);
	}
	im[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		im[i] = im[i >> 1] + 1;
	}
	ans = 0;
	ansl = 0;
	ansr = 0;
	last = 0;
	pos = 0;
	for (int i = 1; i <= n; i++)
	{
		if (i <= last)
		{
			maxx[i] = std::min(maxx[2 * pos - i], last - i);
		}
		else
		{
			maxx[i] = 0;
		}
		while (i - maxx[i] - 1 >= 1 && i + maxx[i] + 1 <= n && s[i - maxx[i] - 1] == s[i + maxx[i] + 1])
		{
			maxx[i]++;
		}
		if (i + maxx[i] > last)
		{
			pos = i;
			last = i + maxx[i];
		}
		ans = std::max(ans, 2 * maxx[i] + 1);
	}
	for (int i = 1; i <= n; i++)
	{
		mx[i][0] = maxx[i];
	}
	for (int j = 1; (1 << j) <= n; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
		}
	}
	getfail();
	for (int i = 1; i <= n; i++)
	{
		t[i] = s[n - i + 1];
	}
	calc();
	for (int i = 1; i <= n; i++)
	{
		if (right[i])
		{
			int ll = i + 1;
			int rr = right[i] - i;
			if (ll <= rr)
			{
				int l = 0;
				int r = (rr - ll) / 2;
				while (l < r)
				{
					int mid = (l + r + 1) >> 1;
					if (query(ll + mid, rr - mid) >= mid)
					{
						l = mid;
					}
					else
					{
						r = mid - 1;
					}
				}
				if (query(ll + l, rr - l) >= l)
				{
					if (2 * i + 2 * l + 1 > ans)
					{
						ans = 2 * i + 2 * l + 1;
						ansl = i;
						ansr = right[i];
					}
				}
			}
		}
	}
	if (ansl)
	{
		printf("3\n");
		int t = (ans - 2 * ansl - 1) / 2;
		int ll = ansl + 1;
		int rr = ansr - ansl;
		for (int i = ll + t; i <= rr - t; i++)
		{
			if (maxx[i] >= t)
			{
				printf("%d %d\n%d %d\n%d %d\n", n - ansr + 1, ansl,  n - (i + maxx[i]) + 1, t * 2 + 1, n - ansl + 1, ansl);
				return 0;
			}
		}
	}
	else
	{
		printf("1\n");
		int t = (ans - 1) / 2;
		for (int i = 1; i <= n; i++)
		{
			if (maxx[i] == t)
			{
				printf("%d %d\n", n - (i + maxx[i]) + 1, ans);
				return 0;
			}
		}
	}
	return 0;
}

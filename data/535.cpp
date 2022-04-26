#include <bits/stdc++.h>

using namespace std;

namespace jumpmelon
{
	typedef long long big;

	const int MAXN = 100000, K = 17;
	const int SEED1 = 269, SEED2 = 271;
	const int MOD1 = 1000000007, MOD2 = 1000000009;
	char S[MAXN + 10];
	int n, P[MAXN + 10];
	int Log2[MAXN + 10], Max[K][MAXN + 10];
	int Pow1[MAXN + 10], Pow2[MAXN + 10];
	int H1[MAXN + 10], H2[MAXN + 10];
	int R1[MAXN + 10], R2[MAXN + 10];

	void hash_init()
	{
		Pow1[0] = Pow2[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			Pow1[i] = int((big)Pow1[i - 1] * SEED1 % MOD1);
			Pow2[i] = int((big)Pow2[i - 1] * SEED2 % MOD2);
		}
		H1[0] = H2[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			H1[i] = int(((big)H1[i - 1] * SEED1 + S[i]) % MOD1);
			H2[i] = int(((big)H2[i - 1] * SEED2 + S[i]) % MOD2);
		}
		R1[n + 1] = R2[n + 1] = 0;
		for (int i = n; i >= 1; i--)
		{
			R1[i] = int(((big)R1[i + 1] * SEED1 + S[i]) % MOD1);
			R2[i] = int(((big)R2[i + 1] * SEED2 + S[i]) % MOD2);
		}
	}

	inline pair<int, int> get_hash(int a, int b)
	{
		return make_pair(
			int((H1[b] + MOD1 - (big)H1[a - 1] * Pow1[b - a + 1] % MOD1) % MOD1),
			int((H2[b] + MOD2 - (big)H2[a - 1] * Pow2[b - a + 1] % MOD2) % MOD2));
	}
	inline pair<int, int> get_rev_hash(int a, int b)
	{
		return make_pair(
			int((R1[a] + MOD1 - (big)R1[b + 1] * Pow1[b - a + 1] % MOD1) % MOD1),
			int((R2[a] + MOD2 - (big)R2[b + 1] * Pow2[b - a + 1] % MOD2) % MOD2));
	}

	inline bool cmp(int i, int j) { return P[i] < P[j]; }

	void RMQ_init()
	{
		Log2[1] = 0;
		for (int i = 2; i <= n; i++)
			Log2[i] = Log2[i >> 1] + 1;
		for (int i = 1; i <= n; i++)
			Max[0][i] = i;
		for (int i = 1, l = 2; l <= n; i++, l <<= 1)
			for (int j = 1; j + l - 1 <= n; j++)
				Max[i][j] = max(Max[i - 1][j], Max[i - 1][j + (l >> 1)], cmp);
	}

	inline int RMQ_query(int a, int b)
	{
		int t = Log2[b - a + 1];
		return max(Max[t][a], Max[t][b - (1 << t) + 1], cmp);
	}

	void palin_init()
	{
		for (int i = 1; i <= n; i++)
		{
			int &a = P[i] = 0, b = min(i - 1, n - i);
			while (a < b)
			{
				int mid = (a + b + 1) >> 1;
				if (get_hash(i - mid, i) == get_rev_hash(i, i + mid))
					a = mid;
				else
					b = mid - 1;
			}
		}
		RMQ_init();
	}

	int calc_mid(int l, int r)
	{
		int a = 0, b = (r - l) >> 1;
		while (a < b)
		{
			int mid = (a + b + 1) >> 1;
			if (P[RMQ_query(l + mid, r - mid)] >= mid)
				a = mid;
			else
				b = mid - 1;
		}
		return a;
	}

	void calc(int &pos1, int &len1, int &pos2, int &len2)
	{
		int ans = -1;
		for (int i = 0, j = 0; i <= n; i++)
		{
			while (j < n - i && (j < i ||
				get_hash(j - i + 1, j) != get_rev_hash(n - i + 1, n)))
				j++;
			if (j >= n - i)
				break;
			else
			{
				int tmp = calc_mid(j + 1, n - i);
				if (((i + tmp) << 1 | 1) > ans)
				{
					ans = (i + tmp) << 1 | 1;
					pos1 = j - i + 1;
					len1 = i;
					pos2 = RMQ_query(j + 1 + tmp, n - i - tmp) - tmp;
					len2 = tmp << 1 | 1;
				}
			}
		}
	}

	void work()
	{
		int pos1, len1, pos2, len2;
		scanf("%s", S + 1);
		n = strlen(S + 1);
		hash_init();
		palin_init();
		calc(pos1, len1, pos2, len2);
		if (len1)
		{
			puts("3");
			printf("%d %d\n", pos1, len1);
			printf("%d %d\n", pos2, len2);
			printf("%d %d\n", n - len1 + 1, len1);
		}
		else
		{
			puts("1");
			printf("%d %d\n", pos2, len2);
		}
	}
}

int main()
{
	jumpmelon::work();
	return 0;
}

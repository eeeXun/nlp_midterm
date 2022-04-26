#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

char ch[100010], st[200010];
int f[200010], len, occur[100010];
int pre[100010];

struct Ans
{
	int l, r;
} ans[10];

void manacher()
{
	st[0] = '#';
	for (int i = 0; i < len; ++i)
	{
		st[i * 2 + 1] = ch[i];
		st[i * 2 + 2] = '#';
	}
	int l = len * 2 + 1;
	
	f[0] = 0;
	int far = 0, id = 0;
	for (int i = 1; i < l; ++i)
	{
		if (far >= i) f[i] = min(f[id * 2 - i], far - i);
		else f[i] = 0;
		while (i - f[i] > 0 && i + f[i] + 1 < l && st[i + f[i] + 1] == st[i - f[i] - 1]) f[i]++;
		if (i + f[i] > far)
		{
			far = i + f[i];
			id = i;
		}
	}
	for (int i = 0; i < len; ++i)
		f[i] = f[i * 2 + 1] / 2;
}

void work_occur()
{
	memset(occur,0,sizeof(occur));
	memset(pre,0,sizeof(pre));
	int n = 0;
	int now = 0, j = 0;
	for (int i = len - 1; i >= 0; --i, ++n)
	{
		st[n] = ch[i];
		if (n == 0) pre[n] = 0; else pre[n] = pre[n - 1];
		while (st[n] != st[pre[n]] && pre[n] > 0) pre[n] = pre[pre[n] - 1];
		if (n > 0 && st[n] == st[pre[n]]) pre[n]++;
		
		for (; j <= n && now < len; ++now)
		{
			while (ch[now] != st[j] && j > 0) j = pre[j - 1];
			if (ch[now] == st[j]) ++j;
		}
		if (j > n && now <= len) occur[i] = now - 1; else occur[i] = len;
	}
}

void work()
{
	int n;
	int maxl = 0;
	for (int i = 0; i < len; ++i)
	{
		int l = i + f[i] + 1, r = len - 1, mid;
		while (l < r)
		{
			mid = (l + r) / 2;
			if (occur[mid] < i - f[i]) r = mid; else l = mid + 1;
		}
		if (l == r && occur[l] < i - f[i])
		{
			int tmp = f[i] * 2 + 1 + (len - l) * 2;
			if (tmp > maxl)
			{
				maxl = tmp;
				n = 3;
				ans[1].l = occur[l] + 1 - (len - l) + 1; ans[1].r = occur[l] + 1 - ans[1].l + 1;
				ans[2].l = i - f[i] + 1; ans[2].r = i + f[i] + 1 - ans[2].l + 1;
				ans[3].l = l + 1; ans[3].r = len - ans[3].l + 1;
			}
		} else
		{
			int tmp = f[i] * 2 + 1;
			if (tmp > maxl)
			{
				maxl = tmp;
				n = 1;
				ans[1].l = i - f[i] + 1; ans[1].r = i + f[i] + 1 - ans[1].l + 1;
			}
		}
	}
	printf("%d\n",n);
	for (int i = 1; i <= n; ++i) printf("%d %d\n",ans[i].l,ans[i].r);
}

int main()
{
	// freopen("e.in","r",stdin);
	scanf("%s",ch);
	len = strlen(ch);
	manacher();
	work_occur();
	work();
	return 0;
}

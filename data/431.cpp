#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;
const int M = 1000000007;

int n;
int f[N];
char s[N];
int expM[N];
int lPos[N];
int rPos[N];
int ans;
int k;
int start[3];
int length[3];


void find(int pos)
{
	int left, right, mid, low, high;
	left = pos - f[pos];
	right = pos + f[pos];
	
	low = 0; 
	high = min(n / 2, n - 1 - right);
	while (high > low)
	{
		mid = (high + low + 1) / 2;
		if (rPos[mid] < left)
		{
			low = mid;
		}
		else
		{
			high = mid - 1;
		}
	}
	
	int res =  (2*f[pos] + 1) + 2 * low;
	if (res > ans)
	{
		ans = res;
		if (!low)
		{
			k = 1;
			start[1] = pos - f[pos];
			length[1] = 2*f[pos] + 1;
		}
		else
		{
			k = 3;
			start[0] = lPos[low];
			length[0] = low;
			start[2] = n - low;
			length[2] = low;
			start[1] = pos - f[pos];
			length[1] = 2*f[pos] + 1;
		}
	}
}

int main()
{
	int i, j, center, right, len;
	int ans = 0;
	scanf("%s", s);
	n = strlen(s);
	right = -1;
	for (i = 0, j = 0; i < n; i++)
	{
		j = i;
		if (right >= i)
		{
			j = min(right, f[2*center - i] + i);
		}
		
		while (j + 1 < n && 2*i - j - 1 >= 0 && s[j + 1] == s[2*i - j - 1])
		{
			j++;
		}
		f[i] = j - i;
		if (j > right)
		{
			right = j;
			center = i;
		}
	}
	
	expM[0] = 1;
	for (i = 1; i <= n; i++)
	{
		expM[i] = expM[i - 1] * M;
	}
	
	fill(lPos, lPos + n, n);
	fill(rPos, rPos + n, n);
	lPos[0] = -1;
	rPos[0] = -1;
	for (i = 0; i < n - 1 && s[i] != s[n - 1]; i++);
	if (i < n - 1)
	{
		unsigned int hash1, hash2;
		hash2 = hash1 = s[i];
		lPos[1] = i;
		rPos[1] = i;
		for (len = 2; len < n / 2 && i + len - 1 < n - len; len++)
		{
			hash2 = hash2 * M + s[n - len];
			hash1 = hash1 * M + s[i + len - 1];
			while (hash1 != hash2 && i + len - 1 < n - len - 2)
			{
				hash1 = (hash1 - expM[len - 1] * s[i]) * M + s[i + len];
				i++;
			}				
			if (hash1 == hash2)
			{
				lPos[len] = i;
				rPos[len] = i + len - 1;
			}
		}
	}
	
	
	for (i = 0; i < n; i++)
	{
		find(i);
	}
	
	printf("%d\n", k);
	if (k == 1)
	{
		printf("%d %d\n", start[1] + 1, length[1]);
	}
	else
	{
		for (i = 0; i < 3; i++)
		{
			printf("%d %d\n", start[i] + 1, length[i]);
		}
	}
	
	return 0;
}
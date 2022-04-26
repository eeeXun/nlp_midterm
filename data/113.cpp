#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#define For(i,x,y) for(int i=x;i<=y;i++)
#define Dor(i,y,x) for(int i=y;i>=x;i--)
#define Clr(a,x) memset(a,x,sizeof(a))
#define eps 1e-8
#define inf 2147483647
#define LL long long
#define MAXN 100005
using namespace std;
//-----------------------------------------------
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
//-----------------------------------------------
unsigned LL h[2][MAXN], po[MAXN];//包括i的往前和往后的哈希值 
char s[MAXN];
int n, f[MAXN], g[MAXN], m[MAXN], q[MAXN];
unsigned LL Hash(int typ, int l, int r)
{
	return h[typ][r] - h[typ][l] * po[abs(r - l)];	
	//else return h[1][l] - h[1][r] * po[l - r];
}
int Calc(int x)
{
    int s = x - f[x] + 1;
	int e = x + f[x] - 1;
    return f[x] * 2 - 1 + min(g[m[s-1]], n - e) * 2;
}
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	h[0][0] = h[1][n + 1] = 0;
	For(i, 1, n)
		h[0][i] = h[0][i - 1] * 29 + s[i] - 'a';	
	Dor(i, n, 1)
		h[1][i] = h[1][i + 1] * 29 + s[i] - 'a';
	po[0] = 1;
	For(i, 1, n)
		po[i] = po[i - 1] * 29;
	For(i, 1, n)
	{
		int l = 1, ans = 1;
		int r = min(i, n - i + 1);	
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (Hash(0, i, i + mid - 1) == Hash(1, i, i - mid + 1))
				l = mid + 1, ans = mid;
			else r = mid - 1;	
		}
		f[i] = ans;
	}
	/*For(i ,1 ,n)
		cout << f[i] << ' ';
	cout <<endl;*/
	int l = 1, r = 0;
	For(i, 1, n)
	{
		if (s[i] == s[n]) q[++ r] = i;
		while (l <= r && Hash(0, q[l], i) != Hash(1, n, n - (i - q[l]))  && n - (i - q[l]) > i)
			l ++;
		if (l > r) g[i] = 0;
		else g[i] = i - q[l] + 1;
	}
	/*For(i, 1, n)
		cout << g[i] << ' ';
	cout <<endl;*/
	For(i, 1, n)
	{
		m[i] = m[i - 1];
		if (g[m[i]] < g[i])
			m[i] = i;
	}
	int ans = 0;
	For(i ,1, n)
		ans = max(ans, Calc(i));
	for (int i=1;i<=n;i++)
        if (ans==Calc(i))
        {
           int s=i-f[i]+1;
           int e=i+f[i]-1;
           int j=min(g[m[s-1]],n-e);
           int k=m[s-1]-g[m[s-1]]+1;
           if (j) cout << 3 << endl 
                       << k << " " << j << endl 
                       << s << " " <<e-s+1 << endl
                       << n-j+1 << " " << j << endl;
           else cout << 1 << endl << s << " " << e-s+1 << endl;
           return 0;
        }
	return 0;
}
//-----------------------------------------------

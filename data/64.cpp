#include<cmath>
#include<math.h>
#include<ctype.h>
#include<algorithm>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cerrno>
#include<cfloat>
#include<ciso646>
#include<climits>
#include<clocale>
#include<complex>
#include<csetjmp>
#include<csignal>
#include<cstdarg>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cwchar>
#include<cwctype>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
const long long base=233;
const long long Mod=1000000007;
char s[100010];
long long h1[100010],h2[100010],p[100010];
int f[100010],g[100010];
long long get1(int l,int r)
{
	long long res=(h1[r+1]-h1[l]*p[r+1-l]%Mod+Mod)%Mod;
	//res=(res+Mod)%Mod;
	return res;
}
long long get2(int l,int r)
{
	long long res=(h2[l]-h2[r+1]*p[r+1-l]%Mod+Mod)%Mod;
	//res=(res+Mod)%Mod;
	return res;
}
int main()
{
	scanf("%s",&s);
	int len=strlen(s);
	h1[0]=0;
	for (int i=0;i<len;i++)
	{
		h1[i+1]=h1[i]*base+s[i];
		h1[i+1]%=Mod;
	}
	h2[len]=0;
	for (int i=len-1;i>=0;i--)
	{
		h2[i]=h2[i+1]*base+s[i];
		h2[i]%=Mod;
	}
	p[0]=1;
	for (int i=1;i<=len;i++)
	{
		p[i]=p[i-1]*base%Mod;
	}
	for (int i=0;i<=len;i++)
	{
		f[i]=1e9;
	}
	for (int i=0;i<len;i++)
	{
		int l=0,r=(len-i)/2,m;
		while (l<r)
		{
			m=(l+r+1)>>1;
			if (get1(i,i+m-1)==get2(len-m,len-1))
			{
				l=m;
			}
			else
			{
				r=m-1;
			}
		}
		f[l]=min(f[l],i-1);
	}
	g[len]=f[len];
	/*
	for (int i=0;i<=len;i++)
	{
		cout<<f[i]<<" ";
	}
	puts("");
	*/
	for (int i=len-1;i>=0;i--)
	{
		g[i]=min(g[i+1],f[i]);
		//cout<<g[i+1]<<" ";
	}
	//puts("");
	for (int i=1;i<=len;i++)
	{
		g[i]+=i;
	}
	/*
	for (int i=0;i<=len;i++)
	{
		cout<<g[i]<<" ";
	}
	puts("");
	for (int i=0;i<=len;i++)
	{
		g[i]=f[i];
	}
	for(int i=len;i;i--)
    {
      g[i-1]=min(g[i-1],g[i]);
      g[i]+=i;
    }
    for (int i=0;i<=len;i++)
    {
    	cout<<g[i]<<" ";
    }
    puts("");
    */
	int ans=0,x1,l1,x2,l2,x3,l3;
	for (int i=0;i<len;i++)
	{
		int l=0,r=min(i,len-i-1),m;
		while (l<r)
		{
			m=(l+r+1)>>1;
			if (get1(i-m,i)==get2(i,i+m))
			{
				l=m;
			}
			else
			{
				r=m-1;
			}
		}
		int L=l;
		l=0,r=len-(i+L)-1;
		while (l<r)
		{
			m=(l+r+1)>>1;
			if (g[m]<i-L)
			{
				l=m;
			}
			else
			{
				r=m-1;
			}
		}
		//cout<<l<<" "<<L<<" "<<L*2+1+2*l<<endl;
		if (L*2+1+2*l>ans)
		{
			ans=L*2+1+2*l;
			x1=g[l]-l+2;
			l1=l;
			x2=i-L+1;
			l2=L*2+1;
			x3=len-l+1;
			l3=l;
		}
	}
	if (l1)
	{
		puts("3");
		printf("%d %d\n%d %d\n%d %d\n",x1,l1,x2,l2,x3,l3);
	}
	else
	{
		puts("1");
		printf("%d %d\n",x2,l2);
	}
    return 0;
}
//夜过也，东窗未白凝残月。
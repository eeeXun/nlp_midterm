#include<cstdio>
#include<algorithm>
#include<cstring>
#include<utility>
using namespace std;
int pi[120000],ll;
char str[120000];
const long long mul1=131;
const long long mul2=31;
long long ant1,ant2;
const long long mod=1000000007;
inline long long sqr(long long x)
{
	return x*x%mod;
}
inline long long fastexp(long long x,long long y)
{
	if(y==0)return 1;
	if(y==1)return x;
	if(y%2==0)return sqr(fastexp(x,y/2));
	return sqr(fastexp(x,y/2))*x%mod;
}
int maxl;
struct hashtable
{
	pair<long long,long long>val[120000];
	pair<long long,long long>exp[120000];
	pair<long long,long long>anti[120000];
	int lef[120000];
	inline void init()
	{
		exp[0]=make_pair(1,1);
		val[0]=make_pair(0,0);
		anti[0]=make_pair(1,1);
		for (int i=1;i<=ll;i++)
		{
			exp[i]=make_pair(exp[i-1].first*mul1%mod,exp[i-1].second*mul2%mod);
			anti[i]=make_pair(fastexp(exp[i].first,mod-2),fastexp(exp[i].second,mod-2));
			val[i]=make_pair((val[i-1].first+exp[i].first*(str[i]-'a'+1))%mod,(val[i-1].second+exp[i].second*(str[i]-'a'+1))%mod);
		}
	}
	inline pair<long long,long long>getva(int le,int ri)
	{
		le--;
		return make_pair((val[ri].first-val[le].first+mod)*anti[le].first%mod,(val[ri].second-val[le].second+mod)*anti[le].second%mod);
	}
	inline void solve()
	{
		int j=1,k=0;maxl=ll+1;
		pair<long long,long long>tmp=make_pair(0,0);
		for (int i=ll;i>=1;i--)
		{
			k++;
			tmp=make_pair((tmp.first+(str[i]-'a'+1)*exp[k].first)%mod,(tmp.second+(str[i]-'a'+1)*exp[k].second)%mod);
			while (getva(j,j+(ll-i))!=tmp&&(j+ll-i)<i-1)j++;
			if(j+ll-i>=i-1)break;
			maxl=i;
			lef[i]=j;
		}
	}
}hash;
inline void manacher()
{
	int mx=0,id;
	for (int i=1;i<=ll;i++)
	{
		if(mx>i)
		{
			pi[i]=min(pi[id*2-i],mx-i);
		}
		else
		{
			pi[i]=1;
		}
		for (;str[i-pi[i]]==str[i+pi[i]];pi[i]++);
		if(i+pi[i]>mx)
		{
			mx=pi[i]+i;
			id=i;
		}
	}
//	for (int i=1;i<=ll;i++)printf("%d %d %d\n",i,pi[i],hash.lef[i]); 
}
struct answer
{
	int a[3][2],siz;
	inline int calc()
	{
		int ss=0;
		for (int i=0;i<siz;i++)
		{
			ss+=a[i][1];
		}return ss;
	}
	inline void print()
	{
		pair<int,int>p[3];
		for (int i=0;i<siz;i++)
		{
			p[i].first=a[i][0];
			p[i].second=a[i][1];
		}
		sort(p,p+siz);printf("%d\n",siz);
		for (int i=0;i<siz;i++)
		{
			printf("%d %d\n",p[i].first,p[i].second);
		}
	}
}pos[120000];
int ans;
inline bool check(int x,int po)
{
	if(hash.lef[x]==0)return false;
	int lb=po-pi[po],rb=po+pi[po];
	if(x<rb)return false;
	if(hash.lef[x]+(ll-x)>lb)return false;
	return true;
}
int main()
{
	scanf("%s",str+1);
	str[0]='$';
	ll=strlen(str+1);
	str[ll+1]='%';
	hash.init();
	hash.solve();
	manacher();
	for (int i=1;i<=ll;i++)
	{
		pos[i].a[0][1]=pi[i]*2-1;
		pos[i].a[0][0]=i-pi[i]+1;
		pos[i].siz=1;
		int le=i+pi[i],ri=ll,mi;
		if(le<maxl)le=maxl;
		if(le>ri)le=ri;
		while (le<ri)
		{
			mi=(le+ri)/2;
			if(!check(mi,i))
			{
				le=mi+1;
			}
			else
			{
				ri=mi;
			}
		}
		if(check(le,i))
		{
			pos[i].siz+=2;
			pos[i].a[1][0]=hash.lef[le];
			pos[i].a[1][1]=ll-le+1;
			pos[i].a[2][0]=le;
			pos[i].a[2][1]=ll-le+1;
		}
		if(pos[i].calc()>pos[ans].calc())ans=i;
	}
	pos[ans].print();
	return 0;
}
/*
abcdcba
*/

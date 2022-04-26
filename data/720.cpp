#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=100100;
char s[N],s1[N];
int l[N],nxt[N],f[N],n,ans;
void manacher()
{
	int i,j,k,p=0,mx=0;
	for(i=1;i<=n;i++)
	{
		if(mx>i)l[i]=min(l[2*p-i],mx-i);
		else l[i]=1;
		while(s[i+l[i]]==s[i-l[i]])l[i]++;
		if(i+l[i]>mx)mx=i+l[i],p=i;
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int i,j,k,p,len;
	scanf("%s",s1+1);n=strlen(s1+1);
	for(i=1;i<=n;i++)s[i]=s1[i];
	reverse(s+1,s+n+1);
	s[0]='+';s[n+1]='-';
	manacher();
	nxt[1]=0;j=0;
	for(i=2;i<=n;i++)
	{
		while((j)&&(s[i]!=s[j+1]))j=nxt[j];
		if(s[j+1]==s[i])j++;
		nxt[i]=j;
	}
	j=0;
	for(i=1;i<=n;i++)
	{
		while((j)&&(s1[i]!=s[j+1]))j=nxt[j];
		if(s[j+1]==s1[i])j++;
		f[n-i+1]=j;
		if(n-i+1==j)break;
	}
	for(i=1;i<=n;i++)f[i]=max(f[i-1]-1,f[i]);
	for(i=n-1;i;i--)f[i]=max(f[i],f[i+1]);
	ans=0;p=0;
	for(i=1;i<=n;i++)
	   if(2*l[i]-1+2*min(i-l[i],f[i+l[i]])>ans)
	   {
		   ans=2*l[i]-1+2*min(i-l[i],f[i+l[i]]);
		   p=i;
	   }
	if(ans==2*l[p]-1)printf("1\n%d %d\n",n-(p+l[p]-1)+1,ans);
	else
	{
		printf("3\n");len=(ans-2*l[p]+1)>>1;
		for(i=n;i;i--)
		   if(f[i]==len){printf("%d %d\n",n-(i+f[i]-1)+1,len);break;}
		printf("%d %d\n",n-(p+l[p]-1)+1,2*l[p]-1);
		printf("%d %d\n",n-len+1,len);
	}
	return 0;
}




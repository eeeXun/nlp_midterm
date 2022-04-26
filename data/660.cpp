#include <bits/stdc++.h>
#define x first
#define y second
#define Pair pair<int,int>
#define mp make_pair
using namespace std;

char s[200048];int len;
char ss[200048];int len2;
int fail[200048];
int maxlen[200048];
int RL[200048],tmp[100048];
int p[100048],f[100048];

/*
inline void getfail()
{
	int i,j,k;
	fail[0]=-1;j=1;k=0;
	while (j<=len2)
	{
		if (k==-1 || ss[j]==ss[k])
			fail[j++]=++k;
		else
			k=fail[k];
	}
	puts(ss+1);
	for (i=1;i<=len2;i++) cout<<fail[i]<<' ';
	cout<<endl;
}
*/

struct node
{
	int next[30];
	int pos,fail;
	inline void init()
	{
		memset(next,0,sizeof(next));
		pos=fail=0;
	}
}trie[200048];int tot=1;

inline void Insert()
{
	int i,w,cur=1;
	for (i=1;i<=len2;i++)
	{
		w=ss[i]-'a'+1;
		//if (i==71) cout<<w<<"*"<<endl;
		if (!trie[cur].next[w])
		{
			trie[cur].next[w]=++tot;
			trie[tot].init();
		}
		cur=trie[cur].next[w];
		trie[cur].pos=i;
	}
}

queue<int> q;
inline void construct_fail()
{
	int i,cur;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=27;i++)
			if (trie[cur].next[i])
			{
				int tmp=trie[cur].fail;
				while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
				trie[trie[cur].next[i]].fail=(tmp?trie[tmp].next[i]:1);
				q.push(trie[cur].next[i]);
			}
	}
}

inline void getRL()
{
	memset(ss,'\0',sizeof(ss));
	int i,slen=0;
	for (i=1;i<=len;i++)
	{
		ss[++slen]='#';
		ss[++slen]=s[i];
	}
	ss[++slen]='#';
	int maxright=0,pos=0;
	for (i=1;i<=slen;i++)
	{
		if (i<maxright) RL[i]=min(maxright-i,RL[2*pos-i]); else RL[i]=1;
		while (i+RL[i]<=slen && i-RL[i]>=1 && ss[i+RL[i]]==ss[i-RL[i]]) RL[i]++;
		if (i+RL[i]-1>maxright) maxright=i+RL[i]-1,pos=i;
	}
	for (i=1;i<=len;i++) tmp[i]=RL[i*2];
	for (i=1;i<=len;i++) RL[i]=tmp[i]-1;
}

int main ()
{
	int i;
	scanf("%s",s+1);len=strlen(s+1);
	for (i=1;i<=len;i++) ss[i]=s[len-i+1];
	len2=len;ss[++len2]='z'+1;
	for (i=len2+1;i<=len2+len;i++) ss[i]=s[i-len2];
	len2+=len;
	Insert();construct_fail();
	for (i=2;i<=tot;i++) fail[trie[i].pos]=trie[trie[i].fail].pos;
	for (i=len+2;i<=len2;i++) maxlen[i-len-1-fail[i]+1]=max(maxlen[i-len-1-fail[i]+1],fail[i]);
	getRL();
	memset(p,0,sizeof(p));
	for (i=1;i<=len;i++)
	{
		int cp=maxlen[i];
		while (cp && !p[cp]) p[cp--]=i;
	}
	memset(f,0,sizeof(f));
	for (i=len;i;i--)
	{
		if (!p[i]) continue;
		int cp=p[i]+i;
		while (cp<=len && !f[cp]) f[cp++]=i;
	}
	Pair ans1=mp(-1,-1),ans2=mp(-1,-1),ans3=mp(-1,-1);int anslen=0,curans;
	for (i=1;i<=len;i++)
	{
		curans=RL[i];
		if (curans>anslen)
		{
			anslen=curans;
			ans1=ans3=mp(-1,-1);ans2=mp(i-RL[i]/2,RL[i]);
		}
		int left=i-RL[i]/2,right=i+RL[i]/2;
		int add=min(f[left],len-right);
		if (add && curans+add*2>anslen)
		{
			anslen=curans+add*2;
			ans1=mp(p[add],add);ans2=mp(i-RL[i]/2,RL[i]);ans3=mp(len-add+1,add);
		}
	}
	if (ans1.x==-1)
	{
		printf("1\n");
		printf("%d %d\n",ans2.x,ans2.y);
	}
	else
	{
		printf("3\n");
		printf("%d %d\n%d %d\n%d %d\n",ans1.x,ans1.y,ans2.x,ans2.y,ans3.x,ans3.y);
	}
	return 0;
}

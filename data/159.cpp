#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 101000;
static char S[maxn],S1[maxn];
static int P[maxn],P1[maxn],P2[maxn],lc[maxn];
static int ans,x1,l1,x2,l2,x3,l3,Pl[maxn];

int main(){
	//freopen("30E.in","r",stdin);
	//freopen("30E.out","w",stdout);
	gets(S+1);
	int len=strlen(S+1);
	int mxl=0,idx=0;
	for (int i=1;i<=len;i++){
		S1[i]=S[len-i+1];
		if (mxl>=i) P[i]=min(mxl-i,P[idx-i+idx]);
		while (P[i]<=i&&i+P[i]<=len&&S[i+P[i]]==S[i-P[i]]) P[i]++;
		P[i]--;
		if (mxl<P[i]+i){
			mxl=P[i]+i;
			idx=i;
		}
	}
	for (int i=2;i<=len;i++){
		P1[i]=P1[i-1];
		while (P1[i]&&S1[P1[i]+1]!=S1[i]) P1[i]=P1[P1[i]];
		if (S1[P1[i]+1]==S1[i]) P1[i]++;
	}
	for (int i=1;i<=len;i++){
		P2[i]=P2[i-1];
		while (P2[i]&&S1[P2[i]+1]!=S[i]) P2[i]=P1[P2[i]];
		if (S1[P2[i]+1]==S[i]) P2[i]++;
	}
	for (int i=len;i;i--) lc[P2[i]]=i;
	int rx=0;
	for (int i=1;i<=len;i++) if (lc[i]) rx=i;
	int dt=0;
	for (int i=1;i<=len;i++){
		int R=min(rx+1,min(len-i-P[i]+1,i-P[i])),L=0;
		while (L+1<R){
			int mid=L+R>>1;
			if (lc[mid]<i-P[i]) L=mid;
			else R=mid;
		}
		if (L*2+P[i]*2+1>ans){
			ans=L*2+P[i]*2+1;
			x1=lc[L]-L+1;l1=L;
			x2=i-P[i];l2=2*P[i]+1;
			x3=len-L+1;l3=L;
		}
		
	}
	if (l1!=0)
		printf("3\n%d %d\n%d %d\n%d %d\n",x1,l1,x2,l2,x3,l3);
	else printf("1\n%d %d\n",x2,l2);
	return 0;
}

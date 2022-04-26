#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int maxn=100010;
const int base=13331;
int n,m,p;
int ans;
int A,B,len,D,E;
char s[maxn];
int lp[maxn],r[maxn];
int mx[maxn<<2];
LL h1[maxn],h2[maxn];
LL xp[maxn];

LL Get_pre(int L,int R){
	return h2[L]-h2[R+1]*xp[R-L+1];
}
LL Get_suf(int L,int R){
	return h1[R]-h1[L-1]*xp[R-L+1];
}
void build(int o,int L,int R){
	if(L==R){mx[o]=r[L];return;}
	int mid=(L+R)>>1;
	build(o<<1,L,mid);
	build(o<<1|1,mid+1,R);
	mx[o]=max(mx[o<<1],mx[o<<1|1]);
}
int Get_max(int o,int L,int R,int x,int y){
	if(L>=x&&R<=y)return mx[o];
	int mid=(L+R)>>1;
	if(y<=mid)return Get_max(o<<1,L,mid,x,y);
	else if(x>mid)return Get_max(o<<1|1,mid+1,R,x,y);
	else return max(Get_max(o<<1,L,mid,x,y),Get_max(o<<1|1,mid+1,R,x,y));
}
void print(){
	int cnt=0;
	if(A<=B)cnt++;
	if(len>0)cnt++;
	if(D<=E)cnt++;
	printf("%d\n",cnt);
	if(A<=B)printf("%d %d\n",A,B-A+1);
	for(int i=B+len;i<=D-len;++i){
		if(r[i]==len){printf("%d %d\n",i-r[i]+1,2*r[i]-1);break;}
	}
	if(D<=E)printf("%d %d\n",D,E-D+1);
}

int main(){
	scanf("%s",s+1);
	xp[0]=1;n=strlen(s+1);
	for(int i=1;i<=n;++i)xp[i]=xp[i-1]*base;
	h1[0]=0;h2[n+1]=0;
	for(int i=1;i<=n;++i)h1[i]=h1[i-1]*base+s[i]-'a';
	for(int i=n;i>=1;--i)h2[i]=h2[i+1]*base+s[i]-'a';
	lp[0]=1;
	for(int i=1;i<=n;++i){
		lp[i]=lp[i-1];
		while(lp[i]+i-1<=n&&Get_pre(lp[i],lp[i]+i-1)!=Get_suf(n-i+1,n))lp[i]++;
	}
	m=p=0;s[0]='$';
	for(int i=1;i<=n;++i){
		r[i]=(m>i?min(r[2*p-i],m-i):1);
		while(s[i-r[i]]==s[i+r[i]])r[i]++;
		if(i+r[i]>m)m=i+r[i],p=i;
	}
	build(1,1,n);
	for(int i=0;i<=n;++i){
		int st=lp[i]+i,ed=n-i;
		if(st>ed)continue;
		int L=0,R=(ed-st+2)>>1;
		while(L<R){
			int mid=L+((R-L+1)>>1);
			if(Get_max(1,1,n,st+mid-1,ed-mid+1)>=mid)L=mid;
			else R=mid-1;
		}
		if(2*i+2*L-1>ans){
			ans=2*i+2*L-1;
			A=lp[i];B=st-1;
			len=L;
			D=ed+1;E=n;
		}
	}
	print();
	return 0;
}

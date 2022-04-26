#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<vector>
typedef long long int LL;
typedef unsigned long long ULL;
const int INF=0x3f3f3f3f;
const LL INFLL=0x3f3f3f3f3f3f3f3fll;
LL getint(){
	LL ret=0;bool f=0;char c;
	while((c=getchar())<'0'||c>'9')if(c=='-')f^=1;
	while(c>='0'&&c<='9'){ret=ret*10+c-'0';c=getchar();}
	return f?-ret:ret;
}
using namespace std;
const int MAXN=200000;
char s[MAXN+10],ss[MAXN+10];
int nxt[MAXN+10],pos[MAXN+10],f[MAXN+10];
void KMP(char s[],int nxt[],int n){
    nxt[1]=nxt[2]=1;
    for(int i=2,j=1;i<=n;++i){
        while(j>1&&s[i]!=s[j])j=nxt[j];
        if(s[i]==s[j])++j;
        nxt[i+1]=j;
    }
}
void manacher(char s[],int f[],int n){
    int mx=0;
    s[n+1]='#';
    for(int i=1;i<=n;++i){
        if(f[mx]+mx>i)
            f[i]=min(f[2*mx-i],f[mx]+mx-i);
        else f[i]=1;
        while(s[i+f[i]]==s[i-f[i]])++f[i];
        if(i+f[i]>mx+f[mx])mx=i;
    }
}
int main(){
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=1;2*i<n+1;++i)
        swap(s[i],s[n-i+1]);
    for(int i=1;i<=n;++i)
        ss[i]=ss[2*n+2-i]=s[i];
    ss[n+1]='*';
    KMP(ss,nxt,2*n+1);
    for(int i=n+2;i<=2*n+1;++i)
        nxt[2*n+2-i]=nxt[i+1]-1;
    nxt[n+1]=0;pos[n]=n;
    for(int i=n-1;i>=1;--i){
        if(nxt[i]>=nxt[i+1])
            pos[i]=i;
        else{
            nxt[i]=nxt[i+1];
            pos[i]=pos[i+1];
        }
    }
    manacher(s,f,n);
    int t=0,id=0;
    for(int i=1;i<=n;++i){
        int ret=2*f[i]-1+2*min(nxt[i+f[i]],i-f[i]);
        if(t<ret)t=ret,id=i;
    }
    int mid=2*f[id]-1;
    int l=min(nxt[id+f[id]],id-f[id]);
    if(l==0){
        printf("1\n");
        printf("%d %d\n",n-(id+f[id]-1)+1,mid);
    }
    else{
        printf("3\n");
        if(nxt[id+f[id]]<=id-f[id])
            printf("%d %d\n",n-(pos[id+f[id]]+l-1)+1,l);
        else
            printf("%d %d\n",n-(pos[id+f[id]]+nxt[id+f[id]]-1)+1,l);
        printf("%d %d\n",n-(id+f[id]-1)+1,mid);
        printf("%d %d\n",n-l+1,l);
    }
}
/*
drnpbmlomzpbrrhcucrencklabjeqtpptkbgtondlrdkgxzbrifkyusafalfkjpaccofagxobsrfoppvuzfqpmgzuwvupmumpqfzu
*/

  	  			 	  	     	    	  		 	
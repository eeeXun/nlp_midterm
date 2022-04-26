//Hello. I'm Peter.
#include<cstdio>
#include<iostream>
#include<sstream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<functional>
#include<cctype>
#include<ctime>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uin;
#define peter cout<<"i am peter"<<endl
#define input freopen("data.txt","r",stdin)
#define randin srand((unsigned int)time(NULL))
#define INT (0x3f3f3f3f)*2
#define LL (0x3f3f3f3f3f3f3f3f)*2
#define gsize(a) (int)a.size()
#define len(a) (int)strlen(a)
#define slen(s) (int)s.length()
#define pb(a) push_back(a)
#define clr(a) memset(a,0,sizeof(a))
#define clr_minus1(a) memset(a,-1,sizeof(a))
#define clr_INT(a) memset(a,INT,sizeof(a))
#define clr_true(a) memset(a,true,sizeof(a))
#define clr_false(a) memset(a,false,sizeof(a))
#define clr_queue(q) while(!q.empty()) q.pop()
#define clr_stack(s) while(!s.empty()) s.pop()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define dep(i, a, b) for (int i = a; i > b; i--)
#define repin(i, a, b) for (int i = a; i <= b; i++)
#define depin(i, a, b) for (int i = a; i >= b; i--)
#define pi 3.1415926535898
#define eps 1e-9
#define MOD 1000000007
#define MAXN 200100
#define N
#define M
char s[MAXN>>1],st[MAXN];
int lens,l[MAXN];
void manacher(char *s,int lens){
    int lenst=0;
    st[lenst++]='#';
    rep(i,0,lens){
        st[lenst++]=s[i];
        st[lenst++]='#';
    }
    st[lenst]='\0';
    int maxto=0,lastpos=0;
    rep(i,0,lenst){
        l[i]=i<maxto?min(l[2*lastpos-i],maxto-i):1;
        while(i-l[i]>=0 && i+l[i]<lenst && st[i-l[i]]==st[i+l[i]]) l[i]++;
        if(i+l[i]>maxto){
            maxto=i+l[i];
            lastpos=i;
        }
        //remember l[i]-1 is answer
    }
    rep(i,0,lens){
        l[i]=l[i<<1|1]-1;
    }
}
int fail[MAXN],p[MAXN];
void kmp(char *s,int lens){
    int lenst=0;
    depin(i,lens-1,0){
        st[lenst++]=s[i];
    }
    st[lenst++]='#';
    rep(i,0,lens){
        st[lenst++]=s[i];
    }
    st[lenst]='\0';
    int i=0,j;
    fail[0]=j=-1;
    while(i<lenst){
        if(j==-1 || st[i]==st[j]){
            fail[i+1]=j+1;
            i++;
            j=j+1;
        }
        else j=fail[j];
    }
    rep(i,0,lens){
        fail[i]=fail[i+1+lens+1];
    }
    int maxi=-1,lastp=0;
    rep(i,0,lens){
        if(fail[i]>maxi){
            maxi=fail[i];
            p[i]=i;
            lastp=i;
        }
        else p[i]=p[i-1];
    }
}
int ansp1,ansp2,ansp3;
int ansl1,ansl2,ansl3;
int maxilen,lent;
int main(){
    scanf("%s",s);
    lens=len(s);
    manacher(s,lens);
    kmp(s,lens);
    maxilen=-1;
    int l1=0,p1=0,maxil=0;
    rep(i,0,lens){
        l1=l[i]>>1;
        if(i-l1-1<0){
            lent=l[i];
            maxil=0;
        }
        else{
            p1=p[i-l1-1];
            maxil=min(fail[p1],lens-(i+l1)-1);
            lent=l[i]+(maxil<<1);
        }
        if(lent<=maxilen) continue;
        maxilen=lent;
        if(maxil==0){
            ansp2=i-l1;
            ansl2=l[i];
            ansp1=ansp3=-1;
        }
        else{
            p1=p1-fail[p1]+1;
            ansp1=p1;
            ansl1=maxil;
            ansp2=i-l1;
            ansl2=l[i];
            ansp3=lens-maxil;
            ansl3=ansl1;
        }
    }
    if(ansp1==-1){
        printf("%d\n",1);
        printf("%d %d\n",ansp2+1,ansl2);
    }
    else{
        printf("%d\n",3);
        printf("%d %d\n",ansp1+1,ansl1);
        printf("%d %d\n",ansp2+1,ansl2);
        printf("%d %d\n",ansp3+1,ansl3);
    }
}




 		  		  		  	 	 	 					  	  		
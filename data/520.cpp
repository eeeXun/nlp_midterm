#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100005
unsigned long long hl[N],hr[N],pow[N];
int f[N],que[N],g[N],m[N];
char c[N];
int sl;
unsigned long long hh(int s,int e){
    if(s<=e) return hl[e]-hl[s]*pow[e-s];
    else return hr[e]-hr[s]*pow[s-e];//****** e<s + right to left , e is larger
}
int calc(int x){
    int s=x-f[x]+1,e=x+f[x]-1;
    //middle palindrome
    return f[x]*2-1+min(g[m[s-1]],sl-e)*2;//************ one side dp,one side fix length
}
int main(){
    while(~scanf("%s",c+1)){
        sl=strlen(c+1);
        hl[0]=hr[sl+1]=0;
        pow[0]=1;
        for(int i=1;i<=sl;++i)pow[i]=pow[i-1]*29;
        for(int i=1;i<=sl;++i)hl[i]=hl[i-1]*29+c[i];
        for(int i=sl;i>=1;--i)hr[i]=hr[i+1]*29+c[i];
        for(int i=1;i<=sl;++i){
            int l=1,r=min(i,sl-i+1);
            while(l<r){
                //printf("l:%d r:%d\n",l,r);
                int md=(l+r+1)>>1;
                if(hh(i,i+md-1) == hh(i,i-md+1))l=md;
                else r=md-1;
            }
            f[i]=l;
        }
//        printf("%s\n",c+1);
//        for(int i=1;i<=sl;++i)printf("i:%d f:%d\n",i,f[i]); 
        int qh,qt;
        qh=qt=0;
        for(int i=1;i<=sl;++i){
            if(c[i]==c[sl])que[qt++]=i;//i is end of suffix()
            //something like ddq
            //#&%$%^zyx .... xyz
            while(qh<qt && hh(que[qh],i)!=hh(sl,sl-(i-que[qh])) && sl-(i-que[qh])>i)++qh;
            if(qh>=qt)g[i]=0;
            else g[i]=i-que[qh]+1;
        }
        m[0]=0;
        for(int i=1;i<=sl;++i){
            m[i]=m[i-1];
            if(g[m[i]]<g[i])m[i]=i;
        }
        int ans=0;
        for(int i=1;i<=sl;++i)ans=max(ans,calc(i));
        bool find=0;
        for(int i=1;i<=sl;++i){
            if(calc(i)==ans && !find){
                find=1;
                int s,e,j=0,k;
                s=i-f[i]+1;
                e=i+f[i]-1;
                j=min(g[m[s-1]],sl-e);
                k=m[s-1]-g[m[s-1]]+1;
                if(j) {
                    puts("3");
                    printf("%d %d\n",k,j);
                    printf("%d %d\n",s,e-s+1);
                    printf("%d %d\n",sl-j+1,j);
                }else{
                    printf("1\n");
                    printf("%d %d\n",s,e-s+1);
                }
            }
        }
    }
    return 0;
}

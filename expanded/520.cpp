# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/520.cpp" 2

# 5 "data/520.cpp"
using namespace std;

unsigned long long hl[100005],hr[100005],pow[100005];
int f[100005],que[100005],g[100005],m[100005];
char c[100005];
int sl;
unsigned long long hh(int s,int e){
    if(s<=e) return hl[e]-hl[s]*pow[e-s];
    else return hr[e]-hr[s]*pow[s-e];
}
int calc(int x){
    int s=x-f[x]+1,e=x+f[x]-1;

    return f[x]*2-1+min(g[m[s-1]],sl-e)*2;
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

                int md=(l+r+1)>>1;
                if(hh(i,i+md-1) == hh(i,i-md+1))l=md;
                else r=md-1;
            }
            f[i]=l;
        }


        int qh,qt;
        qh=qt=0;
        for(int i=1;i<=sl;++i){
            if(c[i]==c[sl])que[qt++]=i;


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


}
# 6 "data/546.cpp" 2
# 1 "/usr/include/c++/11.2.0/cstdlib" 1 3
# 39 "/usr/include/c++/11.2.0/cstdlib" 3
       
# 40 "/usr/include/c++/11.2.0/cstdlib" 3
# 7 "data/546.cpp" 2

# 7 "data/546.cpp"
using namespace std;

typedef long long int LL;
const int MAXN = 1e5;
const int MAXLOG = 17;
const int INF = 0x3f3f3f3f;

char A[MAXN+10],B[MAXN+10];
int n,maxlog;
int pos[MAXN+10];

int nxt[MAXN+10];
void getnxt(char *str){
    int len=strlen(str+1);
    nxt[0]=-1,nxt[1]=0;
    for(int i=2,j;i<=len;++i){
        j=nxt[i-1];
        while(j&&str[j+1]!=str[i])
            j=nxt[j];
        if(str[j+1]!=str[i])nxt[i]=0;
        else nxt[i]=j+1;
    }
}
int kmp(char *scr,char *tar){
    memset(pos,0x3f,sizeof(pos));
    getnxt(tar);
    int lens=strlen(scr+1);
    int lent=strlen(tar+1);
    int ret=0;

    for(int i=1,j=1;i<=lens;){
        if(j>lent)break;
        while(j&&scr[i]!=tar[j])j=nxt[j-1]+1;
        pos[lent-j+1]=min(pos[lent-j+1],i);
        ++i,++j;
    }
    return ret;
}

char tmp[MAXN+10];
int p[MAXN+10];
void manachar(char *str){
    int len=strlen(str+1);
    for(int i=1;i<=len;++i)
        tmp[i]=str[i];
    tmp[++len]='#';

    int maxp=0;
    for(int i=1;i<=len;++i){
        if(i<maxp+p[maxp])p[i]=min(maxp+p[maxp]-i,p[2*maxp-i]);
        else p[i]=0;
        for(;tmp[i-p[i]]==tmp[i+p[i]];++p[i]);
        if(maxp+p[maxp]<i+p[i])maxp=i;
    }
}

int dp[MAXN+10][MAXLOG+5];
int lenth[MAXN+10];
void init(){
    for(int i=2;i<=n;i<<=1)lenth[i]=1;
    for(int i=1;i<=n;++i)lenth[i]+=lenth[i-1];
    for(int i=1;i<=n;++i)dp[i][0]=i;
    for(int len=1;len<=maxlog;++len)
        for(int i=1;i<=n;++i){
            dp[i][len]=dp[i][len-1];
            if(i>=(1<<len)){
                if(p[dp[i][len]]<p[dp[i-(1<<(len-1))][len-1]])
                    dp[i][len]=dp[i-(1<<(len-1))][len-1];
            }
        }
}

int query(int l,int r){
    int t1=dp[r][lenth[r-l+1]];
    int t2=dp[l+(1<<lenth[r-l+1])-1][lenth[r-l+1]];
    return p[t1]<p[t2]?t2:t1;
}

int getmaxlen(int ll,int rr){
    int l=1,r=(rr-ll)/2+1,mid,ret=0,t;
    while(l<=r){
        mid=(l+r)>>1;
        t=query(ll+mid-1,rr-mid+1);
        if(p[t]>=mid)
            ret=t,l=mid+1;
        else r=mid-1;
    }
    return ret;
}

int main(){
    scanf("%s",A+1);
    n=strlen(A+1),maxlog=log(n)/log(2);
    for(int i=1;i<=n;++i)B[n-i+1]=A[i];

    kmp(A,B);
    manachar(A);
    init();

    int maxp=getmaxlen(1,n),maxlen=p[maxp]*2-1;
    int pre=0,suf=0;
    int ans=p[maxp]*2-1;
    for(int i=n;i>=1&&pos[i]<i-1;--i){
        int t=getmaxlen(pos[i]+1,i-1);
        if(min(p[t],min(t-pos[i],i-t))*2-1+(n-i+1)*2>ans){
            maxlen=min(p[t],min(t-pos[i],i-t))*2-1;
            ans=maxlen+(n-i+1)*2;
            maxp=t,pre=pos[i]-(n-i+1)+1,suf=i;
        }
    }

    if(pre){
        puts("3");
        printf("%d %d\n",pre,n-suf+1);
        printf("%d %d\n",maxp-p[maxp]+1,maxlen);
        printf("%d %d\n",suf,n-suf+1);
    }
    else{
        puts("1");
        printf("%d %d\n",maxp-p[maxp]+1,maxlen);
    }
}

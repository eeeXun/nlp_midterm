}
# 6 "data/596.cpp" 2


# 7 "data/596.cpp"
using namespace std;

const int NR=2e5+5;

int n,m;
char s[NR],t[NR];
int d[NR],nxt[NR],maxx[NR],pos[NR];
int pl,pr,ml,mr,sl,sr,cnt=3;

int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    int p=0,maxr=0;
    for(int i=1;i<=n;i++){
        if(i<=maxr) d[i]=min(d[p+maxr-i],maxr-i+1);
        while(i-d[i]>=1&&i+d[i]<=n&&s[i-d[i]]==s[i+d[i]]) d[i]++;
        if(i+d[i]-1>maxr){
            p=i-d[i]+1;
            maxr=i+d[i]-1;
        }
    }
    for(int i=n;i>=1;i--) t[++m]=s[i];
    t[++m]='#';
    for(int i=1;i<=n;i++) t[++m]=s[i];
    for(int i=2,j=0;i<=m;i++){
        while(j>0&&t[i]!=t[j+1]) j=nxt[j];
        if(t[i]==t[j+1]) j++;
        nxt[i]=j;
    }
    for(int i=1;i<=n;i++){
        int j=i+n+1;
        if(nxt[j]>=maxx[i-1]) pos[i]=i;
        else pos[i]=pos[i-1];
        maxx[i]=max(maxx[i-1],nxt[j]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(min(maxx[i-d[i]],n-i-d[i]+1)*2+d[i]*2-1>ans){
            ans=min(maxx[i-d[i]],n-i-d[i]+1)*2+d[i]*2-1;
            pr=pos[i-d[i]]; pl=pr-min(maxx[i-d[i]],n-i-d[i]+1)+1;
            ml=i-d[i]+1,mr=i+d[i]-1;
            sl=n-min(maxx[i-d[i]],n-i-d[i]+1)+1; sr=n;
        }
    }
    if(pl>pr) cnt--;
    if(sl>sr) cnt--;
    printf("%d\n",cnt);
    if(pl<=pr) printf("%d %d\n",pl,pr-pl+1);
    printf("%d %d\n",ml,mr-ml+1);
    if(sl<=sr) printf("%d %d\n",sl,sr-sl+1);
    return 0;
}

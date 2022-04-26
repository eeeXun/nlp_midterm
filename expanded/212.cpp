
# 4 "data/212.cpp"
using namespace std;

int n,next[100005],a[100005],ai[100005],dp[100005],ri,rii,out,q[10];
char s[100005],S[100005];

int ext(int x, int y) {
    int i=x,j=y;
    while ((i>0)&&(j<=n)&&(s[i]==s[j])) {
        i--;
        j++;
    }
    return (j-i-1)>>1;
}

int main() {
    s[0]='@';
    scanf("%s",s+1);
    n=strlen(s+1);
    for (int i=1; i<=n; i++)
        S[i]=s[n-i+1];
    next[0]=-1;
    for (int i=1,j=-1; i<=n; )
        if ((j==-1)||(S[i]==S[j+1])) next[i++]=++j;
        else j=next[j];
    a[0]=0;
    ai[0]=0;
    for (int i=1,j=0; i<=n; ) {
        if ((j==-1)||(s[i]==S[j+1])) {
            a[i]=j+1;
            ai[i]=i;
            if (a[i-1]>a[i]) {
                a[i]=a[i-1];
                ai[i]=ai[i-1];
            }
            i++;
            j++;
        }
        else j=next[j];
    }

    dp[1]=0;
    ri=rii=1;
    out=1;
    q[0]=1;
    q[1]=1;
    q[2]=q[3]=q[4]=q[5]=0;
    for (int i=2; i<=n; i++) {
        if (i<=ri) {
            dp[i]=dp[(rii<<1)-i];
            if (i+dp[i]==ri) dp[i]=ext(i-dp[i]-1,i+dp[i]+1);
            else if (i+dp[i]>ri) dp[i]=ri-i;
        }
        else dp[i]=ext(i-1,i+1);
        if (i+dp[i]>ri) {
            ri=i+dp[i];
            rii=i;
        }
        int l=min(a[i-dp[i]-1],n-(i+dp[i]));
        int temp=l+dp[i]+1+dp[i]+l;
        if (temp>out) {
            out=temp;
            if (l) {
                q[0]=ai[i-dp[i]-1]-a[i-dp[i]-1]+1;
                q[1]=l;
                q[2]=i-dp[i];
                q[3]=dp[i]+1+dp[i];
                q[4]=n-l+1;
                q[5]=l;
            }
            else {
                q[0]=i-dp[i];
                q[1]=dp[i]+1+dp[i];
                q[2]=q[3]=q[4]=q[5]=0;
            }
        }
    }
    if (q[5]) {
        printf("%d\n",3);
        printf("%d %d\n",q[0],q[1]);
        printf("%d %d\n",q[2],q[3]);
        printf("%d %d\n",q[4],q[5]);
    }
    else {
        printf("%d\n",1);
        printf("%d %d\n",q[0],q[1]);
    }

    return 0;
}

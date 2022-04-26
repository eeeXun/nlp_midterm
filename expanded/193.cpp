}
# 5 "data/193.cpp" 2

# 5 "data/193.cpp"
using namespace std;
const int mn=200010;
int len,n,mx,id,A,B,C,D,E,F;
char s[mn],rs[mn];
int next[mn],eq[mn],lc[mn],p[mn];
void up(int a,int b,int c,int d,int e,int f){
    if(b+d+f>len){
        len=b+d+f;
        A=a,B=b,C=c,D=d,E=e,F=f;
    }
}
int main(){


    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)rs[i]=s[n+1-i];
    mx=1,id=1;
    for(int i=1;i<=n;i++){
        if(mx<i)mx=i;
        p[i]=min(p[id*2-i],mx-i);
        while(i-p[i]-1>0&&s[i+p[i]+1]==s[i-p[i]-1])p[i]++;
        if(p[i]+i>mx){
            mx=p[i]+i;
            id=i;
        }
    }
    next[1]=0;
    for(int i=2;i<=n;i++){
        int j=next[i-1];
        while(rs[j+1]!=rs[i]&&j)j=next[j];
        next[i]=rs[j+1]==rs[i]?j+1:0;
    }
    mx=0;
    for(int i=1;i<=n;i++){
        eq[i]=eq[i-1];
        while(rs[eq[i]+1]!=s[i]&&eq[i])eq[i]=next[eq[i]];
        eq[i]=s[i]==rs[eq[i]+1]?eq[i]+1:0;
        mx=max(eq[i],mx);
    }
    for(int i=n;i>=1;i--)lc[eq[i]]=i;
    for(int i=1;i<=n;i++){
        int l=0,r=min(mx,min(i-p[i]-1,n-i-p[i]));
        while(l+1<r){
            int mid=l+r>>1;
            if(lc[mid]<i-p[i])l=mid;
            else r=mid-1;
        }
        if(lc[r]<i-p[i])up(lc[r]-r+1,r,i-p[i],p[i]*2+1,n-r+1,r);
        else up(lc[l]-l+1,l,i-p[i],p[i]*2+1,n-l+1,l);
    }
    if(!B)printf("1\n%d %d\n",C,D);
    else printf("3\n%d %d\n%d %d\n%d %d\n",A,B,C,D,E,F);
    return 0;
}

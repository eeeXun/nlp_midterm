}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 6 "data/841.cpp" 2

# 6 "data/841.cpp"
using namespace std;

const int N=100100;
char s[N],t[N];
int p[N];
void Manacher(int len){
    for(int i=1,mx=0,id;i<=len;i++){
        if(mx>i)p[i]=min(p[2*id-i],mx-i);
        else p[i]=1;
        for(;s[i+p[i]]==s[i-p[i]];p[i]++);
        if(p[i]+i>mx){
            mx=p[i]+i;
            id=i;
        }
    }
}

int f[N],a[N],mx;
pair<int,int> b[N];
void getfail(char s[]){
    f[0]=f[1]=0;
    int len=strlen(s);
    for(int i=1,j=0;i<len;i++){
        j=f[i];
        while(j&&s[i]!=s[j])j=f[j];
        f[i+1]=(s[i]==s[j]?j+1:0);
    }
}

void kmp(char s[]){
    memset(a,63,sizeof(a));
    int len=strlen(s);
    for(int i=0;i<len;i++){
        b[i]=make_pair(0,len);
    }
    for(int i=0,j=0;i<len;i++){
        while(j&&s[i]!=t[j])j=f[j];
        if(s[i]==t[j])j++;
        mx=max(mx,j);
        a[len-j]=min(i,a[len-j]);
        b[i]=make_pair(j,i);
    }
    for(int i=1;i<len;i++){
        b[i]=max(b[i],b[i-1]);
    }
}

int main(){
    s[0]='@';
    scanf("%s",s+1);
    int len=strlen(s+1);
    for(int i=1;i<=len;i++){
        t[i-1]=s[i];
    }
    reverse(t,t+len);
    Manacher(len);
    getfail(t);
    kmp(s+1);

    int ans=1;
    int idx=1,l[3],r[3];
    l[0]=r[0]=1;
    for(int i=1;i<=len;i++){
        if(2*p[i]-1>ans){
            ans=2*p[i]-1;;
            idx=1;
            l[0]=i-p[i]+1;
            r[0]=2*p[i]-1;
        }
        int x=i-p[i]+1,y=i+p[i]-1;
        x--;
        y--;
        int tmp=2*p[i]-1;
        if(x-1>=0&&y+1<len){
            int ll=min(b[x-1].first,min(mx,len-y-1));
            if(0==ll)continue;
            if(tmp+2*ll>ans){
                idx=3;
                ans=tmp+2*ll;
                l[0]=b[x-1].second-ll+2,r[0]=ll;
                l[1]=i-p[i]+1,r[1]=2*p[i]-1;
                l[2]=len-ll+1,r[2]=ll;
            }
        }
    }
    if(1==idx)printf("%d\n%d %d\n",idx,l[0],r[0]);
    else{
        printf("%d\n%d %d\n%d %d\n%d %d\n",idx,l[0],r[0],l[1],r[1],l[2],r[2]);
    }

    return 0;
}

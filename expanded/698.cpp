namespace std __attribute__ ((__visibility__ ("default")))
{

  namespace pmr
  {
    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 16 "data/698.cpp" 2

# 16 "data/698.cpp"
using namespace std;





const long long mod =1000000009;
char z[100005];
char x[100005];
int F[100005];
int now=0;
int q[100005];
void getfail(char *P,int *F)
{
    int m=strlen(P);
    F[0]=0;F[1]=0;
    for (int i=1;i<m;i++){
        int j=F[i];
        while (j && P[i]!=P[j]) j=F[j];
        F[i+1]=P[i]==P[j]?j+1:0;
    }
}

void KMP(char *T,char *P,int *F)
{
    int n=strlen(T),m=strlen(P);
    getfail(P,F);
    int j=0;
    q[0]=-1;
    for (int i=0;i<n;i++){
        while (j && P[j]!=T[i]) j=F[j];
        if (P[j]==T[i]) j++;
        if (j>now){
            q[j]=i;
            now=j;
        }
        if (j==m) {
            j=F[j];
        }
    }
    for (++now;now<n;now++) q[now]=n-1;
}
char str[100005*2+2];
int p[100005*2+2];
int pre(char *s) {
    int i,j,k;
    int n = strlen(s);
    str[0] = '$';
    str[1] = '#';
    for (i=0;i<n;i++) {
        str[i*2 + 2] = s[i];
        str[i*2 + 3] = '#';
    }
    n = n*2 + 2;
    str[n] = 0;
    return n;
}
void kp(char *s) {
    int n=pre(s);
    int i;
    int mx = 0;
    int id;
    for(i=1; i<n; i++) {
        if( mx > i )
            p[i] = min( p[2*id-i], p[id]+id-i );
        else
            p[i] = 1;
        for(; str[i+p[i]] == str[i-p[i]]; p[i]++)
            ;
        if( p[i] + i > mx ) {
            mx = p[i] + i;
            id = i;
        }
    }
    n=strlen(s);
}
int cao[3][2];
int erfen(int maxn,int g,int h)
{
    maxn=min(maxn,h);
    int l=0,r=maxn;
    while (l<r){
        int mid=(l+r)/2+1;
        if (q[mid]<=g) l=mid;
        else r=mid-1;
    }
    return l;
}
int main()
{
    scanf("%s",&z);
    strcpy(x,z);
    int n=strlen(z);
    reverse(x,x+n);
    KMP(z,x,F);
    kp(z);
    bool b=true;
    int m=n*2+2;
    int ans=0;

    for (int j=2;j<m;j++){
        if (j==75){
            int fff=0;
        }
        int l=j-p[j];
        int r=j+p[j];
        l=(l-2)/2;
        r=(r-2)/2;
        int g;
        if (ans<((g=erfen(n-r,l,n/2))*2+p[j]-1) && (g*2+p[j]-1)%2==1){
            cao[0][0]=q[g]-g+1;
            cao[0][1]=g;
            cao[2][1]=g;
            cao[2][0]=n-g;
            cao[1][0]=l+1;
            cao[1][1]=p[j]-1;
            ans=g*2+p[j]-1;
        }
    }
    if (cao[0][1]==0){
        printf("1\n");
        printf("%d %d\n",cao[1][0]+1,cao[1][1]);
    }else {
        printf("3\n");
        for (int j=0;j<3;j++){
            printf("%d %d\n",cao[j][0]+1,cao[j][1]);
        }
    }
    return 0;
}

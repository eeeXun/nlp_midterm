#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define ZERO (1e-10)
#define INF int(1e9+1)
#define CL(A,I) (memset(A,I,sizeof(A)))
#define DEB printf("DEB!\n");
#define D(X) cout<<"  "<<#X": "<<X<<endl;
#define EQ(A,B) (A+ZERO>B&&A-ZERO<B)
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
#define IN(n) int n;scanf("%d",&n);
#define FOR(i, m, n) for (int i(m); i < n; i++)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define FT(m, n) FOR(k, m, n)
#define aa first
#define bb second
void ga(int N,int *A){F(N)scanf("%d",A+i);}
#define LG (18)
#define MX (1<<LG)
#define P2(v) (!(v&(v-1)))
struct RMQ{
    int dp[MX][LG+2],G[MX],XX,O=-1;
    void ini(int *A,int n){
        if(!XX++)FT(1,MX)G[k]=O+=P2(k);
        F(n)dp[i][0]=i;
        FT(1,k-(1<<k)+n+1)F(n+1-(1<<k))
            if(A[dp[i][k-1]]<A[dp[i+(1<<(k-1))][k-1]])
                dp[i][k]=dp[i][k-1];
            else dp[i][k]=dp[i+(1<<(k-1))][k-1];
    }
    int qy(int *A,int L,int R){
        int j(G[R-L+1]);
        if(A[dp[L][j]]<=A[dp[R-(1<<j)+1][j]])
            return A[dp[L][j]];
        return A[dp[R-(1<<j)+1][j]];
    }
}L;
struct RMX{
    int dp[MX][LG+2],G[MX],XX,O=-1;
    void ini(int*A,int n){
        if(!XX++)FT(1,MX)G[k]=O+=P2(k);
        F(n)dp[i][0]=i;
        FT(1,k-(1<<k)+n+1)F(n+1-(1<<k))
            if(A[dp[i][k-1]]>A[dp[i+(1<<(k-1))][k-1]])
                dp[i][k]=dp[i][k-1];
            else dp[i][k]=dp[i+(1<<(k-1))][k-1];      
    }
    int qy(int *A,int L,int R){
        int j(G[R-L+1]);
        if(A[dp[L][j]]>=A[dp[R-(1<<j)+1][j]])
            return dp[L][j];
        return dp[R-(1<<j)+1][j];
    }
}R;
struct SA{
    int sa[MX],R[MX],C[MX],s[MX<<1],t[MX<<1],p[MX],S[MX],U[MX];
    void ss(int n,int m,int*s,int*t,int*p){
        int A=t[n-1]=0,c=*R=-1,*r=s+n,x,y;
        for(int i=n-2;~i;--i)t[i]=s[i]^s[i+1]?s[i]>s[i+1]:t[i+1];
        FOR(i,1,n)R[i]=t[i-1]&&!t[i]?(p[A]=i,A++):-1;
        memset(sa,-1,n*4),memset(S,0,4*m);
        F(n)++S[s[i]];F(m)if(i)S[i]+=S[i-1];F(m)U[i]=S[i]-1;
        for(int i=A-1;~i;--i)sa[U[s[p[i]]]--]=p[i];
        FOR(i,1,m)U[i]=S[i-1];
        F(n)if(sa[i]>0&&t[sa[i]-1])sa[U[s[sa[i]-1]]++]=sa[i]-1;
        F(m)U[i]=S[i]-1;
        for(int i=n-1;~i;--i)if(sa[i]>0&&!t[sa[i]-1])sa[U[s[sa[i]-1]]--]=sa[i]-1;
        F(n)if(~(x=R[sa[i]])){
            if(c<1||p[x+1]-p[x]!=p[y+1]-p[y])++c;
            else for(int j=p[x],k=p[y];j<=p[x+1];++j,++k)
                if((s[j]<<1|t[j])^(s[k]<<1|t[k])){++c;break;}
            r[y=x]=c;
        }
        if(c+1<A)ss(A,c+1,r,t+n,p+A);
        else F(A)sa[r[i]]=i;
        F(A)r[i]=p[sa[i]];
        memset(sa,-1,n*4),memset(S,0,4*m);
        F(n)++S[s[i]];F(m)if(i)S[i]+=S[i-1];F(m)U[i]=S[i]-1;
        for(int i=A-1;~i;--i)sa[U[s[r[i]]]--]=r[i];
        FOR(i,1,m)U[i]=S[i-1];
        F(n)if(sa[i]>0&&t[sa[i]-1])sa[U[s[sa[i]-1]]++]=sa[i]-1;
        F(m)U[i]=S[i]-1;
        for(int i=n-1;~i;--i)if(sa[i]>0&&!t[sa[i]-1])sa[U[s[sa[i]-1]]--]=sa[i]-1;
    }
    void sx(int N,char*r){
        int m,h=*C=0,M=*max_element(r,r+ ++N);
        memset(R,0,4*M+4);
        F(N)R[(int)r[i]]=1;
        F(M)R[i+1]+=R[i];
        F(N)s[i]=R[(int)r[i]]-1;
        m=R[M];
        ss(N,m,s,t,p);
        F(N)R[sa[i]]=i;
        F(N-1){
            while(i+h<N&&sa[R[i]-1]+h<N&&s[i+h]==s[sa[R[i]-1]+h])++h;
            if((C[(int)R[i]]=h))--h;
        }
    }
}Z;
vii o;
char s[MX];
int N,F[MX],B[MX],P[MX],S,E,z;
int qy(int f,int b){
    f=F[f],b=B[b];
    if(f>b)swap(f,b);
    return L.qy(Z.C,f+1,b);
}
bool ok(int t){
    if(!t)return 1;
    if(t>E)return 0;
    int a=P[z=R.qy(P,0,E-t)];
    return a>=t;
}
int bs(int B=0,int E=INF){
    int M;
    while(B<E)
        if(!ok(M=(B+E)>>1))E=M;
        else B=M+1;
    return max(0,B-1);
}
void go(int I){
    int a=qy(I,I),b=I-a+1,e=I+a-1,l,t;
    E=b;
    l=bs(0,min(E,N-e-1)+1),t=2*l+e-b+1;
    if(t>S){
        S=t,ok(l),o.clear();
        if(l)o.PB({z,z+l-1});
        o.PB({b,e});
        if(l)o.PB({N-1-l+1,N-1});
    }
}
int main(void){
    scanf("%s",s),N=strlen(s),strcpy(s+N+1,s),reverse(s+N+1,s+2*N+1),s[N]=63,Z.sx(N*2+1,s),L.ini(Z.C,N*2+2);
    F(2*N+2)if(Z.sa[i]<N)F[Z.sa[i]]=i;
            else if(Z.sa[i]>N)B[N-1-(Z.sa[i]-N-1)]=i;
    F(N)P[i]=qy(i,N-1);
//    F(N)printf("%d: (%s)(%s)\n",i,s+Z.sa[F[i]],s+Z.sa[B[i]]);//TODO ERASE
    R.ini(P,N);
    F(N)go(i);
//    go(2);//TODO ERASE
//    D(S)//TODO ERASE
    printf("%lu\n",o.size());
    for(auto&h:o)printf("%d %d\n",h.aa+1,h.bb-h.aa+1);
    return 0;
}

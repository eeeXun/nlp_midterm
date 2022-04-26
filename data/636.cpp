#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=110000;
int n;char A[maxn];
vector<int> R[maxn];

struct Tbit{
    int n,a[maxn];
    void add(int x){
        for(;x<=n;x+=x&-x)++a[x];
    }
    int get(int x){
        int Fc=0;
        for(;x;x-=x&-x)Fc+=a[x];
        return Fc;
    }
};

namespace Ninit{
    void init(){
        scanf("%s",A+1),n=strlen(A+1);
    }
}

namespace Nsolve{
    Tbit Bt;
    int F[maxn],G[maxn];
    struct Tans{
        int pL,mL,x;
        Tans(int _pL=0,int _x=0,int _mL=0){pL=_pL,x=_x,mL=_mL;}
        inline bool operator <(const Tans &b)const{
            return pL+mL<b.pL+b.mL;
        }
        inline void print(){
            int mx,i;
            for(i=x+pL-1+mL;i<=n;++i)
                if(G[i]==mL){mx=i;break;}
            if(!pL)return printf("1\n%d %d\n",mx-mL+1,mL*2-1),void();
            else {
                printf("3\n%d %d\n",x,pL);
                printf("%d %d\n",mx-mL+1,mL*2-1);
                printf("%d %d\n",n-pL+1,pL);
            }
        }
    }ans;
    
    namespace Nlcp{
        char B[maxn];int f[maxn];
        void solve(){
            int i,l,x,p;
            for(i=1;i<=n;++i)B[i]=A[n-i+1];
            for(x=0,p=0,i=2;i<=n;f[i]=l,++i){
                l=min(max(p-i+1,0),f[i-x+1]);
                for(;i+l<=n && B[1+l]==B[i+l];++l);
                if(i+l-1>p)x=i,p=i+l-1;
            }
            for(x=0,p=0,i=1;i<=n;F[i]=l,++i){
                l=min(max(p-i+1,0),f[i-x+1]);
                for(;i+l<=n && B[1+l]==A[i+l];++l);
                if(i+l-1>p)x=i,p=i+l-1;
            }
        }
    }
    namespace Npal{
        void solve(){
            int i,l,x,p;
            for(G[1]=1,x=1,p=1,i=2;i<=n;G[i]=l,++i){
                l=max(min(G[2*x-i],p-i+1),1);
                for(;i-l>=1 && A[i+l]==A[i-l];++l);
                if(i+l-1>p)p=i+l-1,x=i;
            }
        }
    }
    void solve(){
        int k,i,x,l;
        Nlcp::solve(),Npal::solve();
        for(i=1;i<=n;++i)R[G[i]].push_back(i);
        for(l=0,i=1;i<=n;++i)l=max(l,G[i]);
        for(Bt.n=n,i=0;i<R[l].size();++i)Bt.add(R[l][i]);
        ans=Tans(0,1,l);
        
        for(x=1,k=1;;++k){
            for(;x<n && F[x]<k;++x);
            if(x==n)break;
            for(;l && (x+k-1+l>n-k+1-l || Bt.get(n-k+1-l)-Bt.get(x+k-2+l)<1);--l){
                for(i=0;i<R[l-1].size();++i)Bt.add(R[l-1][i]);
            }
            if(l==0)break;
            ans=max(ans,Tans(k,x,l));
        }
        ans.print();
    }
}

int main(){
    Ninit::init();
    Nsolve::solve();
    return 0;
}
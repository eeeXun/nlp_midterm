#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define oo 200005
using namespace std;

const int p1=41;
const int p2=47;
const int M1=10657;
const int M2=14947;

struct tp{
    int k;
    int x[3],y[3];
}a;

int n,Len,l,p,u,v,root=0,ans=0,AA,BB,CC,DD,r,mid;
vector<int>E[oo];
char s[oo],t[oo];
int ST[oo],EN[oo],L[oo],R[oo],fa[oo],res[oo],A[oo],next[oo];
int b1[oo],b2[oo],H1[oo],H2[oo],H3[oo],H4[oo];

inline int max3(int x,int y,int z)
{
    if (x>y){
        if (z>x) return z;
        return x;
    }
    if (z>y) return z;
    return y;
}

void renew(int x)
{
    res[x]=max3(EN[x]-ST[x]+1,res[L[x]],res[R[x]]);
}

void Zig(int x)
{
    int y=fa[x],z=fa[y];
    L[y]=R[x],fa[R[x]]=y;
    R[x]=y,fa[y]=x;
    fa[x]=z;
    if (y==L[z]) L[z]=x;
    else R[z]=x;
    renew(y);
}

void Zag(int x)
{
    int y=fa[x],z=fa[y];
    R[y]=L[x],fa[L[x]]=y;
    L[x]=y,fa[y]=x;
    fa[x]=z;
    if (y==L[z]) L[z]=x;
    else R[z]=x;
    renew(y);
}

void Splay(int x,int &root)
{
    for (int y,z;fa[x];){
        y=fa[x],z=fa[y];
        if (!z){
            if (x==L[y]) Zig(x);
            else Zag(x);
            break;
        }
        if (y==L[z]){
            if (x==L[y]) Zig(y),Zig(x);
            else Zag(x),Zig(x);
        }else{
            if (x==R[y]) Zag(y),Zag(x);
            else Zig(x),Zag(x);
        }
    }
    root=x;
    renew(root);
}

void Insert(int x,int &root)
{
    if (!root){
        root=x;
        res[x]=EN[x]-ST[x]+1;
        return;
    }
    int p=root;
    for (;p;){
        if (EN[x]<EN[p]){
            if (!L[p]){
                L[p]=x;
                fa[x]=p;
                break;
            }
            p=L[p];
        }else{
            if (!R[p]){
                R[p]=x;
                fa[x]=p;
                break;
            }
            p=R[p];
        }
    }
    Splay(x,root);
}

int Maxpos(int x)
{
    for (;R[x];x=R[x]);
    return x;
}

int Join(int x,int y)
{
    if (!x) return y;
    if (!y) return x;
    int z=Maxpos(x);
    Splay(z,x);
    R[z]=y,fa[y]=z;
    return z;
}

void Delete(int x,int &root)
{
    Splay(x,root);
    int y=L[x],z=R[x];
    fa[y]=fa[z]=0;
    L[x]=R[x]=0;
    root=Join(y,z);
    renew(root);
}

int ask(int x)
{
    int p=root,last=0,res=0;
    for (;p;){
        last=p;
        if (EN[p]>=x){
            res=p;
            p=L[p];
        }else p=R[p];
    }
    Splay(last,root);
    return res;
}

int best(int x,int p)
{
    for (;p;){
        if (EN[p]-ST[p]+1==x) return p;
        if (L[p] && res[L[p]]==x) p=L[p];
        else p=R[p];
    }
    printf("-_-\n");
    return 0;
}

void gettree(int x)
{
    if (L[x]) gettree(L[x]);
    printf("%d %d %d %d\n",x,L[x],R[x],EN[x]-ST[x]+1);
    if (R[x]) gettree(R[x]);
}

void AskL(int i,int j)
{
    AA=(H1[j]-H1[i-1]*b1[j-i+1])%M1;
    if (AA<0) AA+=M1;
    BB=(H2[j]-H2[i-1]*b2[j-i+1])%M2;
    if (BB<0) BB+=M2;
}
void AskR(int i,int j)
{
    CC=(H3[i]-H3[j+1]*b1[j-i+1])%M1;
    if (CC<0) CC+=M1;
    DD=(H4[i]-H4[j+1]*b2[j-i+1])%M2;
    if (DD<0) DD+=M2;
}

int main()
{
//  freopen("input.txt","r",stdin);

    scanf("%s",s+1);
    n=strlen(s+1);
/*  A[1]=0;
    for (int i=2,k=1,j;i<=n;++i){
        Len=k+A[k],l=A[2*k-i];
        if (i+l<=Len) A[i]=l;
        else{
            j=max(0,Len-i);
            while (i+j+1<=n && i-j-1>=1 && s[i+j+1]==s[i-j-1]) ++j;
            A[i]=j;
            k=i;
        }
    }*/

    b1[0]=1,b2[0]=1;
    for (int i=1;i<=n;++i){
        b1[i]=b1[i-1]*p1%M1;
        b2[i]=b2[i-1]*p2%M2;
    }

    for (int i=1;i<=n;++i){
        H1[i]=(H1[i-1]*p1+s[i]-'a'+1)%M1;
        H2[i]=(H2[i-1]*p2+s[i]-'a'+1)%M2;
    }
    for (int i=n;i>=1;--i){
        H3[i]=(H3[i+1]*p1+s[i]-'a'+1)%M1;
        H4[i]=(H4[i+1]*p2+s[i]-'a'+1)%M2;
    }
    

    for (int i=2;i<n;++i)
    if (s[i-1]==s[i+1]){
        l=1,r=min(i-1,n-i),A[i]=1;
        for (;l<=r;){
            mid=(l+r)>>1;
            AskL(i-mid,i-1);
            AskR(i+1,i+mid);
            if (AA==CC && BB==DD){
                A[i]=mid;
                l=mid+1;
            }else r=mid-1;
        }
    }

    for (int i=1;i<=n;++i){
        ST[i]=i-A[i],EN[i]=i+A[i];
        if (EN[i]-ST[i]+1>ans){
            ans=EN[i]-ST[i]+1;
            a.k=1;
            a.x[0]=ST[i];
            a.y[0]=EN[i];
        }
        E[ST[i]].push_back(i);
        Insert(i,root);
    }

    for (int i=1;i<=n;++i) t[i]=s[n-i+1];
    
    next[1]=0;
    for (int i=2;i<=n;++i){
        p=next[i-1];
        while (p && t[p+1]!=t[i]) p=next[p];
        if (t[p+1]==t[i]) next[i]=p+1;
        else next[i]=0;
    }

    p=0;
    for (int i=1;i<=n;++i){
        while (p && t[p+1]!=s[i]) p=next[p];
        if (t[p+1]==s[i]) ++p;
        else p=0;
        
        for (int j=0;j<E[i].size();++j)
            Delete(E[i][j],root);
        
        if (!p) continue;
        u=ask(n-p+1);
        if (u){
            Splay(u,root);
            u=L[u];
        }else u=root;
        
        if (i+p>=n) break;

        if (u && p+p+res[u]>ans){
            ans=p+p+res[u];
            
//          if (i==3) gettree(u);

            v=best(res[u],u);
            
            a.k=3;
            a.x[0]=i-p+1;
            a.y[0]=i;
            a.x[1]=ST[v];
            a.y[1]=EN[v];
            a.x[2]=n-p+1;
            a.y[2]=n;

            Splay(v,root);
        }
    }

    printf("%d\n",a.k);
    for (int i=0;i<a.k;++i) printf("%d %d\n",a.x[i],a.y[i]-a.x[i]+1);
    
    return 0;
}
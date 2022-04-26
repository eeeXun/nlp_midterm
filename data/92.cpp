/**************** library *******************/
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <list>
#include <climits>
#include <cassert>
#include <ctime>
#include <cstring>
using namespace std;
/************* Define **************/
#define LIM 100050
#define PB push_back
#define F first
#define S second
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define FOR(i,s,e) for(int i=(s);i<(e);++i)
#define REV(i,e,s) for(int i=e;i>=s;i--)
#define MS(X,val) memset((X), val, sizeof((X)))
#define _N printf("\n")
#define MOD 1000000007
#define VI vector<int>
#define PII pair<int,int>
#define VI vector<int>
#define VPII vector< PII>
#define MII map<int,int>
#define MSI map<string,int>
#define bit(i) __builtin_popcount(i)

/**************Typedef***************/
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
/*************Constant****************/
const LD PI = acosl(-1.0);
const double EPS = 1e-12;

/*************Function template****************/
//integer to binary representation
void showBit(int no,int N)
{
    for(int i=N-1; i>=0; i--)
        if((no>>i)&1)printf("1");
        else printf("0");
    printf("\n");
}
//binary to integer representation
int binToDec(string s)
{
    int ln=s.length();
    int  sum=0;
    for(int i=ln-1,k=0; i>=0; i--,k++)
        sum=sum+(s[i]-'0')*(1<<k);
    return sum;
}
//combination
void combination(LL com[][1005])
{
    com[0][0]=1;
    int sz=1000;
    for(int i=1; i<=sz; i++)
    {
        com[i][0]=1;
        for(int j=1; j<=i; j++)
        {
            com[i][j]=com[i-1][j]+com[i-1][j-1];
            com[i][j]=com[i][j] % MOD;
        }
    }
}
//union_find
int find_par(int cn)
{
    // if(cn==p[cn])return cn;return p[cn]=find_par(p[cn]);
}
//gcd

int gcd(int u,int v)
{
    if(v==0)return u;
    return gcd(v,u%v);
}
void insert_ind(int cs,int ci,int s,int e)
{
    if(s==e)
    {
        return;
    }
    int mid=(s+e)/2;
    if(ci<=mid)insert_ind(2*cs,ci,s,mid);
    else insert_ind(2*cs+1,ci,mid+1,e);
}
void update_ind(int cs,int ci,int s,int e,int val)
{
    if(s==e)
    {
        return;
    }
    int mid=(s+e)/2;
    if(ci<=mid)update_ind(2*cs,ci,s,mid,val);
    else update_ind(2*cs+1,ci,mid+1,e,val);
}
void update_seg(int cs,int ds,int de,int s,int e,int val)
{
    if(ds==s&&de==e)
    {
        return;
    }
    int mid=(s+e)/2;
    if(ds<=mid)update_seg(2*cs,ds,min(mid,de),s,mid,val);
    if(de>mid) update_seg(2*cs+1,max(mid+1,ds),de,mid+1,e,val);
}
void pattern_match(char pat[],const int len,int pi[])
{
    pi[1]=0;
    for(int i=2; i<=len; i++)
    {
        int st=i-1;
        while(st>=0 && pat[pi[st]+1]!=pat[i] ) st=pi[st];
        if(st==0)pi[i]=0;
        else pi[i] = pi[st]+1;
    }

}
void pattern_match(char pat[],int pi[],char tar[],const int len1,int gi[])
{
    if(pat[0]==tar[0])gi[0]=1;
    for(int i=1; i<len1; i++)
    {
        int st=gi[i-1];
        while(pat[st]!=tar[i] )
        {
            if(st==0)
            {
                st=-1;
                break;
            }
            st = pi[st-1];
        }
        if(st==-1)gi[i]=0;
        else gi[i] = st+1;
    }

}


struct myArray
{
    int mat[10][10];
};

myArray matrix_mul(myArray mat1,myArray mat2,const int sz)
{
    int tmp[sz][sz];
    MS(tmp,0);
    for(int r=0; r<sz; r++)
        for(int c=0; c<sz; c++)
            for(int cr=0; cr<sz; cr++)
                tmp[r][c]+=mat1.mat[r][cr]*mat2.mat[c][cr];
    myArray res;
    for(int r=0; r<sz; r++)
        for(int c=0; c<sz; c++)
            res.mat[r][c]=tmp[r][c];
    return res;
}

myArray unit_matrix(const int sz)
{
    myArray ma;
    MS(ma.mat,0);
    for(int i=0; i<sz; i++)
        ma.mat[i][i]=1;
    return ma;
}

myArray matrix_expo(int p,myArray mat,const int sz)
{
    if(p==0)
    {
        return unit_matrix(sz);
    }
    if(p&1)return matrix_mul(mat, matrix_expo(p-1,mat,sz), sz);
    myArray tmp = matrix_expo(p>>1,mat,sz);
    return matrix_mul(tmp,tmp,sz);

}
MSI msi;
void cal_state(string s,int tran[][30])
{
    int ln=s.length();
    string s1=s;
    for(int i=0; i<ln; i++)
    {
        // cout<<s1<<endl;
        msi[s1]=ln-i;
        s1=s1.substr(0,ln-i-1);

    }
    s1="";
    for(int i=0; i<ln; i++)
    {
        string ts=s1;
        for(int j=0; j<26; j++)
        {

            s1=ts+(char)('a'+j);
            int tln=i+1;
            while(msi[s1]==0)
            {
                s1=s1.substr(1);
                tln--;
                if(tln==0)break;
            }
            if(tln==0)s1="";
            tran[i][j]=msi[s1];
            //cout<<ts+(char)('a'+j)<<" "<<s1<<endl;
            //cout<<i<<" "<<j<<" "<<tran[i][j]<<endl;
        }
        s1=s.substr(0,i+1);

    }

}
int X[]= {0,0,1,-1};
int Y[]= {1,-1,0,0};
int KX[]= {2,2,-2,-2,1,-1,1,-1};
int KY[]= {1,-1,1,-1,2,2,-2,-2};
/*************************End of Template***************************************/


//freopen("in.txt", "r", stdin);
//freopen("out.txt", "w", stdout);
string s;
int pi[LIM],gi[LIM],r[LIM];
int pal[LIM];
int main()
{
    cin>>s;
    int l=s.length();
    for(int i=0,j=0; i<l; )
    {
            //getchar();cout<<i<<" "<<j<<" ";
        while(i+j<l && i-j>=0 && s[i+j]==s[i-j])
            pal[i]++,j++;
        //cout<<pal[i]<<endl;
        if(pal[i]==1)
        {
            i++;
            j=0;
            continue;
        }
        for( j=1; j<pal[i]; j++)
        {
            pal[i+j]=min(pal[i-j],pal[i]-j);
            //cout<<i+j<<" * "<<pal[i+j]<<endl;
            if(pal[i+j]==pal[i]-j)
            {
              // cout<<"hmm\n";
                int tmp=j;
                j=pal[i+j];
                i=i+tmp;
               // cout<<i<<" ** "<<j<<endl;
                break;
            }
        }

    }
//FOR(i,0,l)cout<<pal[i]<<" ";cout<<endl;
pi[l-1]=l;
for(int i=l-2;i>=0;i--)
{
    int in=pi[i+1];
    while(s[in-1]!=s[i]){
        if(in==l){in=l+5; break;}
        in=pi[in];
    }
    if(in==l+5)pi[i]=l;
    else pi[i]=in-1;
}
if(s[0]==s[l-1])gi[0]=l-1;
else gi[0]=l;
for(int i=1;i<l;i++)
{
    int in=gi[i-1];
    while(s[in-1]!=s[i]){
        if(in==l){in=l+5;break;}
        in=pi[in];
    }
    if(in==l+5)gi[i]=l;
    else gi[i]=in-1;
}
gi[0]=l-gi[0];r[0]=gi[0];
for(int i=1;i<l;i++){gi[i]=l-gi[i],r[i]=max(gi[i],r[i-1]);}

//for(int i=0;i<l;i++)cout<<r[i]<<" ";cout<<endl;
int Mx=0,in=-1;
for(int i=0;i<l;i++)
{
    int left,right,mid;
    mid=pal[i];
    if(i-mid<0)left=0;
    else left=min(r[i-mid],l-(i+mid));
    //cout<<i<<" "<<mid<<" "<<left<<endl;
    if(mid*2-1+left*2>Mx){
        Mx=mid*2-1+left*2;
        in=i;
    }


}
int left,right;
if(in-pal[in]<0)left=0;
else left=min(r[in-pal[in]],l-(in+pal[in]));
if(left){
    cout<<3<<endl;
    for(int i=0;i<l;i++)if(gi[i]>=left){cout<<i-left+2<<" "<<left<<endl;break;}
    cout<<in-pal[in]+2<<" "<<2*pal[in]-1<<endl;
    cout<<l-left+1<<" "<<left<<endl;
}
else {
    cout<<1<<endl;
    cout<<in-pal[in]+2<<" "<<2*pal[in]-1<<endl;

}
    return 0;
}


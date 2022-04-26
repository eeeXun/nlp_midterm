# 539 "/usr/include/string.h" 3 4
}
# 43 "/usr/include/c++/11.2.0/cstring" 2 3
# 71 "/usr/include/c++/11.2.0/cstring" 3
extern "C++"
{
namespace std __attribute__ ((__visibility__ ("default")))
{


  using ::memchr;
  using ::memcmp;
  using ::memcpy;
  using ::memmove;
  using ::memset;
  using ::strcat;
  using ::strcmp;
  using ::strcoll;
  using ::strcpy;
  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;
# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 19 "data/92.cpp" 2

# 19 "data/92.cpp"
using namespace std;
# 41 "data/92.cpp"
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const LD PI = acosl(-1.0);
const double EPS = 1e-12;



void showBit(int no,int N)
{
    for(int i=N-1; i>=0; i--)
        if((no>>i)&1)printf("1");
        else printf("0");
    printf("\n");
}

int binToDec(string s)
{
    int ln=s.length();
    int sum=0;
    for(int i=ln-1,k=0; i>=0; i--,k++)
        sum=sum+(s[i]-'0')*(1<<k);
    return sum;
}

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
            com[i][j]=com[i][j] % 1000000007;
        }
    }
}

int find_par(int cn)
{

}


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
    memset((tmp), 0, sizeof((tmp)));
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
    memset((ma.mat), 0, sizeof((ma.mat)));
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
map<string,int> msi;
void cal_state(string s,int tran[][30])
{
    int ln=s.length();
    string s1=s;
    for(int i=0; i<ln; i++)
    {

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


        }
        s1=s.substr(0,i+1);

    }

}
int X[]= {0,0,1,-1};
int Y[]= {1,-1,0,0};
int KX[]= {2,2,-2,-2,1,-1,1,-1};
int KY[]= {1,-1,1,-1,2,2,-2,-2};





string s;
int pi[100050],gi[100050],r[100050];
int pal[100050];
int main()
{
    cin>>s;
    int l=s.length();
    for(int i=0,j=0; i<l; )
    {

        while(i+j<l && i-j>=0 && s[i+j]==s[i-j])
            pal[i]++,j++;

        if(pal[i]==1)
        {
            i++;
            j=0;
            continue;
        }
        for( j=1; j<pal[i]; j++)
        {
            pal[i+j]=min(pal[i-j],pal[i]-j);

            if(pal[i+j]==pal[i]-j)
            {

                int tmp=j;
                j=pal[i+j];
                i=i+tmp;

                break;
            }
        }

    }

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


int Mx=0,in=-1;
for(int i=0;i<l;i++)
{
    int left,right,mid;
    mid=pal[i];
    if(i-mid<0)left=0;
    else left=min(r[i-mid],l-(i+mid));

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

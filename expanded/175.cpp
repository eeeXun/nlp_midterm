                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 8 "data/175.cpp" 2

# 8 "data/175.cpp"
using namespace std;

string t,s;
int i,len,j,w,k,dui,p[200000],qian[200000],daan[200000],ans,pa[5][3],a,b,jl[200000],zui[200000];

int find(int i,int j)
{
    int now=j;
    for (j=j;j<=len;j++)
    {
        if (i+j>=len||i-j<0) return now;
        if (s[i+j]!=s[i-j]) return now;
        now=j;
    }
}

int main()
{

    cin>>s;len=s.length();
    for (i=1;i<=len;i++) t+=s[len-i];
    zui[0]=0;
    j=0;w=0;
    for (i=1;i<s.length();i++)
    {
        if (j+w<i)
        {
            zui[i]=find(i,0);
            j=i;w=zui[i];
        }else
        {
            dui=j-(i-j);
            k=zui[dui];
            if (i+k<j+w) zui[i]=k;else
            {
                zui[i]=find(i,j+w-i);
                j=i;w=zui[i];
            }
        }
    }
    j=0;
    for (i=1;i<len;i++)
    {
        while (j!=0&&t[j]!=t[i]) j=p[j];
        if (j==0)
        {
            if (t[0]==t[i]) j=1;else j=0;
        }else j++;
        p[i+1]=j;
    }
    j=0;
    for (i=0;i<len;i++)
    {
        while (j!=0&&s[i]!=t[j]) j=p[j];
        if (j==0) {if (s[i]==t[0]) j=1;else j=0;} else j++;
        daan[i]=j;
        if (i>0) qian[i]=qian[i-1];
        if (i>0) jl[i]=jl[i-1];
        if (daan[i]>qian[i]) {jl[i]=i;qian[i]=daan[i];}
    }
    for (i=0;i<len;i++)
    {
        a=i-zui[i];b=len-(i+zui[i])-1;
        if (a==0) j=0;else j=qian[a-1];if (j>b) j=b;
        if (zui[i]*2+1+2*j>ans)
        {
            ans=zui[i]*2+1+j*2;
            if (a>=0) pa[1][1]=jl[a-1]+1-j+1;pa[1][2]=j;
            pa[2][1]=a+1;pa[2][2]=2*zui[i]+1;
            pa[3][1]=len-j+1;pa[3][2]=j;
            pa[4][2]=(pa[1][2]>0)+(pa[2][2]>0)+(pa[3][2]>0);
        }
    }
    cout<<pa[4][2]<<endl;
    for (i=1;i<=3;i++) if (pa[i][2]!=0) cout<<pa[i][1]<<" "<<pa[i][2]<<endl;
}

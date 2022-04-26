}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 6 "data/859.cpp" 2

# 6 "data/859.cpp"
using namespace std;

const int maxn=200000+10;
set< pair<int,int> > g;
char s[maxn];
vector<int> p[maxn];
int A[maxn],B[maxn];
int n;

void del(int x)
{
    if (!g.count(make_pair(B[x]*2-1,x))) return;
    g.erase(make_pair(B[x]*2-1,x));
}

int main()
{


    scanf("%s",s+1);
    n=strlen(s+1);
    for (int i=1;i<=n/2;i++) swap(s[i],s[n-i+1]);
    s[n+1]='#';
    for (int i=1;i<=n;i++) s[n+1+i]=s[n-i+1];
    for (A[2]=0;2+A[0]<=n*2+1 && s[1+A[2]]==s[2+A[2]];A[2]++);
    for (int i=3,k=2;i<=n*2+1;i++)
    {
        int len=k+A[k]-1;
        int l=A[i-k+1];
        if (len-i+1>l) A[i]=l;
        else
        {
            int j=len-i+1;if (j<0) j=0;
            while (i+j<=n*2+1 && s[1+j]==s[i+j]) j++;
            A[i]=j;k=i;
        }
    }

    B[1]=1;
    for (int i=2,k=1,j;i<=n;i++)
    {
        if (k+B[k]-1>=i) j=min(k+B[k]-i,B[2*k-i]);
        else j=1;
        while (i+j<=n && i-j>=1 && s[i+j]==s[i-j]) j++;
        B[i]=j;
        if (i+B[i]>k+B[k]) k=i;
    }

    for (int i=1;i<=n;i++)
    {
        p[i-B[i]+1].push_back(i);
        p[i+B[i]-1].push_back(i);
        g.insert(make_pair(B[i]*2-1,i));
    }
    int best=0,x1,x2,y1,y2,z1,z2;
    for (int i=0,j=n+1,L=1,R=n;i<=n/2;i++)
    {
        while (j<=n*2+1 && A[j]<i) j++;
        if (-j+2*n+2<i) break;
        for (;L<=i;L++)
        for (int k=0;k<p[L].size();k++)
            del(p[L][k]);
        for (;R>=-j+2*n+2-i+1;R--)
        for (int k=0;k<p[R].size();k++)
            del(p[R][k]);
        if (!g.size()) break;
        set< pair<int,int> > :: iterator it=g.end();it--;
        if (i*2+it->first<=best) continue;
        best=i*2+it->first;
        x1=1;x2=i;
        y1=it->second-B[it->second]+1;
        y2=it->second+B[it->second]-1;
        z1=-j+2*n+2-i+1;
        z2=-j+2*n+2;
    }

    if (x1>x2) printf("1\n%d %d\n",n-y2+1,y2-y1+1);
    else printf("3\n%d %d\n%d %d\n%d %d\n",n-z2+1,z2-z1+1,n-y2+1,y2-y1+1,n-x2+1,x2-x1+1);
}

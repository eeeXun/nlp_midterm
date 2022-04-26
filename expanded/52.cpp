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
# 20 "data/52.cpp" 2
# 1 "/usr/include/c++/11.2.0/ctime" 1 3
# 39 "/usr/include/c++/11.2.0/ctime" 3
       
# 40 "/usr/include/c++/11.2.0/ctime" 3
# 21 "data/52.cpp" 2


# 22 "data/52.cpp"
using namespace std;
# 34 "data/52.cpp"
int N;
char cs[201000];
int r[201000];
int tx[201000];
int ty[201000];
int pai[201000];
int sa[201000];
bool deng(int *y,int a,int b,int l)
{
 return y[a]==y[b]&&y[a+l]==y[b+l];
}
void dasuffix(int*r,int n,int m)
{
    int*x=tx,*y=ty;
 int i,j;
 for(i=(0);i<(m);i++) pai[i]=0;
 for(i=(0);i<(n);i++) pai[x[i]=r[i]]++;
 for(i=(1);i<(m);i++) pai[i]+=pai[i-1];
 for(i=((n)-1);i>=(0);i--) sa[--pai[x[i]]]=i;
 int p=1;
 for (j=1;p<n;j<<=1,m=p)
 {
  p=0;
  for(i=(n-j);i<(n);i++) y[p++]=i;
  for(i=(0);i<(n);i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=(0);i<(m);i++) pai[i]=0;
     for(i=(0);i<(n);i++) pai[x[y[i]]]++;
     for(i=(1);i<(m);i++) pai[i]+=pai[i-1];
     for(i=((n)-1);i>=(0);i--) sa[--pai[x[y[i]]]]=y[i];
  swap(x,y);
  x[sa[0]]=0,p=1;
  for(i=(1);i<(n);i++) x[sa[i]]=deng(y,sa[i-1],sa[i],j)?p-1:p++;
 }
}
int rank[201000];
int height[201000];
void calheight(int *r,int n)
{
 int i,j;
    for(i=(0);i<(n+1);i++) rank[sa[i]]=i;
 int k=0;
 for(i=(0);i<(n);i++)
 {
  if(k>0) k--;
  j=sa[rank[i]-1];
  for (;r[i+k]==r[j+k];k++);
  height[rank[i]]=k;
 }
}
int M[201000][20];
void initrmq(int n)
{
 int i,j;
    for(i=(0);i<(n);i++) M[i][0]=height[i];
 for (j=1;(1<<j)<=n;j++)
 {
     for (i=0;i+(1<<(j-1))<n;i++)
     {
            M[i][j]=min(M[i][j-1],M[i+(1<<(j-1))][j-1]);
     }
 }
}
int askrmq(int a,int b)
{
    int i;
 for(i=(0);i<(20);i++) if((1<<i)>b-a+1) break;
 i--;
 return min(M[a][i],M[b-(1<<i)+1][i]);
}
int lcp(int a,int b)
{
 a=rank[a];
 b=rank[b];
 if(a>b) a^=b,b^=a,a^=b;
 return askrmq(a+1,b);
}
int main()
{
 int i,j,k;
    scanf("%s",cs);
 int tn=strlen(cs);
 cs[tn]=1;
 for(i=(0);i<(tn);i++) cs[2*tn-i]=cs[i];
 cs[tn*2+1]=0;
 N=strlen(cs);
    for(i=(0);i<(N+1);i++) r[i]=cs[i];
 dasuffix(r,N+1,128);
 calheight(r,N);
 initrmq(N+1);
 int rpos[201000];
 for(i=(0);i<(201000);i++) rpos[i]=1000000000;
 j=0;
 for(i=(1);i<(tn+1);i++)
 {
     for(;j<tn;j++) if(lcp(j,tn+1)>=i)break;
     if(j==tn)break;
     rpos[i]=j+i-1;
    }
    int qr[201000];memset((qr),0,sizeof (qr));;
    j=0;
    for(i=(0);i<(tn);i++)
    {
        while (rpos[j+1] <= i)++j;
        qr[i] = j;
    }
    int len=-1;
    vector<pair<int,int> > ans;
    for(i=(0);i<(tn);i++)
    {
        int zl=lcp(i,N-i-1);
        int lt=i-zl;
        int rt=i+zl;
        int l=(lt>=0)?min(qr[lt],tn-rt):0;
        int tret=zl*2-1+2*l;
        if(tret<=len) continue;
        len=tret;
        ans.clear();
        if(l>0) ans.push_back(make_pair(rpos[l]-l+1,l));
        ans.push_back(make_pair(i-zl+1,2*zl-1));
        if(l>0) ans.push_back(make_pair(tn-l,l));
    }
    printf("%d\n",ans.size());
 for(i=(0);i<(ans.size());i++)
 {
     printf("%d %d\n",ans[i].first+1,ans[i].second);
    }
}

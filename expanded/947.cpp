# 1928 "/usr/include/c++/11.2.0/cmath" 2 3


}
# 7 "data/947.cpp" 2

# 7 "data/947.cpp"
using namespace std;
string s;
typedef long long ll;
ll suf;
ll pre;
const ll M=29;
const ll mod=1231231237LL;
const int maxn=1e5+7;
int m[maxn][20];
ll po[maxn];
int re[3][2];
int p[maxn];
void pk(string t)
{
    int m;
    int maxid;
    int id;
 m=t.length();
 t[m]=0;
 maxid=id=0;
 for(int i=0;i<m;i++)
 {
  if(maxid>i)
  {
   p[i]=min(p[2*id-i],maxid-i);
  }else p[i]=1;

 while(t[i+p[i]]==t[i-p[i]])p[i]++;
 if(p[i]+i>maxid)
 {
  maxid=p[i]+i;
  id=i;
 }
 }
}

int query(int i,int j)
{
 int k=(int)(log(j-i+1)/log(2));
 if(p[m[i][k]]<p[m[j-(1<<k)+1][k]])
    {

        return m[j-(1<<k)+1][k];
    }
    else
    {

        return m[i][k];
    }
}
void init()
{
    pk(s);
    int n=s.length();
    for(int i=0;i<n;i++)m[i][0]=i;

    for(int j=1;(1<<j)-1<n;j++){
    for(int i=0;i+(1<<j)-1<n;i++)
   m[i][j]=p[m[i][j-1]]>p[m[i+(1<<(j-1))][j-1]]?m[i][j-1]:m[i+(1<<(j-1))][j-1];
 }

}
int main()
{
    cin>>s;
    init();
    ll pp=0;
    po[0]=1;
    for(int i=1;i<maxn;i++)po[i]=(po[i-1]*M)%mod;
    int ans1=0;
    int cur_len=0;
    for(int i=s.length()-1;2*i>s.length();i--)
    {
        suf=(suf*M+s[i]-'a'+1)%mod;
        pre=(pre*M+s[pp]-'a'+1)%mod;
        cur_len++;
        pp++;
        while(pp<i&&pre!=suf)
        {
            pre=(pre-(po[cur_len-1]*(s[pp-cur_len]-'a'+1))%mod+mod)%mod;
            pre=(pre*M+s[pp]-'a'+1)%mod;
            pp++;
        }
        if(pp==i)break;


        int l=1,r=(i-1-pp+2)/2;
        int lef=pp,rig=i-1;
        while(l<r)
        {
            int mid=(l+r)/2+1;
            if(p[query(lef+mid-1,rig-mid+1)]>=mid)l=mid;
            else r=mid-1;
        }
        int pos=query(lef+l-1,rig-l+1);
        if(cur_len*2+2*l-1>ans1)
        {
            ans1=cur_len*2+2*l-1;
            re[0][0]=pp-cur_len+1;
            re[0][1]=cur_len;
            re[1][0]=pos-l+2;
            re[1][1]=2*l-1;
            re[2][0]=i+1;
            re[2][1]=cur_len;
        }
    }
    int ans2=0;
    int pos2=0;
    for(int i=0;i<s.length();i++)
    {
        if(ans2<p[i]*2-1)ans2=p[i]*2-1,pos2=i-p[i]+1;
    }
    if(ans1>ans2)
    {
    printf("3\n");
    for(int i=0;i<3;i++)
    {
        printf("%d %d\n",re[i][0],re[i][1]);
    }
    }
    else printf("1\n%d %d\n",pos2+1,ans2);
    return 0;
}

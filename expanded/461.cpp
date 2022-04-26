# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 6 "data/461.cpp" 2

# 6 "data/461.cpp"
using namespace std;
const int u=100010;
unsigned long long p[u],ls[u],rs[u];
int d[u][18],f[u][18],n,i,j,l,r,mid,x,y,ans,pre,pl,cen,cl;
char s[u];

int ask(int x,int y,int k)
{
 int z=(int)(log(y-x+1.0)/log(2.0));
 if(k==0) return max(d[x][z],d[y-(1<<z)+1][z]);
 else return d[x][z]>d[y-(1<<z)+1][z]?f[x][z]:f[y-(1<<z)+1][z];
}

int main()
{
 scanf("%s",s+1);
 n=strlen(s+1);
 for(p[0]=i=1;i<=n;i++) p[i]=p[i-1]*131;
 for(i=1;i<=n;i++) ls[i]=ls[i-1]*131+s[i]-'a'+1;
 for(i=n;i;i--) rs[i]=rs[i+1]*131+s[i]-'a'+1;
 for(i=1;i<=n;i++)
 {
  l=1,r=min(i,n-i+1);
  while(l<r)
  {
   mid=(l+r+1)>>1;
   if(ls[i]-ls[i-mid]*p[mid]==rs[i]-rs[i+mid]*p[mid]) l=mid; else r=mid-1;
  }
  d[i][0]=l,f[i][0]=i;
 }
 for(i=1;i<=16;i++)
  for(j=1;j<=n-(1<<i)+1;j++)
   if(d[j][i-1]>d[j+(1<<i-1)][i-1]) d[j][i]=d[j][i-1],f[j][i]=f[j][i-1];
   else d[j][i]=d[j+(1<<i-1)][i-1],f[j][i]=f[j+(1<<i-1)][i-1];
 cl=ask(1,n,0),ans=cl*2-1,cen=ask(1,n,1);
 for(i=j=1;i<=n/2;i++)
 {
  for(;j<=n-2*i+1&&ls[j+i-1]-ls[j-1]*p[i]!=rs[n-i+1];j++);
  if(j>n-2*i+1) break;
  x=j+i,y=n-i,l=0,r=(y-x+1)/2;
  while(l<r)
  {
   mid=(l+r+1)>>1;
   if(ask(x+mid-1,y-mid+1,0)>=mid) l=mid; else r=mid-1;
  }
  if(2*i+2*l-1>ans) ans=2*i+2*l-1,pre=j,pl=i,cen=ask(x+l-1,y-l+1,1),cl=l;
 }
 cout<<(pl?3:1)<<endl;
 if(pl) printf("%d %d\n%d %d\n%d %d\n",pre,pl,cen-cl+1,cl*2-1,n-pl+1,pl); else printf("%d %d\n",cen-cl+1,cl*2-1);

 return 0;
}

using namespace std;



unsigned long long h1[100005],h2[100005],cf[100005];
int l,i,L,R,mid,j,g[100005],ans,vv[100005],x,f[100005],m[100005];
char s[100005];
inline unsigned long long g1(int l,int r){return h1[r]-h1[l]*cf[r-l];}
inline unsigned long long g2(int l,int r){return h2[l]-h2[r]*cf[r-l];}
int main(){
 scanf("%s",s+1);l=strlen(s+1);
 for(i=cf[0]=1;i<=l;++i)h1[i]=h1[i-1]*1145141923 +s[i],cf[i]=cf[i-1]*1145141923;
 for(i=l;i;--i)h2[i]=h2[i+1]*1145141923 +s[i];
 for(i=0;i<l;++i){
  L=0;R=l-i;
  while(L<R){
   mid=R-(R-L>>1);
   if(g1(i,i+mid)==g2(l-mid+1,l+1))L=mid;
   else R=mid-1;
  }
  f[i+L]=max(f[i+L],L);
 }
 for(i=l;i;--i)f[i]=max(f[i],f[i+1]-1);
 for(i=1;i<=l;++i)g[i]=max(g[i-1],f[i]);
 for(i=1;i<=l;++i){
  L=0;R=min(i-1,l-i);
  while(L<R){
   mid=R-(R-L>>1);
   if(g1(i-mid-1,i+mid)==g2(i-mid,i+mid+1))L=mid;
   else R=mid-1;
  }
  m[i]=L;
  if(L*2+1+min(l-i-L,g[i-L-1])*2>ans)vv[i]=1,ans=L*2+1+min(l-i-L,g[i-L-1])*2;
 }
 for(i=l;i;--i){
  if(vv[i]){
   L=m[i];
   if(x=min(l-i-L,g[i-L-1])){
    cout<<"3\n";
    for(j=1;;++j)if(f[j]==x){cout<<j-x+1<<" "<<x<<"\n";break;}
    cout<<i-L<<" "<<L+L+1<<"\n";
    cout<<l-x+1<<" "<<x<<"\n";
   }
   else cout<<"1\n"<<i-L<<" "<<L+L+1<<"\n";
   return 0;
  }
 }
}

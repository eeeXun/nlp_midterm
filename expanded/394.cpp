# 63 "/usr/include/c++/11.2.0/map" 2 3
# 71 "/usr/include/c++/11.2.0/map" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

  namespace pmr
  {
    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Tp, typename _Cmp = std::less<_Key>>
      using map
 = std::map<_Key, _Tp, _Cmp,
     polymorphic_allocator<pair<const _Key, _Tp>>>;
    template<typename _Key, typename _Tp, typename _Cmp = std::less<_Key>>
      using multimap
 = std::multimap<_Key, _Tp, _Cmp,
   polymorphic_allocator<pair<const _Key, _Tp>>>;
  }

}
# 13 "data/394.cpp" 2
# 28 "data/394.cpp"

# 28 "data/394.cpp"
using namespace std;
typedef long long LL;
typedef double DB;
typedef vector<int> VI;
string s;
int R[110000];
int ex[110000],next[110000];
int Max[110000];
void init(){
 int i,j,k;
 cin>>s;
 R[0]=1;int p=0,mx=0;
 for(i=1;i<s.size();i++){
  if(i<=mx)R[i]=min(R[2*p-i],mx-i+1);
  else R[i]=1;
  while(i-R[i]>=0&&i+R[i]<s.size()&&s[i-R[i]]==s[i+R[i]])R[i]++;
  if(i+R[i]-1>=mx)p=i,mx=i+R[i]-1;
 }

 string t=s;
 for(i=0;i<t.size()/2;i++)swap(t[i],t[t.size()-i-1]);
 for(i=1;i<t.size();i++){
  j=next[i];
  while(j&&t[j]!=t[i])j=next[j];
  if(t[j]==t[i])next[i+1]=j+1;
  else next[i+1]=0;
 }
 for(i=0;i<s.size();i++){
  j=ex[i];
  while(j&&t[j]!=s[i])j=next[j];
  if(t[j]==s[i])ex[i+1]=j+1;
  else ex[i+1]=0;
 }
}
void solve(){
 int i,j,k;
 int ret=0;
 int p1,l1,p2,l2;
 for(i=0;i<s.size();i++){
  if(i)Max[i-1]=max(Max[i-2],ex[i]);
  int tmp=Max[i-R[i]];
  if(i+R[i]-1+tmp>s.size()-1){
   tmp=s.size()-i-R[i];
  }
  if(2*R[i]-1+tmp*2>ret){
   ret=2*R[i]-1+tmp*2;
   l1=tmp;p2=i-R[i]+1;l2=2*R[i]-1;
  }
 }
 if(!l1)printf("1\n%d %d\n",p2+1,l2);
 else {
  puts("3");
  for(i=1;i<s.size();i++)
   if(ex[i]==l1)break;
  printf("%d %d\n",i-l1+1,l1);
  printf("%d %d\n",p2+1,l2);
  printf("%d %d\n",s.size()-l1+1,l1);
 }
}
int main(){

 freopen("in.txt","r",
# 89 "data/394.cpp" 3 4
                     stdin
# 89 "data/394.cpp"
                          );


 init();
 solve();
 return 0;
}

      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 3 "data/109.cpp" 2

# 3 "data/109.cpp"
using namespace std;
# 12 "data/109.cpp"
typedef long long ll;
inline void Fail(){printf("0");exit(0);}

const int maxn=100005;
int n,ans,p;
string s;
char c[maxn];
int z[maxn*2],x[maxn],a[3],len[3];
pair<int,int> mx[maxn];

void Z_algorithm(string S){
 int l=0,r=0;
 for(int (i)=1;(i)<=S.size()-1;i++){
  if(r<i){
   for(int (j)=0;(j)<S.size();j++)
   if(i+j<S.size()&&S[j]==S[i+j])z[i]++;
   else break;
   if(z[i])l=i,r=i+z[i]-1;
  }
  else{
   if(l<i&&i<r&&z[i-l]<r-i)z[i]=z[i-l];
   else{
    z[i]=r-i;
    for(int j=r-i;j<S.size();j++)
    if(i+j<S.size()&&S[j]==S[i+j])z[i]++;
    else break;
    if(z[i])l=i,r=i+z[i]-1;
   }
  }
 }
}

void Manacher(string S){
 int cen,rgt=-1;
 for(int (i)=0;(i)<S.size();i++){
  if(i<rgt)x[i]=min(x[cen*2-i],rgt-i);
  while(i+x[i]+1<S.size()&&i-x[i]-1>=0&&S[i+x[i]+1]==S[i-x[i]-1])x[i]++;
  if(i+x[i]>rgt){
   rgt=i+x[i];
   cen=i;
  }
 }
}

int main(){
 scanf("%s",c);s=c;
 n=s.size();
 Manacher(s);
 string t=s;reverse(t.begin(),t.end());
 Z_algorithm(t+'*'+s);
 mx[0]=make_pair(z[n+1],0);
 for(int (i)=1;(i)<=n-1;i++)mx[i]=max(mx[i-1],make_pair(z[i+n+1],i));

 for(int (i)=0;(i)<n;i++){
  int cur=x[i]*2+1;
  int l=0,r=n;
  while(r-l>1){
   int mid=(l+r)>>1;
   if(i-x[i]-mid>=0&&i+x[i]+mid<n&&mx[i-x[i]-mid].first>=mid)l=mid;
   else r=mid;
  }
  cur+=l*2;
  if(cur>ans){
   ans=cur;
   if(!l)p=1,a[0]=i-x[i],len[0]=x[i]*2+1;
   else{
    p=3;
    a[0]=mx[i-x[i]-l].second;len[0]=l;
    a[1]=i-x[i];len[1]=x[i]*2+1;
    a[2]=n-l;len[2]=l;
   }
  }
 }
 printf("%d\n",p);
 for(int (i)=0;(i)<p;i++)printf("%d %d\n",a[i]+1,len[i]);
 return 0;
}

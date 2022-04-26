 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 3 "data/335.cpp" 2
#pragma GCC optimize(2)

# 4 "data/335.cpp"
using namespace std;
# 14 "data/335.cpp"
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<long long,long long> pll;

void qread(int &x){
    int neg=1;x=0;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')neg=-1;c=getchar();}
    while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
    x*=neg;
}

const int maxn=200005;
int n,m,ans;
char c[maxn];
int z[maxn],p[maxn],mn[maxn],pos[3],len[3];
pii pre[maxn];
string s;

void zalgo(string s){
    int l=0,r=0;
    for(int (i)=1;(i)<=s.size()-1;i++){
 if(i<r)z[i]=min(r-i,z[i-l]);
 while(i+z[i]<s.size()&&s[z[i]]==s[i+z[i]])z[i]++;
 if(i+z[i]-1>r)l=i,r=i+z[i]-1;
    }
}

void manacher(string s){
    int c=0,r=0;
    for(int (i)=0;(i)<s.size();i++){
 if(i<r)p[i]=min(p[2*c-i],r-i);
 while(i-p[i]>=0&&i+p[i]<s.size()&&s[i-p[i]]==s[i+p[i]])p[i]++;
 if(i+p[i]-1>r)c=i,r=i+p[i]-1;
    }
}

int main(){




     scanf("%s",c);n=strlen(c);s=c;
     string t=s;
     reverse(t.begin(),t.end());
     zalgo(t+"#"+s);
     for(int (i)=0;(i)<n;i++)mn[i]=i+1;
     for(int (i)=0;(i)<n;i++)if(z[i+n+1]>=1)mn[i+z[i+n+1]-1]=min(mn[i+z[i+n+1]-1],i);
     for(int i=n-2;i>=0;i--)mn[i]=min(mn[i],mn[i+1]);
     for(int (i)=0;(i)<n;i++)pre[i]=make_pair(i-mn[i]+1,i);
     for(int (i)=1;(i)<=n-1;i++)pre[i]=max(pre[i],pre[i-1]);
     manacher(s);
     for(int (i)=0;(i)<n;i++){
  int l=i-p[i]+1,r=i+p[i]-1;
  if(r-l+1>ans){
      ans=r-l+1;
      m=1;
      pos[0]=l;len[0]=r-l+1;
  }
  if(!l)continue;
  pii cur=pre[l-1];
  cur.first=min(cur.first,n-1-(r+1)+1);
  if(cur.first*2+r-l+1>ans){
      ans=cur.first*2+r-l+1;
      m=3;
      pos[0]=cur.second-cur.first+1;len[0]=cur.first;
      pos[1]=l;len[1]=r-l+1;
      pos[2]=n-1-cur.first+1;len[2]=cur.first;
  }
     }
     printf("%d\n",m);
     for(int (i)=0;(i)<m;i++)printf("%d %d\n",pos[i]+1,len[i]);



     return 0;
}

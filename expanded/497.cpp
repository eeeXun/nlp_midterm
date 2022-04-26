      using argument_type [[__deprecated__]] = variant<_Types...>;
    };

  template<>
    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
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
# 8 "data/497.cpp" 2
# 26 "data/497.cpp"

# 26 "data/497.cpp"
using namespace std;
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct String_Hash{
 long long MUL=1e9+9,MOD=1e9+7;
 long long quick(long long A,long long B){
  if(!B) return 1ll;
  long long tmp=quick(A,B>>1);
  tmp*=tmp;
  tmp%=MOD;
  if(B&1){
   tmp*=A;
   tmp%=MOD;
  }
  return tmp;
 }
 long long val[26];
 long long num[100000+20],inv[100000+20];
 void init(){
  for(int i=0;i<100000;++i)
   inv[i]=quick(quick(MUL,i),MOD-2);
  for(int i=0;i<26;++i){
   val[i]=rng()%1000000000 +1;
  }
 }
 void hash_work(string s){
  long long alr=1;
  for(int i=0;i<s.length();++i)
  {
   num[i+1]=num[i]+val[s[i]-'a']*alr%MOD;
   num[i+1]%=MOD;
   alr*=MUL;
   alr%=MOD;
  }
 }
 long long cut(int l,int r){
  return (num[r]-num[l-1]+MOD)%MOD*inv[l-1]%MOD;
 }
}hs,hs_rev;
const int N=1<<17;
mp segtree[N*2];
void change(int index,int val){
 index+=N-1;
 segtree[index]=max(segtree[index],make_pair(val,index-(N-1)));
 index>>=1;
 while(index){
  segtree[index]=max(segtree[index<<1],segtree[index<<1|1]);
  index>>=1;
 }
}
mp query(int a,int b,int now=1,int l=1,int r=N+1){
 if(r<=a||l>=b){
  return make_pair(0,1);
 }
 if(r<=b&&l>=a){
  return segtree[now];
 }
 int mid=(l+r)>>1;
 return max(query(a,b,now<<1,l,mid),query(a,b,now<<1|1,mid,r));
}
bool comp(mp A , mp B){
 return A.second>B.second;
}
int nxt[200000+20];
int main(){
 ios::sync_with_stdio(false);
 string s;
 cin>>s;
 hs.init();
 hs_rev.init();
 for(int i=0;i<26;++i)
  hs_rev.val[i]=hs.val[i];
 hs.hash_work(s);
 string ss;
 ss=s;
 reverse(s.begin(),s.end());
 ss=s+'#'+ss;
 int j_=0;
 for(int i=0;i<ss.length();++i){
  if(!i) continue;
  if(ss[i]==ss[j_]){
   nxt[i]=++j_;
  }
  else{
   while(j_&&ss[i]!=ss[j_]){
    j_=nxt[j_-1];
   }
   if(ss[i]==ss[j_]){
    nxt[i]=++j_;
   }
   else{
    nxt[i]=0;
   }
  }
 }
 hs_rev.hash_work(s);
 vector<mp> can;
 int len=s.length();
 s='#'+s;
 for(int i=1;i<=len;++i){
  can.push_back(make_pair(nxt[i+len],i));
 }
 sort(can.begin(),can.end());
 vector<mp> queries;
 for(int i=1;i<=len;++i){
  int l=1,r=min(len-i+1,i)+1;
  while(l<r-1){
   int mid=(l+r)>>1;
   if(hs.cut(i,mid+i-1)==hs_rev.cut(len-i+1,len-i+1+mid-1)){
    l=mid;
   }
   else{
    r=mid;
   }
  }
  queries.push_back(make_pair(i-l+1,i+l-1));
 }

 sort(queries.begin(),queries.end(),comp);
 pair<int,pair<mp,mp> > rest=make_pair(-1,make_pair(make_pair(-1,-1),make_pair(-1,-1)));
 int zz=0;
 for(auto it:queries){
  while(zz<can.size()&&can[zz].first<=len-it.second){
   change(can[zz].second,can[zz].first);
   zz++;
  }
  mp qq=query(1,it.first);
  if(it.second-it.first+1+qq.first*2>rest.first)
  rest=make_pair(qq.first*2+it.second-it.first+1,make_pair(it,qq));
 }
 if(rest.second.second.first){
  cout<<3<<endl;
  cout<<rest.second.second.second-rest.second.second.first+1<<" "<<rest.second.second.first<<endl;
  cout<<rest.second.first.first<<" "<<rest.second.first.second-rest.second.first.first+1<<endl;
  cout<<len-rest.second.second.first+1<<" "<<rest.second.second.first<<endl;
 }
 else{
  cout<<1<<endl;
  cout<<rest.second.first.first<<" "<<rest.second.first.second-rest.second.first.first+1<<endl;
 }

 return 0;
}

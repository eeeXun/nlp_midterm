# 75 "data/701.cpp"
             ;
  if(x>y)swap(x,y);
  ++x;
  int k=lg[y-x+1];
  return min(st[x][k],st[y-(1<<k)+1][k]);
 }
 int get_lcp(int x,int y){
  
# 82 "data/701.cpp" 3 4
 (static_cast <bool> (
# 82 "data/701.cpp"
 x!=y
# 82 "data/701.cpp" 3 4
 ) ? void (0) : __assert_fail (
# 82 "data/701.cpp"
 "x!=y"
# 82 "data/701.cpp" 3 4
 , "data/701.cpp", 82, __extension__ __PRETTY_FUNCTION__))
# 82 "data/701.cpp"
             ;
  return rmq(rk[x],rk[y]);
 }
 SA(){}
}sa;
int n;
inline int revpos(int i){
# 88 "data/701.cpp" 3 4
                        (static_cast <bool> (
# 88 "data/701.cpp"
                        1<=i&&i<=n
# 88 "data/701.cpp" 3 4
                        ) ? void (0) : __assert_fail (
# 88 "data/701.cpp"
                        "1<=i&&i<=n"
# 88 "data/701.cpp" 3 4
                        , "data/701.cpp", 88, __extension__ __PRETTY_FUNCTION__))
# 88 "data/701.cpp"
                                          ;return n+2+n-i;}
int solve1(){
 int ans=1;
 for(int i=1;i<=n;++i)ans=max(ans,sa.get_lcp(i,revpos(i)));
 return ans*2-1;
}
void get_ans1(int ans){
 cout<<1<<endl;
 ans=(ans+1)/2;
 for(int i=1;i<=n;++i)if(sa.get_lcp(i,revpos(i))==ans){
  cout<<i-ans+1<<" "<<ans*2-1<<endl;
  return;
 }
 
# 101 "data/701.cpp" 3 4
(static_cast <bool> (
# 101 "data/701.cpp"
0
# 101 "data/701.cpp" 3 4
) ? void (0) : __assert_fail (
# 101 "data/701.cpp"
"0"
# 101 "data/701.cpp" 3 4
, "data/701.cpp", 101, __extension__ __PRETTY_FUNCTION__))
# 101 "data/701.cpp"
         ;
}

int rt[MAXN];
struct FrogTree{
 int sum[MAXN*30],ls[MAXN*30],rs[MAXN*30],cnt;
 void modify(int &x,int y,int l,int r,int pos){
  x=++cnt;
  ls[x]=ls[y],rs[x]=rs[y],sum[x]=sum[y]+1;
  if(l==r)return;
  int mid=(l+r)>>1;
  if(pos<=mid)modify(ls[x],ls[y],l,mid,pos);
  else modify(rs[x],rs[y],mid+1,r,pos);
 }
 int query(int x,int y,int l,int r,int ql,int qr){
  if(!x)return 0;
  if(ql<=l&&qr>=r)return sum[x]-sum[y];
  int mid=(l+r)>>1,res=0;
  if(ql<=mid)res+=query(ls[x],ls[y],l,mid,ql,qr);
  if(qr>mid)res+=query(rs[x],rs[y],mid+1,r,ql,qr);
  return res;
 }
 FrogTree(){}
}T;
int res[MAXN];
int solve3(){
 int ans=0;
 for(int i=1;i<=n;++i)T.modify(rt[i],rt[i-1],1,sa.n,sa.rk[i]);
 for(int i=1;i<=n;++i){
  int len=sa.get_lcp(i,revpos(i));

  
# 132 "data/701.cpp" 3 4
 (static_cast <bool> (
# 132 "data/701.cpp"
 len>=1&&len<=i&&i+len-1<=n
# 132 "data/701.cpp" 3 4
 ) ? void (0) : __assert_fail (
# 132 "data/701.cpp"
 "len>=1&&len<=i&&i+len-1<=n"
# 132 "data/701.cpp" 3 4
 , "data/701.cpp", 132, __extension__ __PRETTY_FUNCTION__))
# 132 "data/701.cpp"
                                   ;
  if(len==i||i+len-1==n)continue;
  int a=1,b=i-len,c=n+2,d=revpos(i+len);
  int L=0,R=min(b-a+1,d-c+1);
  while(L<R){
   int Mid=(L+R+1)>>1;
   int lrange,rrange;
   int l=1,r=sa.rk[c];
   while(l<r){
    int mid=(l+r)>>1;
    if(sa.rmq(mid,sa.rk[c])>=Mid)r=mid;
    else l=mid+1;
   }
   lrange=l;
   l=sa.rk[c],r=sa.n;
   while(l<r){
    int mid=(l+r+1)>>1;
    if(sa.rmq(mid,sa.rk[c])>=Mid)l=mid;
    else r=mid-1;
   }
   rrange=l;
   if(T.query(rt[b-Mid+1],rt[a-1],1,sa.n,lrange,rrange))L=Mid;
   else R=Mid-1;
  }
  if(L)ans=max(ans,L*2+len*2-1),res[i]=L;
 }
 return ans;
}
void get_ans3(int ans){
 cout<<3<<endl;
 for(int i=1;i<=n;++i){
  int len=sa.get_lcp(i,revpos(i));
  if(res[i]&&res[i]*2+len*2-1==ans){
   int a=1,b=i-len,c=n+2;
   for(int j=a;j<=b;++j)if(sa.get_lcp(j,c)>=res[i]){
    cout<<j<<" "<<res[i]<<endl;
    cout<<i-len+1<<" "<<len*2-1<<endl;
    cout<<n-res[i]+1<<" "<<res[i]<<endl;
    return;
   }
   
# 172 "data/701.cpp" 3 4
  (static_cast <bool> (
# 172 "data/701.cpp"
  0
# 172 "data/701.cpp" 3 4
  ) ? void (0) : __assert_fail (
# 172 "data/701.cpp"
  "0"
# 172 "data/701.cpp" 3 4
  , "data/701.cpp", 172, __extension__ __PRETTY_FUNCTION__))
# 172 "data/701.cpp"
           ;
  }
 }
 
# 175 "data/701.cpp" 3 4
(static_cast <bool> (
# 175 "data/701.cpp"
0
# 175 "data/701.cpp" 3 4
) ? void (0) : __assert_fail (
# 175 "data/701.cpp"
"0"
# 175 "data/701.cpp" 3 4
, "data/701.cpp", 175, __extension__ __PRETTY_FUNCTION__))
# 175 "data/701.cpp"
         ;
}
int main() {
 scanf("%s",s+1);
 n=strlen(s+1);
 s[n+1]='#';
 for(int i=n+2;i<=n*2+1;++i)s[i]=s[n-(i-(n+1))+1];
 sa.n=n*2+1;
 sa.init_sa();


 int x=solve1(),y=solve3();
 if(x>y)get_ans1(x);
 else get_ans3(y);
 return 0;
}

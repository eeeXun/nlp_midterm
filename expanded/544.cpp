



typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned long UL;
typedef unsigned short US;
typedef pair < int , int > pii;
typedef pair < int , pii > p3i;
clock_t __stt;
inline void TStart(){__stt=clock();}
inline void TReport(){printf("\nTaken Time : %.3lf sec\n",(double)(clock()-__stt)/
# 18 "data/544.cpp" 3 4
                                                                                 ((__clock_t) 1000000)
# 18 "data/544.cpp"
                                                                                               );}
template < typename T > T MIN(T a,T b){return a<b?a:b;}
template < typename T > T MAX(T a,T b){return a>b?a:b;}
template < typename T > T ABS(T a){return a>0?a:(-a);}
template < typename T > void UMIN(T &a,T b){if(b<a) a=b;}
template < typename T > void UMAX(T &a,T b){if(b>a) a=b;}
const int hs=37;
int n,Z[200005],mv[200005],maxsuf,hsh[200005],pw[200005];
pii poss[200005];
p3i res;
string s,rs;
void getrevZ(string S,int *arr){
 int xb,x2,l=0,r=-1;
 reverse(S.begin(),S.end());
 arr[0]=(int)S.size();
 for(xb=1;xb<(int)S.size();++xb){
  if(xb>r){
   for(x2=0;xb+x2<(int)S.size();++x2){
    if(S[x2]!=S[xb+x2]) break;
   }
   arr[xb]=x2;
  }
  else if(xb+arr[xb-l]-1<r){
   arr[xb]=arr[xb-l];
  }
  else{
   for(x2=r+1-xb;xb+x2<(int)S.size();++x2){
    if(S[x2]!=S[xb+x2]) break;
   }
   arr[xb]=x2;
  }
  if(arr[xb]+xb-1>r){
   l=xb;
   r=arr[xb]+xb-1;
  }
 }
 reverse(arr,arr+(int)S.size());
}
void gethash(string S,int *arr){
 int xb,x2;
 arr[0]=S[0];
 for(xb=1;xb<(int)S.size();++xb){
  arr[xb]=arr[xb-1]*hs+(int)S[xb];
 }
}
inline int calh(int l,int r){
 return hsh[r]-(l?(hsh[l-1]*pw[r-l+1]):0);
}
int getpal(int pos){
 int revpos=n-1-pos,res=0,xb;
 pos+=n+1;
 for(xb=20;xb>=0;--xb){
  if(pos+res+(1<<xb)<=2*n+1 && revpos+res+(1<<xb)<=n && calh(pos,pos+res+(1<<xb)-1)==calh(revpos,revpos+res+(1<<xb)-1))
   res+=(1<<xb);
 }
 return res;
}
int main(){

    cin>>s;




 int xb,x2;
 pw[0]=1;
 n=(int)s.size();
 rs=s;
 for(xb=1;xb<=n*2+1;++xb) pw[xb]=pw[xb-1]*hs;
 reverse(rs.begin(),rs.end());
 getrevZ(rs+"#"+s,Z);
 gethash(rs+"#"+s,hsh);
 reverse(Z,Z+n);
 for(xb=0;xb<n;++xb){
  poss[xb]=make_pair(Z[xb],xb);
  UMAX(maxsuf,Z[xb]);
 }
 sort(poss,poss+n);
 x2=n-1;
 fill(mv,mv+n+1,2000000000);
 for(xb=maxsuf;xb>=0;--xb){
  mv[xb]=mv[xb+1];
  while(x2>=0 && poss[x2].first>=xb){
   UMIN(mv[xb],poss[x2].second);
   --x2;
  }
 }
 for(xb=maxsuf;xb>=0;--xb){
  mv[xb]=mv[xb]+xb;
 }

 for(xb=0;xb<n;++xb){
  int ln=getpal(xb),lb=xb-ln+1,rb=xb+ln-1,pos=upper_bound(mv,mv+maxsuf+1,lb)-mv-1;
  UMIN(pos,n-1-rb);
  UMAX(res,make_pair(pos*2+ln*2-1,make_pair(xb,pos)));

 }
 if(res.second.second==0){
  int ln=(res.first+1)/2,lb=res.second.first-ln+1,rb=res.second.first+ln-1;
  printf("1\n%d %d\n",lb+1,rb-lb+1);
 }
 else{
  printf("3\n");
  int ln=res.second.second,rb=mv[ln]-1,lb=rb-ln+1;
  printf("%d %d\n",lb+1,rb-lb+1);
  ln=(res.first-2*ln+1)/2,lb=res.second.first-ln+1,rb=res.second.first+ln-1;
  printf("%d %d\n%d %d\n",lb+1,rb-lb+1,n-res.second.second+1,res.second.second);
 }



    return 0;
}




typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned long UL;
typedef unsigned short US;
typedef pair < int , int > pii;
clock_t __stt;
inline void TStart(){__stt=clock();}
inline void TReport(){printf("\nTaken Time : %.3lf sec\n",(double)(clock()-__stt)/
# 16 "data/141.cpp" 3 4
                                                                                 ((__clock_t) 1000000)
# 16 "data/141.cpp"
                                                                                               );}
template < typename T > T MIN(T a,T b){return a<b?a:b;}
template < typename T > T MAX(T a,T b){return a>b?a:b;}
template < typename T > T ABS(T a){return a>0?a:(-a);}
template < typename T > void UMIN(T &a,T b){if(b<a) a=b;}
template < typename T > void UMAX(T &a,T b){if(b>a) a=b;}
string s,rs;
int n,Z[200005],sufmin[100005];
pii premax[100005];
LL oh[100005],rh[100005],mul[100005];
vector < pii > zs;
void gethash(){
 int i,j;
 mul[0]=1LL;
 for(i=1;i<=n;++i) mul[i]=mul[i-1]*257LL;
 oh[0]=(LL)s[0];
 for(i=1;i<n;++i){
  oh[i]=oh[i-1]*257LL +(LL)s[i];
 }
 rh[n-1]=(LL)s[n-1];
 for(i=n-2;i>=0;--i){
  rh[i]=rh[i+1]*257LL +(LL)s[i];
 }
}
void getZ(int l){
 int lb=-1,rb=-1,i,j;
 for(i=1;i<l;++i){
  if(i>rb){
   for(j=i;j<l;++j){
    if(rs[j]!=rs[j-i]) break;
   }
   Z[i]=j-i;
  }
  else{
   int p=i-lb;
   if(i+Z[p]-1<rb){
    Z[i]=Z[p];
   }
   else{
    for(j=rb;j<l;++j){
     if(rs[j]!=rs[j-i]) break;
    }
    Z[i]=j-i;
   }
  }
  if(i+Z[i]-1>rb){
   rb=i+Z[i]-1;
   lb=i;
  }
 }
}
bool palind(int l,int r){
 if(!l) return oh[r]==rh[l]-rh[r+1]*mul[r-l+1];
 return oh[r]-oh[l-1]*mul[r-l+1]==rh[l]-rh[r+1]*mul[r-l+1];
}
int maxpal(int cen){
 int low=1,high=MIN(cen+1,n-cen),mid;
 while(low<high){
  mid=((low+high+1)>>1);
  if(palind(cen-mid+1,cen+mid-1)) low=mid; else high=mid-1;
 }
 return low*2-1;
}
int res=0,l1=-1,r1=-1,l2=-1,r2=-1,l3=-1,r3=-1;
int main(){


    cin>>s;





 int i,j,k;
    n=(int)s.size();
 rs=s;
 reverse(rs.begin(),rs.end());
 rs+=s;
 getZ((int)rs.size());
 gethash();
 for(i=n;i<n*2;++i) zs.push_back(make_pair(i-n+Z[i],Z[i]));
 sort(zs.begin(),zs.end());
 premax[0]=make_pair(zs[0].second,zs[0].first-zs[0].second);
 for(i=1;i<n;++i) premax[i]=MAX(premax[i-1],make_pair(zs[i].second,zs[i].first-zs[i].second));
 sufmin[n-1]=zs[n-1].first-zs[n-1].second;
 for(i=n-2;i>=0;--i) sufmin[i]=MIN(sufmin[i+1],zs[i].first-zs[i].second);
 for(i=0;i<n;++i){
  int sl,ml=maxpal(i),lb=i-(ml+1)/2+1,rb=i+(ml+1)/2-1,cl=0;
  int p=lower_bound(zs.begin(),zs.end(),make_pair(lb+1,0))-zs.begin();--p;
  if(p>=0){
   cl=premax[p].first;
   sl=premax[p].second;
  }
  if(p<n-1 && lb-sufmin[p+1]>cl){
   cl=lb-sufmin[p+1];
   sl=sufmin[p+1];
  }
  UMIN(cl,n-rb-1);
  if(cl*2+ml>res){
   res=cl*2+ml;
   if(cl){
    l1=sl;r1=cl;
    l2=lb;r2=ml;
    l3=n-cl;r3=cl;
   }
   else{
    l1=lb;r1=ml;
    l2=l3=-1;
   }
  }
 }
 printf("%d\n",(int)(l1!=-1)+(int)(l2!=-1)+(int)(l3!=-1));
 if(l1!=-1) printf("%d %d\n",l1+1,r1);
 if(l2!=-1) printf("%d %d\n",l2+1,r2);
 if(l3!=-1) printf("%d %d\n",l3+1,r3);



    return 0;
}

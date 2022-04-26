}
# 5 "data/481.cpp" 2



# 7 "data/481.cpp"
using namespace __gnu_pbds;
using namespace std;

string str,s;
int n,k,p[200010],rk[200010],tmp[200010],sa[200010],lcp[200010];
int _n,dat[800010],pos[800010];

inline void manacher(){
 string t="@"+str+"$";
    int c=0,r=0;
    for(int i=1;i<t.size()-1;i++){
        int rev=2*c-i;
        if(r>i) p[i]=min(r-i,p[rev]);
        else p[i]=0;
        while(t[i+p[i]]==t[i-p[i]]) p[i]++;
        if(i+p[i]>r){
            c=i;
            r=i+p[i];
        }
    }
}

inline bool sa_cmp(int x,int y)
{
 if(rk[x]!=rk[y]) return rk[x]<rk[y];
 else{
  int rx=x+k,ry=y+k;
  if(rx<=n) rx=rk[rx];
  else rx=-1;
  if(ry<=n) ry=rk[ry];
  else ry=-1;
  return rx<ry;
 }
}

inline void sa_func()
{
 for(int i=0;i<=n;i++){
  sa[i]=i;
  if(i==n) rk[i]=-1;
  else rk[i]=(int)s[i];
 }
 for(k=1;k<=n;k*=2){
  sort(sa,sa+n+1,sa_cmp);
  tmp[sa[0]]=0;
  for(int i=1;i<=n;i++){
   tmp[sa[i]]=tmp[sa[i-1]];
   if(sa_cmp(sa[i-1],sa[i])) tmp[sa[i]]++;
  }
  for(int i=0;i<=n;i++){
   rk[i]=tmp[i];
  }
 }
}

inline void sa_lcp()
{
 for(int i=0;i<=n;i++) rk[sa[i]]=i;
 int h=0;
 lcp[0]=0;
 for(int i=0;i<n;i++){
  int j=sa[rk[i]-1];
  if(h>0) h--;
  for(;j+h<n&&i+h<n;h++){
   if(s[j+h]!=s[i+h]) break;
  }
  lcp[rk[i]-1]=h;
 }
}

inline void init(int x)
{
 _n=1;
 while(_n<x) _n*=2;
 for(int i=1;i<=2*_n;i++) dat[i]=0;
 for(int i=_n;i<2*_n;i++){
  pos[i]=i-_n+1;
 }
 for(int i=_n-1;i>=1;i--){
  pos[i]=pos[2*i];
 }
}

inline void update(int k,int val)
{
 k+=_n-1;
 dat[k]=val;
 while(k>1){
  k/=2;
  if(dat[k*2]>dat[k*2+1]) pos[k]=pos[k*2];
  else pos[k]=pos[k*2+1];
  dat[k]=max(dat[k*2],dat[k*2+1]);
 }
}

inline pair<int,int> query(int a,int b,int k,int l,int r)
{
 if(r<a||b<l) return make_pair(-1000000007,-1000000007);
 if(a<=l&&r<=b) return make_pair(dat[k],pos[k]);
 int mid=(l+r)/2;
 pair<int,int> vl=query(a,b,k*2,l,mid);
 pair<int,int> vr=query(a,b,k*2+1,mid+1,r);
 return max(vl,vr);
}

signed main()
{
 ios::sync_with_stdio(false);
 cin>>str;
 manacher();
 s=str+'#';reverse(str.begin(),str.end());s+=str;n=s.size();
 reverse(str.begin(),str.end());
 sa_func();sa_lcp();
 int id=rk[str.size()+1];
 init(str.size());
 for(int i=1;i<=str.size();i++) update(i,p[i]*2-1);
 vector<pair<int,int> > ans;
 int anslen=-1;
 for(int i=1;i<=str.size();i++) if(p[i]*2-1>anslen){
  anslen=p[i]*2-1;
  ans={{i-p[i]+1,p[i]*2-1}};
 }
 int minv=lcp[id-1];
 for(int i=id-1;i>=1;i--){
  if(sa[i]<str.size()){
   if(minv==0) continue;
   int l=sa[i]+minv+1,r=str.size()-minv;
   if(l>r){
    int len=str.size()-sa[i];
    if(len%2==0){
     len--;
     if(len>anslen){
      anslen=len;
      ans={{sa[i]+1,len/2},{sa[i]+1+len/2,1},{str.size()-len/2+1,len/2}};
     }
    }
    else{
     if(len>anslen){
      anslen=len;
      ans={{sa[i]+1,len}};
     }
    }
    minv=min(minv,lcp[i-1]);
    continue;
   }
   int L=1,R=(r-l+1)/2+1;
   while(L<=R)
   {
    int mid=(L+R)/2;
    int ll=l+mid-1,rr=r-mid+1;
    if(ll<=rr){
     pair<int,int> val=query(ll,rr,1,1,_n);
     if(val.first>=mid*2-1){
      int len=minv*2+mid*2-1;
      if(len>anslen){
       anslen=len;
       ans={{sa[i]+1,minv},{val.second-mid+1,mid*2-1},{str.size()-minv+1,minv}};
      }
      L=mid+1;
     }
     else{
      R=mid-1;
     }
    }
    else{
     R=mid-1;
    }
   }
  }
  minv=min(minv,lcp[i-1]);
 }
 minv=lcp[id];
 for(int i=id+1;i<=n;i++){
  if(sa[i]<str.size()){
   if(minv==0) continue;
   int l=sa[i]+minv+1,r=str.size()-minv;
   if(l>r){
    int len=str.size()-sa[i];
    if(len%2==0){
     len--;
     if(len>anslen){
      anslen=len;
      ans={{sa[i]+1,len/2},{sa[i]+1+len/2,1},{str.size()-len/2+1,len/2}};
     }
    }
    else{
     if(len>anslen){
      anslen=len;
      ans={{sa[i]+1,len}};
     }
    }
    minv=min(minv,lcp[i-1]);
    continue;
   }
   int L=1,R=(r-l+1)/2+1;
   while(L<=R)
   {
    int mid=(L+R)/2;
    int ll=l+mid-1,rr=r-mid+1;
    if(ll<=rr){
     pair<int,int> val=query(ll,rr,1,1,_n);
     if(val.first>=mid*2-1){
      int len=minv*2+mid*2-1;
      if(len>anslen){
       anslen=len;
       ans={{sa[i]+1,minv},{val.second-mid+1,mid*2-1},{str.size()-minv+1,minv}};
      }
      L=mid+1;
     }
     else{
      R=mid-1;
     }
    }
    else{
     R=mid-1;
    }
   }
  }
  minv=min(minv,lcp[i]);
 }
 cout<<ans.size()<<endl;
 for(int i=0;i<ans.size();i++) cout<<ans[i].first<<" "<<ans[i].second<<endl;
 return 0;
}

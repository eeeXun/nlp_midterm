 {
   this->pbump(__gnu_cxx::__numeric_traits<int>::__max);
   __off -= __gnu_cxx::__numeric_traits<int>::__max;
 }
      this->pbump(__off);
    }




  extern template class basic_stringbuf<char>;
  extern template class basic_istringstream<char>;
  extern template class basic_ostringstream<char>;
  extern template class basic_stringstream<char>;


  extern template class basic_stringbuf<wchar_t>;
  extern template class basic_istringstream<wchar_t>;
  extern template class basic_ostringstream<wchar_t>;
  extern template class basic_stringstream<wchar_t>;




}
# 1218 "/usr/include/c++/11.2.0/sstream" 2 3
# 16 "data/511.cpp" 2
# 32 "data/511.cpp"

# 32 "data/511.cpp"
using namespace std;
inline void read(int &x){
 x=0;char ch=getchar(),flag=0;
 while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
 if(ch=='-') flag=1,ch=getchar();
 while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
 if(flag) x=-x;
}
inline void read(int &x,int &y){read(x),read(y);}
inline void read(int &x,int &y,int &z){read(x),read(y),read(z);}

int n;
char s[200005];
int sa[200005],rank[200005],pos[200005],c[200005],tmp[200005],lcp[200005];
int res[200005],st[200005];

inline void getsa(){
 int m=30,tot;
 for(int i=1;i<=n;i++) s[i+n+1]=s[n-i+1];s[n+1]='z'+1;
 s[n*2+2]=0;n=n*2+1;
 for(int i=1;i<=n;i++) rank[i]=s[i]-'a'+1;
 for(int i=1;i<=m;i++) c[i]=0;
 for(int i=1;i<=n;i++) c[rank[i]]++;
 for(int i=1;i<=m;i++) c[i]+=c[i-1];
 for(int i=1;i<=n;i++)
  sa[c[rank[i]]]=i,c[rank[i]]--;
 for(int k=1;k<n;k<<=1){
  tot=0;
  for(int i=1;i<=m;i++) c[i]=0;
  for(int i=n-k+1;i<=n;i++) tmp[++tot]=i;
  for(int i=1;i<=n;i++) if(sa[i]>k) tmp[++tot]=sa[i]-k;
  for(int i=1;i<=n;i++) c[rank[i]]++;
  for(int i=1;i<=m;i++) c[i]+=c[i-1];
  for(int i=n;i;i--) sa[c[rank[tmp[i]]]]=tmp[i],c[rank[tmp[i]]]--;
  tmp[sa[1]]=1;
  for(int i=2;i<=n;i++){
   int p=sa[i],q=sa[i-1];
   tmp[p]=tmp[q];
   if(rank[p]!=rank[q]||rank[p+k]!=rank[q+k]) tmp[p]++;
  }
  m=tmp[sa[n]];if(m==n) break;
  memcpy(rank,tmp,sizeof(rank));
 }
}
inline void getlcp(){
 for(int i=1;i<=n;i++) pos[sa[i]]=i;
 int k=0;
 for(int i=1;i<=n;i++){
  if(k) k--;
  while(i+k<=n&&sa[pos[i]-1]+k<=n&&s[i+k]==s[sa[pos[i]-1]+k]) k++;
  lcp[pos[i]]=k;
 }
}
int p[100005];
inline void manacher(){
 int maxx=0,id=0;
 for(int i=1;i<=n;i++){
  if(maxx>i) p[i]=min(maxx-i,p[id-i+id]);
  else p[i]=1;
  while(i+p[i]<=n&&i>p[i]&&s[i+p[i]]==s[i-p[i]]) p[i]++;
  if(p[i]+i>maxx) maxx=p[i]+i,id=i;
 }
}

int main(){
 scanf("%s",s+1);n=strlen(s+1);
 getsa();getlcp();
 int bx2k=0;
 for(int i=1;i<=n;i++) if(sa[i]==n/2+2) bx2k=i;

 for(int i=bx2k+1;i<=n;i++){
  if(i!=bx2k+1) lcp[i]=min(lcp[i],lcp[i-1]);
  if(sa[i]<=n/2) res[sa[i]]=lcp[i];
 }
 for(int i=bx2k-1;i;i--){
  lcp[i]=min(lcp[i],lcp[i+1]);
  if(sa[i]<=n/2) res[sa[i]]=lcp[i+1];
 }

 n/=2;s[n+1]=0;
 for(int i=1;i<=n;i++) if(res[i-1]>res[i]){res[i]=res[i-1];st[i]=st[i-1];} else st[i]=i;

 manacher();
 int ans=0,x[5]={0},len[5]={0},k=0;
 for(int i=1;i<=n;i++){

  int l=1,r=min(n-i-p[i]+1,i-p[i])+1;
  while(l<r){
   int mid=l+r>>1;
   if(res[i-p[i]+1-mid]>=mid) l=mid+1; else r=mid;
  }
  r--;
  if(res[i-p[i]]==0) r=0;
  if(r*2+p[i]*2-1>ans){
   ans=r*2+p[i]*2-1;
   x[1]=i-p[i]+1;len[1]=p[i]*2-1;
   x[0]=st[i-p[i]-r+1];len[0]=r;
   x[2]=n-r+1;len[2]=r;
  }
 }

 if(len[2])printf("3\n%d %d\n%d %d\n%d %d\n",x[0],len[0],x[1],len[1],x[2],len[2]); else printf("1\n%d %d\n",x[1],len[1]);
 return 0;
}

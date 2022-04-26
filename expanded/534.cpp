


  template<typename _Key, typename _Val, typename _Cmp1, typename _Alloc,
    typename _Cmp2>
    struct
    _Rb_tree_merge_helper<std::multimap<_Key, _Val, _Cmp1, _Alloc>,
     _Cmp2>
    {
    private:
      friend class std::multimap<_Key, _Val, _Cmp1, _Alloc>;

      static auto&
      _S_get_tree(std::map<_Key, _Val, _Cmp2, _Alloc>& __map)
      { return __map._M_t; }

      static auto&
      _S_get_tree(std::multimap<_Key, _Val, _Cmp2, _Alloc>& __map)
      { return __map._M_t; }
    };



}
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
# 18 "data/534.cpp" 2

# 18 "data/534.cpp"
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uin;
# 49 "data/534.cpp"
char s[200100],st[200100];
int lens,l[200100];
void manacher(char *s,int lens){
    int lenst=0;
    st[lenst++]='#';
    for (int i = 0; i < lens; i++){
        st[lenst++]=s[i];
        st[lenst++]='#';
    }
    st[lenst]='\0';
    int maxto=0,lastpos=0;
    for (int i = 0; i < lenst; i++){
        l[i]=i<maxto?min(l[2*lastpos-i],maxto-i):1;
        while(i-l[i]>=0 && i+l[i]<lenst && st[i-l[i]]==st[i+l[i]]) l[i]++;
        if(i+l[i]>maxto){
            maxto=i+l[i];
            lastpos=i;
        }

    }
    for (int i = 0; i < lens; i++){
        l[i]=l[i<<1|1]-1;
    }
}
int fail[200100],p[200100];
void kmp(char *s,int lens){
    int lenst=0;
    for (int i = lens-1; i >= 0; i--){
        st[lenst++]=s[i];
    }
    st[lenst++]='#';
    for (int i = 0; i < lens; i++){
        st[lenst++]=s[i];
    }
    st[lenst]='\0';
    int i=0,j;
    fail[0]=j=-1;
    while(i<lenst){
        if(j==-1 || st[i]==st[j]){
            fail[i+1]=j+1;
            i++;
            j=j+1;
        }
        else j=fail[j];
    }
    for (int i = 0; i < lens; i++){
        fail[i]=fail[i+1+lens+1];
    }
    int maxi=-1,lastp=0;
    for (int i = 0; i < lens; i++){
        if(fail[i]>maxi){
            maxi=fail[i];
            p[i]=i;
            lastp=i;
        }
        else p[i]=p[i-1];
    }
}
int ansp1,ansp2,ansp3;
int ansl1,ansl2,ansl3;
int maxilen,lent;
int main(){

    scanf("%s",s);
    lens=(int)strlen(s);
    manacher(s,lens);
    kmp(s,lens);
    maxilen=-1;
    int l1=0,p1=0,maxil=0;
    for (int i = 0; i < lens; i++){
        l1=l[i]>>1;
        if(i-l1-1<0){
            lent=l[i];
            maxil=0;
        }
        else{
            p1=p[i-l1-1];
            maxil=min(fail[p1],lens-(i+l1)-1);
            lent=l[i]+(maxil<<1);
        }
        if(lent<=maxilen) continue;
        maxilen=lent;
        if(maxil==0){
            ansp2=i-l1;
            ansl2=l[i];
            ansp1=ansp3=-1;
        }
        else{
            p1=p1-fail[p1]+1;
            ansp1=p1;
            ansl1=maxil;
            ansp2=i-l1;
            ansl2=l[i];
            ansp3=lens-maxil;
            ansl3=ansl1;
        }
    }
    if(ansp1==-1){
        printf("%d\n",1);
        printf("%d %d\n",ansp2+1,ansl2);
    }
    else{
        printf("%d\n",3);
        printf("%d %d\n",ansp1+1,ansl1);
        printf("%d %d\n",ansp2+1,ansl2);
        printf("%d %d\n",ansp3+1,ansl3);
    }
}

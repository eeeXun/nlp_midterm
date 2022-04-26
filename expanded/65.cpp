    {
      std::basic_string<_CharT, _Traits> __tmp;



      const ctype<_CharT>& __ct = use_facet<ctype<_CharT> >(__os.getloc());
      __x._M_copy_to_string(__tmp, __ct.widen('0'), __ct.widen('1'));
      return __os << __tmp;
    }



}







namespace std __attribute__ ((__visibility__ ("default")))
{




  template<size_t _Nb>
    struct hash<std::bitset<_Nb>>
    : public __hash_base<size_t, std::bitset<_Nb>>
    {
      size_t
      operator()(const std::bitset<_Nb>& __b) const noexcept
      {
 const size_t __clength = (_Nb + 8 - 1) / 8;
 return std::_Hash_impl::hash(__b._M_getdata(), __clength);
      }
    };

  template<>
    struct hash<std::bitset<0>>
    : public __hash_base<size_t, std::bitset<0>>
    {
      size_t
      operator()(const std::bitset<0>&) const noexcept
      { return 0; }
    };


}
# 15 "data/65.cpp" 2
# 38 "data/65.cpp"

# 38 "data/65.cpp"
using namespace std;
int n,k,X,Y,kk,seqlen;
vector<int> ln_palindrome(char *seq){
   seqlen = strlen(seq);
  vector <int> p;
  int i=0,palLen=0,s,e,d;
  while(i < seqlen){
    if(i>palLen && seq[i-palLen-1]==seq[i]){
      palLen+=2; i++; continue;
    }
    p.push_back(palLen);

    s = p.size()-2;
    e = s - palLen;
    bool fl = true;
    for(int j=s;j!=e;j--){
      d = j - e - 1;
      if(p[j]==d){
        palLen = d; fl=false; break;
      }
      p.push_back(min(d,p[j]));
    }
    if(fl) palLen=1,i+=1;
  }
  p.push_back(palLen);
  s = p.size()-2;
  e = s- (2*seqlen + 1 - p.size());
  for(int i=s;i!=e;i--){
    d = i - e - 1;
    p.push_back(min(d,p[i]));
  }
  return p;
}

vector<int> p;
char s[100005];
int wei[100005],pl[100005],fail[100005];
void kp(){

}
void arr(){
 int last=0,len=0;

 fail[0]=0;
 for(int i=1,k=0,j;i<seqlen;i++){
  while(k>0&&s[seqlen-1-i]!=s[seqlen-1-k])
  k = fail[k-1];
  if(s[seqlen-1-i]==s[seqlen-1-k]) k++;
  fail[i]=k;
 }




 int qq=0;
 for(int i=0;i<seqlen;i++){
  while(qq>0 && s[i]!=s[seqlen-1-qq])
    qq = fail[qq-1];
  if(s[i] == s[seqlen-1-qq]){
   qq++;
  }
# 115 "data/65.cpp"
  if(qq>len){
   len = qq; wei[i]=i; last=i;
  }else {
   wei[i] = last;
  }
  pl[i]=len;
 }
}
int st[3],ed[3];
main(){
 scanf("%s",s);
 p = ln_palindrome(s);
 arr();


 int index,left,right,mx=-1,K;
 for(int i=1;i<p.size();i+=2){
  index = (i-1)/2;
  int ll = p[i];
  left = index - p[i]/2 - 1; right = index + p[i]/2 + 1;
  if(left<0 || right>seqlen-1){
   if(ll > mx){
    mx = ll; K=1; st[0]=left+1; ed[0]=ll;
   }
   continue;
  }
  int minl = min(seqlen-right,pl[left]);
  if(2*minl + ll > mx){
   mx = 2*minl + ll;
   if(minl==0){
    K=1; st[0]=left+1; ed[0]=ll;
   }else{
    K=3;
    st[0]=wei[left]-minl+1; ed[0]=minl;
    st[1]=left+1; ed[1]=ll;
    st[2]=seqlen-minl; ed[2]=minl;
   }
  }
 }
 printf("%d\n",K);
 for(int i=0;i<K;i++) printf("%d %d\n",st[i]+1,ed[i]);


}

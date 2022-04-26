 vect.clear();
 int n,m;
 cerr<<"Two integers wnated"<<endl;
 in>>n>>m;
 vect.resize(n);
 cerr<<"A matrix "<<n<<" X "<<m<<" wanted"<<endl;
 for(int i=0;i<n;i++)
 {
  vect[i].resize(m);
  for(int j=0;j<m;j++)in>>vect[i][j];
 }
 return in;
}



template<typename T>
inline void updateMax(T& a,const T& b){a=max(a,b);}
template<typename T>
inline void updateMin(T& a,const T& b){a=min(a,b);}
template<typename T>
inline vector<T> erase(vector<T> table,int ind)
{
 
# 120 "data/260.cpp" 3 4
(static_cast <bool> (
# 120 "data/260.cpp"
ind<table.size()
# 120 "data/260.cpp" 3 4
) ? void (0) : __assert_fail (
# 120 "data/260.cpp"
"ind<table.size()"
# 120 "data/260.cpp" 3 4
, "data/260.cpp", 120, __extension__ __PRETTY_FUNCTION__))
# 120 "data/260.cpp"
                        ;
 table.erase(table.begin()+ind);
 return table;
}
template<typename T>
vector<T> unique(vector<T> table)
{
 sort(table.begin(),table.end());
 return vector<T>(table.begin(),unique(table.begin(),table.end()));
}


template<class T>
vector<T> parse(const string& ss,const char* cut=" ")
{
 vector<T> re;
 for(int j=0;j<ss.size();j++)
 {
  string s;
  while(j<ss.size()&&
# 139 "data/260.cpp" 3 4
                    __null
# 139 "data/260.cpp"
                        ==strchr(cut,ss[j]))
   s+=ss[j++];
  if(!s.empty())
  {
   T tmp;
   istringstream is(s);
   is>>tmp;
   re.push_back(tmp);
  }
 }
 return re;
}


int countBit(int n)
{
 int re=0;
 while(n)re++,n^=((((n)^((n)-1))&n));
 return re;
}

int MSB(int n)
{
 if(n==0)return 0;
 while(((((n)^((n)-1))&n))!=n)n^=((((n)^((n)-1))&n));
 return n;
}
void initHash(int n,int hash[])
{
 for(int i=0;i<n;i++)
  hash[((1)<<(i))]=i;
}
void initBcnt(int n,int bcnt[])
{
 bcnt[0]=0;
 for(int i=1;i<((1)<<(n));i++)
  bcnt[i]=bcnt[i^((((i)^((i)-1))&i))]+1;
}




template<typename T>
T __gcd(T n,T m,T& a,T& b)
{
 T a1=0,b1=1;
 a=1,b=0;

 while(m)
 {
  T c=n/m;
  T r=n-m*c;
  T t;
  t=a;a=a1;a1=t-c*a1;
  t=b;b=b1;b1=t-c*b1;
  n=m;m=r;
 }
 return n;
}


struct Node
{
 int r,c,d;
 int v;
 Node(int x,int y,int z,int v1):r(x),c(y),d(z),v(v1){};
 bool operator<(const Node& other)const
 {
  return v>other.v;
 };
};

priority_queue<Node> heap;


const int dir[][2]={{-1,0},{0,1},{1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
const char dname[]="NWSE";



vector<int> KMPmatch(const vector<int>& text,const vector<int>& pattern)
{
 const int n=text.size();
 const int m=pattern.size();
 
# 223 "data/260.cpp" 3 4
(static_cast <bool> (
# 223 "data/260.cpp"
m
# 223 "data/260.cpp" 3 4
) ? void (0) : __assert_fail (
# 223 "data/260.cpp"
"m"
# 223 "data/260.cpp" 3 4
, "data/260.cpp", 223, __extension__ __PRETTY_FUNCTION__))
# 223 "data/260.cpp"
         ;
 vector<int> fail(m);
 fail[0]=-1;
 for(int i=1,k=-1;i<pattern.size();i++)
 {
  while(k!=-1&&pattern[k+1]!=pattern[i])k=fail[k];
  if(pattern[k+1]==pattern[i])k++;
  fail[i]=k;
 }
 vector<int> ret;
 for(int i=0,k=-1;i<n;i++)
 {
  while(k!=-1&&text[i]!=pattern[k+1])k=fail[k];
  if(pattern[k+1]==text[i])k++;
  if(k==m-1)ret.push_back(i-m+1),k=fail[k];
 }
 return ret;
}



void extended_kmp(int pattern[],int n,int extend[])
{
 extend[0]=1;


 int reach=0,idx=0;
 for(int i=1;i<n;i++)
 {
  int p=0;
  if(reach>=i)p=min(reach+1-i,extend[i-idx]);
  while(p+i<n&&pattern[p]==pattern[p+i])p++;
  extend[i]=p;
  if(p+i-1>reach)reach=p+i-1,idx=i;
 }
 extend[0]=n;
}


void longest_common_prefix(int pattern[],int n,int text[],int m,int extend[]=
# 262 "data/260.cpp" 3 4
                                                                            __null
# 262 "data/260.cpp"
                                                                                )
{
 bool allo=false;
 if(extend==
# 265 "data/260.cpp" 3 4
           __null
# 265 "data/260.cpp"
               )
 {
  allo=true;
  extend=new int[n];
  extended_kmp(pattern,n,extend);
 }
 int idx=-1,reach=-1;
 for(int i=0;i<m;i++)
 {
  int p=i;
  if(reach>=i)p=min(reach+1,extend[i-idx]+i);
  while(p-i<n&&pattern[p-i]==text[p])p++;
  text[i]=p-i;
  if(reach<p-1)reach=p-1,idx=i;
 }
 if(allo)delete [] extend;
}


void palindrom_extend(int str[],int n,int extend[])
{

 int idx=0,reach=0;
 extend[0]=0;
 for(int i=1;i<n;i++)
 {
  int len=0;
  if(reach>i)len=min(reach-i,extend[2*idx-i]);
  while(i-len-1>=0&&i+len+1<n&&str[i-len-1]==str[i+len+1])len++;
  extend[i]=len;
  if(reach<extend[i]+i)
  {
   reach=extend[i]+i;
   idx=i;
  }
 }
}
char str[100001],rstr[100001];
int buf[100000],extend[100000],fail[100000];
int match[100000],pos[100000];

int main()
{
 gets(str);
 const int n=strlen(str);



 for(int i=0;i<n;i++)
 {

  buf[i]=str[i];
  rstr[i]=str[i];
 }


 reverse(rstr,rstr+n);
 palindrom_extend(buf,n,extend);

 fail[0]=-1;
 for(int i=1,p=-1;i<n;i++)
 {
  while(p!=-1&&rstr[p+1]!=rstr[i])p=fail[p];
  if(rstr[p+1]==rstr[i])p++;
  fail[i]=p;
 }
 for(int i=0,p=-1;i<n;i++)
 {
  while(p!=-1&&rstr[p+1]!=str[i])p=fail[p];
  if(rstr[p+1]==str[i])p++;
  while(p+1+i+1>n)p=fail[p];
  pos[i]=i;match[i]=p+1;

  if(i&&match[i]<match[i-1])
  {
   match[i]=match[i-1];
   pos[i]=pos[i-1];
  }
 }

 int x1=0,l1=0,x2=0,l2=0,x3=0,l3=0;
 int best=0;
 for(int i=0;i<n;i++)
 {

  int ll=i-extend[i]-1;
  int rr=i+extend[i]+1;
  int p=0,pl=0;
  int s=0,sl=0;
  if(ll>=0&&rr<n)
  {
   int len=min(match[ll],n-rr);
   p=pos[ll]-len+1;
   
# 358 "data/260.cpp" 3 4
  (static_cast <bool> (
# 358 "data/260.cpp"
  p>=0
# 358 "data/260.cpp" 3 4
  ) ? void (0) : __assert_fail (
# 358 "data/260.cpp"
  "p>=0"
# 358 "data/260.cpp" 3 4
  , "data/260.cpp", 358, __extension__ __PRETTY_FUNCTION__))
# 358 "data/260.cpp"
              ;
   s=n-len;
   pl=sl=len;
  }
  if(pl+sl+2*extend[i]+1>best)
  {
   best=pl+sl+2*extend[i]+1;





   x1=p,l1=pl;
   x2=ll+1,l2=2*extend[i]+1;
   x3=s,l3=sl;
  }
 }
 
# 375 "data/260.cpp" 3 4
(static_cast <bool> (
# 375 "data/260.cpp"
l2
# 375 "data/260.cpp" 3 4
) ? void (0) : __assert_fail (
# 375 "data/260.cpp"
"l2"
# 375 "data/260.cpp" 3 4
, "data/260.cpp", 375, __extension__ __PRETTY_FUNCTION__))
# 375 "data/260.cpp"
          ;
 int ans=0;
 if(l1)ans++;
 if(l2)ans++;
 if(l3)ans++;
 cout<<ans<<endl;
 if(l1)cout<<x1+1<<" "<<l1<<endl;
 cout<<x2+1<<" "<<l2<<endl;
 if(l3)cout<<x3+1<<" "<<l3<<endl;
 return 0;
 
# 385 "data/260.cpp" 3 4
(static_cast <bool> (
# 385 "data/260.cpp"
l1==l3
# 385 "data/260.cpp" 3 4
) ? void (0) : __assert_fail (
# 385 "data/260.cpp"
"l1==l3"
# 385 "data/260.cpp" 3 4
, "data/260.cpp", 385, __extension__ __PRETTY_FUNCTION__))
# 385 "data/260.cpp"
              ;
 for(int i=0;i<l2;i++)
# 386 "data/260.cpp" 3 4
                     (static_cast <bool> (
# 386 "data/260.cpp"
                     str[i+x2]==str[x2+l2-i-1]
# 386 "data/260.cpp" 3 4
                     ) ? void (0) : __assert_fail (
# 386 "data/260.cpp"
                     "str[i+x2]==str[x2+l2-i-1]"
# 386 "data/260.cpp" 3 4
                     , "data/260.cpp", 386, __extension__ __PRETTY_FUNCTION__))
# 386 "data/260.cpp"
                                                      ;
 for(int i=0;i<l1;i++)
# 387 "data/260.cpp" 3 4
                     (static_cast <bool> (
# 387 "data/260.cpp"
                     str[x1+i]==str[x3+l1-1-i]
# 387 "data/260.cpp" 3 4
                     ) ? void (0) : __assert_fail (
# 387 "data/260.cpp"
                     "str[x1+i]==str[x3+l1-1-i]"
# 387 "data/260.cpp" 3 4
                     , "data/260.cpp", 387, __extension__ __PRETTY_FUNCTION__))
# 387 "data/260.cpp"
                                                      ;
 return 0;
}

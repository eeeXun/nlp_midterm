using namespace std;
typedef unsigned long long ull;
typedef map <int, int>::iterator mit;
const int N=110000;
const int inf=1e9;
const ull P=31;
ull p[N],hl[N],hr[N];
char s[N];
int lpos[N],rpos[N];
struct Best {
 int len,suf,pref,middle,bsuf,bpref,bmiddle;
} best;
int main () {

        freopen ("input.txt","r",
# 24 "data/320.cpp" 3 4
                                stdin
# 24 "data/320.cpp"
                                     );
        freopen ("output.txt","w",
# 25 "data/320.cpp" 3 4
                                 stdout
# 25 "data/320.cpp"
                                       );

  scanf("%s",s+1);
  int n=strlen(s+1);

  p[1]=1;
  for (int i=2; i<=n; i++) p[i]=p[i-1]*P;
  for (int i=1; i<=n; i++) hl[i]=hl[i-1]+(s[i]-'a'+1)*p[i];
  for (int i=n; i>=1; i--) hr[i]=hr[i+1]+(s[i]-'a'+1)*p[n-i+1];


  lpos[0]=1;
  rpos[0]=0;
  for (int l=1; l<=n/2; l++) {
   lpos[l]=lpos[l-1];
   rpos[l]=rpos[l-1]+1;
   while (rpos[l]<n-l+1 && hl[rpos[l]]-hl[lpos[l]-1]!=hr[n-l+1]*p[lpos[l]]) lpos[l]++, rpos[l]++;
   if (rpos[l]>=n-l+1) {
    for (int l2=l; l2<=n/2; l2++) lpos[l2]=rpos[l2]=inf;
    break;
   }
  }
  for (int l=n/2+1; l<=n; l++) lpos[l]=rpos[l]=inf;

  for (int i=1; i<=n; i++) {
   int l=0, r=min(i-1,n-i)+1;
   while (r-l>1) {
    int m=(l+r)/2;
    ull left=hl[i-1]-hl[i-m-1];
    ull right=hr[i+1]-hr[i+m+1];
    if (n-(i+m)>(i-m)-1) left*=p[(n-(i+m)) - ((i-m)-1) + 1];
    else right*=p[((i-m)-1) - (n-(i+m)) + 1];
    if (left==right) l=m;
    else r=m;
   }
   int middle=l,maxsuf=n-(i+middle), maxpref=i-middle-1;

   l=0, r=maxsuf+1;
   while (r-l>1) {
    int m=(l+r)/2;
    if (rpos[m]<=maxpref) l=m;
    else r=m;
   }
   int suf=l;
   if (2*suf+2*middle+1>best.len) {
    best.len=2*suf+2*middle+1;
    best.suf=best.pref=suf;
    best.middle=2*middle+1;
    best.bsuf=n-suf+1;
    best.bpref=lpos[suf];
    best.bmiddle=i-middle;
   }
  }
  int k=(best.suf?1:0)+(best.pref?1:0)+(best.middle?1:0);
  cout<<k<<endl;
  if (best.pref) cout<<best.bpref<<" "<<best.pref<<endl;
  if (best.middle) cout<<best.bmiddle<<" "<<best.middle<<endl;
  if (best.suf) cout<<best.bsuf<<" "<<best.suf<<endl;

}

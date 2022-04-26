    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/791.cpp" 2

# 2 "data/791.cpp"
using namespace std;
# 11 "data/791.cpp"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N=101010;

char s[N], t[N];
int n;
int ns[N], nt[N], pa[N<<1], ma[N][22];

void kmp(char *s,int *ns,char *t,int *nt){
    int lens = strlen(s);
    int lent = strlen(t);
    nt[0] = -1;
    for(int i=0,j=-1;i<lens;++i){
        while(j >= 0 && s[i] != t[j + 1]) j = nt[j];
        if(s[i] == t[j + 1]) ++j;
        ns[i] = j;
        if(j + 1 == lent) j = nt[j];
    }
}
void KMP(){
    kmp(t+1,nt+1,t,nt);
    kmp(s,ns,t,nt);
}

void Manacher(char *s,int n,int *pa){
    pa[0] = 1;
    for(int i=1,j=0;i<(n<<1)-1;++i){
        int p = i >> 1 , q = i - p , r = ((j + 1)>>1) + pa[j] - 1;
        pa[i] = r < q ? 0 : min(r - q + 1 , pa[(j<<1) - i]);
        while(0 <= p - pa[i] && q + pa[i] < n && s[p - pa[i]] == s[q + pa[i]])
            pa[i]++;
        if(q + pa[i] - 1 > r) j = i;
    }
}

int st_ma(int l,int r) {
 if(l>r) return 0;
 ++l;++r;
 int _=log2(r-l+1);
 return max(ma[l][_], ma[r-(1<<_)+1][_]);
}

int calc(int st,int ed) {
 int ans=0;
 int l=0, r=(ed-st)/2;
 while(l<=r) {
  int mid=l+r>>1;
  if(st_ma(st+mid, ed-mid)>=mid) {
   ans=mid;
   l=mid+1;
  } else {
   r=mid-1;
  }
 }
 return ans*2+1;
}

int main() {

 while(~scanf("%s",s)) {

  n=strlen(s);
  for(int i=(0); i<(n); i++) t[n-1-i]=s[i];t[n]='\0';
  KMP();
  Manacher(s, n, pa);
  for(int i=(1); i<(n+1); i++) ma[i][0]=pa[(i-1)<<1]-1;
  for(int i=1;(1<<i)<=n;++i) {
   for(int j=1;j+(1<<i)-1<=n;++j) {
    ma[j][i]=max(ma[j][i-1], ma[j+(1<<(i-1))][i-1]);
   }
  }
  int ans=calc(0, n-1), len=0, al=0, ar=n-1, l=0, r=n;
  for(int i=(0); i<(n/2+1); i++) {
   --r;
   while(ns[l]<i-1&&l<r-1) ++l;
   if(ns[l]<i-1) break;

   int mid=calc(l+1, r);
   if(mid<=0) break;
   int res=i*2+mid;
   if(res>ans) {
    ans=res;
    len=i;
    al=l+1;
    ar=r;
   }
  }
  int sm=0, lm=(ans-len*2)/2;
  for(int i=(al+lm); i<(ar-lm+1); i++) if(ma[i+1][0]>=lm) {
   sm=i-lm;
   break;
  }
  if(len) {
   puts("3");
   printf("%d %d\n",al-len+1,len);
   printf("%d %d\n",sm+1,lm*2+1);
   printf("%d %d\n",ar+2,len);
  } else {
   puts("1");
   printf("%d %d\n",sm+1,lm*2+1);
  }
 }
 return 0;
}

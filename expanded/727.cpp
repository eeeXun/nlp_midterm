  using ::strcat;
  using ::strcmp;
  using ::strcoll;
  using ::strcpy;
  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;
# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 13 "data/727.cpp" 2
# 26 "data/727.cpp"

# 26 "data/727.cpp"
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> II;
typedef long long LL;


char s[110000];
int n;
int r[110000], f[110000], g[110000];
int hash[110000], rhash[110000], p=1000000007, pp[110000];

void palindrome(){
 int i=1, k=0;
 while(i<=n){
  while(i-k>0 && i+k<=n && s[i-k]==s[i+k])
   k++;
  r[i]=k;
  int j=1;
  while(j<k && k-j!=r[i-j])
   r[i+j]=min(k-j,r[i-j]), j++;
  i=i+j;
  k=k-j;
 }
}

int Hash(int l, int r){
 return (hash[r]-hash[l-1])*pp[n-r];
}

int rHash(int l, int r){
 return (rhash[l]-rhash[r+1])*pp[l-1];
}

int main(){
 scanf("%s",s+1);
 n=strlen(s+1);

 pp[0]=1;
 for (int i=(1); i<=(n); i++) pp[i]=pp[i-1]*p, hash[i]=hash[i-1]+pp[i]*(s[i]-'a'+1);
 for (int i=(n); i>=(1); i--) rhash[i]=rhash[i+1]+pp[n-i+1]*(s[i]-'a'+1);

 palindrome();

 int now=1;
 for (int i=(1); i<=(n); i++){
  while(now+i-1<n-i+1){
   if (Hash(now,now+i-1)==rHash(n-i+1,n))
    break;
   now++;
  }
  if (now+i-1<n-i+1)
   if (f[now+i-1]<i){
    f[now+i-1]=i;
    g[now+i-1]=now+i-1;
   }
 }
 for (int i=(1); i<=(n); i++)
  if (f[i-1]>f[i]) f[i]=f[i-1], g[i]=g[i-1];

 int ans=0;
 string means;
 for (int i=(1); i<=(n); i++){
  int now=r[i]*2-1+2*min(n-(i+r[i]-1), f[i-r[i]]);
  if (now>ans){
   ans=now;
   stringstream o;
   int k=min(n-(i+r[i]-1), f[i-r[i]]);
   if (k==0) o<<1<<endl<<i-r[i]+1<<" "<<2*r[i]-1<<endl;
    else{
     o<<3<<endl;
     o<<g[i-r[i]]-k+1<<" "<<k<<endl;
     o<<i-r[i]+1<<" "<<2*r[i]-1<<endl;
     o<<n-k+1<<" "<<k<<endl;
    }
   means=o.str();
  }
 }
 cout<<means;

    return 0;
}

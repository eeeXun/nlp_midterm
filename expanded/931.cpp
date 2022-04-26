                        stdin
# 8 "data/931.cpp"
                             );
 freopen("tricky.out","w",
# 9 "data/931.cpp" 3 4
                         stdout
# 9 "data/931.cpp"
                               );
}
typedef unsigned ull;
const int MAXN=100110;
const ull base=29;
ull hl[MAXN],hr[MAXN],pw[MAXN];
int f[MAXN],dl[MAXN],g[MAXN],m[MAXN],len;
char s1[MAXN];
ull hash(int s,int e){
 if(s<e) return hl[e]-hl[s]*pw[e-s];
 else return hr[e]-hr[s]*pw[s-e];
}
int calc(int x){
 int s=x-f[x]+1,e=x+f[x]-1;
 return f[x]*2-1+min(g[m[s-1]],len-e)*2;
}
int s,e;
int main(){

 scanf("%s",s1+1);
 len=strlen(s1+1);
 for (int i=1;i<=len;i++){
  hl[i]=hl[i-1]*base+s1[i];
 }
 for (int i=len;i>=1;i--){
  hr[i]=hr[i+1]*base+s1[i];
 }
 pw[0]=1;
 for (int i=1;i<=len;i++){
  pw[i]=pw[i-1]*base;
 }


 for (int i=1;i<=len;i++){
  s=1;
  e=min(i,len-i+1);
  while (s!=e){
   int mid=s+e-(s+e)/2;
   if(hash(i,i+mid-1)==hash(i,i-mid+1))
    s=mid;
   else
    e=mid-1;
  }
  f[i]=s;
 }
 s=1;
 e=0;



 for (int i=1;i<=len;i++){
  if(s1[i]==s1[len]) dl[++e]=i;
  while (s<=e&&hash(dl[s],i)!=hash(len,len-(i-dl[s]))&&len-(i-dl[s])>i) s++;
  if(s>e) g[i]=0;
  else g[i]=i-dl[s]+1;
 }
 int ans=0;
 for (int i=1;i<=len;i++){
  m[i]=m[i-1];
  if(g[m[i]]<g[i]) m[i]=i;
 }
 for (int i=1;i<=len;i++){
  ans=max(ans,calc(i));
 }
 for (int i=1;i<=len;i++){
  if(ans==calc(i)){
   s=i-f[i]+1;
   e=i+f[i]-1;
   int j=min(g[m[s-1]],len-e);
   int k=m[s-1]-g[m[s-1]]+1;
   if(j) cout<<3<<endl
     <<k<<' '<<j<<endl
     <<s<<' '<<e-s+1<<endl
     <<len-j+1<<' '<<j<<endl;
   else cout<<1<<endl<<s<<' '<<e-s+1<<endl;
   return 0;
  }

 }
 return 0;
}

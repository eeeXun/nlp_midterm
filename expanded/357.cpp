using namespace std;
const int N=2e5+50;

int n,m,len[N],id[N],f[N],ex[N],nxt[N],ans;
int Lp,Ll,Mp,Ml,Rp,Rl;
char s[N],t[N];

inline void manacher()
{
 int i,j,ct=0,mx=0;
    for(i=1;i<=n;++i){
     for(j=mx>i?min(mx-i,f[(ct<<1)-i]):1;s[i+j]==s[i-j];++j);
     f[i]=j;if(i+j>mx) mx=i+j,ct=i;
    }
    for(m=0,i=2;i<n;i+=2) ex[++m]=f[i]>>1;
}

int main(){
 int i,j,kmp=0,res;
 scanf("%s",t+1);
 m=strlen(t+1);
 s[0]='!';
 for(i=1;i<=m;++i) s[++n]='#',s[++n]=t[i];
 s[++n]='#';s[++n]='?';manacher();
 t[m+1]='#';for(i=1;i<=m;++i) t[m+i+1]=t[i];
 reverse(t+1,t+m+1);j=m+m+1;
 for(i=2;i<=j;++i){
  for(;kmp&&(t[kmp+1]!=t[i]);kmp=nxt[kmp]);
  kmp+=(t[kmp+1]==t[i]);nxt[i]=kmp;
 }
 for(i=1;i<=m;++i){
  len[i]=len[i-1];id[i]=id[i-1];
  f[i]=nxt[m+i+1];
  if(f[i]>len[i]) len[i]=f[i],id[i]=i;
  j=ex[i];res=min(len[i-j],m-i-j+1);
  if((res<<1)+(j<<1)-1>ans){
   ans=(res<<1)+(j<<1)-1;
   Mp=i-j+1;Ml=(j<<1)-1;
   if(res){Ll=Rl=res;Lp=id[i-j]-res+1;Rp=m-res+1;}
   else Ll=Rl=0;
  }
 }
 puts((Ll&&Rl)?"3":"1");
 if(Ll) printf("%d %d\n",Lp,Ll);
 printf("%d %d\n",Mp,Ml);
 if(Rl) printf("%d %d\n",Rp,Rl);
}

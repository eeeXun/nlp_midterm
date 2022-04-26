
# 4 "data/241.cpp"
typedef int arr[100010];
char a[100010],b[100010];
arr next,p,l,fl,fr;
int n,ansl,ansm,tot;
int min(int a, int b){
 return a<b?a:b;
}
void kmp(void){
 next[1]=0;
 int i,j;
 for (i=2,j=0;i<=n;i++){
  for (;j&&b[j+1]!=b[i];j=next[j]);
  if (b[j+1]==b[i]) j++;
  next[i]=j;
 }
 for (i=1,j=0;i<=n;i++){
  for (;j&&b[j+1]!=a[i];j=next[j]);
  if (b[j+1]==a[i]) j++;
  if (j&&!l[j]){
   if (i<n-j+1){
    l[j]=i;
   }
  }
 }
 for (tot=1;l[tot];tot++);
 tot--;
}
void manacher(void){
 int max=0;
 int mpos=0;
 a[0]='$';
 a[n+1]='#';
 for (int i=1;i<=n;i++){
  if (max>i&&i+p[mpos*2-i]-1<max){
   p[i]=p[mpos*2-i];
  }
  else{
   int x,y;
   for (x=i-1,y=i+1;a[x]==a[y];x--,y++);
   p[i]=y-i;
   max=y-1;
   mpos=i;
  }
 }
}
void getans(void){
 int cur=1;
 int i;
 fl[0]=fr[n+1]=0;
 for (i=1;i<=tot;i++) fl[l[i]]=i;
 for (i=1;i<=n;i++) fl[i]=fl[i]?fl[i]:fl[i-1];
 for (i=n;i>n-tot;i--) fr[i]=n-i+1;
 for (i=1;i<=n-tot;i++) fr[i]=tot;

 int max=0;
 for (i=1;i<=n;i++){
  int temp=min(fl[i-p[i]],fr[i+p[i]]);
  if (2*temp+2*p[i]-1>max){
   max=2*temp+2*p[i]-1;
   ansl=temp;
   ansm=i;
  }
 }
}
void print(void){
 if (ansl==0) printf("1\n%d %d\n",ansm-p[ansm]+1,2*p[ansm]-1);
 else printf("3\n%d %d\n%d %d\n%d %d\n",l[ansl]-ansl+1,ansl,
 ansm-p[ansm]+1,2*p[ansm]-1,n-ansl+1,ansl);
}
int main(){
 scanf("%s",a+1);
 n=strlen(a+1);
 for (int i=1;i<=n;i++) b[i]=a[n-i+1];
 kmp();
 manacher();

 getans();
 print();
}

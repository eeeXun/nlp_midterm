

# 4 "data/855.cpp"
inline long long read(){
 char c=getchar();while (c!='-'&&(c<'0'||c>'9'))c=getchar();
 long long k=0,kk=1;if (c=='-')c=getchar(),kk=-1;
 while (c>='0'&&c<='9')k=k*10+c-'0',c=getchar();return kk*k;
}using namespace std;
void write(long long x){if (x<0)x=-x,putchar('-');if (x/10)write(x/10);putchar(x%10+'0');}
void writeln(long long x){write(x);puts("");}
char s[1000010],a[1000010];
long long nxt[1000010],p[1000010],ma[1000010],l,mx,id,x,y,dd,ans,xx,yy,zz,ddd,sum,flag[1000010];
void build(long long l,long long r,long long d){
 if (l==r){ma[d]=p[l];return;}
 long long m=(l+r)>>1;build(l,m,d*2);build(m+1,r,d*2+1);
 ma[d]=max(ma[d*2],ma[d*2+1]);
}long long find(long long x,long long y,long long l,long long r,long long d){
 if (x>y)return 0;if (x<=l&&y>=r)return ma[d];
 long long m=(l+r)>>1;if (x<=m&&y>m)return max(find(x,y,l,m,d*2),find(x,y,m+1,r,d*2+1));
 if (x<=m)return find(x,y,l,m,d*2);else return find(x,y,m+1,r,d*2+1);
}
signed main(){
 scanf("%s",s+1);l=strlen(s+1);if (l<=2){puts("1");puts("1 1");return 0;}
 for (long long i=1;i<=l;i++){
  a[i]=s[l-i+1];
  long long kk=nxt[i-1];while (kk&&a[kk+1]!=a[i])kk=nxt[kk];
  if (a[kk+1]==a[i]&&kk+1!=i)kk++;
  nxt[i]=kk;
 }for (long long i=1;i<=l;i++){
  p[i]=mx>i?min(p[2*id-i],mx-i):1;
  while (s[i-p[i]]==s[i+p[i]]&&i+p[i]<=l)p[i]++;
  if (p[i]+i-1>=mx)mx=p[i]+i-1,id=i;
 }build(1,l,1);dd=0;
 for (long long i=0;i<=l;i++){
  while (s[i]!=a[dd+1]&&dd)dd=nxt[dd];
  if (s[i]==a[dd+1])dd++;
  x=i+1;y=l-dd;if (x>y){
   while (x>y)x--,y++,dd--;
   if (ans<dd*2+1){ans=dd*2+1;ddd=dd;xx=x;yy=y;zz=1;}
   break;
  }long long ll=0,rr=(y-x+1)/2;
  while (ll<rr){
   long long m=(ll+rr+1)>>1;
   if (find(x+m,y-m,1,l,1)>=m+1)ll=m;else rr=m-1;
  }if (ans<dd*2+ll*2+1){ans=dd*2+ll*2+1;ddd=dd;xx=x;yy=y;zz=ll+1;}
 }if (ddd==0){
  writeln(1);
  for (long long i=xx+zz-1;i<=yy-zz+1;i++)if (p[i]>=zz){
   cout<<i-zz+1<<' '<<zz*2-1<<endl;break;
  }return 0;
 }writeln(3);cout<<xx-ddd<<' '<<ddd<<endl;
 for (long long i=xx+zz-1;i<=yy-zz+1;i++)if (p[i]>=zz){
  cout<<i-zz+1<<' '<<zz*2-1<<endl;break;
 }cout<<yy+1<<' '<<ddd<<endl;
}

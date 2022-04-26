# 4 "data/136.cpp" 2

# 4 "data/136.cpp"
using namespace std;
const int tt=100005;
int len[tt],pos[tt],lft[tt],rgt[tt],nxt[tt];
char s[tt];
bool p[tt];
struct st{
 int num,pos;
 st(){num=pos=0;}
 st(int a,int b){num=a,pos=b;}
 bool operator >(const st &a) const{
  return num>a.num;
 }
 bool operator <(const st &a) const{
  return num<a.num;
 }
} seg[262144],mlen,llen,rlen,pre;
void updata(int i){
 seg[i]=max(seg[i*2],seg[i*2+1]);
}
void del(int i){
 seg[i].num=0;
 for (i>>=1;i;i>>=1) updata(i);
}
void cmax(st &a,const st b){
 if (b>a) a=b;
}
void mana(int n,char *s){
 int md,mp,i;
 for (len[1]=md=mp=1,i=2;i<=n;i++){
  len[i]=i<=md?min(len[mp*2-i],md-i+1):1;
  for (;s[i-len[i]]==s[i+len[i]];len[i]++);
  if (i+len[i]-1>=md) md=i+len[i]-1,mp=i;
 }
}
bool cmp1(int a,int b){
 return a-len[a]<b-len[b];
}
bool cmp2(int a,int b){
 return a+len[a]>b+len[b];
}
int main(){


 int n,i,j,pl,pr,ans,tlen,l,r;
 scanf("%s",s+1);
 n=strlen(s+1),*s=1;
 for (i=1;i<=n;i++) pos[i]=n+1,lft[i]=rgt[i]=i;
 for (nxt[n]=j=n+1,i=n-1;i;i--){
  for (;j!=n+1 && s[i]!=s[j-1];j=nxt[j]);
  if (s[i]!=s[j-1]) nxt[i]=j; else nxt[i]=--j;
 }
 for (j=n+1,i=1;i<=n;i++){
  for (;j!=n+1 && s[i]!=s[j-1];j=nxt[j]);
  if (s[i]==s[j-1] && pos[--j]==n+1) pos[j]=i;
 }
 mana(n,s);
 sort(lft+1,lft+n+1,cmp1);
 sort(rgt+1,rgt+n+1,cmp2);
 for (i=1;i<262144;i++) seg[i].num=0;
 for (ans=tlen=0,i=1;i<=n;i++){
  seg[131071+i]=st(len[i],i);
  if (2*len[i]-1>ans)
   ans=2*len[i]-1,mlen=st(len[i],i);
  p[i]=true;
 }
 for (i=131071;i;i--) updata(i);
 for (pl=pr=l=1,r=i=n,llen=rlen=st(0,0);pos[i]+1<=i-1;i--){
  for (;l<pos[i]+1 || r>i-1;){
   if (l<pos[i]+1){
    for (;pl<=n && lft[pl]-len[lft[pl]]+1==l;pl++) if (p[lft[pl]]){
     p[lft[pl]]=false;
     del(131071+lft[pl]);
     cmax(llen,st(len[lft[pl]],lft[pl]));
    }
    llen.num--,++l;
   }
   if (r>i-1){
    for (;pr<=n && rgt[pr]+len[rgt[pr]]-1==r;pr++) if (p[rgt[pr]]){
     p[rgt[pr]]=false;
     del(131071+rgt[pr]);
     cmax(rlen,st(len[rgt[pr]],rgt[pr]));
    }
    rlen.num--,--r;
   }
  }
  pre=max(max(llen,rlen),seg[1]);
  if (2*pre.num-1+2*(n-i+1)>ans)
   ans=2*pre.num-1+2*(n-i+1),mlen=pre,tlen=n-i+1;
 }
 if (tlen)
  printf("3\n%d %d\n%d %d\n%d %d\n",pos[n-tlen+1]-tlen+1,tlen,
   mlen.pos-mlen.num+1,2*mlen.num-1,n-tlen+1,tlen);
 else
  printf("1\n%d %d\n",mlen.pos-mlen.num+1,2*mlen.num-1);
 return 0;
}

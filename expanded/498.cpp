const int L=1<<19;
char ibuf[L],*ie=ibuf+L,*ip=ie-1;
inline char nc(void){if(++ip==ie)if(fread(ip=ibuf,1,L,
# 8 "data/498.cpp" 3 4
                    stdin
# 8 "data/498.cpp"
                    ));return *ip;}

inline int read(char*str){
 int n=0;char opt;
 while((opt=nc())<'a'||opt>'z');
 while(opt>='a'&&opt<='z')str[n++]=opt,opt=nc();
 str[n]='\0';return n;
}
char s[100001],sr[100001];
int n,ans,Next[100001],f[100001],g[100001],maxl[100001],flag;
signed main(void){
 int i,j,tmp,mx=0,pos=0;scanf("%s",s+1);n=strlen(s+1);s[n+1]='*';
 for(i=1;i<=n;++i){
  maxl[i]=(mx>i)?min(mx-i,maxl[(pos<<1)-i]):1;
  while(s[i+maxl[i]]==s[i-maxl[i]])++maxl[i];
  if(i+maxl[i]>mx)mx=i+maxl[i],pos=i;
  sr[i]=s[n-i+1];
 }
 for(j=0,i=2;i<=n;++i){while(j&&sr[j+1]^sr[i])j=Next[j];if(sr[j+1]==sr[i])Next[i]=++j;}
 for(j=0,i=1;i<=n;++i){while(j&&sr[j+1]^s[i])j=Next[j];if(sr[j+1]==s[i])f[i]=++j;if(f[i]==n)j=Next[j];if(f[i])g[i]=i-f[i]+1;}
 for(i=1;i<=n;++i)if(f[i-1]>f[i])f[i]=f[i-1],g[i]=g[i-1];
 for(i=1;i<=n;++i)if(ans<maxl[i]*2-1)ans=maxl[i]*2-1,pos=i-maxl[i]+1;
 for(i=1;i<=n;++i){
  tmp=i-maxl[i];
  if(2*min(f[tmp],n-(i+maxl[i]-1))+2*maxl[i]-1>ans)flag=1,ans=2*min(f[tmp],n-(i+maxl[i]-1))+2*maxl[i]-1,pos=i;
 }(!flag)?printf("1\n%d %d\n",pos,ans):printf("3\n%d %d\n%d %d\n%d %d\n",g[pos-maxl[pos]],f[pos-maxl[pos]],pos-maxl[pos]+1,2*maxl[pos]-1,n-f[pos-maxl[pos]]+1,f[pos-maxl[pos]]);
 return 0;
}

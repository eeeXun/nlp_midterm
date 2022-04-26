
# 3 "data/187.cpp"
const int n=100005;
int i,j,N,Max,p,t,res,Ans,len;
char s[n],r[n];
int A[n],f[n],g[n],next[n];
int main()
{
 scanf("%s",s);
 N=strlen(s);
 for(i=N;i;--i) s[i]=s[i-1];
 for(i=1;i<=N;++i) r[i]=s[N-i+1];
 Max=p=0;
 for(i=1;i<=N;++i)
 {
  if(i<=Max&&A[2*p-i]<Max-i) A[i]=A[2*p-i];
  else
  {
   if(i<=Max) A[i]=Max-i;
   else A[i]=0;
   for(;i-A[i]-1>0&&i+A[i]+1<=N&&s[i-A[i]-1]==s[i+A[i]+1];++A[i]);
   if(i+A[i]>Max) Max=i+A[i],p=i;
  }
 }
 next[1]=0;
 for(i=2;i<=N;++i)
 {
  for(j=next[i-1];j&&r[j+1]!=r[i];j=next[j]);
  if(r[j+1]==r[i]) next[i]=j+1;
  else next[i]=0;
 }
 j=0;
 for(i=1;i<=N;++i)
 {
  for(;j&&s[i]!=r[j+1];j=next[j]);
  if(s[i]==r[j+1]) ++j;
  f[i]=j;
 }
 for(i=1;i<=N;++i)
 {
  if(f[g[i-1]]>f[i]) g[i]=g[i-1];
  else g[i]=i;
 }
 for(i=1;i<=N;++i)
 {
  t=g[i-A[i]-1];
  if(f[t]<N-i-A[i]) res=A[i]*2+1+f[t]*2;
  else res=A[i]*2+1+(N-i-A[i])*2;
  if(res>Ans) Ans=res,p=i;
 }
 t=g[p-A[p]-1];
 if(f[t]<N-p-A[p]) len=f[t];
 else len=N-p-A[p];
 if(len>0) printf("3\n");
 else printf("1\n");
 if(len>0) printf("%d %d\n",t-len+1,len);
 printf("%d %d\n",p-A[p],2*A[p]+1);
 if(len>0) printf("%d %d\n",N-len+1,len);
 return 0;
}

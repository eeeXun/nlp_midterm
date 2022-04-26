unsigned Geth(unsigned l,unsigned r){return h[r]-h[l-1]*Po[r-l+1];}
unsigned Getg(unsigned l,unsigned r){return g[l]-g[r+1]*Po[r-l+1];}
unsigned Getmx(unsigned l,unsigned r){
 if(l>r)return 0;
 unsigned k=Log[r-l+1],x=st[k][l],y=st[k][r-(1<<k)+1];
 return d[x]>d[y]?x:y;
}
void Rabit_in(){
 scanf("%s",s+1);n=strlen(s+1);Po[0]=1;unsigned i,j,mx=0,id=0;
 for(i=1;i<=n;i++)h[i]=h[i-1]*P+s[i],Po[i]=Po[i-1]*P;
 for(i=n;i;i--)g[i]=g[i+1]*P+s[i];
 n=n<<1|1;s[0]='$';
 for(i=n;i;i--)if(i&1)s[i]='#';else s[i]=s[i>>1];
 for(i=1;i<=n;i++){
  d[i]=i<mx?min(d[id+id-i],mx-i):1;
  while(s[i+d[i]]==s[i-d[i]])d[i]++;
  if(i+d[i]>mx)mx=i+d[i],id=i;
 }
 n>>=1;
 for(i=0;1<<i<=n;i++)Log[1<<i]=i;
 for(i=1;i<=n;i++)if(!Log[i])Log[i]=Log[i-1];
 for(i=1;i<=n;i++)d[i]=d[i<<1]>>1,st[0][i]=i;

 for(j=1;j<=Log[n];j++)
 for(i=1;i<=n;i++){
  st[j][i]=st[j-1][i],id=i+(1<<(j-1));
  if(id<=n&&d[st[j][i]]<d[st[j-1][id]])st[j][i]=st[j-1][id];
 }
}
void Get(unsigned L,unsigned R,unsigned &Midl,unsigned &Midr){
 unsigned l=0,r=(R-L+1)>>1,mid,tmp,res;
 while(l<=r){
  mid=(l+r)>>1,tmp=Getmx(L+mid,R-mid);
  if(d[tmp]>mid)l=mid+1,Midl=tmp-mid,Midr=tmp+mid;else r=mid-1;
 }
}
void Rabit_ans(){
 unsigned l=1,len,tmpl,tmpr,Left=0,Right=0,Midl=0,Midr=0,ans=0;
 for(len=0;len<n;len++){
  while(l+len<n-len&&Geth(l,l+len)^Getg(n-len,n))l++;
  if(l+len+1>=n-len)break;
  Get(l+len+1,n-len-1,tmpl,tmpr);
  if(ans<len+len+2+tmpr-tmpl+1)
   ans=len+len+2+tmpr-tmpl+1,Left=l,Right=n-len,Midl=tmpl,Midr=tmpr;
 }
 len=Getmx(1,n);
 if((d[len]<<1)-1>=ans){
  printf("%u\n%u %u\n",1,len-d[len]+1,(d[len]<<1)-1);return;
 }
 puts("3");
 printf("%u %u\n",Left,n-Right+1);
 printf("%u %u\n",Midl,Midr-Midl+1);
 printf("%u %u\n",Right,n-Right+1);
}
signed main(){

 Rabit_in();Rabit_ans();
 fclose(
# 65 "data/302.cpp" 3 4
       stdin
# 65 "data/302.cpp"
            );fclose(
# 65 "data/302.cpp" 3 4
                     stdout
# 65 "data/302.cpp"
                           );return 0;
}

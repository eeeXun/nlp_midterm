using namespace std;

const int N=200010;
int n,p[N],pos[N],tem[N],suiv[N],f[N],c[5][2];
char s[N],t[N];

inline int manacher(char* s)
{
 t[0]='$',t[1]='#';
 int l=strlen(s+1),len=1;
 for(int i=1;i<=l;i++)
  t[++len]=s[i],pos[i]=len,t[++len]='#';
 int maxi=0,id=0;
 for(int i=1;i<=len;i++)
 {
  p[i]=(maxi>i)?min(maxi-i,p[(id<<1)-i]):1;
  while(t[i+p[i]]==t[i-p[i]])p[i]++;
  if(i+p[i]>maxi)maxi=i+p[i],id=i;
 }
 memcpy(tem,p,sizeof(p));
 memset(p,0,sizeof(p));
 for(int i=1;i<=l;i++)p[i]=tem[pos[i]]>>1;
}

inline void kmp(char* s)
{
 for(int i=1;i<=n;i++)t[n-i+1]=s[i];
 for(int i=2,j=0;i<=n;i++)
 {
  while(j && t[j+1]!=t[i])j=suiv[j];
  if(t[j+1]==t[i])j++;
  suiv[i]=j;
 }
 for(int i=1,j=0;i<=n;i++)
 {
  while(j && s[i]!=t[j+1])j=suiv[j];
  if(s[i]==t[j+1])j++;
  if(f[i-1]>j)
   f[i]=f[i-1],pos[i]=pos[i-1];
  else f[i]=j,pos[i]=i-j+1;
 }
}

int main()
{
 scanf("%s",s+1);
 n=strlen(s+1);
 manacher(s);
 memset(pos,0,sizeof(pos));
 kmp(s);
 int ans=0;
 for(int i=1;i<=n;i++)
 {
  int tem=p[i]+min(f[i-p[i]],n-(i+p[i]-1));
  if(ans<tem)
  {
   ans=tem;
   int mini=min(f[i-p[i]],n-(i+p[i]-1));
   c[2][0]=i-p[i]+1,c[2][1]=p[i]*2-1;
   if(mini==0)c[1][0]=-1;
   else c[1][0]=pos[i-p[i]],c[1][1]=mini,
    c[3][0]=n-mini+1,c[3][1]=mini;
  }
 }
 if(c[1][0]==-1)
  printf("1\n%d %d\n",c[2][0],c[2][1]);
 else printf("3\n%d %d\n%d %d\n%d %d\n",c[1][0],c[1][1],c[2][0],c[2][1],c[3][0],c[3][1]);
 return 0;
}

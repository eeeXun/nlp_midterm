# 2 "data/277.cpp"
using namespace std;
string s;
const int maxn=1e5+10;
int P[maxn*2];
int Q[maxn];
void getP()
{
 string F="@";
 for(int i=0;i<s.length();i++)
 {
  F+="#"+s.substr(i,1);
 }
 F+="#$";
 int c=0,r=0;
 for(int i=1;i<F.length()-1;i++)
 {
  int im=c-(i-c);
  if(r>i)P[i]=min(r-i,P[im]);
  while(F[i+1+P[i]]==F[i-1-P[i]])P[i]++;
  if(i+P[i]>r)
  {
   c=i;
   r=i+P[i];
  }
 }
 int j=0;
 for(int i=0;i<F.length();i++)
  if(F[i]>='a'&&F[i]<='z')
  {
   Q[j++]=P[i];
  }
}
int zi[maxn*2];
int Z[maxn];
void getZ()
{
 string F=s;
 reverse(F.begin(),F.end());
 F+=s;

 int len=F.length();
 zi[0]=len;
 int l=0,r=0;
 for(int k=1;k<len;k++)
 {
  if(k>r)
  {
   int i=0,j=k;
   while(F[i]==F[j]&&i<len&&j<len)
    i++,j++;
   j--;
   l=k,r=j;
   zi[k]=r-l+1;
  }
  else
  {
   int kk=k-l;
   if(k+zi[kk]-1<r)
    zi[k]=zi[kk];
   else
   {
    int i=r+1-k,j=r+1;
    while(F[i]==F[j]&&i<len&&j<len)
     i++,j++;
    j--;
    l=k,r=j;
    zi[k]=r-l+1;
   }
  }

 }
 for(int i=0;i<s.length();i++)
 {
  Z[i]=zi[i+s.length()];

 }
}
const int maxt=1<<18;
int dat[maxt][3];
void _inittree()
{
 for(int i=0;i<maxt;i++)
  dat[i][0]=0,dat[i][1]=maxt;
}
int query1(int x,int l,int r,int tl,int tr)
{
 if(l>tr||r<tl)return maxt;
 if(tl<=l&&r<=tr)
 {

  return dat[x][1];
 }
 int mid=(l+r)>>1;
 return min(query1(x*2,l,mid,tl,tr),query1(x*2+1,mid+1,r,tl,tr));
}
pair<int,int> query0(int x,int l,int r,int tl,int tr)
{
 if(l>tr||r<tl)return make_pair(0,-1);
 if(tl<=l&&r<=tr)
 {

  return make_pair(dat[x][0],dat[x][2]);
 }
 int mid=(l+r)>>1;
 return max(query0(x*2,l,mid,tl,tr),query0(x*2+1,mid+1,r,tl,tr));
}
void upd(int x,int l,int r,int pos,int len,int endpos)
{
 if(l>endpos||r<endpos)return;
 if(l==r)
 {
  if(len>dat[x][0])
  {
   dat[x][0]=len;
   dat[x][2]=pos;
  }
  dat[x][1]=min(dat[x][1],pos);

  return;
 }
 int mid=(l+r)>>1;
 upd(x*2,l,mid,pos,len,endpos);
 upd(x*2+1,mid+1,r,pos,len,endpos);
 dat[x][0]=max(dat[x*2][0],dat[x*2+1][0]);
 dat[x][1]=min(dat[x*2][1],dat[x*2+1][1]);
 dat[x][2]=(dat[x][0]==dat[x*2][0])?dat[x*2][2]:dat[x*2+1][2];
}
int ans;
pair<int,int> rec[3];
int main()
{
 cin.sync_with_stdio(false);
 cin.tie(0);
 cout.sync_with_stdio(false);
 cout.tie(0);

 cin>>s;
 getP();
 getZ();
 _inittree();
 ans=0;
 for(int i=0;i<3;i++)rec[i]=make_pair(-1,-1);
 for(int i=0;i<s.length();i++)
 {
  int res=Q[i];
  int L=i-Q[i]/2,R=i+Q[i]/2;

  pair<int,int> pp=query0(1,0,s.length()-1,0,L-1);
  int tmp=query1(1,0,s.length()-1,L,s.length()-1);


  int buf=pp.first,pos=pp.second;
  if(L-tmp>buf)
  {
   buf=L-tmp;
   pos=tmp;
  }
  buf=min(buf,(int)s.length()-1-R);

  res+=buf*2;

  if(res>ans)
  {
   ans=res;
   if(buf==0)
   {
    rec[0]=make_pair(L,Q[i]);
    rec[1]=make_pair(-1,-1);
    rec[2]=make_pair(-1,-1);
   }
   else
   {
    rec[0]=make_pair(pos,buf);
    rec[1]=make_pair(L,Q[i]);
    rec[2]=make_pair(s.length()-buf,buf);
   }
  }
  upd(1,0,s.length()-1,i,Z[i],i+Z[i]-1);
 }
 if(rec[1].first==-1)
 {
  printf("1\n");
  printf("%d %d\n",rec[0].first+1,rec[0].second);
 }
 else
 {
  printf("3\n");
  for(int i=0;i<3;i++)
   printf("%d %d\n",rec[i].first+1,rec[i].second);
 }
 return 0;
}

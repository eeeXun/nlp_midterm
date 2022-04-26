#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
char V[100010];
int PF[100010],pos[100010];
// settint preffix func.
int TMP[200010];char VR[200010];
void set_PF(){
  int i,j,N=2*n+1;
  for(i=n-1;i>=0;--i)VR[n-i-1]=V[i];
  VR[n]='$';
  for(i=0;i<n;++i)VR[n+i+1]=V[i];
  TMP[0]=0;
  for(i=1;i<N;++i){
   j=i-1;
   while(j>0 && VR[TMP[j]]!=VR[i])j=TMP[j]-1;
   TMP[i]=TMP[j]+((VR[TMP[j]]==VR[i])?1:0);
                  }
  PF[0]=TMP[n+1];
  for(i=n+2;i<N;++i)PF[i-n-1]=max(TMP[i],PF[i-n-2]);
  memset(pos,-1,sizeof pos);
  for(i=0;i<n;++i)
   if(pos[PF[i]]==-1)pos[PF[i]]=i;
}
// setting palindrome sizes
int PS[100010];
void set_PS(){
  int i,lr=-1,lc=-1;
  for(i=0;i<n;++i){
   int sf=0;
   if(i<lr)sf=min(lr-i,PS[2*lc-i]);
   while(i-sf>=0 && i+sf<n && V[i-sf]==V[i+sf])++sf;
   --sf;PS[i]=sf;
   if(i+sf>lr){lr=i+sf;lc=i;}
                  }
}
// RMQ on PS -> for maximum statichno
int SPAN[100010],TREE[100010][17];
void init_RMQ(){
  SPAN[1]=0;
  int i,j;
  for(i=2;i<=n;++i)
   if((1<<(SPAN[i-1]+1))<=i)SPAN[i]=SPAN[i-1]+1;
   else SPAN[i]=SPAN[i-1];
  for(i=0;i<n;++i)TREE[i][0]=i;
  for(int move=1;move<17;++move)
   for(j=0;j<n;++j){
    TREE[j][move]=TREE[j][move-1];
    int neo=j+(1<<(move-1));
    if(neo<n)
     if(PS[TREE[neo][move-1]]>PS[TREE[j][move]])TREE[j][move]=TREE[neo][move-1];
                   }
}
int get(int f,int t){
  int S=SPAN[t-f+1];
  int ret=TREE[f][S],neo=t-(1<<S)+1;
  if(PS[ret]>PS[TREE[neo][S]])return ret;
  return TREE[neo][S];
}
// THIS IS THE ANS
int L=0;
vector<int> pp,pl,num;
bool compare(const int& a,const int& b){return pp[a]<pp[b];}
int main(){
  int i,j,k,l;
  //system("pause");
  scanf("%s",&V);n=strlen(V);
  set_PF();set_PS();
  init_RMQ();
  L=2*PS[get(0,n-1)]+1;pp.push_back(get(0,n-1)-PS[get(0,n-1)]);pl.push_back(L);
  for(i=1;i<n;++i){
   if(pos[i]<0)continue;
   int le=pos[i],re=n-i;
   if(le>=re)break;
   int ml=0,mr=(re-le-1)/2-(re-le)%2,M;
   while(1){
    if(mr-ml<2){
     if(PS[get(le+1+mr,re-1-mr)]>=mr)M=mr;
     else M=ml;
     break;
               }
    M=(ml+mr)/2;
    if(PS[get(le+1+M,re-1-M)]>=M)ml=M;
    else mr=M;
           }
   if(2*i+2*M+1>L){
    L=2*i+2*M+1;
    pp.clear();pl.clear();
    pp.push_back(le-i+1);pl.push_back(i);
    pp.push_back(re);pl.push_back(i);
    pp.push_back(get(le+1+M,re-1-M)-M);pl.push_back(2*M+1);
                  }
                  }
  // printing ans
  for(i=0;i<pp.size();++i)num.push_back(i);
  sort(num.begin(),num.end(),compare);
  printf("%d\n",num.size());
  for(i=0;i<num.size();++i)
   printf("%d %d\n",pp[num[i]]+1,pl[num[i]]);
  //system("pause");
  return 0;
}


typedef long long ll;
const int MAX=2e5+7;


char s1[MAX],s[MAX];
int R[MAX]; int mine[MAX]; int b[MAX];

const int MAX2=22;
const int m=0xff+1;
int sa[MAX],x[MAX],y[MAX],c[MAX],rank[MAX],height[MAX];
int n;

int maps[MAX][MAX2];

void build_sa(int m) {
 for(int i=(0);i<=m-1;i++) c[i]=0;
 for(int i=(0);i<=n-1;i++) c[x[i]=s[i]]++;
 for(int i=(1);i<=m-1;i++) c[i]+=c[i-1];
 for(int i=(n-1);i>=0;i--) sa[--c[x[i]]]=i;
 for(int k=1;k<=n;k<<=1) {
  int p=0;
  for(int i=(n-k);i<=n-1;i++) y[p++]=i;
  for(int i=(0);i<=n-1;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
  for(int i=(0);i<=m-1;i++) c[i]=0;
  for(int i=(0);i<=n-1;i++) c[x[y[i]]]++;
  for(int i=(1);i<=m-1;i++) c[i]+=c[i-1];
  for(int i=(n-1);i>=0;i--) sa[--c[x[y[i]]]]=y[i];
  swap(x,y);
  p=1,x[sa[0]]=0;
  for(int i=(1);i<=n-1;i++) {
   x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&((sa[i-1]+k>=n&&sa[i]+k>=n)||(sa[i-1]+k<n&&sa[i]+k<n&&y[sa[i-1]+k]==y[sa[i]+k]))?
      p-1:p++;
  }
  if(p>=n) break;
  m=p;
 }
}
void getHeight() {
 int i,j,k=0;




 for(i=0;i<n;i++) rank[sa[i]]=i;
 for(i=0;i<n;i++) {
  if(k!=0) k--;
  if(rank[i]==0) height[rank[i]]=0;
  else {
   int j=sa[rank[i]-1];
   while(s[i+k]==s[j+k]) k++;
   height[rank[i]]=k;
  }
 }
}

void createSPTable(int M[][MAX2], int A[], int N)
{
    int i, j;
    for (i = 0; i < N; i++)
        M[i][0] = i;
    for (j = 1; 1 << j <= N; j++) {
        for (i = 0; i + (1 << j) - 1 < N; i++){
            if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
                M[i][j] = M[i][j - 1];
            else
                M[i][j] = M[i + (1 << (j - 1))][j - 1];
        }
    }
}

int spQuery(int i,int j,int M[][MAX2], int A[]) {
 int l=j-i+1,k=0;
 while(l>1) l>>=1,k++;
 if(A[M[i][k]]<=A[M[j+1-(1<<k)][k]]) return M[i][k];
 else return M[j+1-(1<<k)][k];
}


void manac(char *s,int *R) {
 int maxPos=-1,p=-1,len=strlen(s),l;
 for(int i=0;i<len;i++) {
  if(i>maxPos) {
   for(l=1;i+l<len&&i-l>=0&&s[i+l]==s[i-l];l++);
   maxPos=max(maxPos,i+l-1);
   p=i;
   R[i]=l-1;
  } else {
   int j=2*p-i,neMaxPos=2*p-maxPos;
   if(j-R[j]>neMaxPos) R[i]=R[j];
   else {
    for(l=1;maxPos+l<len&&2*i-maxPos-l>=0&&s[maxPos+l]==s[2*i-maxPos-l];l++);
    p=i;
    R[i]=maxPos+l-1-i;
    maxPos=max(maxPos,maxPos+l-1);
   }
  }
 }
}

struct xx{
 int pos;
 int k;
 int len;
 int l;
 int v;
} aa[MAX];
int nums=0;

int main() {






  nums=0;
  scanf("%s",s1);
  manac(s1,R);





  int len=strlen(s1);
  for(int i=(0);i<=len-1;i++) {
   s[i]=s1[i];
  }
  s[len]='&';
  for(int i=(len+1);i<=2*len;i++) {
   s[i]=s1[2*len-i];
  }
  s[2*len+1]='\0';
  n=strlen(s);



  build_sa(m);
  getHeight();
  createSPTable(maps,height,n);
  for(int i=(0);i<=len-1;i++) {
   int r1=rank[i],r2=rank[len+1];
   int idx=spQuery(min(r1,r2)+1,max(r1,r2),maps, height);
   mine[i]=height[idx];
  }
  memset(b,-1,sizeof(b));
  int mm=
# 152 "data/732.cpp" 3 4
        (-0x7fffffff - 1)
# 152 "data/732.cpp"
               ;
  for(int i=(0);i<=len-1;i++) {
   if(mm==
# 154 "data/732.cpp" 3 4
         (-0x7fffffff - 1)
# 154 "data/732.cpp"
                ) {
    mm=mine[i];
    for(int j=(0);j<=mm;j++) {
     b[j]=0;
    }
   } else if(mine[i]>mm) {
    for(int j=(mm+1);j<=mine[i];j++) b[j]=i;
    mm=mine[i];
   }
  }
# 172 "data/732.cpp"
  for(int i=(0);i<=len-1;i++) {
   int pos=i,l=pos-R[i],r=pos+R[i];
   int msl=len-1-r;
   int low=0,high=msl,p;
   if(pos==2)
    p=1;
   while(low<=high) {



    if(low==high) {
     if(b[low]+low-1<=l-1) break;
    }
    int mid=(low+high+1)>>1;
    if(b[mid]!=-1&&b[mid]+mid-1<=l-1) low=mid;
    else high=mid-1;
   }

   if(low==0) {
    aa[nums].k=1;
    aa[nums].pos=pos;
    aa[nums].v=2*R[pos]+1;
    nums++;
   } else {
    aa[nums].pos=pos;
    aa[nums].k=3;
    aa[nums].len=low;
    aa[nums].l=b[low];
    aa[nums].v=2*R[pos]+1+aa[nums].len*2;
    nums++;
   }
  }
  int idd,opt=
# 204 "data/732.cpp" 3 4
             (-0x7fffffff - 1)
# 204 "data/732.cpp"
                    ;
  for(int i=0;i<nums;i++) {
   if(aa[i].v>opt) {
    idd=i;
    opt=aa[i].v;
   }
  }
  if(aa[idd].k==1) {
   printf("1\n%d %d\n",aa[idd].pos-R[aa[idd].pos]+1,2*R[aa[idd].pos]+1);
  } else {
   printf("3\n%d %d\n%d %d\n%d %d\n",aa[idd].l+1,aa[idd].len,
   aa[idd].pos-R[aa[idd].pos]+1,2*R[aa[idd].pos]+1,
   len-aa[idd].len+1,aa[idd].len);
  }




 return 0;
}

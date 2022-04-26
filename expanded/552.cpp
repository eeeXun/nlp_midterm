
# 4 "data/552.cpp"
using namespace std;



double eps = 1e-8;
char init_str[101000], str[101000], mnc_str[101000], cmb_str[2*101000];
int len[101000], mnc_len;
int a[3][2];
int nxt[2*101000];
int match[101000], rgt_max_match[101000];

void manacher(char *init_str, int n) {
 mnc_str[0]='$';
 mnc_str[1]='#';
 int cnt=2;
 for(int i=0; i<n; i++)
  mnc_str[cnt++]=init_str[i],mnc_str[cnt++] = '#';
 mnc_str[cnt] = '\0';
 int id=0,max_r=0;
 for(int i = 1; i < cnt; i++) {
  if(i<max_r) len[i]=min(len[2*id-i], max_r-i+1);
  else len[i]=1;
  for(; i+len[i] < cnt && i-len[i] >= 0 && mnc_str[i+len[i]] == mnc_str[i-len[i]]; len[i]++);
  if(i+len[i]-1 > max_r)
   max_r = i+len[i]-1,id=i;
 }
 mnc_len=cnt;
}
void get_kmp_next(char* str, int n) {
 nxt[0]=-1;
 for(int i=1; i<n; i++) {
  int p=nxt[i-1];
  while(p>=0 && str[p+1]!=str[i]) p=nxt[p];
  p=str[p+1]==str[i]?p+1:-1;
  nxt[i]=p;
 }
}
void pre_proccess(int n) {
 for(int i=1; i<=n; i++)
  match[n-i]=nxt[n+i]+1;
 rgt_max_match[n-1]=n-1;
 for(int i=n-2; i>=0; i--)
  if(match[i]>match[rgt_max_match[i+1]])
   rgt_max_match[i]=i;
  else rgt_max_match[i]=rgt_max_match[i+1];
}
int main() {
 scanf("%s",init_str);
 int n=strlen(init_str);
 int cmb_cnt=0;
 for(int i=0; i<n; i++)
  cmb_str[cmb_cnt++] = init_str[n-i-1];
 cmb_str[cmb_cnt++]='$';
 for(int i=0; i<n; i++)
  cmb_str[cmb_cnt++]=init_str[i];
 get_kmp_next(cmb_str, cmb_cnt);
 for(int i=0; i<n/2; i++)
  swap(init_str[i],init_str[n-i-1]);
 manacher(init_str,n);
 pre_proccess(n);
 int maxv=-1,flag;
 for(int i=2; i<mnc_len; i+=2) {
  int l=(i-len[i]+1)/2, r=(i+len[i]-1)/2-1;
  if(r<l) continue;
  int L;
  if(r+1>=n || l<=0)
   L=0;
  else
   L=min(match[rgt_max_match[r+1]],l);
  int sum_len=r-l+1+2*L;
  if(sum_len>=maxv) {
   maxv=sum_len;
   if(L==0) {
    flag=0;
    a[1][0]=l+1,a[1][1]=r-l+1;
   } else {
    flag=1,a[0][0]=1,a[0][1]=L;
    a[1][0]=l+1,a[1][1]=r-l+1;
    a[2][0]=rgt_max_match[r+1]+1,a[2][1]=L;
   }
  }
 }
 if(flag) {
  printf("3\n");
  for(int i=0; i<3; i++) {
   printf("%d %d\n", n-a[3-i-1][0]+2-a[3-i-1][1], a[3-i-1][1]);
  }
 } else {
  printf("1\n");
  printf("%d %d\n", n-a[1][0]+2-a[1][1], a[1][1]);
 }

 return 0;
}

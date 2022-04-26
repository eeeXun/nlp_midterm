# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/563.cpp" 2

# 5 "data/563.cpp"
using namespace std;
const int MAXL = 100030,MAXA = 5;
char s[MAXL],a[MAXL << 1];
int n,ans,tot,Maxlen,Maxid,tmp,pre[MAXL],p[MAXL],q,l[MAXA],pos[MAXA],r[MAXL << 1];

void KMP(){
 p[n - 1] = n; q = n;
 for(int i = n - 2;i >= 0;-- i){
  while(q != n && s[i] != s[q - 1]) q = p[q];
  if(s[q - 1] == s[i]) -- q;
  p[i] = q;
 }
 q = n;
 for(int i = 0;i < n;++ i){
  while(q != n && s[i] != s[q - 1]) q = p[q];
  if(s[q - 1] == s[i]) -- q;
  pre[i] = n - q;
  if(i && pre[i - 1] > pre[i]) pre[i] = pre[i - 1];
 }
}

void Manacher(){
 a[0] = '!'; a[1] = '$';
 for(int i = 1;i <= n;++ i){
  a[i << 1] = s[i - 1]; a[i << 1 | 1] = '$';
 }
 Maxlen = 0;
 ans = 0; tot = 0;
 int tmp,o,lsd,rsd;
 for(int i = 1,lim = (n << 1) | 1 ;i <= lim;++ i){
  if(i < Maxlen) r[i] = min(Maxlen - i,r[(Maxid << 1) - i]);
  else r[i] = 1;
  while(a[i + r[i]] == a[i - r[i]]) ++ r[i];
  if(i + r[i] > Maxlen){
   Maxlen = i + r[i];
   Maxid = i;
  }
  if((r[i] - 1) & 1){
   if(r[i] - 1 > ans){
    ans = r[i] - 1; tot = 1; pos[0] = (i >> 1) - (ans >> 1); l[0] = r[i] - 1;
   }
   o = (i >> 1) - 1; lsd = o - (r[i] >> 1); rsd = o + (r[i] >> 1);
   if(lsd >= 0 && rsd < n){
    tmp = min(pre[lsd],n - rsd);
    if(tmp + tmp + r[i] - 1 > ans){
     ans = r[i] - 1 + tmp + tmp; tot = 3;
     l[1] = r[i] - 1; pos[1] = (i >> 1) - (l[1] >> 1);
     pos[2] = n - tmp + 1; l[2] = tmp;
    }
   }
  }
 }
 if(tot > 1){
  q = n;
  for(int i = 0;i < n;++ i){
   while(q != n && s[q - 1] != s[i]) q = p[q];
   if(s[q - 1] == s[i]) -- q;
   if(n - q == l[2]){
    pos[0] = i + 2 - l[2]; l[0] = l[2];
    break;
   }
  }
 }
}

int main(){
 scanf("%s",s);
 n = strlen(s);
 KMP();
 Manacher();
 printf("%d\n",tot);
 for(int i = 0;i < tot;++ i) printf("%d %d\n",pos[i],l[i]);
 return 0;
}

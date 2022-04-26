//CODEFORCES-ROUND30.DIV1-E
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define k1  100007;
#define k2  199997;
#define k3 199993;
char s[100010], t[100010];
long int n, lmax[100010], p[100010], f[100010], cs[100010];
FILE *fin, *fout;

void call_lmax()
{
     long int c;
     c=1; lmax[1]=0;
     while (c<n) {
           while (s[c - lmax[c] - 1]==s[c + lmax[c] + 1]) lmax[c]++;
           for (long int i=c+1; i<=c+lmax[c]+1; i++)
               if (i<=c+lmax[c]){
                  lmax[i]=lmax[c*2-i];
                  if (lmax[i]>=c+lmax[c]-i){
                     lmax[i]=c+lmax[c] - i;
                     c=i;
                     break;                          
                  }                 
               } else {
                      c=i;    
                      break;
                      }
     }
};

void call_f()
{
     for (long int i=1; i<=n; i++)
         if (s[i]==s[n]){
            p[1]=i;
            break;
         }
     //if p[1]=n then return;
     long long p1, p2, p3, hl1, hl2, hl3, hr3, hr1, hr2;
     long int r;
     p1=26; p2=26; p3=26;
     hl1=hr1=s[n] % k1;
     hl2=hr2=s[n] % k2;
     hl3=hr3=s[n] % k3;
     
     for (long int i=2; i<=n/2; i++){
         r=p[i-1]+1;
         hl1=(hl1*26 + s[r]) % k1;
         hl2=(hl2*26 + s[r]) % k2;
         hl3=(hl3*26 + s[r]) % k3;
         hr1=(hr1*26 + s[n-i+1]) % k1;
         hr2=(hr2*26 + s[n-i+1]) % k2;
         hr3=(hr3*26 + s[n-i+1]) % k3;
         
         while (hl1!=hr1 || hl2!=hr2 || hl3!=hr3){
               if (r>=n-i+1) break;       
               r++;
               hl1=((hl1-s[r-i]*p1)*26 + s[r]) % k1;
               while(hl1<0) hl1=hl1+k1;
               
               hl2=((hl2-s[r-i]*p2)*26 + s[r]) % k2;
               while(hl2<0) hl2=hl2+k2;
               
               hl3=((hl3-s[r-i]*p3)*26 + s[r]) % k3;
               while (hl3<0) hl3=hl3+k3;
               
               //if (r==1277) printf("%I64d %I64d %I64d %I64d %I64d %I64d\n", hl1, hr1, hl2, hr2, hl3, hr3);
         }
         
         if (r>=n-i+1) break;
         p[i]=r;
         p1=(p1*26) % k1;
         p2=(p2*26) % k2;
         p3=(p3*26) % k3;
     }
     
     r=1;
     for (long int i=1; i<=n; i++) f[i]=0;
     for (long int i=1; i<=n; i++) if (f[p[i]] < i) f[p[i]]=i;
 
         
     f[0]=p[0]=cs[0]=0;
     for (long int i=1; i<=n; i++)
         if (f[i]<=f[i-1]) f[i]=f[i-1];
    // for (long int i=1; i<=n; i++) printf("%d ", p[i]);
};

void call_res()
{
     long int pos, res, l;
     res=0;
     for (long int i=1; i<=n; i++)
         if (res < lmax[i]*2+1 + 2*(f[i-lmax[i]-1]<(n-i-lmax[i])? f[i-lmax[i]-1]:(n-i-lmax[i]))){
            res= lmax[i]*2+1 + 2*(f[i-lmax[i]-1]<(n-i-lmax[i])? f[i-lmax[i]-1]: (n-i-lmax[i]));
            pos=i;
         }
     
   l=(f[pos-lmax[pos]-1] < (n-pos-lmax[pos]) ? f[pos-lmax[pos]-1] : (n-pos-lmax[pos]));
   if (l > 0){
      printf("3\n");
      printf("%d %d\n", p[l]-l+1, l);
      printf("%d %d\n", pos-lmax[pos], lmax[pos]*2+1);
      printf("%d %d\n", n-l+1, l);
   }
   else printf("1\n%d %d", pos-lmax[pos], 1+2*lmax[pos]);
};

int main()
{   

    scanf("%s", &t);
    n=0; 
    while (t[n])n++;
    s[0]='-';
    for (long int i=1; i<=n; i++) s[i]=t[i-1];
    s[n+1]='?'; s[n+2]='\0';
    
          call_lmax();
          call_f();
          call_res();
}
//qmdmxlhwjldezdahqtixkbdtvuzjsgoirrwrqrbtulnhixpmghfjcbwgtcikpsgdfgvhxhrlqbmhlffr

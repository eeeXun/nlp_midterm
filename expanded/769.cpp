


}
# 7 "data/769.cpp" 2

# 7 "data/769.cpp"
using namespace std;




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

     long long p1, p2, p3, hl1, hl2, hl3, hr3, hr1, hr2;
     long int r;
     p1=26; p2=26; p3=26;
     hl1=hr1=s[n] % 100007;;
     hl2=hr2=s[n] % 199997;;
     hl3=hr3=s[n] % 199993;;

     for (long int i=2; i<=n/2; i++){
         r=p[i-1]+1;
         hl1=(hl1*26 + s[r]) % 100007;;
         hl2=(hl2*26 + s[r]) % 199997;;
         hl3=(hl3*26 + s[r]) % 199993;;
         hr1=(hr1*26 + s[n-i+1]) % 100007;;
         hr2=(hr2*26 + s[n-i+1]) % 199997;;
         hr3=(hr3*26 + s[n-i+1]) % 199993;;

         while (hl1!=hr1 || hl2!=hr2 || hl3!=hr3){
               if (r>=n-i+1) break;
               r++;
               hl1=((hl1-s[r-i]*p1)*26 + s[r]) % 100007;;
               while(hl1<0) hl1=hl1+100007;;

               hl2=((hl2-s[r-i]*p2)*26 + s[r]) % 199997;;
               while(hl2<0) hl2=hl2+199997;;

               hl3=((hl3-s[r-i]*p3)*26 + s[r]) % 199993;;
               while (hl3<0) hl3=hl3+199993;;


         }

         if (r>=n-i+1) break;
         p[i]=r;
         p1=(p1*26) % 100007;;
         p2=(p2*26) % 199997;;
         p3=(p3*26) % 199993;;
     }

     r=1;
     for (long int i=1; i<=n; i++) f[i]=0;
     for (long int i=1; i<=n; i++) if (f[p[i]] < i) f[p[i]]=i;


     f[0]=p[0]=cs[0]=0;
     for (long int i=1; i<=n; i++)
         if (f[i]<=f[i-1]) f[i]=f[i-1];

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

# 2 "data/595.cpp"
using namespace std;
const int N = 3e5+10;
int z[N];
char ch[N];
char chf[N];
int n,len[N];
int l;
int cc;

void Z_algorithm(){
   z[1] = l;
   int mx = 0,R = 0;
   for(int i = 2;i <= l; ++i){
      z[i] = (i < R)?min(R-i,z[i-mx+1]):0;
      while(ch[i+z[i]] == ch[z[i]+1])++z[i],++cc;
      if(i+z[i]-1 > R)R = i+z[i]-1,mx = i;
   }
}

void Manacher(){
   int mx = 0,R = 0;
   len[1] = 1;
   for(int i = 2;i <= l; ++i){
      len[i] = (i < R)?min(R-i,len[2*mx-i]):1;

      while(i-len[i] > 0 && i+len[i] <= l && ch[i-len[i]] == ch[i+len[i]])++len[i];

      if(i+len[i] > R)R = i+len[i]-1,mx = i;
   }
}

int mxl[N];
int mxp[N];
int main(){
   scanf("%s",ch+1);
   n = strlen(ch+1);
   for(int i = 1;i <= n; ++i){
      chf[n+1-i] = ch[i];
      ch[i+n+1] = ch[i];
   }
   for(int i = 1;i <= n; ++i){
      ch[i] = chf[i];
   }
   ch[n+1] = '#'; ch[2*n+2] = '\0';
   l = 2*n+1;
   Z_algorithm(); Manacher();

   mxl[0] = 0; mxp[0] = 0;
   for(int i = 1;i <= n; ++i){
      int &w = mxl[i+z[i+n+1]-1];
      if(w < z[i+n+1]){
         mxp[i+z[i+n+1]-1] = i;
         w = z[i+n+1];
      }
   }
   for(int i = 1;i <= n; ++i){
      if(mxl[i] < mxl[i-1]){
         mxl[i] = mxl[i-1]; mxp[i] = mxp[i-1];
      }
   }
   int ans = 0;
   for(int i = 1;i <= n; ++i){
      ans = max(min(mxl[i-len[i+n+1]],n-i-len[i+n+1]+1)*2+2*len[i+n+1]-1,ans);
   }
   for(int i = 1;i <= n; ++i){
      if(min(mxl[i-len[i+n+1]],n-i-len[i+n+1]+1)*2+2*len[i+n+1]-1 == ans){
         int curl = min(mxl[i-len[i+n+1]],n-i-len[i+n+1]+1);
         if(curl == 0){
            cout << 1 << endl;
            cout << i-len[i+n+1]+1 <<' ' << 2*len[i+n+1]-1 << endl;
         }
         else {
            cout << 3 << endl;
            cout << mxp[i-len[i+n+1]] << ' ' << curl <<endl;
            cout << i-len[i+n+1]+1 <<' ' << 2*len[i+n+1]-1 << endl;
            cout << n-curl+1 << ' ' << curl << endl;
         }
         return 0;
      }
   }
   return 0;
}

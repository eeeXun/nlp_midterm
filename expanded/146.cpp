 }
      this->pbump(__off);
    }




  extern template class basic_stringbuf<char>;
  extern template class basic_istringstream<char>;
  extern template class basic_ostringstream<char>;
  extern template class basic_stringstream<char>;


  extern template class basic_stringbuf<wchar_t>;
  extern template class basic_istringstream<wchar_t>;
  extern template class basic_ostringstream<wchar_t>;
  extern template class basic_stringstream<wchar_t>;




}
# 1218 "/usr/include/c++/11.2.0/sstream" 2 3
# 16 "data/146.cpp" 2
# 28 "data/146.cpp"

# 28 "data/146.cpp"
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn=100007;
const ll base=73471;

pii pre,mid,suf,pos[maxn];
int n,p[maxn],k,res,Left[maxn];
char s[maxn];
ll hashpw[maxn],val[maxn],valrev[maxn];

ll get(int i, int j){
    return val[j]-val[i-1]*hashpw[j-i+1];
}

int main(){

    gets(s+1);
    n=strlen(s+1);
    hashpw[0]=1;
    for (int i=1,_c=n;i<=_c;i++) hashpw[i]=hashpw[i-1]*base;
    for (int i=1,_c=n;i<=_c;i++) val[i]=val[i-1]*base+s[i];
    for (int i=n;i>=1;i--) valrev[i]=valrev[i+1]*base+s[i];

    int v=0; p[0]=0;
    for (int i=1,_c=n;i<=_c;i++){
        if(v+p[v]>=i) p[i]=min(p[2*v-i],2*v-i-(v-p[v]));
        else p[i]=1;
        while(i-p[i]>=1 && i+p[i]<=n && s[i-p[i]]==s[i+p[i]]) p[i]++;
        if(v+p[v]<i+p[i]) v=i;
    }

    Left[0]=0;
    int it=1;
    for (int i=n;i>=1;i--){
        while(it<i && get(it,it+n-i)!=valrev[i]) it++;
        if(it+n-i<i){
            Left[it+n-i]=n-i+1;
            pos[it+n-i]=pii(it,n-i+1);
        }else break;
    }
    for (int i=1,_c=n;i<=_c;i++) if(!Left[i]){
        Left[i]=Left[i-1];
        pos[i]=pos[i-1];
    }
    res=0;
    int len;
    for (int i=1,_c=n;i<=_c;i++){
        len=Left[i-p[i]];
        if(n-(i+p[i]-1)<len) len=n-(i+p[i]-1);
        if(res<p[i]*2-1 + len*2){
            res=p[i]*2-1 + len*2;
            if(len){
                k=3;
                pre=pos[i-p[i]]; pre.second=len;
                mid=pii(i-p[i]+1,p[i]*2-1);
                suf=pii(n-len+1,len);
            }else{
                k=1;
                mid=pii(i-p[i]+1,p[i]*2-1);
            }
        }
    }

    printf("%d\n",k);
    if(k==3) printf("%d %d\n",pre.first,pre.second);
    printf("%d %d\n",mid.first,mid.second);
    if(k==3) printf("%d %d\n",suf.first,suf.second);


    return 0;
}

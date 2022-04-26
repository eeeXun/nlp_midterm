  using ::memcpy;
  using ::memmove;
  using ::memset;
  using ::strcat;
  using ::strcmp;
  using ::strcoll;
  using ::strcpy;
  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;
# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 16 "data/486.cpp" 2


# 17 "data/486.cpp"
using namespace std;
# 31 "data/486.cpp"
template<class T> ostream &operator<<(ostream &os, vector<T> &vec)
{
  os<<'{';
  for(int i=(0), __i=(((int)(vec).size())); i<__i; i++){
    os<<vec[i];
    if (i+1!=((int)(vec).size())) os<<',';
  }
  os<<'}';
  return os;
}

template<class T1, class T2> ostream &operator<<(ostream &os, pair<T1, T2> &par)
{
  os<<'('<<par.first<<','<<par.second<<')';
  return os;
}

typedef long long lint;
typedef vector<int> VI;
typedef pair<int,int> PII;

const int dim = 110000;
char s[dim];
char s1[dim];
int p[dim];
int a[dim];
int a1[dim];

lint r1[dim];
lint r2[dim];
lint r3[dim];

int main(){
    scanf("%s", s);
    int n = strlen(s);
    for(int i=(0), __i=(n); i<__i; i++) s1[i] = s[n - 1 - i];
    s1[n] = 0;

    p[0] = -1;
    int g = -1;
    for(int i=(1), __i=(n); i<__i; i++){
        while(g != -1 && s1[g + 1] != s1[i]){
            g = p[g];
        }
        if(s1[g + 1] == s1[i]) ++g;
        p[i] = g;
    }

    g = -1;
    a[0] = 0;
    a1[0] = 0;
    for(int i=(0), __i=(n); i<__i; i++){
        while(g != -1 && s1[g + 1] != s[i]){
            g = p[g];
        }
        if(s1[g + 1] == s[i]) ++g;
        if(a[i] > g + 1){
            a1[i + 1] = a1[i];
        }else{
            a1[i + 1] = i - g;
        }
        a[i + 1] = max(a[i], g + 1);
    }

    r1[0] = 0;
    r2[0] = 0;
    r3[0] = 1;
    lint cc = 52152551;
    for(int i=(0), __i=(n); i<__i; i++){
        r1[i + 1] = r1[i] + s[i] * r3[i];
        r2[i + 1] = r2[i] + s1[i] * r3[i];
        r3[i + 1] = r3[i] * cc;
    }

    int ans = 0;
    int i1, j1;
    int i2, j2;
    for(int i=(0), __i=(n); i<__i; i++){
        int l = 0, r = n;
        while(r - l > 1){
            int mid = (l + r) / 2;
            if(i - mid >= 0 && i + mid < n && (r1[i + 1] - r1[i - mid]) * r3[n - i - mid - 1] == (r2[n - i] - r2[n - i - mid - 1]) * r3[i - mid]){
                l = mid;
            }else{
                r = mid;
            }
        }
        int t = min(a[i - l], n - i - l - 1);
        int ans1 = t * 2 + l * 2 + 1;
        if(ans < ans1){
            ans = ans1;
            i1 = a1[i - l];
            j1 = t;
            i2 = i - l;
            j2 = l * 2 + 1;
        }
    }
    if(j1 == 0){
        printf("1\n");
        printf("%d %d\n", i2 + 1, j2);
    }else{
        printf("3\n");
        printf("%d %d\n", i1 + 1, j1);
        printf("%d %d\n", i2 + 1, j2);
        printf("%d %d\n", n - j1 + 1, j1);
    }
    return 0;
}

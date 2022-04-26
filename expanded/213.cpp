  using ::tm;

  using ::clock;
  using ::difftime;
  using ::mktime;
  using ::time;
  using ::asctime;
  using ::ctime;
  using ::gmtime;
  using ::localtime;
  using ::strftime;
}



namespace std
{
  using ::timespec;
  using ::timespec_get;
}
# 15 "data/213.cpp" 2
# 28 "data/213.cpp"

# 28 "data/213.cpp"
using namespace std;

typedef long long int64;
typedef unsigned long long lint;
typedef long double ld;

template<typename type> inline void _cutedebug(const type &a, string name, int ln, ostream &cerr);
template<typename type1, typename type2> inline void _cutedebug(const pair<type1, type2> &a, ostream &cerr);
template<typename type1, typename type2> inline void _cutedebug(const map<type1, type2> &a, ostream &cerr);
template<typename type> inline void _cutedebug(const type &a, ostream &cerr);
template<typename type> inline void _cutedebug(const vector<type> &a, ostream &cerr);
template<typename type> inline void _cutedebug(const set<type> &a, ostream &cerr);

template<typename type> inline static void _cutedebug(const type &a, ostream &cerr){
 cerr << a;
}
template<typename type1, typename type2> inline void _cutedebug(const pair<type1, type2> &a, ostream &cerr){
 cerr << "("; _cutedebug(a.first, cerr); cerr << ", "; _cutedebug(a.second, cerr); cerr << ")";
}
template<typename type> inline void _cutedebug(const vector<type> &a, ostream &cerr){
 cerr << "[";
 bool flag = true;
 for (typename vector<type>::const_iterator i = a.begin(); i != a.end(); i++){
  if (flag)
   flag = false;
  else
   cerr << ", ";
  _cutedebug(*i, cerr);
 }
 cerr << "]";
}
template<typename type> inline void _cutedebug(const set<type> &a, ostream &cerr){
 cerr << "{";
 bool flag = true;
 for (typename set<type>::const_iterator i = a.begin(); i != a.end(); i++){
  if (flag)
   flag = false;
  else
   cerr << ", ";
  _cutedebug(*i, cerr);
 }
 cerr << "}";
}
template<typename type1, typename type2> inline void _cutedebug(const map<type1, type2> &a, ostream &cerr){
 cerr << "{";
 bool flag = true;
 for (typename map<type1, type2>::const_iterator i = a.begin(); i != a.end(); i++){
  if (flag)
   flag = false;
  else
   cerr << ", ";
  cerr << "(";
  _cutedebug((*i).first, cerr);
  cerr << ": ";
  _cutedebug((*i).second, cerr);
  cerr << ")";
 }
 cerr << "}";
}
# 97 "data/213.cpp"
const char* fin = "input.txt";
const char* fout = "output.txt";

const int inf = ((1 << 30) - 1);
const int64 linf = ((1ll << 62) - 1);
const int cmax = 100500;

int n;
char s[cmax];
int d[cmax];

void initPal(){
    int l = -1, r = -1;
    for (int i = 0; i < n; i++){
        d[i] = 0;
        if (i < r)
            d[i] = min(d[l - (i - l)], min(r - i, i - (l - (r - l))));
        while (i - d[i] - 1 >= 0 && i + d[i] + 1 < n && s[i - d[i] - 1] == s[i + d[i] + 1])
            ++d[i];
        if (i + d[i] > r)
            l = i, r = i + d[i];
    }
}

const int cc = 20;

int table[cmax][cc], pw2[cmax], invPw[cmax];

void initTable(){
    for (int i = 0; i < cc; i++)
        pw2[i] = i ? pw2[i - 1] * 2 : 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < cc; j++)
            if (pw2[j + 1] > i){
                invPw[i] = j;
                break;
            }
    for (int i = n - 1; i >= 0; i--){
        table[i][0] = d[i];
        for (int j = 1; j < cc; j++)
            if (i + pw2[j - 1] < n)
                table[i][j] = max(table[i][j - 1], table[i + pw2[j - 1]][j - 1]);
            else
                table[i][j] = -1;
    }
}

int getValue(int l, int r){
    if (l > r)
        return -inf;
    int ans = max(table[l][invPw[r - l + 1]], table[r - pw2[invPw[r - l + 1]] + 1][invPw[r - l + 1]]);
    return ans;
}

int maxValue(int l, int r, int &index){
    int left = 0, right = r - l + 1;
    while (right - left > 1){
        int m = (left + right) / 2;
        if (getValue(l + m, r - m) >= m)
            left = m;
        else
            right = m;
    }
    int answer = left;
    left = l + answer - 1; right = r - answer + 1;
    while (right - left > 1){
        int m = (left + right) / 2;
        if (getValue(l + answer, m) >= answer)
            right = m;
        else
            left = m;
    }
    index = right - answer;
    return answer * 2 + 1;
}

const lint p = 259;

lint h[cmax], rh[cmax], pw[cmax];

inline lint value(int l, int r){
    if (l > r)
        return 0;
    if (l == 0)
        return h[r];
    return h[r] - h[l - 1] * pw[r - l + 1];
}

int main(){




    
# 190 "data/213.cpp" 3 4
   (static_cast <bool> (
# 190 "data/213.cpp"
   scanf("%s", s)
# 190 "data/213.cpp" 3 4
   ) ? void (0) : __assert_fail (
# 190 "data/213.cpp"
   "scanf(\"%s\", s)"
# 190 "data/213.cpp" 3 4
   , "data/213.cpp", 190, __extension__ __PRETTY_FUNCTION__))
# 190 "data/213.cpp"
                         ; n = strlen(s);
    initPal();
    initTable();
    h[0] = s[0], pw[0] = 1;
    for (int i = 1; i < n; i++)
        h[i] = h[i - 1] * p + s[i], pw[i] = pw[i - 1] * p;
    rh[n - 1] = s[n - 1];
    for (int i = n - 2; i >= 0; i--)
        rh[i] = rh[i + 1] * p + s[i];
    int size = -inf, prefsize = -1, wh = -1, midLeft = -1, midSize = -1;
    for (int i = 0; i < n; i++){
        int l = 0, r = n - i;
        while (r - l > 1){
            int m = (l + r) / 2;
            if (value(i, i + m - 1) == rh[n - m] && i + m + m < n)
                l = m;
            else
                r = m;
        }
        int cursize, curmidLeft;
        if (size < l + l + (cursize = maxValue(i + l, n - 1 - l, curmidLeft)))
            size = l + l + cursize, wh = i, midLeft = curmidLeft, midSize = cursize, prefsize = l;
    }
    if (prefsize == 0){
        printf("1\n");
        printf("%d %d\n", midLeft + 1, midSize);
    }
    else{
        printf("3\n");
        printf("%d %d\n", wh + 1, prefsize);
        printf("%d %d\n", midLeft + 1, midSize);
        printf("%d %d\n", n - prefsize + 1, prefsize);
    }
    return 0;
}

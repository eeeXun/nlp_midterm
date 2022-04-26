
    strstream();
    strstream(char*, int, ios_base::openmode = ios_base::in | ios_base::out);
    virtual ~strstream();


    strstream(strstream&& __rhs)
    : iostream(std::move(__rhs)), _M_buf(std::move(__rhs._M_buf))
    { set_rdbuf(&_M_buf); }

    strstream& operator=(strstream&&) = default;


    __attribute__ ((__const__)) strstreambuf* rdbuf() const throw ();
    void freeze(bool = true) throw ();
    __attribute__ ((__pure__)) int pcount() const throw ();
    char* str() throw ();

  private:
    strstreambuf _M_buf;
  };


}
# 21 "data/924.cpp" 2



# 1 "/usr/include/c++/11.2.0/ctime" 1 3
# 39 "/usr/include/c++/11.2.0/ctime" 3
       
# 40 "/usr/include/c++/11.2.0/ctime" 3
# 25 "data/924.cpp" 2

# 25 "data/924.cpp"
using namespace std;
# 38 "data/924.cpp"
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long LL;
typedef pair<int,int> PII;

char s[100010], s1[100010];
int len;
int next[100010], p[100010], pidx[100010], pld[100010];

void GetNext(char s[], int next[]){
    int l = strlen(s), i = 0, j = -1;
    next[0] = -1;
    while(i <= l) {
        if(j == -1 || s[i] == s[j]){
             j ++ ; i ++ ;
             if(s[i] != s[j]) next[i] = j;
             else next[i] = next[j];
        }
        else j = next[j];
    }
}

void Kmp(char s[], char s1[], int next[], int p[]){
    int l = strlen(s), l1 = strlen(s1), i = 0, j = 0, ans = 0;
    while(i < l) {
        if (j == -1 || s[i] == s1[j]){
            p[i] = j;
            j ++ ; i ++ ;
            if (j == l1) j = next[j] ;
        }
        else j = next[j];
    }
}

void MakePld(char s[], int len, int p[]) {
    int maxp = 0;
    p[0] = 1;
    for (int i = 1; i < len; i ++ ) {
        if (maxp + p[maxp] - 1 < i) p[i] = 1;
        else p[i] = min(p[maxp * 2 - i], maxp + p[maxp] - i);
        while (i + p[i] < len && i - p[i] >= 0
               && s[i + p[i]] == s[i - p[i]]) p[i] ++ ;
        if (i + p[i] > maxp + p[maxp]) maxp = i;
    }
}

int main() {
    scanf("%s", s);

    len = strlen(s);
    for (int i = 0; i < len; i ++ )
        s1[len - i - 1] = s[i];
    s1[len] = '\0';

    GetNext(s1, next);
    Kmp(s, s1, next, p);
    if (p[0] == -1)
        pidx[0] = -1;
    else
        pidx[0] = 0;
    for (int i = 1; i < len; i ++ )
        if (p[i - 1] > p[i]) {
            p[i] = p[i - 1];
            pidx[i] = pidx[i - 1];
        }
        else
            if (p[i] == -1)
                pidx[i] = -1;
            else
                pidx[i] = i - p[i];

    MakePld(s, len, pld);

    int ansl = 0, ansk[4][2];

    for (int i = 0; i < len; i ++ ) {
        if (pld[i] * 2 - 1 > ansl) {
            ansl = pld[i] * 2 - 1;
            ansk[0][0] = 1;
            ansk[1][0] = i - pld[i] + 1;
            ansk[1][1] = ansl;
        }
        int l = i - pld[i], r = i + pld[i];
        if (l < 0 || p[l] == -1) continue;
        if (min(p[l] + 1, len - r) * 2 + pld[i] * 2 - 1 > ansl) {
            ansl = min(p[l] + 1, len - r) * 2 + pld[i] * 2 - 1;
            ansk[0][0] = 3;
            ansk[1][0] = pidx[l];
            ansk[1][1] = min(p[l] + 1, len - r);
            ansk[2][0] = l + 1;
            ansk[2][1] = pld[i] * 2 - 1;
            ansk[3][0] = len - min(p[l] + 1, len - r);
            ansk[3][1] = min(p[l] + 1, len - r);
        }
    }

    printf("%d\n",ansk[0][0]);
    for (int i = 1; i <= ansk[0][0]; i ++)
        printf("%d %d\n", ansk[i][0] + 1, ansk[i][1]);
    return 0;
}

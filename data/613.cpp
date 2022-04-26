#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

#define FOR(x,y,z) for(int x=y;x<=z;++x)
#define FORD(x,y,z) for(int x=y;x>=z;--x)
#define FOReach(x,Z) for(__typeof((Z).begin()) x=(Z).begin();x!=(Z).end();++x)
#define REP(x,y) for(int x=0;x<y;++x)

#define PB push_back
#define ALL(X) (X).begin(),(X).end()
#define SZ(X) ((int)(X).size())
#define CLR(X,x) memset(X, x, sizeof(X))

#define MP make_pair
#define ST first
#define ND second

#define DBG

#ifdef DBG
#define debug printf
#else
#define debug(fmt, ...)
#endif


const int MAX = 100000;
const int INF = 1000000001;

void manacher(char T[], int n, int R[], bool p) {
    int j = -1;
    REP(i,n)
    {
        R[i] = min(R[max(0, j-(i-j))], j + R[j] - i);
        R[i] = max(R[i], 0);
        while(i+R[i]+1 < n && i-R[i]-p >= 0 && T[i+R[i]+1] == T[i-R[i]-p])
            ++R[j = i];
    }
}
void prefpref(char T[], int n, int PP[]) {
    PP[0] = 0;
    int j = 0;
    FOR(i,1,n-1)
    {
        PP[i] = min(PP[j]+j-i, PP[max(0, i-j)]);
        PP[i] = max(PP[i], 0);
        while(PP[i]+i < n && T[PP[i]] == T[PP[i]+i])
            ++PP[j = i];
    }
}

char A[2*MAX+2];

int palin[MAX];
int pref[2*MAX+1];
int Pmax[MAX];

int n;

int binSearch(int prefLen, int sufLen) {
    int p = 0, q = min(prefLen, sufLen);
    while(p < q)
    {
        int r = (p+q+1)/2;
        if(Pmax[prefLen-r] >= r)
            p = r;
        else
            q = r - 1;
    }
    return p;
}

int main(int argc, char *argv[]) {
    scanf("%s", A);
    n = strlen(A);
    if(n < 3) {
        printf("1\n1 1\n");
        return 0;
    }
    manacher(A, n, palin, true);
    A[n] = '$';
    memcpy(A+n+1, A, n);
    reverse(A, A+n);
    prefpref(A, 2*n+1, pref);
    Pmax[0] = pref[n+1];
    FOR(i,1,n-1)
        Pmax[i] = max(Pmax[i-1], pref[n+1+i]);
    reverse(A, A+n);
    int ans;
    int ansLen = 0;
    FOR(i,1,n-2)
    {
        int midLen = 2 * palin[i] + 1;
        int prefLen = i - palin[i];
        int sufLen = n - midLen - prefLen;
        int x = binSearch(prefLen, sufLen);
        int passLen = 2*x + midLen;
        if(passLen > ansLen) {
            ans = i;
            ansLen = passLen;
        }
    }
    int midLen = 2 * palin[ans] + 1;
    int prefLen = ans - palin[ans];
    int sufLen = n - midLen - prefLen;
    int x = binSearch(prefLen, sufLen);
//  printf("palin: "); REP(i,n) printf("%d ", palin[i]); printf("\n");
//  printf("Pmax: "); REP(i,n) printf("%d ", Pmax[i]); printf("\n");
//  printf("ans %d   pref mid suf x %d %d %d %d\n", ans, prefLen, midLen, sufLen, x);
//  REP(i,2*n+1) printf("%c%d ", A[i], pref[i]); printf("\n");
    if(x) {
        printf("3\n");
        int i = 0;
        while(pref[n+1+i] < x)
            ++i;
        printf("%d %d\n", i + 1, x);
        printf("%d %d\n", ans - palin[ans] + 1, midLen);
        printf("%d %d\n", n - x + 1, x);
    }
    else {
        printf("1\n");
        printf("%d %d\n", prefLen + 1, midLen);
    }
    return 0;
}
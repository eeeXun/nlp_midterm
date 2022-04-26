#include <map>
#include <set>
#include <queue>
#include <stack>
#include <time.h>
#include <bitset>
#include <math.h>
#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>

#define ff first
#define ss second
#define pp pop_back
#define mp make_pair
#define pb push_back
#define lld long long
#define inf 1000000009
#define mid(x, y) (x+y)/2
#define pii pair <int, int>
#define sz(x) (int)x.size()
#define gcd(x, y) __gcd (x, y)
#define all(x) x.begin(), x.end()
#define lcm(x, y) (x*y) / __gcd (x, y);
#define random srand((unsigned)time(NULL))

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> Maksat;

//min beryar ---> priority_queue < pii, vector< pii >, greater< pii > > Q;
//max beryar ---> priority_queue < pii > Q;

const int Max = 100005;

int n, m, ans;

int P[Max<<1], M[Max];

char s[Max], t[Max<<1];

pair< int, int > T[Max<<2], Ans[9];

void Build(int l, int r, int v) {
    if (l == r)
        {T[v] = {P[l+n], l}; return;}

    Build(l, mid(l, r), v*2+1);
    Build(mid(l, r)+1, r, v*2);

    T[v] = max(T[v*2], T[v*2+1]);
}

pii Tap(int x, int y, int l, int r, int v) {
    if (x <= l && r <= y) return T[v];
    if (l > y  ||  r < x) return {0,0};

    return max(Tap(x, y, l, mid(l, r), v*2+1),
               Tap(x, y, mid(l, r)+1, r, v*2));
}

void Kmp() {
    for (int i=1; i<m; i++) {
        int Nah = P[i-1];

        while(Nah > 0 && t[Nah] != t[i])
            Nah = P[Nah-1];

        if (t[Nah] == t[i])
            Nah++;

        P[i] = Nah;
    }
}

void Manacher() {
    int r=-1, l=0;

    for (int i=0; i<n; i++) {
        int Mal = i <= r ? min(r-i, M[l+r-i]) : 0;

        while (i-Mal >= 0 && i+Mal < n && s[i-Mal] == s[i+Mal]) Mal++;

        if (r <= i+Mal)
            l = i-Mal+1, r=i+Mal-1;

        M[i] = Mal;
    }
}

int main() {
	//freopen("file.in", "r", stdin);
	//freopen("file.out", "w", stdout);

    scanf("%s", &s);

    n = strlen(s);

    for (int i=n-1; i>=0; i--) t[m++] = s[i];
    t[m++] = '#';
    for (int i=0; i<=n-1; i++) t[m++] = s[i];

    Kmp();
    Manacher();
    Build(1, n, 1);

    for (int i=0; i<n; i++) {
        pii x = Tap(1, i-M[i]+1, 1, n, 1);

        x.ss = x.ss-x.ff+1;

        x.ff = min(x.ff, n-i-M[i]);

        if (ans < x.ff+x.ff+(2*M[i]-1)) {
            ans = x.ff+x.ff+(2*M[i]-1);

            Ans[0] = {x.ss, x.ff};
            Ans[2] = {n-x.ff+1, x.ff};
            Ans[1] = {i-M[i]+2, 2*M[i]-1};
        }
    }

    if (Ans[0].ss == 0) cout << "1\n";
    else                cout << "3\n";

    for (int i=0; i<3; i++)
        if (Ans[i].ss != 0)
            cout << Ans[i].ff << ' ' << Ans[i].ss << '\n';

	return 0;
}

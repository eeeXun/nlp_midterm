#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <assert.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define TR(i,x) for(typeof(x.begin()) i=x.begin();i!=x.end();i++)
#define ALL(x) x.begin(),x.end()
#define SORT(x) sort(ALL(x))
#define CLEAR(x) memset(x,0,sizeof(x))
#define FILL(x,c) memset(x,c,sizeof(x))

using namespace std;

const double eps = 1e-8;

#define PB push_back
#define MP make_pair

typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<long double> VD;
typedef pair<int,int> PII;
typedef long long int64;
typedef long long ll;
typedef unsigned int UI;
typedef long double LD;
typedef unsigned long long ULL;

void next_function(char S[], int n, int next[])
{
    next[0] = n;
    int j = 0, k = 1;
    while(1+j<n && S[j] == S[1+j]) j++;
    next[1] = j;
    for(int i=2; i<n; ++i)
    {
        int len = k + next[k] - 1;
        int l = next[i - k];
        if(l < len - i + 1) next[i] = l;
        else
        {
            int j = max(0, len - i + 1);
            while(S[i+j] == S[j] && i + j < n) j++;
            next[i] = j;
            k = i;
        }
    }
}

void ext(char S[], int n, char T[], int m, int next[], int lcp[])
{
    next_function(T, m, next);
    int j = 0, k = 0;
    while(j<min(n, m) && T[j] == S[j]) ++j;
    lcp[0] = j;
    for(int i=1; i<n; ++i)
    {
        int len = k + lcp[k] - 1;
        int l = next[i - k];
        if(l < len - i + 1) lcp[i] = l;
        else
        {
            int j = max(0, len - i + 1);
            while(i+j<n && j<m && S[i+j]==T[j]) j++;
            lcp[i] = j;
            k = i;
        }
    }
}

const int maxn = 200007;

char a[maxn], b[maxn];
int next[maxn], lcp[maxn];

char c[maxn*2], str[maxn*2];
int p[maxn*2];
pair<int, int> rad[maxn], out[maxn];

void man(char *s, int len)
{
    str[0] = '$';
    for (int i = 0;i < len;++i)
    {
        str[i*2+1] = '#';
        str[i*2+2] = s[i];
    }
    str[len*2+1] = '#';
    int n = len * 2 + 1;
    int i,mx=0,left, right, id;
    for(i=1;i<=n;i++)
    {
        if(mx>i)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        for(;str[i+p[i]]==str[i-p[i]];p[i]++)  //没完全覆盖
            ;
        if(p[i]+i>mx)
        {
            mx=p[i]+i;
            id=i;
        }
    }
    int ret = 0;
    for (int i = 1;i <= n;++i)
    {
        if (i & 1) continue;
        ret = (p[i]/2);
        left = (i/2 - 1) - ret + 1;
        right = (i/2 - 1) + ret - 1;
        rad[i/2-1] = MP(left, right);
    }
}

int main()
{
    scanf("%s", a);
    int n = strlen(a);

    REP(i, n) b[i] = a[i];
    reverse(b, b+n);

    ext(a, n, b, n, next, lcp);
    man(a, n);

    sort(rad, rad+n);
    reverse(rad, rad+n);

   // REP(i, n) cout << lcp[i] << endl;

    REP(i, n)
        out[i] = MP(lcp[i], i);

   // cout << "rad[i] : ";
   // REP(i, n) cout << rad[i].first << " " << rad[i].second << endl;

    sort(out, out+n);
    reverse(out, out+n);

   // cout << "out[i] : ";
   // REP(i, n) cout << out[i].first << " " << out[i].second << endl;

    int maxi = 0, m[3], l[3];
    int top = n+1, now = 0;

    REP(i, n)
    {
        while (now < n && out[now].second + out[now].first - 1 >= rad[i].first)
        {
            top = min(top, out[now].second);
            ++now;
        }
        int tmp = 0;

        if (now == n) out[now].first = -0x7f7f7f7f;

        tmp = max(tmp, min(n-1-rad[i].second, max(out[now].first, rad[i].first - top)));
        int part = rad[i].second - rad[i].first + 1 + 2*tmp;
        if (part > maxi)
        {
            maxi = part;
            if (now >= n || out[now].first < rad[i].first-top)
                m[0] = top;
            else m[0] = out[now].second;

            l[0] = m[0]+tmp-1;
            m[2] = n-tmp;
            l[2] = n-1;

            m[1] = rad[i].first, l[1] = rad[i].second;
        }
    }

  //  cout << "here\n";

  //  REP(i, 3) cout << "m[i] = " << m[i] << " l[i] = " << l[i] << endl;



  //  cout << "maxi = " << maxi << endl;

    vector<PII> vv, vs;

    vs.resize(3);

    REP(i, 3) vs[i] = (pair<int, int>(m[i], l[i]));

    REP(i,3)
    {
        if (vs[i].second != vs[i].first-1)
            vv.PB(vs[i]);
    }

    cout << vv.size() << endl;
    REP(i, vv.size())
        cout << vv[i].first+1 << " " << vv[i].second-vv[i].first+1 << endl;

    return 0;
}
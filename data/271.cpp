#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

//kAc
const double pi = acos(-1.0), eps = 1e-9;
const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[8] = {0, 0, 1, -1, 1, -1, -1, 1};
const int MO = (int)(1e9 + 7);

#define ALL(x) x.begin(), x.end()
#define fr(x, E) for (__typeof(E.begin()) x = E.begin(); x != E.end(); x++)
#define MP make_pair
#define PB push_back
#define FR first
#define SC second
#define ERR cerr << "ERROR" << endl
#define LL long long
#define LD long double
#define PII pair<int, int>
#define PIII pair<PII, int>
#define PDI pair<double, int>
#define PID pair<int, double>
#define SZ(a) (int)((a).size())
#define VEC vector
#define STR string
#define ISS istringstream
#define OSS ostringstream
#define CLR(a, b) memset(a, b, sizeof(a))
#define gmin(a, b) { if (b < a) a = b; }
#define gmax(a, b) { if (b > a) a = b; }
using namespace std;
char s[100500];

string x;
int z[2 * 100500];
pair <int, int> ref[100500];
int pal[100500];
int n;

inline void z_func()
{
    int l, r, q;
    z[0] = l = r = 0;
    for (int k = 1; k < (int)x.size(); k++)
    {
        if (k > r)
        {
            q = k;
            while (q < (int)x.size() && x[q] == x[q - k])
                q++;
            z[k] = q - k;
            l = k;
            r = q - 1;
        }
        else
        {
            if (z[k - l] < r - k + 1)
                z[k] = z[k - l];
            else
            {
                q = r + 1;
                while (q < (int)x.size() && x[q] == x[q - k])
                    q++;
                z[k] = q - k;
                l = k;
                r = q - 1;
            }
        }
    }
}

void Solve()
{
    for (int i = 0; i < n; i++)
        ref[i].first = ref[i].second = -1;

    z_func();
    int last = 0;

    for (int i = n + 1; i < (int)x.size(); i++)
        if (z[i] > last)
        {
            if (i + (z[i] << 1) + 1 < (int)x.size())
            {
                ref[i - n - 1].first = z[i];
                ref[i - n - 1].second = i - n - 1;
            }
            last = z[i];
        }
    for (int i = 1; i < n; i++)
        ref[i] = max (ref[i], ref[i - 1]);

    int l, r, k, mx;
    mx = 0;
    l = 0, r = -1;
    for (int i = 0; i < n; i++)
    {
        k = (r < i ? 0 : min (pal[l + r - i], r - i)) + 1;      
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
            k++;
        pal[i] = --k;
        if (i + k > r)  
        {
            l = i - k;
            r = i + k;
        }

        int pre_len = 0;
        int pos = i - pal[i] - 1;
        if (pos < 0)
            mx = max (mx, (pal[i] << 1) + 1);
        else
        {
            pre_len = ref[pos].first;
            if (pre_len == -1)
                mx = max (mx, (pal[i] << 1) + 1);
            else
            {
                pre_len = min (pre_len, pos - ref[pos].second + 1);
                pre_len = min (pre_len, n - i - pal[i] - 1);
                mx = max (mx, (pal[i] << 1) + 1 + (pre_len << 1) + 1);
            }
                
        }
    }

    for (int i = 0; i < n; i++)
    {
        int pre_len = 0;
        int pos = i - pal[i] - 1;
        if (pos < 0)
            k = (pal[i] << 1) + 1;
        else
        {
            pre_len = ref[pos].first;
            if (pre_len == -1)
                k = (pal[i] << 1) + 1;
            else
            {
                pre_len = min (pre_len, pos - ref[pos].second + 1);
                pre_len = min (pre_len, n - i - pal[i] - 1);
                k = (pal[i] << 1) + 1 + (pre_len << 1) + 1;
            }
                
        }
        if (k == mx)
        {
            if ((pal[i] << 1) + 1 == k)
                printf ("1\n%d %d", pos + 2, (pal[i] << 1) + 1);
            else
            {
                printf ("3\n"); 
                printf ("%d %d\n", ref[pos].second + 1, pre_len);
                printf ("%d %d\n", pos + 2, (pal[i] << 1) + 1);
                printf ("%d %d\n", n - pre_len + 1, pre_len);
            }

            return;
        }
    }
}
                
int main()
{
    gets (s);
    n = strlen(s);
    x = (string)s;
    reverse (x.begin(), x.end());
    x = x + "#" + (string)s;
    Solve();
}

#include<iostream>
#include<fstream>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<iomanip>
#include<bitset>
using namespace std;

const int N = 200100;
const int inf = 2000000;

char a[N];
int n, pal[N], poz[N];

void calcpal() {
    int i, c = 0, pmax = -1;

    for(i = 0; i < n; ++i) {
        int el;

        if(i > pmax)
            el = 0;
        else
            el = min(pmax - i + 1, pal[2 * c - i]);

        while(i - el >= 0 && i + el < n && a[i - el] == a[i + el])
            ++el;
        --el;

        pal[i] = el + 1;

        if(i + el > pmax) {
            pmax = i + el;
            c = i;
        }
    }
}

void calcp() {
    int i, c = 0, pmax = -1;

    for(i = 1; i < 2 * n; ++i) {
        int elc;

        if(i > pmax)
            elc = 0;
        else
            elc = min(pmax - i + 1, poz[i - c]);

        while(i + elc < 2 * n && a[elc] == a[i + elc])
            ++elc;
        --elc;

        poz[i] = elc + 1;

        if(i + elc > pmax) {
            pmax = i + elc;
            c = i;
        }
    }
}

int aib[N], pmax[N], pc;

void update(int poz, int val) {
    int pi = poz;
    for(; poz <= n; poz += (poz & (-poz))) {

        if(val > aib[poz]) {
            aib[poz] = val;
            pmax[poz] = pi;
        }
    }
}

int query(int poz) {
    int r = 0;
    if(poz < 0)
        return 0;

    for(; poz; poz -= (poz & (-poz))) {
        if(aib[poz] > r) {
            r = aib[poz];
            pc = pmax[poz];
        }
    }

    return r;
}

void calcpoz() {
    int i;

    for(i = n; i < 2 * n; ++i)
        a[i] = a[i - n];
    for(i = 0; i < n; ++i)
        a[i] = a[2 * n - i - 1];

    calcp();

    for(i = 0; i < n; ++i)
        poz[i] = i + 1;
    for(i = 0; i < n; ++i) if(poz[i + n])
        poz[min(n - 1, i + poz[i + n] - 1)] = min(poz[min(n - 1, i + poz[i + n] - 1)], i);

    for(i = n - 1; i >= 0; --i) {
        if(i != n - 1) poz[i] = min(poz[i], poz[i + 1]);
        update(i + 1, i - poz[i] + 1);
    }
}

int main() {
    int i;
    //freopen("ttt", "r", stdin);

    cin >> a;
    n = strlen(a);

    calcpal();
    calcpoz();

    int rez = 0;
    vector<pair<int, int> > parts;

    for(i = 0; i < n; ++i) {
        int siz = min(query(i - pal[i] + 1), n - (i + pal[i]));
        int rc = pal[i] * 2 - 1 + siz * 2;
        --pc;

        if(rc > rez) {
            rez = rc;
            parts.clear();

            parts.push_back(pair<int, int>(i - pal[i] + 1, 2 * pal[i] - 1));

            if(siz) {
                parts.push_back(pair<int, int>(poz[pc], siz));
                parts.push_back(pair<int, int>(n - siz, siz));
            }
        }
    }

    //cout << rez << "\n";
    sort(parts.begin(), parts.end());

    cout << parts.size() << "\n";
    for(i = 0; i < parts.size(); ++i)
        cout << parts[i].first + 1 << " " << parts[i].second << "\n";

    return 0;
}

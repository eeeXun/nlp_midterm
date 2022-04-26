# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 8 "data/584.cpp" 2


# 9 "data/584.cpp"
using namespace std;

const int N = 100010;

int lmax;
vector<pair<int, int> > rez;

int n, pal[N], pot[N];
char a[N], b[2 * N];

void calcpal() {
    int i, j, c = 1, pm = 1;

    pal[1] = 1;

    for(i = 2; i <= n; ++i) {
        if(i > pm) {

            for(j = 1; i + j - 1 <= n && i - j + 1 > 0 && a[i + j - 1] == a[i - j + 1]; ++j);
            --j;

            pal[i] = j;
            c = i;
            pm = i + j - 1;
        }
        else {
            j = min(pm - i + 1, pal[2 * c - i]);

            for(; i + j - 1 <= n && i - j + 1 > 0 && a[i + j - 1] == a[i - j + 1]; ++j);
            --j;

            pal[i] = j;

            if(i + j - 1 > pm) {
                c = i;
                pm = i + j - 1;
            }
        }
    }
}

int nr, pref[2 * N];

void calcpot() {
    int i, j;

    for(i = n; i; --i)
        b[++nr] = a[i];
    a[++nr] = 0;
    for(i = 1; i <= n; ++i)
        b[++nr] = a[i];

    int pstart = 1, pend = 1;

    for(i = 2; i <= nr; ++i) {
        if(i > pend) {

            for(j = 1; i + j - 1 <= nr && b[j] == b[i + j - 1]; ++j);
            --j;

            pref[i] = j;

            pstart = i;
            pend = i + j - 1;
        }
        else {
            j = min(pend - i + 1, pref[i - pstart + 1]);

            for(; i + j - 1 <= nr && b[j] == b[i + j - 1]; ++j);
            --j;
            j = max(0, j);

            pref[i] = j;

            if(i + j - 1 > pend) {
                pstart = i;
                pend = i + j - 1;
            }
        }
    }

    for(i = 1; i <= n; ++i)
        pot[i] = 3 * n;

    for(i = n + 2; i <= 2 * n + 1; ++i) {
        pot[pref[i]] = min(pot[pref[i]], i - n - 1);
    }

    for(i = n - 1; i; --i)
        pot[i] = min(pot[i], pot[i + 1]);
}

int d[18][N], p2[N];

void calcrmq() {
    int i, j;

    for(i = 2; i < N; ++i)
        p2[i] = p2[i / 2] + 1;

    for(i = 1; i <= n; ++i)
        d[0][i] = i;

    for(i = 1; i < 18; ++i) {

        for(j = 1; j <= n - (1<<i) + 1; ++j) {

            if(pal[d[i - 1][j]] > pal[d[i - 1][j + (1<<(i - 1))]])
                d[i][j] = d[i - 1][j];
            else
                d[i][j] = d[i - 1][j + (1<<(i - 1))];
        }
    }
}

int smax(int p1, int pa2) {
    if(p1 > pa2)
        return 0;

    int l = p2[pa2 - p1 + 1];

    if(pal[d[l][p1]] > pal[d[l][pa2 - (1<<l) + 1]])
        return d[l][p1];
    else
        return d[l][pa2 - (1<<l) + 1];
}

int main() {
    int i, pas = 1<<17;

    ios_base::sync_with_stdio(false);

    cin >> (a + 1);
    n = strlen(a + 1);

    calcpal();
    for(i = 1; i <= n; ++i) {
        if(lmax < 2 * pal[i] - 1) {
            lmax = 2 * pal[i] - 1;
            rez.clear();
            rez.push_back(pair<int,int>(i - pal[i] + 1, i + pal[i] - 1));
        }
    }

    calcpot();

    calcrmq();

    for(i = 1; i <= n; ++i) {

        int p2 = n - i, p1 = pot[i] + i;

        if(p1 > p2 - 1)
            continue;

        if(2 * i > lmax) {
            lmax = 2 * i;
            rez.clear();
            rez.push_back(pair<int, int>(pot[i], pot[i] + i - 1));
            rez.push_back(pair<int, int>(n - i + 1, n));
        }

        int j;

        pas = 1<<17;

        for(j = 0; pas; pas>>=1) if(j + pas <= p2 - p1 + 1) {
            bool ver = 1;

            int ss = smax(p1 + pas + j - 1, p2 - pas - j + 1);

            if(pal[ss] < pas + j)
                continue;

            j += pas;

            if(2 * i + 2 * j - 1 > lmax) {
                lmax = 2 * j - 1 + 2 * i;
                rez.clear();

                rez.push_back(pair<int, int>(pot[i], pot[i] + i - 1));
                rez.push_back(pair<int, int>(ss - j + 1, ss + j - 1));
                rez.push_back(pair<int, int>(n - i + 1, n));
            }
        }
    }

    cout << rez.size() << "\n";

    for(i = 0; i < rez.size(); ++i)
        cout << rez[i].first << " " << rez[i].second - rez[i].first + 1 << "\n";

    return 0;
}

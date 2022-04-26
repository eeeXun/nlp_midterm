# 4 "data/964.cpp" 2


# 5 "data/964.cpp"
using namespace std;

string nap1, nap2;
int n;

const int P = 9000007;

struct node
{
    int r, ind;
};

struct pods
{
    int l, p;
};

vector<node> T;
int l, size;

void Stworz()
{
    int p = 1;
    while (p < n)
        p *= 2;
    l = p;
    size = 2 * p - 1;
    for (int i = 0; i <= size; ++i)
        T.push_back({-1, -1});
}

void Dodaj(int a, node x)
{
    a += l;
    T[a] = x;
    a /= 2;
    while (a != 0)
    {
        if (T[2 * a].r >= T[2 * a + 1].r)
            T[a] = T[2 * a];
        else
            T[a] = T[2 * a + 1];
        a /= 2;
    }
}

node Max(int a, int b)
{
    if (a > b)
        return {-1, -1};
    a += l;
    b += l;
    node odp = T[a];
    if (T[b].r > odp.r)
        odp = T[b];
    while (a / 2 != b / 2)
    {
        if (a % 2 == 0)
        {
            if (T[a + 1].r > odp.r)
                odp = T[a + 1];
        }
        if (b % 2 == 1)
        {
            if (T[b - 1].r > odp.r)
                odp = T[b - 1];
        }
        a /= 2;
        b /= 2;
    }
    return odp;
}

void prepare(vector<int>& H, vector<int>& pot, string nap)
{
    pot[0] = 1;
    for (int i = 1; i < n + 1; ++i)
        pot[i] = pot[i - 1] * P;
    H[n] = 0;
    for (int i = n - 1; i >= 0; --i)
        H[i] = H[i + 1] * P + nap[i];
}

int Hasz(vector<int>& H, vector<int>& pot, int l, int p)
{
    return H[l] - pot[p - l + 1] * H[p + 1];
}

void Palindromy(vector<int>& H1, vector<int>& H2, vector<int>& pot, vector<int>& pal)
{
    for (int i = 0; i < n; ++i)
    {
        int l = 1, p = min(i + 1, n - i), s, r;
        while (l <= p)
        {
            s = (l + p) / 2;
            int L1 = i - s + 1, P1 = i;
            int L2 = i, P2 = i + s - 1;
            if (Hasz(H1, pot, L1, P1) == Hasz(H2, pot, n - P2 - 1, n - L2 - 1))
            {
                 r = s;
                 l = s + 1;
            }
            else
                p = s - 1;
        }
        pal[i] = r;
    }
}

node Szukaj(int L, int P)
{
    int l = 1, p = P - L + 1, s;
    node r = {-1, -1};
    while (l <= p)
    {
        s = (l + p) / 2;
        node x = Max(L + s - 1, P - s + 1);
        if (x.r >= s)
        {
            r = x;
            l = s + 1;
        }
        else
            p = s - 1;
    }
    int dl = min(r.ind - L + 1, P - r.ind + 1);
    r.r = min(r.r, dl);
    return r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin >> nap1;
    n = nap1.size();
    nap2 = nap1;
    reverse(nap2.begin(), nap2.end());
    vector<int> H1(n + 1), H2(n + 1);
    vector<int> pot(n + 1);
    prepare(H1, pot, nap1);
    prepare(H2, pot, nap2);
    vector<int> pal(n);
    Palindromy(H1, H2, pot, pal);
    Stworz();
    for (int i = 0; i < n; ++i)
        Dodaj(i, {pal[i], i});
    vector<pods> odp;
    int D = 0;
    for (int dl = 1, i = 0; dl <= n; ++dl)
    {
        while (true)
        {
            int L1 = i, P1 = i + dl - 1;
            int L2 = n - dl, P2 = n - 1;
            if (P1 >= L2)
            {
                i = -1;
                break;
            }
            if (Hasz(H1, pot, L1, P1) == Hasz(H2, pot, n - P2 - 1, n - L2 - 1))
                break;
            ++i;
        }
        if (i == -1 || n - 1 - i + 1 == 2 * dl)
            break;
        node x = Szukaj(i + dl, n - dl - 1);
        if (2 * x.r - 1 + 2 * dl > D)
        {
            D = 2 * x.r - 1 + 2 * dl;
            odp.clear();
            odp.push_back({i, i + dl - 1});
            odp.push_back({x.ind - x.r + 1, x.ind + x.r - 1});
            odp.push_back({n - dl, n - 1});
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (2 * pal[i] - 1 > D)
        {
            D = 2 * pal[i] - 1;
            odp.clear();
            odp.push_back({i - pal[i] + 1, i + pal[i] - 1});
        }
    }
    cout << odp.size() << endl;
    for (int i = 0; i < odp.size(); ++i)
        cout << odp[i].l + 1 << " " << odp[i].p - odp[i].l + 1 << endl;
    return 0;
}

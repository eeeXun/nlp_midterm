
    template<typename It>
    list_update(It first, It last)
    { base_type::copy_from_range(first, last); }

    list_update(const list_update& other)
    : base_type((const base_type&)other) { }

    virtual
    ~list_update() { }

    list_update&
    operator=(const list_update& other)
    {
      if (this !=& other)
 {
   list_update tmp(other);
   swap(tmp);
 }
      return *this;
    }

    void
    swap(list_update& other)
    { base_type::swap(other); }
  };




}
# 20 "data/399.cpp" 2
# 36 "data/399.cpp"

# 36 "data/399.cpp"
using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> Maksat;




const int Max = 100005;

int n, m, ans;

int P[Max<<1], M[Max];

char s[Max], t[Max<<1];

pair< int, int > T[Max<<2], Ans[9];

void Build(int l, int r, int v) {
    if (l == r)
        {T[v] = {P[l+n], l}; return;}

    Build(l, (l+r)/2, v*2+1);
    Build((l+r)/2 +1, r, v*2);

    T[v] = max(T[v*2], T[v*2+1]);
}

pair <int, int> Tap(int x, int y, int l, int r, int v) {
    if (x <= l && r <= y) return T[v];
    if (l > y || r < x) return {0,0};

    return max(Tap(x, y, l, (l+r)/2, v*2+1),
               Tap(x, y, (l+r)/2 +1, r, v*2));
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



    scanf("%s", &s);

    n = strlen(s);

    for (int i=n-1; i>=0; i--) t[m++] = s[i];
    t[m++] = '#';
    for (int i=0; i<=n-1; i++) t[m++] = s[i];

    Kmp();
    Manacher();
    Build(1, n, 1);

    for (int i=0; i<n; i++) {
        pair <int, int> x = Tap(1, i-M[i]+1, 1, n, 1);

        x.second = x.second-x.first+1;

        x.first = min(x.first, n-i-M[i]);

        if (ans < x.first+x.first+(2*M[i]-1)) {
            ans = x.first+x.first+(2*M[i]-1);

            Ans[0] = {x.second, x.first};
            Ans[2] = {n-x.first+1, x.first};
            Ans[1] = {i-M[i]+2, 2*M[i]-1};
        }
    }

    if (Ans[0].second == 0) cout << "1\n";
    else cout << "3\n";

    for (int i=0; i<3; i++)
        if (Ans[i].second != 0)
            cout << Ans[i].first << ' ' << Ans[i].second << '\n';

 return 0;
}

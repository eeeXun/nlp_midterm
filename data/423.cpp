#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define fr first
#define sc second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define SPEED ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define sz size()
#define all(x) x.begin(),x.end()
#define OO 1e18
#define iOO INT_MAX
#define Mdp memset(Dp,-1,sizeof Dp)
#define R return
#define Test int TT;cin>>TT;for(int T=1;T<=TT;T++)
using namespace std;
int n;
string s;
int Tree[4*100010];
vector<int> P;
vector<int> Manacher(string s)
{
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }

    R d1;
}

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    vector<int> Res;
    for(int i=s.sz/2+1;i<z.sz;i++)
        Res.pb(z[i]);
    return Res;
}

void Build(int Node=1,int l=0,int r=n-1)
{
    if(l == r)
    {
        Tree[Node] = P[l];
        R;
    }
    int Mid = (l+r)/2;
    Build(Node*2,l,Mid);
    Build(Node*2+1,Mid+1,r);
    Tree[Node] = max(Tree[Node*2],Tree[Node*2+1]);
}

int Query(int ql,int qr,int Node=1,int l=0,int r=n-1)
{

    if(l > qr || r < ql)
        R 0;

    if(l >= ql && r <= qr)
        R Tree[Node];
    int Mid = (l+r)/2;
    int R1 = Query(ql,qr,Node*2,l,Mid);
    int R2 = Query(ql,qr,Node*2+1,Mid+1,r);
    R max(R1,R2);
}


int Bs(int l,int r,int x,int y)
{
    int Mid = (l+r)/2;

    int Len = 2*Mid+1;

    int ql = x+Mid,qr = y-Mid;
    int Mx = Query(ql,qr);

    if(Mid == r)
    {
        if(Mx-1 >= Mid)
            R Len;
        R Bs(l,Mid-1,x,y);
    }

    int Mid2 = Mid+1;
    int Len2 = 2*Mid2+1;
    ql = x+Mid2,qr = y-Mid2;
    int Mx2 = Query(ql,qr);

    if(Mx-1 >= Mid && Mx2-1 < Mid2)
        R Len;
    if(Mx-1 >= Mid)
        R Bs(Mid+1,r,x,y);
    R Bs(l,Mid-1,x,y);
}

int main()
{
    SPEED;

    cin >> s;
    n = s.sz;

    P = Manacher(s);
    Build();

    string tmp = s;
    reverse(all(tmp));
    tmp += '?';
    tmp += s;
    vector<int> Z = z_function(tmp);

    int Ans = 0;
    vector<pii> Res;
    for(int i=0;i<n;i++)
    {
        if(2*(P[i]-1)+1 > Ans)
        {
            Ans = 2*(P[i]-1)+1;
            Res.clear();
            Res.pb({i+1-(P[i]-1),Ans});
        }
    }
    for(int i=0;i<n;i++)
    {
        int Cur = Z[i];
        if(Cur == 0)
            continue;
        //cout << Cur << endl;
        if(Cur == n-i)
        {
            if(Cur > Ans && Cur%2)
            {
                Ans = Cur;
                Res.clear();
                Res.pb({i+1,Cur});
            }
        }
        else
        {
            int l = i+Cur;
            int r = n-Cur-1;
            int Len = r-l+1;
            if(Len%2 == 0)
                Len--;
            int Mx = Bs(0,Len/2,l,r);
            if(2*Cur + Mx > Ans)
            {
                Ans = 2*Cur + Mx;
                Res.clear();
                Res.pb({i+1,Cur});
                Res.pb({r+2,Cur});
                Res.pb({Mx,-1});
            }
        }

    }

    if(Res.sz == 1)
    {
        cout << 1 << endl;
        cout << Res[0].fr << " " << Res[0].sc << endl;
    }
    else
    {
        cout << 3 << endl;
        int Need = Res[2].fr;
        Need /= 2;
        Res.pop_back();
        for(int i=Res[0].fr-1+Res[0].sc+Need;;i++)
        {
            if(P[i] == Need+1)
            {
                Res.insert(Res.begin()+1,{i+1-Need,2*Need+1});

                break;
            }
        }
        for(int i=0;i<Res.sz;i++)
        {
            cout << Res[i].fr << " " << Res[i].sc << endl;
        }
    }


    R 0;
}

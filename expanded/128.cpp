# 3 "data/128.cpp"
using namespace std;
const int MAXN = 200100;

const int alpha = 300;

int c[20][MAXN] , p[MAXN] , cn[MAXN] , pn[MAXN] , cnt[MAXN];

void suffix_ini(string s){
    int n = s.size();

    for(int i = 0;i < n;i++) cnt[s[i]] ++;
    for(int i = 1;i < alpha;i++) cnt[i] += cnt[i - 1];
    for(int i = n - 1;i >= 0;i--) p[--cnt[s[i]]] = i;

    int cla = 0;
    c[0][p[0]] = 0;

    for(int i = 1;i < n;i++){
        if(s[p[i]] != s[p[i - 1]]) ++cla;
        c[0][p[i]] = cla;
    }
}

void suffix(string s){
    int n = s.size();

    for(int h = 0;(1 << h) < n;h++){
        for(int i = 0;i < n;i++){
            pn[i] = p[i] - (1 << h);
            if(pn[i] < 0) pn[i] += n;
        }

        memset(cnt,0,sizeof cnt);

        for(int i = 0;i < n;i++) cnt[c[h][pn[i]]] ++;
        for(int i = 0;i < n;i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1;i >= 0;i--) p[--cnt[c[h][pn[i]]]] = pn[i];

        int cla = 0;
        cn[p[0]] = 0;

        for(int i = 1;i < n;i++){
            pair<int,int> cur = {c[h][p[i]],c[h][(p[i] + (1 << h)) % n]};
            pair<int,int> pre = {c[h][p[i - 1]],c[h][(p[i - 1] + (1 << h)) % n]};

            if(cur.first != pre.first || cur.second != pre.second) cla ++;
            cn[p[i]] = cla;
        }

        for(int i = 0;i < n;i++) c[h + 1][i] = cn[i];
    }
}

int g[MAXN];
int pal[MAXN];

int comp(int x,int y){
    int res = 0;

    for(int i = 19;i >= 0;i--){
        if(c[i][x] == c[i][y] && c[i][x] != -1){
            res += (1 << i);
            x += (1 << i);
            y += (1 << i);
        }
    }

    return res;
}

int main(){
    memset(c,-1,sizeof c);

    string s;
    cin >> s;

    int n = s.size();

    string is;
    for(int i = s.size() - 1;i >= 0;i--){
        is += s[i];
    }

    s = is + s;
    s += "$";



    suffix_ini(s);
    suffix(s);

    int last = n;

    int p = 0;

    while(p < n && last < s.size()){
        int r = comp(0,last);

        if(r < p + 1) last ++;
        else g[last - n + p] = p + 1, p ++;
    }

    for(int i = 1;i < n;i++){
        g[i] = max(g[i - 1], g[i]);
    }

    for(int i = 0;i < n;i++){
        pal[i] = comp(n + i,n - 1 - i);
        pal[i] = min({pal[i],i + 1,n - i + 1});
    }


    vector<pair<int,int>> resp;

    int soma = 0;
    int k = -1;
    for(int i = 0;i < n;i++){
        int at = 0;

        at += 2 * pal[i] - 1;

        if(at - pal[i] >= 0){
            int r1 = 2 * g[i - pal[i]];
            int r2 = 2 * (n - (i + pal[i]));



            at += min(r1, r2);
        }

        if(at >= soma){
            soma = at;
            k = i;
        }
    }

    for(int i = 0;i < n;i++){
        int at = 2 * pal[k] - 1;

        if(at == soma){
            cout << 1 << endl;
            if(soma >= n) cout << 1 << " " << n + (n % 2 - 1) << endl;
            else cout << k - pal[k] + 2 << " " << at << endl;
            return 0;
        }

        if(at + 2*g[i] >= soma){

            cout << 3 << endl;
            cout << i - g[i] + 2 << " " << g[i] << endl;
            cout << k - pal[k] + 2 << " " << at << endl;
            cout << n - (soma - at) / 2 + 1 << " " << g[i] << endl;
            return 0;
        }
    }

    cout << k << " " << soma << endl;
}

#include<bits/stdc++.h>

#define sz(a) (int)a.size()
#define pb push_back
#define all(a) a.begin(), a.end()
#define for0(i, n) for(int i = 0; i < n; i++)
#define for1(i, n) for(int i = 1; i <= n; i++)
#define x first
#define y second
#define int long long

using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;


//const int M = 4398042316799;
const int M = 1e9 + 7;
const int P = 239017;

int binprod(int a, int b){
    return (a * b) % M;
}


//int binprod (int a, int b) {
//	int res = 0;
//	while (b) {
//        res = (res + a * (b % 1024)) % M;
//		a = (1024 * a) % M;
//		b = b / 1024;
//	}
//	return res;
//}

// deg[] = {1, P, P^2, P^3, ...}
// h[] = {0, s[0], s[0]*P + s[1], s[0]*P^2 + s[1]*P + s[2], ...}

void start(string &s, vi &h, vi &deg){
    int n = sz(s);
h.resize(n + 1), deg.resize(n + 1);
h[0] = 0, deg[0] = 1;

    for (int i = 0; i < n; i++) {
        h[i + 1] = ((binprod(h[i], P)) % M + s[i]) % M;
        deg[i + 1] = (binprod(deg[i], P)) % M;

    }
}


int get_hash(int l, int r, vi &h, vi &deg) {

  return  (h[r + 1] + M - (binprod(h[l],deg[r - l + 1])) % M) % M;


}

signed main(){
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
       ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

   string s, rs;
   cin >> s;
   int n = sz(s);
   rs = s;
   reverse(all(rs));
   vi h, deg,rh, rdeg;
   start(s, h, deg);
   start(rs, rh, rdeg);

   vi mxpal(n, 1);

   for0(i, n){
        int ri = n - 1 - i;
        int L = 0;
        int R = min(i, ri) + 1;
        while(R - L > 1){
            int M = (R + L) / 2;
            int H = get_hash(i - M, i + M, h, deg);
            int rH = get_hash(ri - M, ri + M, rh, rdeg);

            if(H == rH)
                L = M;
            else
                R = M;
        }

        mxpal[i] = L;
        //cout << i << ": "<<L<<endl;
   }

        vi posleft(n + 1);
        int t = 0;
        for0(i, n){
            int rH = get_hash(0, i, rh, rdeg);
            while(t < n && get_hash(t, t + i, h, deg) != rH)
                t++;
            posleft[i] = t;
        }

//        for0(i, n)
//            cout << i << ": "<<posleft[i]<<endl;

int mxans = 0, lla = -1, dla, rla, dra, cla, dca;

for0(i, n){
    if(2 * mxpal[i] + 1 > mxans){
        cla = i - mxpal[i];
        dca = 2 * mxpal[i] + 1;
        mxans = 2 * mxpal[i] + 1;
    }
}

//cout <<"mxans = "<<mxans<<endl;

        for0(i, n){
            int lpal = i - mxpal[i];
            int rpal = i + mxpal[i];


            if(rpal < n - 1 && posleft[0] < lpal){
                int R = n - 1 - rpal;
                int L = 0;
                while(R - L > 1){
                    int M = (R + L) / 2;

                    if(posleft[M] + M < lpal)
                        L = M;
                    else
                        R = M;
                }
                    if(rpal - lpal + 1 + 2 *(L + 1) > mxans){
                        //cout << i <<": "<<lpal<<' '<<rpal<<" - "<< rpal - lpal + 1 + 2 *(L + 1) << endl;
                        cla = lpal;
                        dca = rpal - lpal + 1;
                        lla = posleft[L];
                        dla = L + 1;
                        rla = n - 1 - L;
                        dra = L + 1;
                        mxans = rpal - lpal + 1 + 2 *(L + 1);
                    }

            }
        }

        if(lla == -1){
            cout << 1 << endl;
            cout << cla + 1<<' '<<dca<<endl;
        }
        else{
            cout << 3<< endl;
            cout << lla + 1 << ' ' << dla << endl;
            cout << cla + 1 << ' ' << dca << endl;
            cout << rla + 1 << ' ' << dra << endl;
        }

}

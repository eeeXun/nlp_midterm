    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/468.cpp" 2
# 12 "data/468.cpp"

# 12 "data/468.cpp"
using namespace std;
typedef pair<long long, long long> pii;
typedef vector<long long> vi;
typedef vector<vector<long long> > vvi;



const long long M = 1e9 + 7;
const long long P = 239017;

long long binprod(long long a, long long b){
    return (a * b) % M;
}
# 40 "data/468.cpp"
void start(string &s, vi &h, vi &deg){
    long long n = (long long)s.size();
h.resize(n + 1), deg.resize(n + 1);
h[0] = 0, deg[0] = 1;

    for (long long i = 0; i < n; i++) {
        h[i + 1] = ((binprod(h[i], P)) % M + s[i]) % M;
        deg[i + 1] = (binprod(deg[i], P)) % M;

    }
}


long long get_hash(long long l, long long r, vi &h, vi &deg) {

  return (h[r + 1] + M - (binprod(h[l],deg[r - l + 1])) % M) % M;


}

signed main(){


       ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

   string s, rs;
   cin >> s;
   long long n = (long long)s.size();
   rs = s;
   reverse(rs.begin(), rs.end());
   vi h, deg,rh, rdeg;
   start(s, h, deg);
   start(rs, rh, rdeg);

   vi mxpal(n, 1);

   for(long long i = 0; i < n; i++){
        long long ri = n - 1 - i;
        long long L = 0;
        long long R = min(i, ri) + 1;
        while(R - L > 1){
            long long M = (R + L) / 2;
            long long H = get_hash(i - M, i + M, h, deg);
            long long rH = get_hash(ri - M, ri + M, rh, rdeg);

            if(H == rH)
                L = M;
            else
                R = M;
        }

        mxpal[i] = L;

   }

        vi posleft(n + 1);
        long long t = 0;
        for(long long i = 0; i < n; i++){
            long long rH = get_hash(0, i, rh, rdeg);
            while(t < n && get_hash(t, t + i, h, deg) != rH)
                t++;
            posleft[i] = t;
        }




long long mxans = 0, lla = -1, dla, rla, dra, cla, dca;

for(long long i = 0; i < n; i++){
    if(2 * mxpal[i] + 1 > mxans){
        cla = i - mxpal[i];
        dca = 2 * mxpal[i] + 1;
        mxans = 2 * mxpal[i] + 1;
    }
}



        for(long long i = 0; i < n; i++){
            long long lpal = i - mxpal[i];
            long long rpal = i + mxpal[i];


            if(rpal < n - 1 && posleft[0] < lpal){
                long long R = n - 1 - rpal;
                long long L = 0;
                while(R - L > 1){
                    long long M = (R + L) / 2;

                    if(posleft[M] + M < lpal)
                        L = M;
                    else
                        R = M;
                }
                    if(rpal - lpal + 1 + 2 *(L + 1) > mxans){

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

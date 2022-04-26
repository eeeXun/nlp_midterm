#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <vector>


int crypt_len;
std::vector<std::pair<int, int> > solution;
std::string crypt, r_crypt;


struct bit {
    int capacity;
    std::vector<int> data;

    bit ( void ) : capacity(0) { }

    void resize ( int c ) {
        capacity = c;
        data.resize(c, 1e9);
    }

    void update ( int pos , int val ) {
        while ( pos > 0 ) {
            data[pos] = std::min(val, data[pos]);
            pos -= pos & (-pos);
        }
    }

    int query ( int pos ) {
        int answer = 1e9;
        if ( pos != 0 ) {
            while ( pos < capacity ) {
                answer = std::min(data[pos], answer);
                pos += pos & (-pos);
            }
        }
        return answer;
    }
};


template <class iterator>
void manacher ( const iterator fr , const iterator to , std::vector<int>& P ) {
    int R, C;
    int str_len;
    int i, i2, l, r, Ri, n;

    C = R = -1;
    str_len = to - fr;
    n = (str_len - 1) << 1;

    P.resize(n + 1);

    for ( i = 0 ; i <= n ; ++i ) {

        i2 = 2*C - i;
        P[i] = (R >= i) ? std::min(R - i + 1, P[i2]) : !(i % 2);

        l = (i - P[i]) >> 1;
        r = (i + P[i] + 1) >> 1;

        while ( l >= 0 && r < str_len && fr[l] == fr[r] ) {
            P[i] += 2;
            l -= 1; r += 1;
        }

        Ri = P[i] ? ((i + P[i]) >> 1) << 1 : i;
        if ( Ri > R ) {
            C = i;
            R = Ri;
        }
    }
}

template <class iterator>
void Z_algorithm ( const iterator fr , const iterator to , std::vector<int>& z ) {
    const int N = to - fr;
    int L, R, i, k;

    z.clear();
    z.resize (N);
    z[0] = N;

    L = 0;
    R = 0;
    for ( i = 1 ; i < N ; ++ i ) {
        if ( i > R ) {
            L = R = i;
            while ( R < N && fr[R-L] == fr[R] ) {
                R++;
            }
            z[i] = R - L;
            -- R;
        }
        else {
            k = i - L;
            if ( z[k] < R - i + 1 ) {
                z[i] = z[k];
            }
            else {
                L = i;
                while ( R < N && fr[R - L] == fr[R] ) {
                    ++ R;
                }
                z[i] = R - L;
                -- R;
            }
        }
    }
}

void bsearch ( void ) {
    bit leftmost;
    std::string text;
    std::vector<int> P, z;

    int max;
    int left, right;
    int i, lo, hi, mid;

    text = r_crypt + crypt;
    Z_algorithm(text.begin(), text.end(), z);
    manacher(crypt.begin(), crypt.end(), P);

    leftmost.resize(crypt_len + 1);
    for ( i = crypt_len ; i < text.size() ; ++ i ) {
        leftmost.update(z[i], i - crypt_len + z[i] - 1);
    }

    for ( i = crypt_len - 1 ; i > 0 ; -- i ) {
        z[i] = leftmost.query(i);
    }

    max = 0;
    for ( i = 0 ; i < P.size() ; i += 2 ) {
        left = (i >> 1) - (P[i] >> 1);
        right = (i >> 1) + (P[i] >> 1);

        lo = 0;
        hi = crypt_len - right - 1;

        while ( lo != hi ) {
            if ( lo + 1 == hi ) {
                if ( z[hi] < left ) {
                    lo = hi;
                }
                break;
            }

            mid = (lo + hi) >> 1;

            if ( z[mid] < left ) {
                lo = mid;
            }
            else {
                hi = mid - 1;
            }
        }

        if ( lo + P[i] + lo > max ) {
            max = lo + P[i] + lo;
            solution.clear();
            if ( lo == 0 ) {
                solution.push_back(std::make_pair(left + 1, right - left + 1));
            }
            else {
                solution.push_back(std::make_pair(z[lo] - lo + 2, lo));
                solution.push_back(std::make_pair(left + 1, right - left + 1));
                solution.push_back(std::make_pair(crypt_len - lo + 1, lo));
            }
        }
    }

}


int main ( void ) {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(static_cast<std::ostream*>(nullptr));

    std::cin >> crypt;

    r_crypt = crypt;
    crypt_len = crypt.size();

    std::reverse(r_crypt.begin(), r_crypt.end());
    bsearch();

    std::cout << solution.size() << std::endl;
    for ( std::pair<int, int>& p : solution ) {
        std::cout << p.first << " " << p.second << std::endl;
    }

    return 0;
}

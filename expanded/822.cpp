# 71 "/usr/include/c++/11.2.0/set" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

  namespace pmr
  {
    template<typename _Tp> class polymorphic_allocator;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using set = std::set<_Key, _Cmp, polymorphic_allocator<_Key>>;
    template<typename _Key, typename _Cmp = std::less<_Key>>
      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 15 "data/822.cpp" 2


# 16 "data/822.cpp"
using namespace std;


const int MAX_N = 200005;


int P[MAX_N];
char __s[MAX_N];



char ss[MAX_N * 2 + 5];
int manacher(char* s) {
    int n = strlen(s);
    if (n <= 1) {
        return n;
    }


    for (int i = 0; i < 2*n+1; i++) {
        if (i & 1) {
            ss[i] = s[i>>1];
        } else {
            ss[i] = '#';
        }
    }

    P[0] = 1;
    int L = 0, R = 0;
    int max_r = 1;
    for (int i = 1; i < 2*n+1; i++) {
        if (i > R) {
            int ll = i, rr = i;
            while (ll-1 >= 0 && rr+1 < 2*n+1 && ss[ll-1] == ss[rr+1]) {
                ll--, rr++;
            }
            P[i] = rr - i + 1;
        } else {
            int j = L + R - i;
            int l_bound = j - P[j] + 1;
            if (l_bound > L) {
                P[i] = P[j];
            } else if (l_bound < L) {
                P[i] = R - i + 1;
            } else {
                int ll = i-P[j]+1, rr = i+P[j]-1;
                while (ll-1 >= 0 && rr+1 < 2*n+1 && ss[ll-1] == ss[rr+1]) {
                    ll--, rr++;
                }
                P[i] = rr - i + 1;
            }
        }

        if (i + P[i] - 1 > R) {
            R = i + P[i] - 1;
            L = i - P[i] + 1;
        }

        max_r = max(max_r, P[i]);
    }

    return max_r - 1;
}


int pi[MAX_N];
int* get_kmp_pi(char* s, int n) {
    memset(pi, 0, sizeof(int) * n);
    pi[0] = 0;
    int i = 1, j = 0;
    while (i < n) {
        if (s[i] == s[j]) {
            pi[i] = j + 1;
            i++, j++;
        } else {
            if (j == 0) {
                i++;
            } else {
                j = pi[j-1];
            }
        }
    }

    return pi;
}


char buf[MAX_N];
int p_len[MAX_N];
int match[MAX_N];
int match_pos[MAX_N];


char buf1[MAX_N];

struct node {
    int a, b;
};


int main() {



    scanf("%s", buf);
    int n = strlen(buf);
    manacher(buf);

    for (int i = 0; i < n; i++) {
        p_len[i] = ((P[i*2 + 1] - 1) / 2) + 1;
    }

    int idx = 0;
    for (int i = n-1; i >= 0; i--) {
        buf1[idx++] = buf[i];
    }
    buf1[idx++] = '?';
    strcpy(buf1+idx, buf);
    get_kmp_pi(buf1, 2*n+1);

    for (int i = n+1; i < 2*n+1; i++) {
        match[i - (n+1)] = pi[i];
    }

    match_pos[0] = 0;
    for (int i = 1; i < n; i++) {
        if (match[i] > match[i-1]) {
            match_pos[i] = i;
        } else {
            match[i] = match[i-1];
            match_pos[i] = match_pos[i-1];
        }

        match[i] = max(match[i], match[i-1]);
    }


    int ll[2], rr[2], mm[2];
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int left_len = n-1 - (i + p_len[i] - 1);

        if (left_len == 0 || i - (p_len[i] - 1) == 0 || match[i - (p_len[i] - 1)-1] == 0) {

            if (2 * p_len[i] - 1 > max_len) {
                max_len = 2 * p_len[i] - 1;
                ll[0] = ll[1] = -1;
                rr[0] = rr[1] = -1;
                mm[0] = i - (p_len[i]-1);
                mm[1] = i + (p_len[i]-1);
            }
        } else {
            int prefix_len = min(left_len, match[i - (p_len[i] - 1)-1]);

            int cur_len = 2 * p_len[i] - 1 + prefix_len * 2;
            if (cur_len > max_len) {
                max_len = cur_len;
                ll[0] = match_pos[i - (p_len[i] - 1)-1] - prefix_len + 1;
                ll[1] = match_pos[i - (p_len[i] - 1)-1];
                rr[0] = n-1 - prefix_len + 1;
                rr[1] = n-1;
                mm[0] = i - (p_len[i]-1);
                mm[1] = i + (p_len[i]-1);
            }
        }
    }

    vector<node> v;
    v.push_back({ll[0], ll[1]});
    v.push_back({mm[0], mm[1]});
    v.push_back({rr[0], rr[1]});

    vector<node> ans;
    for (auto& val : v) {
        if (val.a == -1) {
            continue;
        }

        ans.push_back({val.a, val.b});
    }

    printf("%lu\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].a+1, ans[i].b - ans[i].a + 1);
    }

    return 0;
}

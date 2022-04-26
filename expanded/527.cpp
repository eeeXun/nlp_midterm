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
# 12 "data/527.cpp" 2

# 12 "data/527.cpp"
using namespace std;







typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> pii;


const int N = 101111;



void manacher(char s[], int p[], int n) {
    int maxid=0;
    for (int i=1;i<=n;i++) {
        if (maxid+p[maxid]>=i) p[i]=min(p[maxid*2-i],maxid+p[maxid]-i);
        else p[i]=0;
        while (i+p[i]<n && s[i+p[i]+1]==s[i-p[i]-1]) p[i]++;
        if (i+p[i]>maxid+p[maxid]) maxid=i;

    }

}

void kmp(char s[], int fail[], int n){
    memset(fail, 0, sizeof(fail));
    for (int i = 2; i <= n; i++){
        int p = fail[i - 1];
        while (p && s[i] != s[p + 1])
            p = fail[p];
        if (s[i] == s[p + 1])
            fail[i] = p + 1;


    }
}




char S[N], rev[N];
int fail[N];
pii lst[N];
int t[N], n;
int main(){
    scanf("%s", S + 1);
    n = strlen(S + 1);
    manacher(S, t, n);
    for (int i=(1);i<=(n);i++){
        rev[i] = S[n - i + 1];
    }
# 79 "data/527.cpp"
    kmp(rev, fail, n);
    int p = 0;
    for (int i=(1);i<=(n);i++){
        while (p && rev[p + 1] != S[i])
            p = fail[p];
        if (rev[p + 1] == S[i])
            p++;
        else
            p = 0;
        lst[i] = pii(p, i);
    }
    for (int i=(2);i<=(n);i++){
        lst[i] = max(lst[i], lst[i - 1]);
    }
    pii ans = pii(0, 0);
    for (int i=(1);i<=(n);i++){
        int tmp = t[i] * 2 + 1;
        int right_len = n - (i + t[i]);
        tmp += min(right_len, lst[i - t[i] - 1].first) * 2;
        ans = max(ans, pii(tmp, i));
    }
    if (ans.first == t[ans.second] * 2 + 1){
        printf("1\n%d %d\n", ans.second - t[ans.second], t[ans.second] * 2 + 1);
    }
    else{
        printf("3\n");
        int p = ans.second;
        {
            int right_len = n - (p + t[p]), left_pos = lst[p - t[p] - 1].second;
            if (right_len < lst[p - t[p] - 1].first)
                printf("%d %d\n", left_pos - lst[left_pos].first + 1, right_len);
            else
                printf("%d %d\n", left_pos - lst[left_pos].first + 1, lst[left_pos].first);
        }
        printf("%d %d\n", p - t[p], t[p] * 2 + 1);
        printf("%d %d\n", n - (ans.first - (t[ans.second] * 2 + 1)) / 2 + 1, (ans.first - (t[ans.second] * 2 + 1)) / 2);
    }
    return 0;
}

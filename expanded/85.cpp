# 3 "data/85.cpp"
const int MAX_N = 100000;
int expand[MAX_N];
int kmp[MAX_N+1+MAX_N], bestsuff[1+MAX_N];

void run_manacher(int N, const std::string &str) {
    int center = 0;
    expand[center] = 0;
    for(int i = 1; i < N; ++i) {

        if(i > center + expand[center])
            center = i;

        expand[i] = expand[center - (i - center)];
        if(i + expand[i] >= center + expand[center]) {
            expand[i] = (center + expand[center]) - i;
            center = i;
        }

        while(center + expand[center] + 1 < N && center - expand[center] - 1 >= 0
        && str[center + expand[center] + 1] == str[center - expand[center] - 1])
            ++expand[center];
    }
}

void run_kmp(int N, std::string &str) {
    kmp[0] = 0;
    for(int i = 1; i < N; ++i) {
        kmp[i] = kmp[i - 1];
        while(kmp[i] > 0 && str[i] != str[kmp[i]])
            kmp[i] = kmp[kmp[i] - 1];
        if(str[i] == str[kmp[i]])
            ++kmp[i];
    }
}

int best_len;
std::vector<std::pair<int, int> > pieces;

int main() {
    std::string str;

    std::cin >> str;
    int N = str.size();

    std::reverse(str.begin(), str.end());

    str.push_back('!');
    for(int i = N - 1; i >= 0; --i)
        str.push_back(str[i]);

    run_manacher(N, str);
    run_kmp(N + 1 + N, str);

    for(int i = 1; i <= N; ++i) {
        bestsuff[i] = bestsuff[i - 1];
        if(kmp[N + i] > kmp[bestsuff[i]])
            bestsuff[i] = N + i;
    }

    for(int i = 0; i < N; ++i) {

        int len = 1 + 2 * expand[i];
        int sufflen = N - (i + expand[i]) - 1;
        int best_suff_len = std::min(kmp[bestsuff[sufflen]], i - expand[i]);
        len += 2 * best_suff_len;
        if(len > best_len) {
            best_len = len;
            pieces.clear();
            pieces.push_back({1 + i - expand[i], 1 + 2 * expand[i]});
            if(best_suff_len > 0) {
                pieces.push_back({1, best_suff_len});
                pieces.push_back({1 + N * 2 - (bestsuff[sufflen] - (kmp[bestsuff[sufflen]] - best_suff_len)),
                    best_suff_len});
            }
        }

    }


    for(int i = 0; i < pieces.size(); ++i) {
        pieces[i].first = N - pieces[i].first + 1;
        pieces[i].first = pieces[i].first - pieces[i].second + 1;
    }
    std::sort(pieces.begin(), pieces.end());

    std::cout << pieces.size() << "\n";
    for(auto it: pieces)
        std::cout << it.first << " " << it.second << "\n";

    return 0;
}

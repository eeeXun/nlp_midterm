
# 3 "data/971.cpp"
using namespace std;


string str, t;
int d1[100005], d2[100005];

vector<int> prefix_function(string str)
{
    int n = (int)str.length();
    vector<int> pi(n);
    pi[0] = 0;
    for(int i=1; i<n; i++){
        int j = pi[i-1];
        while(j > 0 && str[i] != str[j]){
            j = pi[j-1];
        }
        if(str[i] == str[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

void manacher()
{
    int n = str.length();
    for(int i=0, l=0, r=-1; i<n; i++){
        int k = (i>r) ? 1:min(d1[r-i+l], r-i);
        while(i-k>=0 && i+k<n && str[i-k]==str[i+k]){
            k++;
        }
        d1[i] = k--;
        if(i+k>r){
            r = i+k;
            l = i-k;
        }
    }
    for(int i=0, l=0, r=-1; i<n; i++){
        int k = (i>r) ? 0:min(d2[r-i+l+1], r-i+1);
        while(i-k-1>=0 && i+k<n && str[i-k-1]==str[i+k]){
            k++;
        }
        d2[i] = k--;
        if(i+k>r){
            r = i+k;
            l = i-k-1;
        }
    }
}

int main()
{

    cin >> str;
    string temp = str;
    reverse(temp.begin(), temp.end());
    t = temp + "#" + str;
    int len = str.length();
    vector<int> pi = prefix_function(t);
    int maxs = 0;
    int table[len];
    for(int i=len+1; i<t.length(); i++){
        if(pi[i] > maxs){
            int pos = i-(len+1);
            int k = 0;
            for(int j=pi[i]; j>maxs; j--){
                table[j] = pos-k;
                k--;
            }
            maxs = pi[i];
        }
    }
    int ans = 0;
    int n = str.length();
    manacher();
    vector<pair<int, int> > V;
    for(int i=0; i<n; i++){
        int k = d1[i];
        int l = i-k;
        int r = i+k;
        int tot = 2*k-1;
        if(l >= 0 && r < n){
            int last = n-r;
            int mins = min(last, maxs);
            int lo = 1, hi = mins, best = -1, sol = -1;
            while(lo<=hi){
                int mid = (lo+hi)/2;
                if(table[mid] <= l){
                    best = mid;
                    sol = table[mid];
                    lo = mid+1;
                }
                else hi = mid-1;
            }
            if(best != -1){
                tot += 2*best;
                if(tot > ans){
                    ans = tot;
                    V.clear();
                    V.push_back(make_pair(sol-best+1+1, best));
                    V.push_back(make_pair(i-k+1+1, 2*k-1));
                    V.push_back(make_pair(n-best+1, best));
                }
            }
            else {
                if(tot > ans){
                    ans = tot;
                    V.clear();
                    V.push_back(make_pair(i-k+1+1, 2*k-1));
                }
            }
        }
        else {
            if(tot > ans){
                ans = tot;
                V.clear();
                V.push_back(make_pair(i-k+1+1, 2*k-1));
            }
        }
    }
    cout << V.size() << endl;
    for(int i=0; i<V.size(); i++) cout << V[i].first << " " << V[i].second << endl;
}

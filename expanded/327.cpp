}
# 5 "data/327.cpp" 2


# 6 "data/327.cpp"
using namespace std;
typedef unsigned long long ULL;
const int MAXN = 100000;
const ULL Base = 27;
ULL Hash_bak[MAXN+10], pw27[MAXN+10], Hash[MAXN+10];
int pre_tar[MAXN+10];
char str[MAXN+10];
int main(){
    memset(pre_tar, 0x3f, sizeof pre_tar);
    scanf("%s", str+1);
    int n = strlen(str+1);
    pw27[0] = 1;
    for(int i=1,j=n;i<=n;i++,j--){
        Hash_bak[i] = Hash_bak[i-1]*Base+str[j]-'a'+1;
        pw27[i] = pw27[i-1]*Base;
    }
    for(int i=1;i<=n;i++)
        Hash[i] = Hash[i-1]*Base+str[i]-'a'+1;
    int bp = n;
    for(int i=1;i<=n;i++){
        int L = i, R = n, pos = i-1;
        while(L <= R){
            int mid=(L+R)>>1;
            if((Hash[mid]-Hash[i-1]*pw27[mid-i+1]) == Hash_bak[mid-i+1]){
                pos = mid;
                L = mid+1;
            }else R = mid-1;
        }
        int bakp = n-(pos-i+1)+1;
        for(;bp>=bakp;bp--)
            pre_tar[bp] = i+n-bp;
    }
    int ans = 0;
    int L1, L2, L3, R1, R2, R3;
    for(int i=1;i<=n;i++){
        int L = 2, R = min(n-i+1, i), rd = 1;
        while(L <= R){
            int mid=(L+R)>>1;
            if(Hash[i+mid-1]-Hash[i-1]*pw27[mid] == Hash_bak[n-i+mid]-Hash_bak[n-i]*pw27[mid]){
                rd = mid;
                L = mid+1;
            }else R = mid-1;
        }
        L = i+rd, R = n;
        int pos = n+1;
        while(L <= R){
            int mid=(L+R)>>1;
            if(pre_tar[mid] >= i-rd+1)
                L = mid+1;
            else{
                R = mid-1;
                pos = mid;
            }
        }
        int cur_len = rd*2-1+2*(n-pos+1);

        int hlen = n-pos+1;
        if(cur_len > ans){
            ans = cur_len;
            L1 = L2 = L3 = R1 = R2 = R3 = -1;
            L1 = i-rd+1, R1 = i+rd-1;
            if(hlen){
                L2 = pos, R2 = n;
                L3 = pre_tar[pos]-hlen+1;
                R3 = pre_tar[pos];
            }
        }
    }
    vector<pair<int,int> > vec;
    vec.push_back(make_pair(L1, R1));
    if(L2 != -1){
        vec.push_back(make_pair(L2, R2));
        vec.push_back(make_pair(L3, R3));
    }
    sort(vec.begin(), vec.end());
    printf("%d\n", (int)vec.size());
    for(int i=0;i<(int)vec.size();i++)
        printf("%d %d\n", vec[i].first, vec[i].second-vec[i].first+1);

    return 0;
}

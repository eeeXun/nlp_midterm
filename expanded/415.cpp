  priority_queue<_Tp, _Sequence, _Compare>& __y)
    noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y); }

  template<typename _Tp, typename _Sequence, typename _Compare,
    typename _Alloc>
    struct uses_allocator<priority_queue<_Tp, _Sequence, _Compare>, _Alloc>
    : public uses_allocator<_Sequence, _Alloc>::type { };



}
# 65 "/usr/include/c++/11.2.0/queue" 2 3
# 10 "data/415.cpp" 2
# 18 "data/415.cpp"

# 18 "data/415.cpp"
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;



uLL base[100010];
char str[100010];
int L[100010],pos[100010];

vector<pii> v;
int maxL;

int main(){
    scanf("%s", str );
    int len = strlen(str);
    for(int i = 0; i<len; i++) base[i] = i?base[i-1]*37:1;
    L[0] = 1;
    for (int i = 1, lim = 0,x = 0; str[i]; i++){
        if ( i > lim ) L[i] = 1;
        else L[i] = min( L[x*2-i] , lim-i+1);

        while ( i+L[i]<len && i>=L[i] && str[i+L[i]] == str[i-L[i]] && i+L[i] >= lim ){
            L[i]++;
            lim++;
            x = i;
        }

    }
    pos[0] = 0;
    uLL last = 0, first = 0;
    for (int i = 1; i*2<len; i++){
        last = last*37 + (str[len-i]-'a'+1);
        first = first*37 + (str[pos[i-1]+i-1] -'a'+1);
        pos[i] = pos[i-1];
        while ( pos[i]+i<len && last != first ) {
            first -= (str[pos[i]]-'a'+1)*base[i-1];
            first = first*37 + (str[pos[i]+i] -'a'+1);
            pos[i]++;
        }
    }
    for(int i = 0; i<len; i++){
        int st = i-L[i], ed = i+L[i];
        int g = 1 , h = min( st+1 , len-ed ), ans = 0;
        while ( g <= h ) {
            int mid = (g+h)/2;
            if ( pos[mid]+mid-1 <= st ) ans = mid , g = mid+1;
            else h = mid-1;
        }
        if ( L[i]*2-1+ans*2 > maxL ){
            maxL = L[i]*2-1+ans*2;
            v.clear();
            if ( ans ) v.push_back( make_pair(pos[ans],ans) );
            v.push_back( make_pair(i-L[i]+1,L[i]*2-1) );
            if ( ans ) v.push_back( make_pair(len-ans,ans) );
        }
    }
    printf("%d\n" , (int)v.size() );
    for( __typeof(v.begin()) it = v.begin(); it!=v.end(); it++) printf("%d %d\n" , it->first+1 , it->second );
    return 0;
}

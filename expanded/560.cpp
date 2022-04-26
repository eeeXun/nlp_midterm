using std::fmin;
using std::hypot;
using std::ilogb;
using std::lgamma;
using std::llrint;
using std::llround;
using std::log1p;
using std::log2;
using std::logb;
using std::lrint;
using std::lround;
using std::nearbyint;
using std::nextafter;
using std::nexttoward;
using std::remainder;
using std::remquo;
using std::rint;
using std::round;
using std::scalbln;
using std::scalbn;
using std::tgamma;
using std::trunc;
# 18 "data/560.cpp" 2


# 19 "data/560.cpp"
using namespace std;
# 29 "data/560.cpp"
typedef long long lli;







const int maxn=2*100000+10, MOD=1000*1000*1000+7, INF=1000*1000*1000;
const double EPS=1e-9, PI=2*acos(0.0);


int till[maxn];



class KMP{
public:
    vector <int> back;
    string pattern, motherStr;
    int itI, itJ;

    void preProcess(){
        int i, j;
        i = 0;
        j = -1;
        back.push_back(-1);
        while(i < pattern.size()){
            while(j >= 0 && pattern[i] != pattern[j]) j = back[j];
            i++; j++;
            back.push_back(j);
        }
    }

    KMP(string motherStr): motherStr(motherStr){}

    void search(){
        int sz;
        sz=motherStr.size();
        itI=itJ=0;
        while(itI < motherStr.size()){
            while(itJ >= 0 && motherStr[itI] != pattern[itJ]) itJ = back[itJ];
            till[itI]=itJ+1;
            itI++; itJ++;
            if(itJ == pattern.size())
                return;
        }
    }

    void clear(){
        back.clear();
        pattern.clear();
        motherStr.clear();
    }

};



template <class RAI1,class RAI2>
void manacher(RAI1 seq,RAI1 seqEnd,RAI2 out)
{
    int seqLen=seqEnd-seq;
    int i=0,j,d,s,e,lLen,k=0;
    int palLen=0;
    while (i<seqLen)
    {
        if (i>palLen && seq[i-palLen-1]==seq[i])
        {
            palLen+=2;
            i++;
            continue;
        }
        out[k++]=palLen;
        s=k-2;
        e=s-palLen;
        bool b=true;
        for (j=s; j>e; j--)
        {
            d=j-e-1;
            if (out[j]==d)
            {
                palLen=d;
                b=false;
                break;
            }
            out[k++]=min(d,out[j]);
        }
        if (b)
        {
            palLen=1;
            i++;
        }
    }
    out[k++]=palLen;
    lLen=k;
    s=lLen-2;
    e=s-(2*seqLen+1-lLen);
    for (i=s; i>e; i--)
    {
        d=i-e-1;
        out[k++]=min(d,out[i]);
    }
}

pair<int, int> maxtill[maxn];

void solve(string str){
    int sz, i;
    sz=str.size();

    if(sz<3){
        cout << 1 << endl;
        if(sz==2){
            if(str[0]==str[1]){
                cout << 1 << ' ' << 2 << endl;
                return;
            }
        }
        cout << 1 << ' ' << 1 << endl;
        return;
    }


    vector<int> rad (2*sz+1);
    manacher(str.begin(), str.end(), rad.begin());
    vector<int> r;
    for(i=1;i<rad.size();i+=2)
        r.push_back((rad[i]+1)/2);

    KMP kmp("");
    kmp.clear();
    kmp.motherStr=str;
    kmp.pattern=str;
    reverse(kmp.pattern.begin(), kmp.pattern.end());
    kmp.preProcess();
    kmp.search();

    maxtill[0]=make_pair(0, till[0]);
    for(i=1;i<sz;i++){
        maxtill[i]=maxtill[i-1];
        if(maxtill[i].second < till[i]){
            maxtill[i].second=till[i];
            maxtill[i].first=i;
        }
    }

    int right, left, maxi, cur, lenght;
    pair<int, int> s, mid, e;
    maxi=-1;
    for(i=1;i<sz-1;i++){
        left=i-r[i];
        right=i+r[i];
        if(left==-1){
            r[i]--;
            left=i-r[i];
            right=i+r[i];
        }
        lenght=min(maxtill[left].second, sz-right);
        cur=(right-left-1) + 2*lenght;
        if(maxi<cur){
            maxi=cur;
            s.first=maxtill[left].first-maxtill[left].second+1;
            s.second=lenght;
            mid.first=left+1;
            mid.second=right-left-1;
            e.first=sz-lenght;
            e.second=lenght;
        }
    }

    if(s.second!=0){
        cout << 3 << endl;
        cout << s.first+1 << ' ' << s.second << endl;
        cout << mid.first+1 << ' ' << mid.second << endl;
        cout << e.first+1 << ' ' << e.second << endl;
    }
    else{
        cout << 1 << endl;
        cout << mid.first+1 << ' ' << mid.second << endl;
    }

}


int main(){


    ios_base::sync_with_stdio(false);
    string str, pattern;
    int i;

    while(cin >> str){
        solve(str);
    }


    return 0;
}

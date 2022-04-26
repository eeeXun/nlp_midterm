#include <iostream>
#include <map>
#include <stdio.h>
#include <set>
#include <stack>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <list>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <string.h>
#include <math.h>
#include <time.h>
using namespace std;
/**
 * @author: Shamir14 -- Amirhossein Shapoori
 * lordamir14@gmail.com
 * ACM team: AnotherChorMangz
 * Tehran, Iran
 * Still listening to Mark Knopfler...
 * :P
 */
 
typedef long long lli;
#define pii pair<int, int> 
#define pB push_back
#define mP make_pair
#define X first
#define Y second
#define SP system("pause");
#define assert(x) {cerr << (#x) << ": " << (x) << endl;}
const int maxn=2*100000+10, MOD=1000*1000*1000+7, INF=1000*1000*1000;
const double EPS=1e-9, PI=2*acos(0.0);


int till[maxn];
// KMP(O(N + M))
// pattern is the pattern that you wanna find it in the motherStr
// first call preProcess, then call search
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

pii maxtill[maxn];

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

    // palindromse radius
    vector<int> rad (2*sz+1);
    manacher(str.begin(), str.end(), rad.begin());
    vector<int> r;
    for(i=1;i<rad.size();i+=2)
        r.pB((rad[i]+1)/2);

    KMP kmp("");
    kmp.clear();
    kmp.motherStr=str;
    kmp.pattern=str;
    reverse(kmp.pattern.begin(), kmp.pattern.end());
    kmp.preProcess();
    kmp.search();
    
    maxtill[0]=mP(0, till[0]);
    for(i=1;i<sz;i++){
        maxtill[i]=maxtill[i-1];
        if(maxtill[i].Y < till[i]){
            maxtill[i].Y=till[i];
            maxtill[i].X=i;
        }
    }

    int right, left, maxi, cur, lenght;
    pii s, mid, e;
    maxi=-1;
    for(i=1;i<sz-1;i++){
        left=i-r[i];
        right=i+r[i];
        if(left==-1){
            r[i]--;
            left=i-r[i];
            right=i+r[i];
        }
        lenght=min(maxtill[left].Y, sz-right);
        cur=(right-left-1) + 2*lenght;
        if(maxi<cur){
            maxi=cur;
            s.X=maxtill[left].X-maxtill[left].Y+1;
            s.Y=lenght;
            mid.X=left+1;
            mid.Y=right-left-1;
            e.X=sz-lenght;
            e.Y=lenght;
        }
    }

    if(s.Y!=0){
        cout << 3 << endl;
        cout << s.X+1 << ' ' << s.Y << endl;
        cout << mid.X+1 << ' ' << mid.Y << endl;
        cout << e.X+1 << ' ' << e.Y << endl;
    }
    else{
        cout << 1 << endl;
        cout << mid.X+1 << ' ' << mid.Y << endl;
    }
    
}


int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);   
    string str, pattern;
    int i;
    
    while(cin >> str){
        solve(str);
    }
        
    
    return 0;
}
				 				      				  					
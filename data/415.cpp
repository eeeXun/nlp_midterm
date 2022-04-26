//By Lin
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>

#define sqr(x) ((x)*(x))
#define Rep(i,n) for(int i = 0; i<n; i++)
#define foreach(i,n) for( __typeof(n.begin()) i = n.begin(); i!=n.end(); i++)
#define X first
#define Y second
#define mp(x,y) make_pair(x,y)

using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;

#define N 100010
#define BASE 37
uLL     base[N];
char    str[N];
int     L[N],pos[N];

vector<pii> v;
int     maxL;

int     main(){
    scanf("%s", str );
    int len = strlen(str);
    Rep(i,len) base[i] = i?base[i-1]*BASE:1;
    L[0] = 1;
    for (int i = 1, lim = 0,x = 0; str[i]; i++){
        if ( i > lim ) L[i] = 1;
        else L[i] = min( L[x*2-i] , lim-i+1);
//      if ( i<=lim ) L[i] = L[x*2-i];
        while ( i+L[i]<len && i>=L[i] && str[i+L[i]] == str[i-L[i]] && i+L[i] >= lim ){
            L[i]++;
            lim++;
            x = i; 
        }
//      printf("%c %d\n" , str[i] , L[i] );
    }
    pos[0] = 0; 
    uLL last = 0, first = 0;
    for (int i = 1; i*2<len; i++){
        last = last*BASE + (str[len-i]-'a'+1);
        first = first*BASE + (str[pos[i-1]+i-1] -'a'+1);
        pos[i] = pos[i-1];
        while ( pos[i]+i<len && last != first ) {
            first -= (str[pos[i]]-'a'+1)*base[i-1];
            first = first*BASE + (str[pos[i]+i] -'a'+1);
            pos[i]++;
        }
    }
    Rep(i,len){
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
            if ( ans ) v.push_back( mp(pos[ans] , ans) );
            v.push_back( mp(i-L[i]+1,L[i]*2-1) );
            if ( ans ) v.push_back( mp(len-ans , ans) );
        }
    }
    printf("%d\n" , (int)v.size() );
    foreach(it,v) printf("%d %d\n" , it->X+1 , it->Y );
    return 0;
}

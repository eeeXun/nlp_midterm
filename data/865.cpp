//#pragma comment(linker, "/stack:16777216")
#include<cmath>
#include<vector>
#include<deque>
#include<list>
#include<set>
#include<map>
#include<numeric>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

#define sz(X) ((int)(X).size())
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define all(X) (X).begin(),(X).end()
#define FOR(i, a, n) for(int i=(a), __ ## i=(n); i<__ ## i; i++)
#define REP(I,N) FOR(I,0,N)
#define PR(X) cout<<#X<<" = "<<(X)<<" "
#define PRL cout<<endl
#define PRV(X) {cout<<#X<<" = {";REP(__prv,sz(X)-1)cout<<(X)[__prv]<<",";if(sz(X))cout<<*(X).end();cout<<"}"<<endl;}

template<class T> ostream &operator<<(ostream &os, vector<T> &vec)
{
  os<<'{';
  REP(i, sz(vec)){
    os<<vec[i];
    if (i+1!=sz(vec)) os<<',';
  }
  os<<'}';
  return os;
}

template<class T1, class T2> ostream &operator<<(ostream &os, pair<T1, T2> &par)
{
  os<<'('<<par.X<<','<<par.Y<<')';
  return os;
}

typedef long long lint;
typedef vector<int> VI;
typedef pair<int,int> PII;

const int dim = 110000;
char s[dim];
char s1[dim];
int p[dim];
int a[dim];
int a1[dim];
int d[dim];

int main(){
    scanf("%s", s);
    int n = strlen(s);
    REP(i, n) s1[i] = s[n - 1 - i];
    s1[n] = 0;

    p[0] = -1;
    int g = -1;
    FOR(i, 1, n){
        while(g != -1 && s1[g + 1] != s1[i]){
            g = p[g];
        }
        if(s1[g + 1] == s1[i]) ++g;
        p[i] = g;
    }

    g = -1;
    a[0] = 0;
    a1[0] = 0;
    REP(i, n){
        while(g != -1 && s1[g + 1] != s[i]){
            g = p[g];
        }
        if(s1[g + 1] == s[i]) ++g;
        if(a[i] > g + 1){
            a1[i + 1] = a1[i];
        }else{
            a1[i + 1] = i - g;
        }
        a[i + 1] = max(a[i], g + 1);
    }


    int ans = 0;
    int i1, j1;
    int i2, j2;
    int le = 0, ri = -1;
    REP(i, n){
        int g = (i > ri ? 0: min(d[le + ri - i], ri - i)) + 1;
        while(i + g < n && i - g >= 0 && s[i - g] == s[i + g]) ++g;
        d[i] = --g;
        if(i + g > ri){
            ri = i + g;
            le = i - g;
        }

        int t = min(a[i - d[i]], n - i - d[i] - 1);
        int ans1 = t * 2 + d[i] * 2 + 1;
        if(ans < ans1){
            ans = ans1;
            i1 = a1[i - d[i]];
            j1 = t;
            i2 = i - d[i];
            j2 = d[i] * 2 + 1;
        }
    }
    if(j1 == 0){
        printf("1\n");
        printf("%d %d\n", i2 + 1, j2);
    }else{
        printf("3\n");
        printf("%d %d\n", i1 + 1, j1);
        printf("%d %d\n", i2 + 1, j2);
        printf("%d %d\n", n - j1 + 1, j1);
    }
    return 0;
}

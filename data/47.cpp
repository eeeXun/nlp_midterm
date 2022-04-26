#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

#define MAXN 111111

char s[MAXN], str[MAXN << 1];
int p[MAXN << 1];

void pre()
{
    int len = strlen(s);
    str[0] = '$';
    str[1] = '#';
    for(int i = 0; i < len; i++) {
        str[i*2 + 2] = s[i];
        str[i*2 + 3] = '#';
    }
    len = len * 2 + 2;
    str[len] = 0;
}

void pk()
{
    int mx = 0, id;
    int len = strlen(str);
    for(int i = 1; i < len; i++) {
        if(mx > i)
            p[i] = min(p[2*id-i], mx-i);        
        else
            p[i] = 1;
        for(; str[i+p[i]] == str[i-p[i]]; p[i]++);
        if(p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
    }
}

string s2;
int nxt[MAXN << 1];
int o;
void find_nxt(string a)
{
    nxt[0]=0;
    for(int i=1;i<a.size();i++)
    {
        int j=nxt[i-1];
        while(a[j]!=a[i] && j>0)
        {
            j=nxt[j-1];
        }
        if(a[j]==a[i]) nxt[i]=j+1;
        else nxt[i]=0;
    }
}

int Mx[MAXN], pos[MAXN];

int main()
{
    //freopen("pro.in","r",stdin);

    scanf("%s", s);
    int n = strlen(s);

    pre();
    pk();

    s2 = "";

    for(int i = n - 1; i >= 0; i--) s2 += s[i];

    s2 += '$';

    for(int i = 0; i < n; i++) s2 += s[i];

    find_nxt(s2);

    Mx[0] = nxt[n + 1]; pos[0] = 0;
    for(int i = 1; i < n; i++) {
        if(Mx[i - 1] < nxt[i + n + 1]) {
            Mx[i] = nxt[i + n + 1];
            pos[i] = i;
        } else {
            Mx[i] = Mx[i - 1];
            pos[i] = pos[i - 1];
        }
    }

    int ans = 0;
    vector <pair<int, int> > f_ans;
    for(int i = 0; i < n; i++) {
        int len = p[2 * i + 2] - 1;
        int a = len / 2;
        int l = i - a; int r = i + a;
        if(l != 0 && r != n - 1) {
            int b = Mx[l - 1]; int x = pos[l - 1];
            if(r + b >= n) {
                b = n - r - 1;
            } 
            if(b != 0 && ans < 2 * b + len) {
                ans = 2 * b + len;
                f_ans.clear();
                f_ans.push_back(make_pair(x - b + 1, b));
                f_ans.push_back(make_pair(l, len));
                f_ans.push_back(make_pair(n - b, b));
            }
        }
        if(ans < len) {
            ans = len;
            f_ans.clear();
            f_ans.push_back(make_pair(l, len));
        }
    }

    printf("%d\n", f_ans.size());

    for(int i = 0; i < f_ans.size(); i++) {
        printf("%d %d\n", f_ans[i].first + 1, f_ans[i].second);
    }

    return 0;
}
	  			      		   		  		 		 	 	
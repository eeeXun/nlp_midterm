#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
char s[maxn],ss[maxn];
int nxt[maxn],r[maxn],f[maxn],g[maxn];
signed main(){
#ifndef ONLINE_JUDGE
    freopen("D:\\in.txt","r",stdin);
#endif // ONLINE_JUDGE
    scanf("%s",s+1); int n=strlen(s+1); s[n+1]='#';
    int mx = 0, id = 0;
    for(int i=1;i<=n;i++){
        if(mx > i) r[i] = min(r[2*id - i],mx - i);
        else r[i] = 1;
        while(s[i + r[i]] == s[i - r[i]]) r[i] ++;
        if(r[i] + i > mx) mx = r[i] + i, id = i;
    }
    for(int i=1;i<=n;i++) ss[i] = s[n-i+1];
    nxt[0] = nxt[1] = 0;
    for(int i=2,j=0;i<=n;i++){
        while(j && ss[i]!=ss[j+1]) j=nxt[j];
        if(ss[i] == ss[j+1]) nxt[i] = ++j;
    }
    for(int i=1,j=0;i<=n;i++){
        while(j && s[i]!=ss[j+1]) j=nxt[j];
        if(s[i] == ss[j+1]) f[i] = ++j;
        if(f[i] == n) j = nxt[j];
        if(f[i]) g[i] = i - f[i] + 1;
    }
    for(int i=1;i<=n;i++) if(f[i-1]>f[i]) f[i]=f[i-1],g[i]=g[i-1];
    bool ok = false;
    int ans = 0,pos = 0;
    for(int i=1;i<=n;i++) if(2*r[i]-1>ans) ans = 2*r[i]-1, pos = i-r[i]+1;
    for(int i=1;i<=n;i++){
        int t = i-r[i];
        if(2*min(f[t],n-(i+r[i]-1))+2*r[i]-1>ans){
            ok = true;
            ans = 2*min(f[t],n-(i+r[i]-1))+2*r[i]-1;
            pos = i;
        }
    }
    if(!ok) printf("1\n%d %d\n",pos,ans);
    else{
        printf("3\n");
        printf("%d %d\n",g[pos-r[pos]],f[pos-r[pos]]);
        printf("%d %d\n",pos-r[pos]+1,2*r[pos]-1);
        printf("%d %d\n",n-f[pos-r[pos]]+1,f[pos-r[pos]]);
    }
    return 0;
}
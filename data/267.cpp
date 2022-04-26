#include<bits/stdc++.h>
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d %d",&x,&y)
#define siii(x,y,z) scanf("%d %d %d",&x,&y,&z)
#define su(x) scanf("%u",&x)
#define sl(x) scanf("%ld",&x)
#define sli(x) scanf("%lld",&x)
#define slii(x,y) scanf("%lld %lld",&x,&y)
#define sliii(x,y,z) scanf("%lld %lld %lld",&x,&y,&z)
#define slu(x) scanf("%llu",&x)
#define sf(x) scanf("%f",&x)
#define slf(x) scanf("%lf",&x)
#define slff(x,y) scanf("%lf %lf",&x,&y)
#define slfff(x,y,z) scanf("%lf %lf %lf",&x,&y,&z)
#define sc(x) scanf("%c",&x)
#define ss(x) scanf("%s",x)
#define pf printf
#define fpf fprintf
#define pb push_back
#define f(i,x,y,z) for(int i=x;i<y;i=i+z)
#define f1(i,x,y,z) for(int i=x;i>y;i=i-z)
#define MAX ((int)(1e8))
#define pi 2*acos(0)
#define mp make_pair
#define M ((ll)(1e9+7))
#define xx first
#define yy second
#define NN 4005
#define N ((int)(2e5+10))
#define vc vector
#define pq priority_queue
#define Q queue
#define eps 1e-12


using namespace std;

typedef long long int ll;
typedef unsigned long long int lu;

char s[N], str[N];

int pal[N];

void manach(char *str){
    int i;
    for(i = 0; str[i]!='\0'; i++){
        s[2*i] = str[i];
        s[2*i + 1] = '#';
    }
    s[2*i-1] = '\0';
    ///printf("%s\n",s);
    pal[0] = 0;
    int now = 0;
    for(i = 1; s[i]!='\0'; i++){
        pal[i] = max(0,min(pal[now]-(i-now),pal[now-(i-now)])) + 1;
        while(i-pal[i]>=0 && s[i+pal[i]]==s[i-pal[i]]) pal[i]++;
        pal[i]--;
        if(pal[i]>pal[now]) now = i;
    }
    for(i = 0; s[i]!='\0'; i++){
        if(s[i]=='#') pal[i] = (pal[i]+1)/2;
        else pal[i] = pal[i]/2;
    }
    ///for(i = 0; s[i]!='\0'; i++) cout<<pal[i]<<endl;
}



///kmp
int prefx[N];
void kmp(char *s){
    prefx[0] = -1;
    int now;
    for(int i = 1; s[i]!='\0'; i++){
        now = prefx[i-1];
        while(now!=-1 && s[i]!=s[now+1]) now = prefx[now];
        if(s[i]==s[now+1]) prefx[i] = now+1;
        else prefx[i] = -1;
    }
}

vector < int > v[N];


int main()
{
    int i, n, j, l, ans,x, y, keep, tmp;
    while(0){
        scanf("%d",&i);
        cout<<(char)i;
    }

    scanf("%s",str);
    n = strlen(str);
    manach(str);
    for(i = 0; str[i]!='\0'; i++){
        pal[i] = pal[i*2];
        v[i-pal[i]].pb(i+pal[i]);
    }
    ///printf("%s\n",str);
    ///for(i = 0; str[i]!='\0'; i++) cout<<pal[i]<<endl;

    for(i = 0; i<n; i++) s[i] = str[n-1-i];
    s[n] = '#';
    for(i = 0; i<n; i++) s[i+n+1] = str[i];
    s[2*n+1] = '\0';

    kmp(s);
    l = 0;

    keep = ans = 0;
    for(i = 0; i<n; i++){

        for(j = 0; j<v[i].size(); j++){
            tmp = v[i][j]-i+1+2*min(prefx[keep]+1,n-1-v[i][j]);
            if(tmp>ans){
                x = i;
                y = v[i][j];
                ans = tmp;
                ///cout<<x<<" "<<y<<endl;
                ///cout<<ans<<endl;
            }
        }

        if(prefx[l+n+1]>prefx[keep]){
            keep = l+n+1;
        }
        l++;
    }

    ///cout<<keep-n<<endl;
    keep = 0;
    for(i = 0; i<x; i++){
        if(prefx[i+n+1]>prefx[keep]) keep = i+n+1;
    }

    if(keep==0){
        printf("1\n");
        printf("%d %d\n",x+1,y-x+1);
    }
    else{
        printf("3\n");
        if(prefx[keep]+1>n-1-y) printf("%d %d\n",keep-n-1-(n-1-y)+2,n-1-y);
        else printf("%d %d\n",keep-n-1-prefx[keep]+1,prefx[keep]+1);
        printf("%d %d\n",x+1,y-x+1);
        if(prefx[keep]+1>n-1-y) printf("%d %d\n",n-(n-1-y)+1,n-1-y);
        else printf("%d %d\n",n-prefx[keep],prefx[keep]+1);
    }
    return 0;
}

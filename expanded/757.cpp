}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 6 "data/757.cpp" 2

# 6 "data/757.cpp"
using namespace std;

typedef pair<int,int> PII;

vector<int> manacher(const char* s, int n){
    vector<int> u(n+n-1,1);
    for(int i=1,x=0;i<n+n-1;i++){
        u[i]=max(x+u[x]-i,1-i%2);
        if(x+x>=i) u[i]=min(u[i],u[x+x-i]);
        int a=(i-1-u[i])>>1,b=(i+1+u[i])>>1;
        while(a>=0 && b<n && s[a]==s[b]) a--,b++,u[i]+=2;
        if(i+u[i]>x+u[x]) x=i;
    }
    return u;
}

vector<int> calcP(const char* s, int n){
    vector<int> P(n);
    for(int x=0,y=1;y<n;y++){
        while(x && s[x]!=s[y]) x=P[x-1];
        if(s[x]==s[y]) P[y]=++x;
    }
    return P;
}

char s[100005];
PII hi[100005],ppp,ooo,qqq;
vector<int> u;

int main(){
    int n=strlen(gets(s));
    string o=s; o+='#'; o+=s;
    reverse(o.begin(),o.begin()+n);
    u=calcP(o.c_str(),o.size());
    int top=0,pos=0,ans=0;
    for(int i=0;i<n;i++){
        int x=min(u[n+i+1],n-i-2);
        if(x>top) top=x,pos=i;
        hi[i]={top,pos};
    }
    u=manacher(s,n);
    for(int i=0;i<n;i++){
        int x=(u[i+i]+1)/2;
        int a=i-x,b=i+x;
        if(x*2-1>ans){
            ans=x*2-1;
            ppp=qqq={0,0};
            ooo={a+1,x*2-1};
        }
        if(a<0 || !hi[a].first) continue;
        int l=hi[a].first,t=hi[a].second-l+1;
        if(n-l<b) l=n-b;
        if(!l) continue;
        if(l*2+x*2-1>ans){
            ans=l*2+x*2-1;
            ppp={t,l};
            ooo={a+1,x*2-1};
            qqq={n-l,l};
        }
    }
    if(!ppp.second){
        puts("1");
        printf("%d %d\n",ooo.first+1,ooo.second);
    }else{
        puts("3");
        printf("%d %d\n",ppp.first+1,ppp.second);
        printf("%d %d\n",ooo.first+1,ooo.second);
        printf("%d %d\n",qqq.first+1,qqq.second);
    }
}

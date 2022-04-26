

# 3 "data/163.cpp"
using namespace std;






typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

ll modpow(ll a, ll b, ll mod){

    ll ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;
        b=b/2;
    }
    return ans;
}
ll mod1 = 1000000007, mod2 = 1000000009;
ll fhash1[100010],rhash1[100010],fhash2[100010],rhash2[100010];
ll ipow261[100010],ipow262[100010];
int n;
ll getFHash1(int l, int r){

    ll res = fhash1[r];
    if(l){
        res = (res-fhash1[l-1]+mod1)%mod1;
    }

    res = (res*ipow261[l])%mod1;
    return res;
}

ll getFHash2(int l, int r){

    ll res = fhash2[r];
    if(l){
        res = (res-fhash2[l-1]+mod2)%mod2;
    }

    res = (res*ipow262[l])%mod2;
    return res;
}

ll getRHash1(int l, int r){

    ll res = rhash1[l];

    res = (res-rhash1[r+1]+mod1)%mod1;

    res = (res*ipow261[n-1-r])%mod1;
    return res;
}

ll getRHash2(int l, int r){

    ll res = rhash2[l];

    res = (res-rhash2[r+1]+mod2)%mod2;

    res = (res*ipow262[n-1-r])%mod2;
    return res;
}

int chk(int ind, int len){

    if((getRHash1(ind+1,ind+len)==getFHash1(ind-len,ind-1)) && (getRHash2(ind+1,ind+len)==getFHash2(ind-len,ind-1))){
        return 1;
    }

    return 0;

}

int fail[200010];
int pre[100010],prew[100010];

int palin[100010];

int main(){


    ios::sync_with_stdio(0);
    cin.tie(0);

    ipow261[0]=1;
    ipow262[0]=1;

    ll inv261 = modpow(26,mod1-2,mod1);
    ll inv262 = modpow(26,mod2-2,mod2);

    for(int i=1;i<100010;i++){
        ipow261[i]=(ipow261[i-1]*inv261)%mod1;
        ipow262[i]=(ipow262[i-1]*inv262)%mod2;
    }

    string s;
    string s1;
    cin>>s;

    s1=s;
    reverse(s1.begin(),s1.end());
    s1+="$";
    s1+=s;

    n = s.length();

    fail[0]=0;
    int i=1,j=0;
    while(i<s1.length()){
        if(s1[i]==s1[j]){
            fail[i]=j+1;
            j++;
            i++;
        }
        else if(j>0){
            j=fail[j-1];
        }
        else{
            fail[i]=0;
            i++;
        }

    }

    for(int i=0;i<n;i++){
        fail[i]=fail[i+n+1];
    }

    pre[0]=fail[0];
    prew[0]=0;

    for(int i=1;i<n;i++){
        pre[i]=pre[i-1];
        prew[i]=prew[i-1];
        if(fail[i]>pre[i]){
            pre[i]=fail[i];
            prew[i]=i;
        }
    }

    fhash1[0]=s[0]-'a';
    fhash2[0]=s[0]-'a';
    ll pw26h1 = 26, pw26h2 = 26;
    for(int i=1;i<n;i++){
        fhash1[i]=(fhash1[i-1]+(s[i]-'a')*pw26h1)%mod1;
        fhash2[i]=(fhash2[i-1]+(s[i]-'a')*pw26h2)%mod2;
        pw26h1=(pw26h1*26)%mod1;
        pw26h2=(pw26h2*26)%mod2;
    }
    pw26h1 = 1;
    pw26h2 = 1;
    for(int i=n-1;i>=0;i--){
        rhash1[i]=(rhash1[i+1]+(s[i]-'a')*pw26h1)%mod1;
        rhash2[i]=(rhash2[i+1]+(s[i]-'a')*pw26h2)%mod2;
        pw26h1=(pw26h1*26)%mod1;
        pw26h2=(pw26h2*26)%mod2;
    }

    for(int i=0;i<n;i++){

        int lo = 1, hi = min(n-1-i,i), md;
        int ans = 0;
        while(lo<=hi){
            md = (lo+hi)/2;
            if(chk(i,md)){
                ans=md;
                lo=md+1;
            }
            else{
                hi=md-1;
            }
        }

        palin[i]=ans;
    }
    int mxans = 0;
    int mxlen = 0;
    int mxst = 0;
    int mxmid = 0;
    for(int i=1;i<n-1;i++){
        int lft = i-palin[i]-1;
        if(lft>=0){
            int cur = palin[i]*2 + 1 + min(n-1-i-palin[i],pre[lft])*2;
            if(cur>mxans){
                mxans=cur;
                mxlen = min(n-1-i-palin[i],pre[lft]);
                mxst = prew[lft];
                mxmid = i;
            }
        }
    }

    int singleComp = 0;
    int whch = 0;
    for(int i=0;i<n;i++){
        if(2*palin[i]+1>singleComp){
            singleComp=2*palin[i]+1;
            whch=i;
        }
    }

    if(singleComp>=mxans){
        cout<<1<<endl;
        cout<<whch-palin[whch]+1<<" "<<singleComp<<endl;
    }
    else{
        cout<<3<<endl;
        cout<<(mxst-fail[mxst]+1)+1<<" "<<mxlen<<endl;
        cout<<(mxmid-palin[mxmid]+1)<<" "<<palin[mxmid]*2+1<<endl;
        cout<<(n-mxlen+1)<<" "<<mxlen<<endl;
    }




}

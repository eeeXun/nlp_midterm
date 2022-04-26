}
# 5 "data/616.cpp" 2


# 6 "data/616.cpp"
using namespace std;
void pattern_match(char pat[],const int len,int pi[])
{
    pi[1]=0;
    for(int i=2; i<=len; i++)
    {
        int st=i-1;
        while(st>=1 && pat[pi[st]+1]!=pat[i] ) st=pi[st];
        if(st==0)pi[i]=0;
        else pi[i] = pi[st]+1;
    }

}
void pattern_match(char pat[],int pi[],char tar[],const int len1,int gi[])
{
    if(pat[1]==tar[1])gi[1]=1;
    for(int i=2; i<=len1; i++)
    {
        int st=gi[i-1];
        while(pat[st+1]!=tar[i] )
        {
            if(st==0)
            {
                st=-1;
                break;
            }
            st = pi[st];
        }
        if(st==-1)gi[i]=0;
        else gi[i] = st+1;
    }

}
char S[100005],a[100005];
int N,f[100005],g[100005],h[100005],r[100005];

int main()
{
    scanf("%s",S+1),N=strlen(S+1),S[0]=1;
    for (int i=1; i<=N; i++) a[i]=S[N-i+1];
    S[N+1]=2;
    int s=1,in=0;
    while(s<=N)
    {
        while(S[s-in]==S[s+in])r[s]++,in++;

        int i,j;


        if(r[s]==1)
        {
            s++;
            in=0;
            continue;
        }

        for(i=s+1,j=1; i<s+in; i++,j++)
        {
            r[i]=in-j;
            r[i]=min(r[i],r[s-j]);
            if(r[i]==in-j)
            {
                s=i;
                in=r[i];
                break;
            }

        }

    }
    g[1]=0;
    pattern_match(a,N,g);
    pattern_match(a,g,S,N,h);







    int Max=0;
    in=0;
    for(int i=1; i<=N; i++)
    {
        f[i-h[i]+1]=h[i];
        g[i]=N+10;
        if(Max<h[i])
        {
            in=i;
            Max=h[i];
        }
        if(Max)g[i]=in-h[in]+1;

    }



    in=-1;
    int ans=0;
    for(int i=1;i<=N;i++)
    {
        int ln = min(f[g[i-r[i]]],(i-r[i])-g[i-r[i]]+1);
        ln=max(0,ln);
        int rl=0;
        if(ln>0)
        {
            rl=min(ln,(N-(i+r[i]-1)));
        }

        int cans=2*r[i]-1+min(ln,rl)*2;
        if(ans<cans){ans=cans;in=i;}



    }
    int ln = min(f[g[in-r[in]]],(in-r[in])-g[in-r[in]]+1);
    ln=max(0,ln);
    int rl=0;
    if(ln>0)rl=min(N-(in+r[in]-1),ln);
    ln=min(ln,rl);

    if(ln)cout<<3<<endl<<g[in-r[in]]<<" "<<ln<<endl;
    else cout<<1<<endl;
    cout<<in-r[in]+1<<" "<<2*r[in]-1<<endl;
    if(ln)cout<<N-ln+1<<" "<<ln<<endl;


}

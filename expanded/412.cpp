



# 7 "data/412.cpp"
int lgr[1000000];
char s[1000000];
unsigned long long mul[1000000];
unsigned long long h1[1000000];
unsigned long long h3[1000000];
int min(int a,int b){
    if (a<b)
        return a;
    return b;
}
int n;
unsigned long long l1(int a,int b){

    return (h1[b+1]-h1[a])*mul[(n-a)];
}
unsigned long long l2(int a,int b){

    return (h3[a]-h3[b+1])*mul[(b+1)];
}

int main(){
    scanf("%s",s);
    n=strlen(s);
    mul[0]=1;
    for (int i=1;i<1000000;i++)
        mul[i]=mul[i-1]*1000007;
    int len=0;
    memset(lgr,-1,sizeof(lgr));

    lgr[0]=0;
    int l=0;
    h1[0]=0;
    for (int i=1;i<=n;i++)
        h1[i]=h1[i-1]+(s[i-1]-' ')*mul[i-1];
    h3[n]=0;
    for (int i=n-1;i>=0;i--)
        h3[i]=h3[i+1]+(s[i]-' ')*mul[n-i-1];

    unsigned long long h2;
    h2=0;
    while (true){
        len++;
        h2+=(s[n-len]-' ')*mul[len-1];
        while (h2*mul[l]!=h1[l+len]-h1[l]&&l<n-len)
            l++;

        if (l>=n-len)
            break;
        lgr[len]=l;
    }
    int max=0;
    int k=0;
    int c11,c12;
    int c21,c22;
    int c31,c32;

    for (int i=0;i<n;i++){
        int a=0;
        int b=min(i,n-i-1);

        while (a<b){
            int c=(a+b)/2+(a+b)%2;
            if (l1(i-c,i)==l2(i,i+c))
                a=c;
            else
                b=c-1;
       }
        int len=a;
        a=0;
        b=n-1-i-len;
        while (a<b){
            int c=(a+b)/2+(a+b)%2;
            if (lgr[c]==-1)
                    b=c-1;
            else{
                if (lgr[c]+c-1>=i-len)
                    b=c-1;
                else
                    a=c;
            }
        }
        if (2*len+1+(a)*2>max){
            max=2*len+1+(a)*2;
            if (a>0)
            {
                   k=3;
                    c11=lgr[a]+1;
                    c12=lgr[a]+a;
                    c21=i-len+1;
                    c22=i+len+1;
                    c31=n-a+1;
                    c32=n;

            }else
            {
                k=1;
                c21=i-len+1;
                c22=i+len+1;
            }
        }
    }

    printf("%d\n",k);
    if (k==1)
        printf("%d %d",c21,c22-c21+1);
    if (k==3){

        printf("%d %d\n",c11,c12-c11+1);
        printf("%d %d\n",c21,c22-c21+1);

        printf("%d %d\n",c31,c32-c31+1);
    }
    if (k==2){

        printf("%d %d\n",c11,c12-c11+1);
        printf("%d %d\n",c31,c32-c31+1);
    }
}

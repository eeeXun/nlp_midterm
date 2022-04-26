#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100100;
char str[N];
int lenth[N];
char lenstr[2*N];
int lenlen[2*N];
char acstr[2*N];
int kmp[2*N];
int ac[N];
int maxac[N];

void getlenstr()
{
    int cont = 0;
    int len = strlen(str);
    for(int i = 0; i<len; i++)
    {
        lenstr[cont++] = '#';
        lenstr[cont++] = str[i];
    }
    lenstr[cont++] = '#';
    lenstr[cont] = '\0';
    //printf("%s\n",lenstr);
}

void getlenlen()
{
    int maxr = -1,maxd;
    int len;
    int lennum = strlen(lenstr);
    for(int i = 0; i<lennum; i++)
    {
        if(i<maxr)
            len = min(lenlen[2*maxd-i],(maxr-i)*2+1);
        else
            len = 1;
        for(int j = len/2+1; i+j<lennum && i-j>=0 && lenstr[i+j] == lenstr[i-j]; len+=2, j = len/2+1);
        lenlen[i] = len;
        if(i+len/2>maxr)
        {
            maxr = i+len/2;
            maxd = i;
        }
    }
    //for(int i = 0; i<lennum; i++)
    //printf("%d %c : %d\n",i,lenstr[i],lenlen[i]);
}

void getlen()
{
    int lennum = strlen(lenstr);
    for(int i = 1; i<lennum; i+=2)
        lenth[i/2] = (lenlen[i]-3)/2+1;
    //for(int i = 0; i<strlen(str); i++)
    //printf("%d %c : %d\n",i,str[i],lenth[i]);
}
void getlenth()
{
    getlenstr();
    getlenlen();
    getlen();
}

int getacstr()
{
    int cont = 0;
    int len = strlen(str);
    for(int i = len-1; i>=0; i--)
        acstr[cont++] = str[i];
    int mid = cont;
    acstr[cont++] = '$';
    for(int i = 0; i<len; i++)
        acstr[cont++] = str[i];
    acstr[cont] = '\0';
    //printf("%s\n",acstr);
    return mid;
}

void getkmp()
{
    kmp[0] = -1;
    int len = strlen(acstr);
    for(int i = 1; i<len; i++)
    {
        int t = kmp[i-1];
        while(t != -1 && acstr[t+1] != acstr[i])
            t = kmp[t];
        if(acstr[t+1] == acstr[i])
            kmp[i] = t+1;
        else
            kmp[i] = -1;
    }
    //for(int i = 0; i<strlen(acstr); i++)
    //printf("%d %c : %d\n",i,acstr[i],kmp[i]);
}

void getac(int mid)
{
    int len = strlen(str);
    int lennum = strlen(acstr);
    for(int i = mid+1; i<lennum; i++)
        ac[len-1-(2*mid-i)] = kmp[i]+1;
    //for(int i = 0; i<len; i++)
    //printf("%d %c : %d\n",i,str[i],ac[i]);
}

void getacth()
{
    int mid = getacstr();
    getkmp();
    getac(mid);
}

void getmaxac()
{
    maxac[0] = ac[0];
    int len = strlen(str);
    for(int i = 1; i<len; i++)
        maxac[i] = max(maxac[i-1],ac[i]);
    //for(int i = 0; i<strlen(str); i++)
    //printf("%d %c : %d\n",i,str[i],maxac[i]);
}

int main()
{
    scanf("%s",str);
    getlenth();
    getacth();
    getmaxac();

    int maxlen = -1;
    int number;
    int al,ar,bl,br,cl,cr;

    int len = strlen(str);
    for(int i = 0; i<len; i++)
    {
        int l = i - lenth[i]/2;
        int r = i + lenth[i]/2;
        if(l == 0 || r == len-1 || maxac[l-1] == 0)
        {
            if(lenth[i]>maxlen)
            {
                maxlen = lenth[i];
                number = 1;
                al = l;
                ar = r;
            }
            continue;
        }
        int t = min(maxac[l-1], len-1-r);
        int total = lenth[i] + t*2;
        if(total>maxlen)
        {
            maxlen = total;
            number = 3;
            for(int j = l-1; j>=0; j--)
            {
                if(ac[j]>=t)
                {
                    al = j-t+1;
                    ar = j;
                    break;
                }
            }
            bl = l;
            br = r;
            cl = len-t;
            cr = len-1;
        }
    }
    printf("%d\n",number);
    printf("%d %d\n",al+1,ar-al+1);
    if(number == 3)
    {
        printf("%d %d\n",bl+1,br-bl+1);
        printf("%d %d\n",cl+1,cr-cl+1);
    }
    return 0;
}

/*

abacaba
axbya
xabyczba

*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100100;
char str[N];
char acstr[2*N];
char lenstr[2*N];
int lenth[2*N];
int ac[2*N];
int aba[N];
int maxaba[N];
int len,aclen,lenlen;

void getlenstr()
{
    int cont = 0;
    for(int i = 0; i<len; i++)
    {
        lenstr[cont++] = '#';
        lenstr[cont++] = str[i];
    }
    lenstr[cont++] = '#';
    lenstr[cont] = '\0';
    lenlen = cont;
    //printf("lenstr: %s\n",lenstr);
}

void getlenth()
{
    getlenstr();
    int now;
    int maxr = -1,maxd;
    for(int i = 0; i<lenlen; i++)
    {
        if(i<maxr)
            now = min(lenth[2*maxd - i], (maxr-i)*2+1);
        else
            now = 1;
        for(int j = now/2+1; i+j<lenlen && i-j>=0 && lenstr[i-j] == lenstr[i+j]; now+=2,j = now/2+1);
        lenth[i] = now;
        if(i+lenth[i]/2 > maxr)
        {
            maxr = i+lenth[i]/2;
            maxd = i;
        }
    }
    int temp[2*N];
    for(int i = 0; i<lenlen; i++)
    temp[i] = lenth[i];
    for(int i = 1; i<lenlen; i+=2)
        lenth[i/2] = (temp[i]-3)/2+1;
        /*
    printf("array lenlen:\n");
    for(int i = 0; i<lenlen; i++)
        printf("%d %c : %d\n",i+1, lenstr[i], temp[i]);
    printf("\n");
    printf("array lenth:\n");
    for(int i = 0; i<len; i++)
        printf("%d %c : %d\n",i+1, str[i], lenth[i]);
        */

}

int getacstr()
{
    int cont = 0;
    for(int i = len-1; i>=0; i--)
        acstr[cont++] = str[i];
    int mid = cont;
    acstr[cont++] = '$';
    for(int i = 0; i<len; i++)
        acstr[cont++] = str[i];
    acstr[cont] = '\0';
    aclen = cont;

    //printf("acstr: %s\n",acstr);
    return mid;
}

void getac()
{
    ac[0] = -1;
    for(int i = 1; i<aclen; i++)
    {
        int t = ac[i-1];
        while(t != -1 && acstr[t+1] != acstr[i])
            t = ac[t];
        if(acstr[t+1] == acstr[i])
            ac[i] = t+1;
        else
            ac[i] = -1;
    }

/*
    printf("array ac:\n");
    for(int i = 0; i<aclen; i++)
        printf("%d %c : %d\n",i+1,acstr[i],ac[i]);
        */
}

void getaba()
{
    int mid = getacstr();

    getac();

    for(int i = mid+1; i<aclen; i++)
        aba[len-1-(2*mid-i)] = ac[i]+1;
/*
    printf("array aba:\n");
    for(int i = 0; i<len; i++)
        printf("%d %c : %d\n",i+1,str[i],aba[i]);
*/
}

int main()
{
    scanf("%s",str);
    len = strlen(str);

    getlenth();

    getaba();

    maxaba[0] = aba[0];
    for(int i = 1; i<len; i++)
        maxaba[i] = max(maxaba[i-1],aba[i]);
    int maxlen = -1;
    int number;
    int al,ar,bl,br,cl,cr;
    for(int i = 0; i<len; i++)
    {
        int l = i-lenth[i]/2;
        int r = i+lenth[i]/2;
        //if(i == 1)
            //printf("asas\n");
        if(l == 0 || r == len-1 || maxaba[l-1] == 0)
        {
            if(lenth[i]>maxlen){
            maxlen = lenth[i];
            number = 1;
            al = l;
            ar = r;
            }
            continue;
        }
        int t = min(maxaba[l-1], len-1-r);
        int total = lenth[i]+2*t;
        //if(i == 1)
            //printf("---%d\n",total);
        if(total > maxlen)
        {
            maxlen = total;
            for(int j = l-1; j>=0; j--)
                if(aba[j]>=t)
            {
                al = j-t+1;
                ar = j;
                break;
            }
            bl = l;
            br = r;
            cl = len-t;
            cr = len-1;
            number = 3;
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

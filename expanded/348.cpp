}
}
# 6 "data/348.cpp" 2


# 7 "data/348.cpp"
using namespace std;

char trans[200020];
char str[100001];
char inverse[200200];
int maxlen[100000];
int aclen[100100];
int kmp[200200];
int aclentemp[100100];

int lenth,translen,inverselen;

void transforming()
{
    translen = 0;
    lenth = strlen(str);
    for(int i = 0; i<lenth; i++)
    {
        trans[translen++] = '#';
        trans[translen++] = str[i];
    }
    trans[translen++] = '#';
    trans[translen] = '\0';
}

void getmaxlen()
{
    memset(maxlen, 1, sizeof(maxlen));
    transforming();
    int lena[200200];
    int maxr = -1,maxd;
    for(int i = 0; i<translen; i++)
    {
        int len = 1;
        if(i<maxr)
        len = min(lena[2*maxd-i],2*(maxr-i)+1);

        for(int j = len/2+1; i+j<translen && i-j>=0 && trans[i+j] == trans[i-j]; len+=2,j = len/2+1);

        lena[i] = len;
        if(lena[i]/2 + i > maxr)
        {
            maxr = lena[i]/2 + i;
            maxd = i;
        }
    }

    for(int i = 1; i<translen; i+=2)
    {

        maxlen[i/2] = (lena[i]-3)/2+1;
    }

}

void KMP()
{
    int len = inverselen;
    kmp[0] = -1;
    for(int i = 1; i<len; i++)
    {
        int t = kmp[i-1];
        while(t != -1 && inverse[i] != inverse[t+1])
        t = kmp[t];
        if(inverse[i] == inverse[t+1])
            kmp[i] = t+1;
        else
            kmp[i] = -1;
    }
}

void getaclen()
{
    int cont = 0;
    for(int i = lenth-1; i>=0; i--)
        inverse[cont++] = str[i];
    int mid = cont;
    inverse[cont++] = '$';
    for(int i = 0; i<lenth; i++)
        inverse[cont++] = str[i];
    inverse[cont] = '\0';
    inverselen = cont;

    KMP();





    for(int i = mid+1; i<inverselen; i++)
    {
        aclen[lenth-1-(2*mid - i)] = kmp[i]+1;
    }




    for(int i = 0; i<lenth; i++)
        aclentemp[i] = aclen[i];
    for(int i = 1; i<lenth; i++)
    {
        aclen[i] = max(aclen[i-1], aclen[i]);
    }
}
int main()
{
    scanf("%s",str);
    getmaxlen();




    getaclen();

    int al,ar,bl,br,cl,cr,number;
    int maxlena = 0;
    for(int i = 0; i<lenth; i++)
    {

        int d = (maxlen[i]-1)/2;
        int l = i-d;
        int r = i+d;
        if(r == lenth-1)
        {
            if(maxlen[i]>maxlena)
            {
                maxlena = maxlen[i];
                number = 1;
                al = l;
                ar = r;
            }
            continue;
        }
        if(l == 0)
        {
            if(maxlen[i]>maxlena)
            {
                maxlena = maxlen[i];
                number = 1;
                al = l;
                ar = r;
            }
            continue;
        }
        int total = maxlen[i] + 2*min(aclen[l-1], lenth-r-1);

         int t = min(aclen[l-1], lenth-1-r);

        if(total > maxlena)
        {
            maxlena = total;
            if(t>0){
            number = 3;
            for(int j = l-1; j>=0; j--)
            {
                if(aclentemp[j]>=t)
                {
                    al = j-t+1;
                    ar = j;

                    break;
                }
            }
            bl = l;
            br = r;
            cl = lenth-t;
            cr = lenth-1;
            }
            else
            {
                number = 1;
                al = l;
                ar = r;
            }
        }
    }
    if(number == 1)
    {
        printf("%d\n",1);
        printf("%d %d\n",al+1,ar-al+1);
    }
    if(number == 3)
    {
        printf("%d\n",3);
        printf("%d %d\n%d %d\n%d %d\n",al+1,ar-al+1,bl+1,br-bl+1,cl+1,cr-cl+1);
    }
    return 0;
}

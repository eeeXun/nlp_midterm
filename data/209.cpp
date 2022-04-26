#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<queue>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cctype>
#include<string>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
using namespace std;
int next[120000];
int extend[120000];
void get_next(char s[])
{
    int i = 0, ptr = 0;
    int len, l, j;
    while (s[i] == s[i+1]) ++i;
    next[1] = i;
    ptr = 1;
    for (i = 2; s[i] != 0; i++)
    {
        len = ptr+next[ptr]-1;
        l = next[i-ptr];
        if (l < len-i+1) next[i] = l;
        else
        {
            j = len-i+1;
            if (j < 0) j = 0;
            while (s[i+j] == s[j]) ++j;
            next[i] = j;
            ptr = i;
        }
    }
}
void extend_kmp(char s[], char t[],int *extend,int n)
{
    get_next(s);
    int i = 0, len, l, ptr, j;
    while (t[i] == s[i] && s[i] != 0 && t[i] != 0) i++;
    extend[0] = i;
    ptr = 0;
    for (i = 1; i < n; i++)
    {
        len = ptr+extend[ptr]-1;
        l = next[i-ptr];
        if (l < len-i+1) extend[i] = l;
        else
        {
            j = len-i+1;
            if (j < 0) j = 0;
            while (t[i+j] == s[j] && i+j < n && s[j] != 0) ++j;
            extend[i] = j;
            ptr = i;
        }
    }
}
char s[200000],t[200000];
int len[400000];
void palindrome(char*cs)
{
    int n =strlen(cs);
    for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0))
    {
        while (i - j >= 0 && i + j + 1 < n * 2
                && cs[(i - j) / 2] == cs[(i + j + 1) / 2]) j++;
        len[i] = j;
        for (k = 1; i - k >= 0 && j - k >= 0 && len[i - k] != j - k; k++)
        {
            len[i + k] = min(len[i - k], j - k);
        }
    }
}
const int maxn=250010;
int val[maxn],val1[maxn];
int Max[20][maxn],Max1[20][maxn];
int idx[maxn];
int n;
void init()
{
        idx[0]=-1;
        int i,j,k;
        for (i=1;i<=n;i++)
        {
                idx[i]=(i&(i-1))?idx[i-1]:idx[i-1]+1;
                Max[0][i]=val[i];
                Max1[0][i]=val1[i];
        }
        for (i=1;i<=idx[n];i++)
        {
                int lim=n+1-(1<<i);
                for (j=1;j<=lim;j++)
                {
                        Max[i][j]=max(Max[i-1][j],Max[i-1][j+(1<<i>>1)]);
                        Max1[i][j]=max(Max1[i-1][j],Max1[i-1][j+(1<<i>>1)]);
                }
        }
}
int getval(int x,int y)
{
        x++;
        y++;
        int t=idx[y-x+1];
        y-=(1<<t)-1;
        return max(Max[t][x],Max[t][y]);
}
int gaoval(int x,int y)
{
        x++;
        y++;
        int t=idx[y-x+1];
        y-=(1<<t)-1;
        return max(Max1[t][x],Max1[t][y]);
}
int main()
{
        int i,j,k;
        scanf("%s",s);
        int l=strlen(s);
        for (i=l-1;i>=0;i--)
        {
                t[i]=s[l-i-1];
        }
        extend_kmp(t,s,extend,l);
        n=l;
        for (i=1;i<=n;i++)
        {
                val[i]=extend[i-1];
        }
        int aa=0;
        vector<int>ot(10);
        palindrome(s);
        for (i=0;i<2*l-1;i+=2)
        {
                val1[i/2+1]=len[i];
                aa=max(aa,len[i]);
        }
        ot[0]=1;
        ot[1]=aa;
        init();
        if (l==1)
        {
                puts("1\n1 1");
                return 0;
        }
        for (i=1;i<=l;i++)
        {
                //[l-i+1...l]
                int low=0,high=l-2*i,ans=-1,mid;
                if (low>high)continue;
                if (getval(low,high)<i)continue;
                while (low<=high)
                {
                        mid=(low+high)>>1;
                        int tmp=getval(0,mid);
                        if (tmp>=i)
                        {
                                high=mid-1;
                                ans=mid;
                        }
                        else 
                        {
                                low=mid+1;
                        }
                }
                if (ans==-1)continue;
                int lp=ans;
        
                int left=ans+i;
                int right=l-i-1;
                ans=-1;
                int lt=(right-left+1);
                if (lt%2==1)high=lt/2;
                else high=(lt-1)/2;
                low=0;
                //printf("%d\n",gaoval(1,3));
                while (low<=high)
                {
                        mid=(low+high)>>1;
                        int ll=2*mid+1;
                        int tmp=gaoval(left+mid,right-mid);
                        if (tmp>=ll)
                        {
                                low=mid+1;
                                ans=ll;
                        }
                        else 
                        {
                                high=mid-1;
                        }
                }
        
                if (ans==-1)continue;
                
                if (2*i+ans>aa)
                {
                        aa=2*i+ans;
                        ot[0]=3;
                        ot[1]=aa;
                        ot[2]=i;
                        ot[3]=lp;
                }                       
        }
        if (ot[0]==1)
        {
                puts("1");
                for (i=0;i<2*l-1;i+=2)
                {
                        if (len[i]==aa)
                        {
                                printf("%d %d\n",i/2+1-aa/2,aa);
                                break;
                        }
                }
                return 0;
        }
        puts("3");
        printf("%d %d\n",ot[3]+1,ot[2]);
        for (i=0;i<2*l-1;i+=2)
        {
                if (i/2>=ot[3]+ot[2]&&i/2<l-ot[2])
                {
                        if (len[i]==aa-2*ot[2])
                        {
                                if (i/2-(aa-2*ot[2])/2>=ot[3]+ot[2]&&i/2+(aa-2*ot[2])/2<l-ot[2])
                                {
                                        printf("%d %d\n",i/2+1-(aa-2*ot[2])/2,aa-2*ot[2]);
                                        break;
                                }
                        }
                }
        }
        printf("%d %d\n",l-ot[2]+1,ot[2]);
        return 0;
}
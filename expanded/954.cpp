      using multiset = std::multiset<_Key, _Cmp, polymorphic_allocator<_Key>>;
  }

}
# 12 "data/954.cpp" 2
# 1 "/usr/include/c++/11.2.0/cstdlib" 1 3
# 39 "/usr/include/c++/11.2.0/cstdlib" 3
       
# 40 "/usr/include/c++/11.2.0/cstdlib" 3
# 13 "data/954.cpp" 2


# 14 "data/954.cpp"
using namespace std;
int Fail[1000000+5],f[1000000+5],num[1000000+5];
char Patlern[1000000+5],Text[1000000+5];
int a[1000000+5];
char c[1000000+5];
int go(int st,char c)
{
    if (Patlern[st]==c)
        return st+1;
    else if (st>0)
        return go(Fail[st],c);
    else
        return 0;
}
string s1,s2;
int main()
{
    int i;
    cin >> s1;
    int n=s1.length();
    for (int i=0;i<n;i++)
        Text[i]=s1[i];
    int st=0,u=0;
    for (i=0;i<n;i++)
    {
        Patlern[i]=s1[n-i-1];
        if (i>=1)
            Fail[i+1]=go(Fail[i],Patlern[i]);
        while (st!=i+1&&u<n)
            st=go(st,Text[u]),u++;
        if (st==i+1&&u-1<n-i-1)
        {

            num[(u-1)+1]=i+1;
        }


    }
    for (i=2;i<=n;i++)
        num[i]=max(num[i],num[i-1]);
    int t=0,r=0,last,ans=0;
    c[++t]='~';
    for (i=0;i<s1.length();i++)
        c[++t]=s1[i];
    for (i=1;i<=t;i++)
    {
        if (i<=r)
            a[i]=min(a[last*2-i],r-i+1);
        while (c[i+a[i]]==c[i-a[i]])
            a[i]++;
        if (i+a[i]>r)
            r=i+a[i]-1,last=i;
        if (i!=1)
            ans=max(ans,a[i]*2-1+2*min(t-(i+a[i])+1,num[i-a[i]-1]));
    }
    for (i=2;i<=t;i++)
        if (a[i]*2-1==ans)
        {
            printf("1\n");
            printf("%d %d\n",i-a[i],a[i]*2-1);
            return 0;
        }
    printf("3\n");
    int len1,len2,id;
    for (i=2;i<=t;i++)
    {
        if (a[i]*2-1+2*min(t-(i+a[i])+1,num[i-a[i]-1])==ans)
        {
            id=i-a[i];
            len2=a[i]*2-1;
            len1=min(t-(i+a[i])+1,num[i-a[i]-1]);
            break;
        }
    }
    for (i=1;i<=n;i++)
        if (num[i]==len1)
        {
            printf("%d %d\n",i-len1+1,len1);
            break;
        }
    printf("%d %d\n",id,len2);
    printf("%d %d\n",n-len1+1,len1);
}

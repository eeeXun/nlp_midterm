  using ::timespec;
  using ::timespec_get;
}
# 8 "data/805.cpp" 2

# 8 "data/805.cpp"
using namespace std;
int fail[200000],f1[200000],f2[200000],g[200000];
char s[200000],ss[200000];
int a[4][2];
int main()
{


    scanf("%s",s);
    int len=strlen(s);
    int x=0;
    for (int i=0;i<len;i++)
    ss[i]=s[len-i-1];
    fail[0]=-1;
    for (int i=1;i<len;i++)
    {
        for (x=fail[i-1];x!=-1&&ss[x+1]!=ss[i];x=fail[x]);
        if (ss[x+1]==ss[i]) fail[i]=x+1;
        else fail[i]=-1;
    }
    int j=-1;
    for (int i=0;i<len;i++)
    {
        if (ss[j+1]==s[i]) j++;
        else
        if (j!=-1)
        {
            for (j=fail[j];j!=-1&&ss[j+1]!=s[i];j=fail[j]);
            if (ss[j+1]==s[i])j++;
        }
        f1[i]=j+1;
    }
    f2[0]=1;x=0;j=0;
    for (int i=1;i<len;i++)
    {
        if (i>=x)f2[i]=1;
        else f2[i]=min(x-i,f2[2*j-i]);
        for (;i>=f2[i]&&s[i+f2[i]]==s[i-f2[i]];f2[i]++);
        if (x<i+f2[i]-1)
        {x=i+f2[i]-1;j=i;}
    }
    for (int i=1;i<len;i++)
    {
        if (f1[i]>f1[i-1]) g[i]=i;
        else
        {
            f1[i]=f1[i-1];
            g[i]=g[i-1];
        }
    }
    int ans=0;
    for (int i=0;i<len;i++)
    if (ans<2*f2[i]-1+2*min(f1[i-1],len-(i+f2[i])))
    {
        ans=2*f2[i]-1+2*min(f1[i-f2[i]],len-(i+f2[i]));
        x=i;
    }
    j=0;
    if (min(f1[x-f2[x]],len-(x+f2[x]))>0)
    {
        a[++j][0]=g[x-f2[x]]-f1[x-f2[x]]+1;
        a[j][1]=g[x-f2[x]];
    }
    a[++j][0]=x-f2[x]+1;
    a[j][1]=x+f2[x]-1;
    if (min(f1[x-f2[x]],len-(x+f2[x]))>0)
    {
        a[++j][0]=len-f1[x-f2[x]];
        a[j][1]=len-1;
    }
    printf("%d\n",j);
    for (int i=1;i<=j;i++)
    printf("%d %d\n",a[i][0]+1,a[i][1]-a[i][0]+1);
}

  using ::strstr;
# 122 "/usr/include/c++/11.2.0/cstring" 3

}
}
# 3 "data/425.cpp" 2
# 1 "/usr/include/c++/11.2.0/cstdio" 1 3
# 39 "/usr/include/c++/11.2.0/cstdio" 3
       
# 40 "/usr/include/c++/11.2.0/cstdio" 3
# 4 "data/425.cpp" 2

# 4 "data/425.cpp"
using namespace std;
int next1[100100],next[100100],l,p[100100],f[100100][2],a[3][2];
char str[100100],str1[100100];
# 21 "data/425.cpp"
void getnext(char b[])
{
   next1[0]=0;
   int m=strlen(b);
   int k=0;
   for(int q=1;q<m;q++)
   {
       while(k>0&&b[k]!=b[q])
         k=next1[k-1];
       if(b[k]==b[q])
         k++;
       next1[q]=k;
   }
}
int kmp(char a[],char b[])
{
   int n=strlen(a),m=strlen(b),q=0;
   for(int i=0;i<n;i++)
   {
       while(q>0&&a[i]!=b[q])
         q=next1[q-1];
       if(a[i]==b[q])
         q++;
       next[i]=q;
       if(q==m)
       {
           q=next1[q-1];
       }
   }
   return 0;
}int manacher()
{
        int mx=0,id;
        for(int i=0;i<l;i++)
        {
            if(mx>i)
                    p[i]=min(p[2*id-i],mx-i);
            else
                    p[i]=1;
            for(;i>=p[i]&&str[i+p[i]]==str[i-p[i]];p[i]++)
              ;
            if(p[i]+i>mx)
            {
                mx=p[i]+i;
                id=i;
            }
        }
        return 0;
}
int main()
{
    while(scanf("%s",str)!=
# 72 "data/425.cpp" 3 4
                          (-1)
# 72 "data/425.cpp"
                             )
    {
        l=strlen(str);
        for(int i=0;i<l;i++)
          str1[i]=str[l-i-1];
        getnext(str1);
        kmp(str,str1);
        manacher();
        int ans=0,k;
        f[0][0]=next[0];f[0][1]=0;
        for(int i=1;i<l;i++)
        {
            if(f[i-1][0]>next[i])
            {
                f[i][0]=f[i-1][0]; f[i][1]=f[i-1][1];
            }
            else
            {
                f[i][0]=next[i]; f[i][1]=i;
            }
        }
        for(int i=0;i<l;i++)
        {
            int now=2*p[i]-1,t=0;
            if(i-p[i]>=0&&i+p[i]<l)
            {
                t=f[i-p[i]][0];
                if(t>l-(i+p[i]))
                  t=l-(i+p[i]);
                now+=2*t;
            }
            if(now>ans)
            {
                ans=now;
                if(t>0)
                {
                    k=3;
                    a[0][0]=f[i-p[i]][1]-f[i-p[i]][0]+2; a[0][1]=t;
                    a[1][0]=i-p[i]+2; a[1][1]=now-2*t;
                    a[2][0]=l-t+1; a[2][1]=t;
                }
                else
                {
                    k=1;
                    a[0][0]=i-p[i]+2; a[0][1]=now;
                }
            }
        }
        printf("%d\n",k);
        for(int i=0;i<k;i++)
          printf("%d %d\n",a[i][0],a[i][1]);
    }
    return 0;
}

    void
    swap(list_update& other)
    { base_type::swap(other); }
  };




}
# 13 "data/962.cpp" 2



# 15 "data/962.cpp"
char s[300005],t[300005];
int pi[300005];
vector<pair<int,int> > V;
void prefix_function()
{
    int n=strlen(s);
    int i,now=-1;
    pi[0]=now;
    for(i=1;i<n;i++)
    {
        while(now!=-1&&s[i]!=s[now+1]) now=pi[now];
        if(s[i]==s[now+1]) pi[i]=++now;
        else pi[i]=now=-1;
    }
}

void KMP()
{
    int m=strlen(s),n=strlen(t);
    int i,now=-1;
    for(i=0;i<n;i++)
    {
        while(now!=-1&&t[i]!=s[now+1]) now=pi[now];
        if(t[i]==s[now+1]) now++;
        else now=-1;
        V.push_back(make_pair(now+1,i+1));
        if(now==m-1)
        {
            now=pi[now];
        }
    }
}

template <class T>
class STable
{
    int n;
    pair<int,int> *cal;
    vector<T> *SparseTable;
    T (*comp)(T,T);
    void initialize()
    {
        int i,j;
        cal[1].second=1;
        for(i=1,j=1<<i; j<=n; i++,j=1<<i)
        {
            cal[j].first=1;
            cal[j].second=j;
        }
        for(i=2; i<=n; i++)
        {
            cal[i].first=cal[i].first+cal[i-1].first;
            if(cal[i].second==0) cal[i].second=cal[i-1].second;
        }
    }
public:
    STable(vector<T> &arr,T (*f)(T,T))
    {
        n=arr.size();
        comp=f;
        cal=new pair<int,int>[n+1];
        initialize();
        SparseTable=new vector<T>[n];
        int i,j,m;
        for(i=0,j=0; i<n; i++)
        {
            SparseTable[i].push_back(arr[i]);
        }
        for(j=0,m=1<<j; m<n; j++,m=1<<j)
        {
            for(i=0; i+m<n; i++)
            {
                SparseTable[i].push_back(comp(SparseTable[i][j],SparseTable[i+m][SparseTable[i+m].size()-1]));
            }
        }
    }
    T query(int l,int r)
    {
        int difference=(r-l+1);
        return comp(SparseTable[l][cal[difference].first],SparseTable[r-cal[difference].second+1][cal[difference].first]);
    }
    ~STable()
    {
        int i;
        for(i=0;i<n;i++)
        {
            SparseTable[i].clear();
        }
        delete []SparseTable;
        delete []cal;
        comp=0;
    }
};

pair<int,int> maximum(pair<int,int> a,pair<int,int> b)
{
    return max(a,b);
}

int length(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
    return a.second-a.first+b.second-b.first+c.second-c.first+3;
}

int main()
{
    gets(t);
    int n=strlen(t);
    int i;
    for(i=0;i<n;i++) s[i]=t[n-1-i];
    prefix_function();
    KMP();
    STable<pair<int,int> > max_match(V,maximum);
    vector<pair<int,int> > ans;
    ans.push_back(make_pair(0,-1));
    ans.push_back(make_pair(1,1));
    ans.push_back(make_pair(n+2,n+1));
    int len=1;
    for(i=0;i<n-1-i;i++) swap(s[i],s[n-1-i]);
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }
    for(i=0;i<n;i++)
    {
        pair<int,int> prefix=make_pair(0,-1), suffix=make_pair(n+2,n+1),middle=make_pair(i-d1[i]+2,i+d1[i]);
        if(middle.first>1&&middle.second<n)
        {
            pair<int,int> q=max_match.query(0,middle.first-2);
            pair<int,int> p;
            p.first=q.second-q.first+1;
            p.second=p.first+min(n-middle.second,q.first)-1;
            prefix=p;
            suffix.first=n-(p.second-p.first);
            suffix.second=n;
        }
        if(length(prefix,middle,suffix)>length(ans[0],ans[1],ans[2]))
        {
            ans[0]=prefix;
            ans[1]=middle;
            ans[2]=suffix;
        }
    }
    if(ans[0].first>ans[0].second)
    {
        printf("1\n%d %d",ans[1].first,(ans[1].second-ans[1].first+1));
    }
    else
    {
        printf("3");
        for(i=0;i<ans.size();i++)
        {
            printf("\n%d %d",ans[i].first,(ans[i].second-ans[i].first+1));
        }
    }
    return 0;
}

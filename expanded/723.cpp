    struct __variant_hash_call_base_impl<false, _Types...> {};

  template<typename... _Types>
    using __variant_hash_call_base =
    __variant_hash_call_base_impl<(__poison_hash<remove_const_t<_Types>>::
       __enable_hash_call &&...), _Types...>;

  template<typename... _Types>
    struct hash<variant<_Types...>>
    : private __detail::__variant::_Variant_hash_base<
 variant<_Types...>, std::index_sequence_for<_Types...>>,
      public __variant_hash_call_base<_Types...>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = variant<_Types...>;
    };

  template<>
    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 7 "data/723.cpp" 2
# 35 "data/723.cpp"

# 35 "data/723.cpp"
int dr[]= {2, 2, -2, -2, 1, -1, 1, -1};
int dc[]= {1,-1, 1, -1, 2, 2,-2, -2};
int dr1[]= {0, 0, 1, 1, 1, -1, -1, -1};
int dc1[]= {-1, 1,-1, 0, 1, -1, 0, 1};
int dr2[]= {-1, 0, 0, 1};
int dc2[]= {-1,-1, -2, -1 };

using namespace std;





long long int siz,last,b[300005],occ[300005];

struct automata
{
    long long int len,link,next[30];
} st[300005];


void inser(char c,long long int x)
{
    long long int now=++siz;
    st[now].len=st[last].len+1;
    long long int p,q,cl;
    b[now]=x;
    occ[now]=1;

    for(p=last; p!=-1&&!st[p].next[c]; p=st[p].link)
        st[p].next[c]=now;
    if(p==-1)
        st[now].link=0;
    else
    {
        q=st[p].next[c];
        if(st[p].len+1==st[q].len)
            st[now].link=q;

        else
        {
            cl=++siz,st[cl].len=st[p].len+1;

            st[cl].link=st[q].link;

            memcpy(st[cl].next,st[q].next,sizeof(st[cl].next));

            for(; p!=-1&&st[p].next[c]==q; p=st[p].link)
                st[p].next[c]=cl;

            st[now].link=st[q].link=cl;
        }

    }

    last=now;
}

vector<long long int>adj[300005];

void process(long long int x)
{
    long long int i,j;
    for(i=1;i<=siz;i++)
    {
        long long int p=st[i].len;
        adj[p].push_back(i);
    }

    for(i=x;i>=1;i--)
    {
        for(j=0;j<adj[i].size();j++)
        {
             occ[st[adj[i][j]].link]+=occ[adj[i][j]];
            long long int p=st[adj[i][j]].link;
            b[p]=min(b[p],b[adj[i][j]]);

        }
    }
}




vector<int> manacar(string s)
{
    long long int n=s.size(),i,j;
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
    return d1;

}

long long int suf[300005];


int main()
{
    long long int i,j;
    siz=0;
    memset(st,0,sizeof(st));
    st[0].link=-1;
    string t;
    cin>>t;

    for(i=0;i<300005;i++)
    {
        b[i]=100000000000000000;
        suf[i]=100000000000000000;
    }


    for(i=0;i<t.size();i++)inser(t[i]-'a',i);
    process(t.size());

    vector<int>v=manacar(t);
    vector<pair<long long int,long long int> >ans1;

    long long int len=t.size();

    long long int max1=0,ind;

    for(i=0;i<v.size();i++)
    {
            if(v[i]*2-1>max1)
            {
                ind=i-v[i]+1;
                max1=v[i]*2-1;
            }
    }

    long long int now=0;
    ans1.push_back(make_pair(ind,max1));


    for(i=len-1;i>=0;i--)
    {
        long long int p=st[now].next[t[i]-'a'];
        if(p==0)break;
        now=p;
        if(b[now]>=i)
        {
            continue;
        }
        suf[i]=b[now];

    }


    for(i=0;i<v.size();i++)
    {
        long long int x=i-v[i]+1;
        long long int y=i+v[i];
        long long int lo=y,hi=len-1,mid,ans=-1;
        while(lo<=hi)
        {
            long long int mid=(lo+hi)>>1;
            if(suf[mid]<x)
            {
                ans=mid;
                hi=mid-1;
            }
            else lo=mid+1;
        }
        if(ans==-1)continue;
        long long int k=(len-ans)*2+(v[i]*2-1);
        if(k>max1)
        {
            max1=k;
            ans1.clear();
            long long int r=len-ans;
            ans1.push_back(make_pair(suf[ans]-r+1,r));
            ans1.push_back(make_pair(x,v[i]*2-1));
            ans1.push_back(make_pair(ans,r));

        }
    }

    cout<<ans1.size()<<endl;
    for(i=0;i<ans1.size();i++)cout<<ans1[i].first+1<<" "<<ans1[i].second<<endl;
# 237 "data/723.cpp"
    return 0;
}
